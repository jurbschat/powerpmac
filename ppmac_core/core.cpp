//
// Created by urbschaj on 11.01.19.
//

#include "core.h"
#include "stopwatch.h"
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
		auto console = spdlog::stdout_color_mt("console");
		console->flush_on(spdlog::level::debug);
	}

	void Core::ErrorHandlingSetup() {
		std::set_terminate(exception::TerminateHandler);
	}

	void Core::SetupDeadTimer() {
		deadTimerThread = std::thread([this](){
			DeadTimerRunner();
		});
	}

	void Core::Initialize(const std::string& host, int port) {
		remoteHost = host;
		remotePort = port;
		/*keepConnectionAlive = true;
		remoteShellKeepAlive = std::thread([this](){
			KeepAliveRunner();
		});*/
		auto res = SetupRemoteShell(remoteHost, remotePort);
		if(res == RemoteShellErrorCode::Ok) {
			SPDLOG_DEBUG("remote shell setup complete!");
			stateUpdater.Start();
			OnConnectionEstablished();
		} else {
			SPDLOG_DEBUG("unable to create remote shell (exiting), error: ", wise_enum::to_string(res));
			exit(-1);
		}
		//std::this_thread::sleep_for(std::chrono::seconds(3000));
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
			if(!keepConnectionAlive) {
				return;
			}
			auto res = SetupRemoteShell(remoteHost, remotePort);

			while(remoteShell.IsConnected()) {
				auto cmd = ppmac::cmd::GlobalInfo();
				remoteShell.ChannelWrite(cmd, std::chrono::milliseconds{1000});
				auto res = remoteShell.ChannelRead(std::chrono::milliseconds{1000});
				std::this_thread::sleep_for(std::chrono::milliseconds{1000});
			}

			if(res == RemoteShellErrorCode::Ok) {
				SPDLOG_DEBUG("remote shell setup complete!");
				stateUpdater.Start();
			} else {
				SPDLOG_DEBUG("unable to create remote shell, error: ", wise_enum::to_string(res));
			}
		}
	}

	sigs::Signal<void()>& Core::GetSignalConnectionEstablished() {
		return sigConEst;
	}

	sigs::Signal<void()>& Core::GetSignalConnectionLost() {
		return sigConLost;
	}

	sigs::Signal<void(uint64_t newState, uint64_t changes)>& Core::GetSignalMotorStatusChanged(MotorID id) {
		return sigMotorStatus[from_enum(id)];
	}

	void Core::OnConnectionEstablished() {
		sigConEst();
	}

	void Core::OnConnectionLost() {
		stateUpdater.Stop();
		sigConLost();
	}

	void Core::OnMotorStateChanged(int32_t motorIndex, uint64_t newState, uint64_t changes) {
		sigMotorStatus[motorIndex](std::move(newState), std::move(changes));
	}

	bool Core::IsConnected() {
		return remoteShell.IsConnected();
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

	void Core::RunUpdater() {
		stateUpdater.CheckForMotorStateChanges();
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
			try
			{
				{ // keep empty scope for lock guard
					std::lock_guard<std::mutex> lock(deadTimerMutex);
					deadTimer.Update();
					deadTimer.RemoveExpired();
				}
				std::this_thread::sleep_for(std::chrono::milliseconds{1});
			} catch (std::exception& e) {
				SPDLOG_DEBUG("exception in dead timer: '{}'", e.what());
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
