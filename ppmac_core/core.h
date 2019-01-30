//
// Created by urbschaj on 11.01.19.
//

#ifndef POWERPMAC_PPMACCORE_H
#define POWERPMAC_PPMACCORE_H

#include "coreinterface.h"
#include "remoteshell.h"
#include "libs/slot_map.h"
#include "pmac/defines.h"
#include "pmacstateholder.h"

#include <mutex>
#include <atomic>
#include <condition_variable>
#include <functional>
#include <unordered_map>
#include <cstdint>
#include <string>
#include <thread>

namespace ppmac {

class Core : public CoreInterface
{
public:
	Core();
	virtual ~Core();
	bool Initialize(std::string host, int port);
	bool IsConnected();
	HandleType RegisterConnectionEstablished(CoreInterface::ConnectionEstablishedType cb);
	bool UnregisterConnectionEstablished(HandleType handle);
	HandleType RegisterConnectionLost(CoreInterface::ConnectionLostCallbackType cb);
	bool UnregisterConnectionLost(HandleType handle);

	// pmac logic
	std::string ExecuteCommand(const std::string& str);
	void QueryAll();
	void QueryMotors();
	void QueryStates();
	void QueryPorts();

	MotorInfo GetMotorInfo(MotorID::TYPE motor);
	PortInfo GetPortInfo(PortID::TYPE port);
private:
	void LoggingSetup();
	void MainLoop();
	RemoteShellErrorCode SetupRemoteShell(const std::string &host, int port);
	void OnConnectionEstablished();
	void OnConnectionLost();
	RemoteShell rs;
	PmacStateHolder pmacStateHolder;
	stdext::slot_map<CoreInterface::ConnectionEstablishedType> connectionEstablishedCbs;
	stdext::slot_map<CoreInterface::ConnectionLostCallbackType> connectionLostCbs;
};

}


#endif //POWERPMAC_PPMACCORE_H
