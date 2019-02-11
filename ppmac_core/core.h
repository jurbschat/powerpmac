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
	void Initialize(const std::string& host, int port);
	bool IsConnected();

	// pmac logic
	std::string ExecuteCommand(const std::string& str);
	//void RunUpdater();

	MotorInfo GetMotorInfo(MotorID motor);
	virtual IOInfo GetIoInfo(IoID io);
	virtual GlobalInfo GetGlobalInfo();
	virtual CoordInfo GetCoordInfo(CoordID coord);

	sigs::Signal<void()>& GetSignalConnectionEstablished();
	sigs::Signal<void()>& GetSignalConnectionLost();
	sigs::Signal<void(uint64_t newState, uint64_t changes)>& GetSignalMotorStatusChanged(MotorID id);
	HandleType AddDeadTimer(std::chrono::microseconds timeout, std::function<void()> callback);
	void RemoveDeadTimer(HandleType handle);
private:
	void LoggingSetup();
	void ErrorHandlingSetup();
	void SetupDeadTimer();
	void MainLoop();
	RemoteShellErrorCode SetupRemoteShell(const std::string &host, int port);
	void KeepAliveRunner();
	void OnConnectionEstablished(); // from remoteShell
	void OnConnectionLost(); // from remoteShell
	void OnMotorStateChanged(int32_t motorIndex, uint64_t oldState, uint64_t newState);
	void DeadTimerRunner();

	std::string remoteHost;
	int remotePort;
	RemoteShell remoteShell;
	StateUpdater stateUpdater;
	sigs::Signal<void()> sigConEst;
	sigs::Signal<void()> sigConLost;
	std::map<int32_t, sigs::Signal<void(uint64_t newState, uint64_t changes)>> sigMotorStatus;
	bool keepConnectionAlive;
	std::thread remoteShellKeepAlive;
	bool runDeadTimer;
	std::thread deadTimerThread;
	std::mutex deadTimerMutex;
	IntervalTimer deadTimer;
};

}


#endif //POWERPMAC_PPMACCORE_H
