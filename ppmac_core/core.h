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
//#include "libs/blockingconcurrentqueue.h"
#include "pmac/defines.h"
#include "eventsystem/globaleventsystem.h"
#include "events.h"

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
	PmacExecutableInfo GetPlcInfo(int32_t id) const;
	int32_t GetPlcCount() const;

	SignalHandler& Signals();
	HandleType AddDeadTimer(std::chrono::microseconds timeout, std::function<void()> callback);
	void RemoveDeadTimer(HandleType handle);
	void ForceReconnect();
	es::TSEventSystem& GetEventSystem();
private:
	void EsOnConnectionEstablished(const ConnectionEstablishedEvent& e);
	void EsOnConnectionLost(const ConnectionLostEvent& e);
	void EsOnMotorStateChanged(const MotorStateChangedEvent& e);
	void EsOnMotorCtrlChanged(const MotorCtrlChangedEvent& e);
	void EsOnCoordStateChanged(const CoordStateChangedEvent& e);
	void EsOnCoordAxisChanged(const CoordAxisChangedEvent& e);
	void EsOnCompensationTablesChanged(const CompensationTableChangedEvent& e);
	void EsOnStateupdaterInitialized(const StateUpdaterInitializedEvent& e);

	void LoggingSetup();
	void ErrorHandlingSetup();
	void SetupDeadTimer();
	void SetupEventHandling();
	void MainLoop();
	RemoteShellErrorCode InitializePmacConnection(const std::string &host, int port);
	void CoreRunner();
	void DeadTimerRunner();
	void EventSystemRunner();

	void OnConnectionEstablished();
	void OnConnectionLost();
	void OnMotorStateChanged(MotorID motorID, uint64_t newState, uint64_t changes);
	void OnMotorCtrlChanged(MotorID motorID, uint64_t newState, uint64_t changes);
	void OnCoordStateChanged(CoordID coordID, uint64_t newState, uint64_t changes);
	void OnCoordAxisChanged(CoordID coordID, uint32_t availableAxis);
	void OnCompensationTablesChanged(CompensationTableID compensationTable, bool active);
	void OnStateupdaterInitialized();

	UdpSink* udpSink;
	std::string remoteHost;
	int remotePort;
	RemoteShell remoteShell;
	StateUpdater stateUpdater;
	SignalHandler signalHandler;
	bool coreShouldRun;
	std::thread coreThread;
	bool runDeadTimer;
	std::thread deadTimerThread;
	std::mutex deadTimerMutex;
	std::mutex coreMutex;
	IntervalTimer deadTimer;
	bool isConnected;
	bool shutdownStarted;
	es::TSEventSystem eventSystem;
	//std::thread esRunner;
};

}


#endif //POWERPMAC_PPMACCORE_H
