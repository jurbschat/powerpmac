//
// Created by urbschaj on 11.01.19.
//

#ifndef POWERPMAC_PPMACCORE_H
#define POWERPMAC_PPMACCORE_H

#include "coreinterface.h"
#include "corenotifyinterface.h"
#include "remoteshell.h"
#include "stateupdater.h"
#include "signalhandler.h"
#include "libs/sigs.h"
#include "pmac/defines.h"

#include <mutex>
#include <atomic>
#include <functional>
#include <map>
#include <cstdint>
#include <string>
#include <thread>

namespace ppmac {

class UdpSink;

class Core : public CoreInterface, public CoreNotifyInterface
{
public:
	using mutex_type = TicketSpinLock;

	Core();
	virtual ~Core();
	void Initialize(InitObject init);
	bool IsConnected();
	void StopCoreThread();

	// pmac logic
	std::string ExecuteCommand(const std::string& str);
	std::string ExecuteCommandConsume(const std::string& str, std::chrono::milliseconds timeout);

	MotorInfo GetMotorInfo(MotorID motor);
	IOInfo GetIoInfo(IoID io);
	GlobalInfo GetGlobalInfo();
	CoordInfo GetCoordInfo(CoordID coord);
	std::vector<CoordAxisDefinitionInfo> GetMotorAxisDefinitions(CoordID id);
	PmacExecutableInfo GetPlcInfo(int32_t id);
	int32_t GetPlcCount();

	SignalHandler& Signals();
	HandleType AddDeadTimer(std::chrono::microseconds timeout, std::function<void()> callback);
	void RemoveDeadTimer(HandleType handle);
private:
	void LoggingSetup();
	void ErrorHandlingSetup();
	RemoteShellErrorCode InitializePmacConnection(const std::string &host, int port);
	void CoreRunner();

	void OnMotorStateChanged(MotorID motorID, uint64_t newState, uint64_t changes);
	void OnMotorCtrlChanged(MotorID motorID, uint64_t newState, uint64_t changes);
	void OnCoordStateChanged(CoordID coordID, uint64_t newState, uint64_t changes);
	void OnCoordAxisChanged(CoordID coordID, uint32_t availableAxis);
	void OnCompensationTablesChanged(CompensationTableID compensationTable, bool active);

	void UpdateDeadTimers();
	void ExecuteEvents();

	std::string remoteHost;
	int remotePort;
	RemoteShell remoteShell;
	StateUpdater stateUpdater;
	SignalHandler signalHandler;
	IntervalTimer deadTimer;
	TicketSpinLock coreTsl;
	std::mutex initMtx;
	std::atomic<bool> coreShouldRun;
	std::atomic<bool> isConnected;
	std::atomic_flag isCoreStartupInProcess;
	std::mutex deadTimerMutex;
	std::thread coreThread;
	std::vector<std::function<void()>> events;
	UdpSink* udpSink;
};

}


#endif //POWERPMAC_PPMACCORE_H
