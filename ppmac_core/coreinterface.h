//
// Created by urbschaj on 10.01.19.
//

#include <string>
#include <functional>
#include <cstdint>
#include "handletype.h"
#include "pmac/defines.h"
#include "pmac/datastructures.h"
#include "libs/sigs.h"

#ifndef POWERPMAC_PPMACCOREINTERFACE_H
#define POWERPMAC_PPMACCOREINTERFACE_H

namespace ppmac {

	enum class SignalType {
		ConnectionEstablished,
		ConnectionLost,
		MotorStateChanged,
		CoordinateError
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
		virtual void Initialize(const std::string& host, int port) = 0;
		virtual bool IsConnected() = 0;
		/*virtual HandleType RegisterConnectionEstablished(CoreInterface::ConnectionEstablishedType cb) = 0;
		virtual bool UnregisterConnectionEstablished(HandleType handle) = 0;
		virtual HandleType RegisterConnectionLost(ConnectionLostCallbackType cb) = 0;
		virtual bool UnregisterConnectionLost(HandleType handle) = 0;*/

		virtual std::string ExecuteCommand(const std::string& str) = 0;

		virtual MotorInfo GetMotorInfo(MotorID::TYPE motor) = 0;
		virtual IOInfo GetIoInfo(IoID::TYPE io) = 0;
		virtual GlobalInfo GetGlobalInfo() = 0;
		virtual CoordInfo GetCoordInfo(CoordID::TYPE coord) = 0;

		//virtual MotorInfo* GetMotorInfoWritable(MotorID::TYPE motor) = 0;
		//virtual MotorInfo* GetMotorInfoWritable(MotorID::TYPE motor) = 0;

		virtual sigs::Signal<void()>* GetSignal(SignalType type) = 0;
	};

	CoreInterface& GetCoreObject();
}


#endif //POWERPMAC_PPMACCOREINTERFACE_H
