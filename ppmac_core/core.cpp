//
// Created by urbschaj on 11.01.19.
//

#include "core.h"
#include "stopwatch.h"
#include "udpsink.h"
#include "uuid.h"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <signal.h>

namespace ppmac {

	Core::Core()
		: remoteHost(),
		remotePort(0),
		remoteShell(this),
		stateUpdater(*this, remoteShell),
		keepConnectionAlive(false),
		runDeadTimer(true)
	{
		ErrorHandlingSetup();
		LoggingSetup();
		SetupDeadTimer();
	}

	Core::~Core() {
		stateUpdater.Stop();
		keepConnectionAlive = false;
		if(remoteShellKeepAlive.joinable()) {
			remoteShellKeepAlive.join();
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
		deadTimerThread = std::thread([this](){
			DeadTimerRunner();
		});
	}

	void Core::Initialize(InitObject init) {
		if(remoteShell.IsConnected()) {
			return;
		}
		// this sink sends the log lines as udp messages to a graylog host
		if(!init.logginHost.empty() && init.loggingPort != 0) {
			try{
				auto udpSink = std::make_shared<udp_sink_mt>(init.logginHost, init.loggingPort);
				udpSink->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [" + uuid::GetProgramLifetimeUUID() + "] [%l] [%t] [%@] %v");
				spdlog::default_logger()->sinks().push_back(udpSink);
				SPDLOG_DEBUG("initializing udp logging form: {}", udpSink->GetHost());
			}
			catch(const std::exception& e) {
				SPDLOG_WARN("unable to create udp sink: {}", e.what());
			}
		}
		config::dumpAllCommunication = init.dumpCommunication;
		remoteHost = init.host;
		remotePort = init.port;
		keepConnectionAlive = true;
		remoteShellKeepAlive = std::thread([this](){
			KeepAliveRunner();
		});
		stateUpdater.Start();
	}

	RemoteShellErrorCode Core::SetupRemoteShell(const std::string& host, int port) {
		auto connect = remoteShell.Connect(host, port);
		if(connect != RemoteShellErrorCode::Ok) {
			return connect;
		}
		SPDLOG_DEBUG("Connection established, starting 'gpascii -2 -f'");
		auto gpa = remoteShell.ChannelWrite("gpascii -2");
		if(gpa != RemoteShellErrorCode::Ok) {
			return gpa;
		}
		SPDLOG_DEBUG("setting echo mode to 7");
		auto cons = remoteShell.ChannelConsume(std::chrono::seconds(1));
		if(!cons) {
			return cons.error();
		}
		auto echo = remoteShell.ChannelWriteRead("echo7");
		// did we get an error? then disconnect
		if(!echo) {
			return echo.error();
		}

		return RemoteShellErrorCode::Ok;
	}

	void Core::KeepAliveRunner()
	{
		while(keepConnectionAlive)
		{
			if(remoteShell.IsConnected()) {
				std::this_thread::sleep_for(std::chrono::seconds{1});
				continue;
			}
			SPDLOG_INFO("trying to connect to {}:{}", remoteHost, remotePort);
			auto res = SetupRemoteShell(remoteHost, remotePort);
			if(res == RemoteShellErrorCode::Ok) {
				SPDLOG_DEBUG("remote shell setup complete!");
				//OnConnectionEstablished();
			} else {
				SPDLOG_ERROR("unable to create remote shell, error: {}", wise_enum::to_string(res));
				std::this_thread::sleep_for(std::chrono::seconds{1});
			}
		}
	}

	bool Core::IsConnected() {
		return remoteShell.IsConnected();
	}

	SignalHandler& Core::Signals() {
		return signalHandler;
	}

	void Core::OnConnectionEstablished() {
		SPDLOG_INFO("connection to {}:{} established", remoteHost, remotePort);
		signalHandler.ConnectionEstablished()();
	}

	void Core::OnConnectionLost() {
		//stateUpdater.Stop();
		SPDLOG_ERROR("connection to { }:{} lost", remoteHost, remotePort);
		signalHandler.ConnectionLost()();
	}

	void Core::OnMotorStateChanged(int32_t motorIndex, uint64_t newState, uint64_t changes) {
		// this is actually quite stupid that we need to make revalue refs out if this
		// but i have no time to fix it and it doesnt do anything here, same for the other handlers
		signalHandler.StatusChanged(to_enum_motor(motorIndex))(std::move(newState), std::move(changes));
	}

	void Core::OnMotorCtrlChanged(int32_t motorIndex, uint64_t newState, uint64_t changes) {
		signalHandler.CtrlChanged(to_enum_motor(motorIndex))(std::move(newState), std::move(changes));
	}

	void Core::OnCoordStateChanged(int32_t coordIndex, uint64_t newState, uint64_t changes) {
		signalHandler.StatusChanged(to_enum_coord(coordIndex))(std::move(newState), std::move(changes));
	}

	void Core::OnCoordAxisChanged(int32_t coordIndex, uint32_t availableAxis) {
		signalHandler.CoordChanged(to_enum_coord(coordIndex))(std::move(availableAxis));
	}

	void Core::OnStateupdaterInitialized() {
		AddDeadTimer(std::chrono::seconds{0}, [this](){
			OnConnectionEstablished();
		});
	}

	std::string Core::ExecuteCommand(const std::string& str) {
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
		return stateUpdater.GetMotorInfo(motor);
	}

	IOInfo Core::GetIoInfo(IoID port)
	{
		return stateUpdater.GetIoInfo(port);
	}

	GlobalInfo Core::GetGlobalInfo() {
		return stateUpdater.GetGlobalInfo();
	}

	CoordInfo Core::GetCoordInfo(CoordID coord) {
		return stateUpdater.GetCoordInfo(coord);
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
			} catch (std::exception) {
				SPDLOG_WARN("exception in dead timer:\n{}", StringifyException(std::current_exception(), 4, '>'));
			}
		}
	}

	HandleType Core::AddDeadTimer(std::chrono::microseconds timeout, std::function<void()> callback) {
		std::lock_guard<std::mutex> lock(deadTimerMutex);
		return deadTimer.AddTimer(UpdateTime{timeout, callback});
	}

	void Core::RemoveDeadTimer(ppmac::HandleType handle) {
		std::lock_guard<std::mutex> lock(deadTimerMutex);
		deadTimer.RemoveTimer(handle);
	}
}
