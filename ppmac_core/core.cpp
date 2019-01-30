//
// Created by urbschaj on 11.01.19.
//

#include "core.h"
#include "stopwatch.h"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
//#include "commandbuilder.h"

namespace ppmac {

	Core::Core()
		: pmacStateHolder(rs)
	{
		LoggingSetup();
	}

	void Core::LoggingSetup() {
		auto console = spdlog::stdout_color_mt("console");
		console->flush_on(spdlog::level::debug);
	}

	Core::~Core() {}

	bool Core::Initialize(std::string host, int port) {
		//TODO: this needs to start the connection keep alive thread not
		// directly connect
		auto res = SetupRemoteShell(host, port);
		if(res == RemoteShellErrorCode::Ok) {
			return true;
		}
		return false;
	}

	RemoteShellErrorCode Core::SetupRemoteShell(const std::string &host, int port)
	{
		auto connect = rs.Connect(host, port);
		if(connect != RemoteShellErrorCode::Ok) {
			return connect;
		}
		SPDLOG_DEBUG("Connection established, starting 'gpascii -f -2'");
		auto gpa = rs.ChannelWrite("gpascii -2");
		if(gpa != RemoteShellErrorCode::Ok) {
			return gpa;
		}
		SPDLOG_DEBUG("setting echo mode to 7");
		auto cons = rs.ChannelConsume(std::chrono::seconds(1));
		if(!cons) {
			return cons.error();
		}
		auto echo = rs.ChannelWriteRead("echo7");
		// did we get an error? then disconnect
		if(!echo) {
			return echo.error();
		}

		pmacStateHolder.Start();
		std::this_thread::sleep_for(std::chrono::seconds(3000));
		exit(0);
		return RemoteShellErrorCode::Ok;
	}

	void OnConnectionEstablished() {

	}
	void OnConnectionLost() {

	}

	bool Core::IsConnected() {
		return rs.IsConnected();
	}

	HandleType Core::RegisterConnectionEstablished(CoreInterface::ConnectionEstablishedType cb) {
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
	}

	std::string Core::ExecuteCommand(const std::string& str) {
		auto result = rs.ChannelWriteRead(str);
		if(!result){
			SPDLOG_DEBUG("error for command '{}': {}", str, wise_enum::to_string(result.error()));
			THROW_RUNTIME_ERROR("network error: {}", wise_enum::to_string(result.error()));
		}
		return *result;
	}

	void Core::QueryAll() {
		pmacStateHolder.UpdateAllState();
	}

	void Core::QueryMotors() {
		pmacStateHolder.UpdateMotorValues();
	}

	void Core::QueryStates() {
		pmacStateHolder.UpdateMotorStates();
	}

	void Core::QueryPorts() {

	}

	MotorInfo Core::GetMotorInfo(MotorID::TYPE motor) {
		return pmacStateHolder.GetMotorInfo(motor);
	}

	PortInfo Core::GetPortInfo(PortID::TYPE port)
	{
		return pmacStateHolder.GetPortInfo(port);
	}
}
