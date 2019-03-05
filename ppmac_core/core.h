//
// Created by urbschaj on 11.01.19.
//

#ifndef POWERPMAC_PPMACCORE_H
#define POWERPMAC_PPMACCORE_H

#include "coreinterface.h"
#include "corenotifyinterface.h"
#include "remoteshell.h"
//#include "libs/slot_map.h"
#include "libs/sigs.h"
#include "pmac/defines.h"
#include "stateupdater.h"
#include "signalhandler.h"

#include <mutex>
#include <atomic>
#include <functional>
#include <map>
#include <cstdint>
#include <string>
//#include <thread>

namespace ppmac {

class Core : public CoreInterface, public CoreNotifyInterface
{
public:
	Core();
	virtual ~Core();
	void Initialize(InitObject init);
	bool IsConnected();

	// pmac logic
	std::string ExecuteCommand(const std::string& str);
	std::string ExecuteCommandConsume(const std::string& str, std::chrono::milliseconds timeout);

	MotorInfo GetMotorInfo(MotorID motor);
	IOInfo GetIoInfo(IoID io);
	GlobalInfo GetGlobalInfo();
	CoordInfo GetCoordInfo(CoordID coord);
	std::vector<CoordAxisDefinitionInfo> GetMotorAxisDefinitions(CoordID id);

	SignalHandler& Signals();
	HandleType AddDeadTimer(std::chrono::microseconds timeout, std::function<void()> callback);
	void RemoveDeadTimer(HandleType handle);
private:
	void LoggingSetup();
	void ErrorHandlingSetup();
	void SetupDeadTimer();
	void MainLoop();
	RemoteShellErrorCode SetupRemoteShell(const std::string &host, int port);
	void KeepAliveRunner();
	void OnConnectionEstablished();
	void OnConnectionLost();
	void OnMotorStateChanged(int32_t motorIndex, uint64_t newState, uint64_t changes);
	void OnMotorCtrlChanged(int32_t motorIndex, uint64_t newState, uint64_t changes);
	void OnCoordStateChanged(int32_t coordIndex, uint64_t newState, uint64_t changes);
	void OnCoordAxisChanged(int32_t coordIndex, uint32_t availableAxis);
	void OnCompensationTablesChanged(int32_t compensationTable, bool active);
	void OnStateupdaterInitialized();
	void DeadTimerRunner();

	std::string remoteHost;
	int remotePort;
	RemoteShell remoteShell;
	StateUpdater stateUpdater;
	SignalHandler signalHandler;
	bool keepConnectionAlive;
	std::thread remoteShellKeepAlive;
	bool runDeadTimer;
	std::thread deadTimerThread;
	std::mutex deadTimerMutex;
	IntervalTimer deadTimer;
};

}


#endif //POWERPMAC_PPMACCORE_H
