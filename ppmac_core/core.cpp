//
// Created by urbschaj on 11.01.19.
//

#include "core.h"
#include "stopwatch.h"
#include "udpsink.h"
#include "uuid.h"
#include "threading.h"
#include <spdlog/sinks/stdout_color_sinks.h>

namespace ppmac {

	Core::Core()
		: remoteHost(),
		remotePort(0),
		stateUpdater(*this, remoteShell),
		coreShouldRun(false),
		isConnected(false)
	{
		ErrorHandlingSetup();
		LoggingSetup();
	}

	Core::~Core() {
		remoteShell.Disconnect();
		signalHandler.Clear();
		coreShouldRun = false;
		if(coreThread.joinable()) {
			coreThread.join();
		}
	}

	void Core::LoggingSetup() {
		auto defaultLogger = spdlog::stdout_color_mt("defaultLogger");
		defaultLogger->flush_on(spdlog::level::debug);
		// [%n] would be the logger name, we dont care about that atm
		defaultLogger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] [%t] [%@] %v");
		spdlog::set_default_logger(defaultLogger);
	}

	void Core::ErrorHandlingSetup() {
		std::set_terminate(exception::TerminateHandler);
	}

	void Core::Initialize(InitObject init) {
		std::lock_guard<mutex_type> lock(coreTsl);
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
				SPDLOG_DEBUG("enable udp logging to: {}", sink->GetHost());
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
			{
				std::lock_guard<mutex_type> lock(coreTsl);
				SPDLOG_INFO("trying to connect to {}:{}", remoteHost, remotePort);
				auto res = InitializePmacConnection(remoteHost, remotePort);
				if (res != RemoteShellErrorCode::Ok) {
					SPDLOG_ERROR("unable to create remote shell, error: {}", wise_enum::to_string(res));
					std::this_thread::sleep_for(std::chrono::seconds{3});
					continue;
				}
			}
			try {
				{
					std::lock_guard<mutex_type> lock(coreTsl);
					stateUpdater.SetupInitialState();
				}
				isConnected = true;
				signalHandler.RunConnectionEstablished();
				while(remoteShell.IsConnected() && coreShouldRun) {
					{
						std::lock_guard<mutex_type> lock(coreTsl);
						stateUpdater.ManualUpdate();
					}
					UpdateDeadTimers();
					ExecuteEvents();
					std::this_thread::sleep_for(std::chrono::milliseconds{500});
				}
			} catch (const std::exception&) {
				SPDLOG_WARN("exception in core thread, stopping connection:\n{}", StringifyException(std::current_exception(), 4, '>'));
			}
			isConnected = false;
			SPDLOG_ERROR("connection to {}:{} lost", remoteHost, remotePort);
			signalHandler.RunConnectionLost();
		}
	}

	void Core::UpdateDeadTimers() {
		try {
			std::lock_guard<std::mutex> lock(deadTimerMutex);
			deadTimer.Update();
			deadTimer.RemoveAlreadyExecuted();
		} catch (const std::exception&) {
			SPDLOG_WARN("exception in dead timer:\n{}", StringifyException(std::current_exception(), 4, '>'));
		}
	}
	void Core::ExecuteEvents() {
		for(auto& e : events) {
			e();
		}
		events.clear();
	}

	bool Core::IsConnected() {
		return isConnected;
	}

	SignalHandler& Core::Signals() {
		return signalHandler;
	}

	std::string Core::ExecuteCommand(const std::string& str) {
		std::lock_guard<mutex_type> lock(coreTsl);
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
		std::lock_guard<mutex_type> lock(coreTsl);
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
		std::lock_guard<mutex_type> lock(coreTsl);
		return stateUpdater.GetMotorInfoAndStartTimer(motor);
	}

	IOInfo Core::GetIoInfo(IoID port) {
		std::lock_guard<mutex_type> lock(coreTsl);
		return stateUpdater.GetIoInfoAndStartTimer(port);
	}

	GlobalInfo Core::GetGlobalInfo() {
		std::lock_guard<mutex_type> lock(coreTsl);
		return stateUpdater.GetGlobalInfoAndStartTimer();
	}

	CoordInfo Core::GetCoordInfo(CoordID coord) {
		std::lock_guard<mutex_type> lock(coreTsl);
		return stateUpdater.GetCoordInfoAndStartTimer(coord);
	}

	std::vector<CoordAxisDefinitionInfo> Core::GetMotorAxisDefinitions(CoordID id) {
		std::lock_guard<mutex_type> lock(coreTsl);
		return stateUpdater.GetMotorAxisDefinitions(id);
	}

	PmacExecutableInfo Core::GetPlcInfo(int32_t id) {
		std::lock_guard<mutex_type> lock(coreTsl);
		auto info = stateUpdater.GetPlcInfo(id);
		if(info) {
			return *info;
		}
		return PmacExecutableInfo{};
	}

	int32_t Core::GetPlcCount() {
		std::lock_guard<mutex_type> lock(coreTsl);
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

	void Core::ReloadPLC() {

	}

	void Core::OnMotorStateChanged(MotorID motorID, uint64_t newState, uint64_t changes) {
		// this is actually quite stupid that we need to make revalue refs out if this
		// but i have no time to fix it and it doesnt do anything here, same for the other handlers
		//signalHandler.RunStatusChanged(motorID, newState, changes);
		events.emplace_back([this, motorID, newState, changes](){
			signalHandler.RunStatusChanged(motorID, newState, changes);
		});
	}

	void Core::OnMotorCtrlChanged(MotorID motorID, uint64_t newState, uint64_t changes) {
		//signalHandler.RunCtrlChanged(motorID, newState, changes);
		events.emplace_back([this, motorID, newState, changes](){
			signalHandler.RunCtrlChanged(motorID, newState, changes);
		});
	}

	void Core::OnCoordStateChanged(CoordID coordID, uint64_t newState, uint64_t changes) {
		//signalHandler.RunStatusChanged(coordID, newState, changes);
		events.emplace_back([this, coordID, newState, changes](){
			signalHandler.RunStatusChanged(coordID, newState, changes);
		});
	}

	void Core::OnCoordAxisChanged(CoordID coordID, uint32_t availableAxis) {
		//signalHandler.RunCoordChanged(coordID, availableAxis);
		events.emplace_back([this, coordID, availableAxis](){
			signalHandler.RunCoordChanged(coordID, availableAxis);
		});
	}

	void Core::OnCompensationTablesChanged(CompensationTableID compensationTable, bool active) {
		//signalHandler.RunCompTableChanged(compensationTable, active);
		events.emplace_back([this, compensationTable, active](){
			signalHandler.RunCompTableChanged(compensationTable, active);
		});
	}

}
