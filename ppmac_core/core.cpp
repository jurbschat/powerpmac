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
		keepConnectionAlive(false),
		remoteShell(this),
		stateUpdater(remoteShell)
	{
		ErrorHandlingSetup();
		LoggingSetup();
	}

	void Core::LoggingSetup() {
		auto console = spdlog::stdout_color_mt("console");
		console->flush_on(spdlog::level::debug);
	}

	Core::~Core() {
		stateUpdater.Stop();
		keepConnectionAlive = false;
		if(remoteShellKeepAlive.joinable()) {
			remoteShellKeepAlive.join();
		}
	}

	void Core::Bla() {
		stateUpdater.Stop();
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

	RemoteShellErrorCode Core::SetupRemoteShell(const std::string& host, int port)
	{
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

		//fmt::print(detail::Backtrace(0));

		return RemoteShellErrorCode::Ok;
	}

	void Core::ErrorHandlingSetup() {

		std::set_terminate(exception::TerminateHandler);
		throw std::runtime_error("lol");
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

	void Core::OnConnectionEstablished() {
		signals[SignalType::ConnectionEstablished]();
	}

	void Core::OnConnectionLost() {
		stateUpdater.Stop();
		signals[SignalType::ConnectionLost]();
	}

	void Core::OnMotorError() {
		signals[SignalType::MotorStateChanged]();
	}

	bool Core::IsConnected() {
		return remoteShell.IsConnected();
	}

	/*HandleType Core::RegisterConnectionEstablished(CoreInterface::ConnectionEstablishedType cb) {
		return connectionEstablishedCbs.insert(cb);
	}

	bool Core::UnregisterConnectionEstablished(HandleType handle) {
		return connectionEstablishedCbs.erase(handle);
	}

	HandleType Core::RegisterConnectionLost(CoreInterface::ConnectionLostCallbackType cb) {
		return connectionLostCbs.insert(cb);
	}

	bool Core::UnregisterConnectionLost(HandleType handle) {
		return connectionLostCbs.erase(handle) == 1;
	}*/

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

	MotorInfo Core::GetMotorInfo(MotorID::TYPE motor) {
		return stateUpdater.GetMotorInfo(motor);
	}

	IOInfo Core::GetIoInfo(IoID::TYPE port)
	{
		return stateUpdater.GetIoInfo(port);
	}

	GlobalInfo Core::GetGlobalInfo() {
		return stateUpdater.GetGlobalInfo();
	}

	CoordInfo Core::GetCoordInfo(CoordID::TYPE coord) {
		return stateUpdater.GetCoordInfo(coord);
	}

	sigs::Signal<void()>* Core::GetSignal(SignalType type)
	{
		auto it = signals.emplace(type, sigs::Signal<void()>());
		return &it.first->second;
		return nullptr;
	}
}
