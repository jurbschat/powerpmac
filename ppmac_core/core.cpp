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
		auto res = ConnectToPMAC(host, port);
		if(res == RemoteShellErrorCode::Ok) {
			return true;
		}
		return false;
	}

	RemoteShellErrorCode Core::ConnectToPMAC(const std::string& host, int port) {

		auto establishConnection = [&]() -> RemoteShellErrorCode {
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
			return RemoteShellErrorCode::Ok;
		};

		/*auto valueOrError = [](auto val){
			if(val) {
				SPDLOG_DEBUG(*val);
			} else {
				SPDLOG_DEBUG(wise_enum::to_string(val.error()));
			}
		};*/


		/*auto connect = rs.Connect(host, port);
		SPDLOG_DEBUG(wise_enum::to_string(connect));

		rs.ChannelWrite("gpascii -2");
		auto welcomeMessage = rs.ChannelConsume(std::chrono::seconds(1));
		valueOrError(welcomeMessage);*/
		//auto a = ch.ChannelWriteRead("echo7");
		//valueOrError(a);
		/*auto b = rs.ChannelWriteRead("Motor[1].Pos");
		valueOrError(b);
		auto c = rs.ChannelWriteRead("Motor[1].AmpFault");
		valueOrError(c);
		auto d = rs.ChannelWriteRead("Motor[1].Pos;Motor[1].PhaseCtrl;vers");
		valueOrError(d);
		auto e = rs.ChannelWriteRead("Gate3[0].Chan[0].ServoCapt");
		valueOrError(e);
		StopWatch sw{true};
		for(int i = 0; i < 1000; i++) {
			auto f = rs.ChannelWriteRead("Sys.CpuTemp");
			valueOrError(f);
			if(i == 10) {
				rs.Disconnect();
			}
			if(i == 15) {
				//rs.Connect(host, port);
				establishConnection();
			}
			std::this_thread::sleep_for(std::chrono::seconds{1});
		}
		SPDLOG_DEBUG(sw.elapsed().count());*/

		auto result = establishConnection();
		pmacStateHolder.Start();
		std::this_thread::sleep_for(std::chrono::seconds(3));
		exit(0);

		return result;
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
