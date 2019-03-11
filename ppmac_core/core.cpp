//
// Created by urbschaj on 11.01.19.
//

#include "core.h"
#include "stopwatch.h"
#include "udpsink.h"
#include "uuid.h"
#include "threading.h"
#include "events.h"
#include <spdlog/sinks/stdout_color_sinks.h>

namespace ppmac {

	Core::Core()
		: remoteHost(),
		remotePort(0),
		remoteShell(this),
		stateUpdater(*this, remoteShell),
		coreShouldRun(false),
		runDeadTimer(true),
		isConnected(false),
		shutdownStarted(false)
	{
		ErrorHandlingSetup();
		LoggingSetup();
		SetupDeadTimer();
	}

	Core::~Core() {
		remoteShell.Disconnect();
		signalHandler.Clear();
		stateUpdater.Stop();
		coreShouldRun = false;
		if(coreThread.joinable()) {
			coreThread.join();
		}
		runDeadTimer = false;
		if(deadTimerThread.joinable()) {
			deadTimerThread.join();
		}
	}

	void Core::LoggingSetup() {
		auto defaultLogger = spdlog::stdout_color_mt("defaultLogger");
		defaultLogger->flush_on(spdlog::level::debug);
		// [%n] would be the logger name, we dont care about that atm
		defaultLogger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%l] [%t] [%@] %v");
		spdlog::set_default_logger(defaultLogger);
	}

	void Core::ErrorHandlingSetup() {
		std::set_terminate(exception::TerminateHandler);
	}

	void Core::SetupDeadTimer() {
		deadTimerThread = MakeThread("DeadTimer", [this](){
			DeadTimerRunner();
		});
	}

	void Core::EsOnConnectionEstablished(const ConnectionEstablishedEvent& e) {}
	void Core::EsOnConnectionLost(const ConnectionLostEvent& e) {}
	void Core::EsOnMotorStateChanged(const MotorStateChangedEvent& e) {}
	void Core::EsOnMotorCtrlChanged(const MotorCtrlChangedEvent& e) {}
	void Core::EsOnCoordStateChanged(const CoordStateChangedEvent& e) {}
	void Core::EsOnCoordAxisChanged(const CoordAxisChangedEvent& e) {}
	void Core::EsOnCompensationTablesChanged(const CompensationTableChangedEvent& e) {}
	void Core::EsOnStateupdaterInitialized(const StateUpdaterInitializedEvent& e) {}

	void Core::SetupEventHandling() {
		eventSystem.Connect(this, &Core::EsOnConnectionEstablished);
		eventSystem.Connect(this, &Core::EsOnConnectionLost);
		eventSystem.Connect(this, &Core::EsOnMotorStateChanged);
		eventSystem.Connect(this, &Core::EsOnMotorCtrlChanged);
		eventSystem.Connect(this, &Core::EsOnCoordStateChanged);
		eventSystem.Connect(this, &Core::EsOnCoordAxisChanged);
		eventSystem.Connect(this, &Core::EsOnCompensationTablesChanged);
		eventSystem.Connect(this, &Core::EsOnStateupdaterInitialized);
	}

	void Core::Initialize(InitObject init) {
		std::lock_guard<std::mutex> lock(coreMutex);
		if(remoteShell.IsConnected()) {
			SPDLOG_INFO("the core can only be initialized once, please restart the device server if required");
			return;
		}
		SPDLOG_INFO("initializing core");
		// this sink sends the log lines as udp messages to a graylog host
		if(!init.logginHost.empty() && init.loggingPort != 0) {
			try{
				auto sink = std::make_shared<udp_sink_mt>(init.logginHost, init.loggingPort);
				sink->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [" + uuid::GetProgramLifetimeUUID() + "] [%l] [%t] [%@] %v");
				spdlog::default_logger()->sinks().push_back(sink);
				udpSink = sink.get();
				SPDLOG_DEBUG("enable udp logging to : {}", sink->GetHost());
			}
			catch(const std::exception& e) {
				SPDLOG_WARN("unable to create udp logger, error: {}", e.what());
			}
		}
		config::dumpAllCommunication = init.dumpCommunication;
		remoteHost = init.host;
		remotePort = init.port;
		coreShouldRun = true;
		coreThread = MakeThread("Core", [this](){
			CoreRunner();
		});
	}

	void Core::ForceReconnect() {
		remoteShell.Disconnect();
	}

	es::TSEventSystem& Core::GetEventSystem() {
		return eventSystem;
	}

	RemoteShellErrorCode Core::InitializePmacConnection(const std::string &host, int port) {
		auto connect = remoteShell.Connect(host, port);
		if(connect != RemoteShellErrorCode::Ok) {
			return connect;
		}
		SPDLOG_DEBUG("ssh channel setup complete");
		// read motd and stuff
		remoteShell.ChannelConsume();
		SPDLOG_DEBUG("retrieving plc list'");
		auto plc = remoteShell.ChannelWriteConsume("cat /var/ftp/usrflash/Database/pp_prog.sym", std::chrono::seconds(1));
		if(!plc) {
			return plc.error();
		}
		stateUpdater.SetPLC(*plc);
		SPDLOG_DEBUG("starting 'gpascii -2 -f'");
		// start gpascii and read its startup message
		auto gpa = remoteShell.ChannelWriteConsume("gpascii -2 -f", std::chrono::seconds(1));
		if(!gpa) {
			return gpa.error();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds{250});
		SPDLOG_DEBUG("setting echo mode to 7");
		// set echomode to 7 this will return only the result without the command
		// e.g. "Motor[1].Pos" returns now "12.54" not "Motor[1].Pos=12.54"
		auto echo = remoteShell.ChannelWriteRead("echo7");
		if(!echo) {
			return echo.error();
		}
		return RemoteShellErrorCode::Ok;
	}

	void Core::CoreRunner()
	{
		while(coreShouldRun)
		{
			if(remoteShell.IsConnected()) {
				std::this_thread::sleep_for(std::chrono::seconds{10});
				continue;
			}
			SPDLOG_INFO("trying to connect to {}:{}", remoteHost, remotePort);
			auto res = InitializePmacConnection(remoteHost, remotePort);
			if(res != RemoteShellErrorCode::Ok) {
				SPDLOG_ERROR("unable to create remote shell, error: {}", wise_enum::to_string(res));
				std::this_thread::sleep_for(std::chrono::seconds{1});
				continue;
			}
			stateUpdater.SetupInitialState();
			while(coreShouldRun) {
				if(remoteShell.IsConnected()) {
					stateUpdater.ManualUpdate();
				}
				eventSystem.ProcessQueue();
			}
		}
	}

	void Core::DeadTimerRunner() {
		while (runDeadTimer) {
			try {
				{ // keep scope for lock guard
					std::lock_guard<std::mutex> lock(deadTimerMutex);
					deadTimer.Update();
					deadTimer.RemoveAlreadyExecuted();
				}
				std::this_thread::sleep_for(std::chrono::milliseconds{10});
			} catch (const std::exception&) {
				SPDLOG_WARN("exception in dead timer:\n{}", StringifyException(std::current_exception(), 4, '>'));
			}
		}
	}

	void Core::EventSystemRunner() {
		while(true) {
			eventSystem.ProcessQueue();
		}
	}

	bool Core::IsConnected() {
		//std::lock_guard<std::mutex> lock(coreMutex);
		return isConnected;
	}

	SignalHandler& Core::Signals() {
		return signalHandler;
	}

	std::string Core::ExecuteCommand(const std::string& str) {
		std::lock_guard<std::mutex> lock(coreMutex);
		auto result = remoteShell.ChannelWriteRead(str);
		if(!result){
			THROW_RUNTIME_ERROR("command '{}' stopped with error {}", str, wise_enum::to_string(result.error()));
		}
		if(parser::detail::CheckForError(*result)) {
			THROW_RUNTIME_ERROR("command '{}' returned '{}'", str, *result);
		}
		return *result;
	}

	std::string Core::ExecuteCommandConsume(const std::string& str, std::chrono::milliseconds timeout) {
		std::lock_guard<std::mutex> lock(coreMutex);
		auto result = remoteShell.ChannelWriteConsume(str, timeout);
		if(!result){
			THROW_RUNTIME_ERROR("command '{}' stopped with error {}", str, wise_enum::to_string(result.error()));
		}
		if(parser::detail::CheckForError(*result)) {
			THROW_RUNTIME_ERROR("command '{}' returned '{}'", str, *result);
		}
		return *result;
	}

	MotorInfo Core::GetMotorInfo(MotorID motor) {
		std::lock_guard<std::mutex> lock(coreMutex);
		return stateUpdater.GetMotorInfoAndStartTimer(motor);
	}

	IOInfo Core::GetIoInfo(IoID port) {
		std::lock_guard<std::mutex> lock(coreMutex);
		return stateUpdater.GetIoInfoAndStartTimer(port);
	}

	GlobalInfo Core::GetGlobalInfo() {
		std::lock_guard<std::mutex> lock(coreMutex);
		return stateUpdater.GetGlobalInfoAndStartTimer();
	}

	CoordInfo Core::GetCoordInfo(CoordID coord) {
		std::lock_guard<std::mutex> lock(coreMutex);
		return stateUpdater.GetCoordInfoAndStartTimer(coord);
	}

	std::vector<CoordAxisDefinitionInfo> Core::GetMotorAxisDefinitions(CoordID id) {
		std::lock_guard<std::mutex> lock(coreMutex);
		return stateUpdater.GetMotorAxisDefinitions(id);
	}

	PmacExecutableInfo Core::GetPlcInfo(int32_t id) const {
		auto info = stateUpdater.GetPlcInfo(id);
		if(info) {
			return *info;
		}
		return PmacExecutableInfo{};
	}

	int32_t Core::GetPlcCount() const {
		return stateUpdater.GetPlcCount();
	}


	HandleType Core::AddDeadTimer(std::chrono::microseconds timeout, std::function<void()> callback) {
		std::lock_guard<std::mutex> lock(deadTimerMutex);
		return deadTimer.AddTimer(UpdateTime{timeout, callback});
	}

	void Core::RemoveDeadTimer(ppmac::HandleType handle) {
		std::lock_guard<std::mutex> lock(deadTimerMutex);
		deadTimer.RemoveTimer(handle);
	}


	void Core::OnConnectionEstablished() {
		isConnected = true;
		SPDLOG_INFO("network initialisation for {}:{} complete", remoteHost, remotePort);
		signalHandler.RunConnectionEstablished();
	}

	void Core::OnConnectionLost() {
		isConnected = false;
		SPDLOG_ERROR("connection to {}:{} lost", remoteHost, remotePort);
		AddDeadTimer(std::chrono::seconds{0}, [this](){
			stateUpdater.Stop();
			signalHandler.RunConnectionLost();
		});
	}

	void Core::OnMotorStateChanged(MotorID motorID, uint64_t newState, uint64_t changes) {
		// this is actually quite stupid that we need to make revalue refs out if this
		// but i have no time to fix it and it doesnt do anything here, same for the other handlers
		signalHandler.RunStatusChanged(motorID, newState, changes);
	}

	void Core::OnMotorCtrlChanged(MotorID motorID, uint64_t newState, uint64_t changes) {
		signalHandler.RunCtrlChanged(motorID, newState, changes);
	}

	void Core::OnCoordStateChanged(CoordID coordID, uint64_t newState, uint64_t changes) {
		signalHandler.RunStatusChanged(coordID, newState, changes);
	}

	void Core::OnCoordAxisChanged(CoordID coordID, uint32_t availableAxis) {
		signalHandler.RunCoordChanged(coordID, availableAxis);
	}

	void Core::OnCompensationTablesChanged(CompensationTableID compensationTable, bool active) {
		signalHandler.RunCompTableChanged(compensationTable, active);
	}

	void Core::OnStateupdaterInitialized() {
		AddDeadTimer(std::chrono::seconds{0}, [this](){
			OnConnectionEstablished();
		});
	}
}
