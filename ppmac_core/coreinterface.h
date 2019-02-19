//
// Created by urbschaj on 10.01.19.
//

#include <string>
#include <functional>
#include <cstdint>
#include <chrono>
#include "config.h"
#include "signalhandler.h"
#include "pmac/defines.h"
#include "pmac/datastructures.h"

#ifndef POWERPMAC_PPMACCOREINTERFACE_H
#define POWERPMAC_PPMACCOREINTERFACE_H

namespace ppmac {

	struct InitObject {
		std::string host;
		int port;
		std::string logginHost;
		int loggingPort;
	};

	class CoreInterface
	{
	public:
		/*using ConnectionLostCallbackType = std::function<void(const std::string& reason)>;
		using ConnectionEstablishedType = std::function<void()>;*/

		CoreInterface() {}
		CoreInterface(const CoreInterface&) = delete;
		CoreInterface(const CoreInterface&&) = delete;
		CoreInterface& operator=(const CoreInterface&) = delete;
		CoreInterface& operator=(const CoreInterface&&) = delete;

		virtual ~CoreInterface() {}
		virtual void Initialize(InitObject init) = 0;
		virtual bool IsConnected() = 0;

		virtual std::string ExecuteCommand(const std::string& str) = 0;
		//virtual void RunUpdater() = 0;

		virtual MotorInfo GetMotorInfo(MotorID motor) = 0;
		virtual IOInfo GetIoInfo(IoID io) = 0;
		virtual GlobalInfo GetGlobalInfo() = 0;
		virtual CoordInfo GetCoordInfo(CoordID coord) = 0;

		virtual SignalHandler& Signals() = 0;

		virtual HandleType AddDeadTimer(std::chrono::microseconds timeout, std::function<void()> callback) = 0;
		virtual void RemoveDeadTimer(HandleType handle) = 0;
	};

	CoreInterface& GetCoreObject();
}


#endif //POWERPMAC_PPMACCOREINTERFACE_H
