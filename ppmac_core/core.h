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
	void Bla();
	bool IsConnected();

	// pmac logic
	std::string ExecuteCommand(const std::string& str);

	MotorInfo GetMotorInfo(MotorID::TYPE motor);
	virtual IOInfo GetIoInfo(IoID::TYPE io);
	virtual GlobalInfo GetGlobalInfo();
	virtual CoordInfo GetCoordInfo(CoordID::TYPE coord);

	sigs::Signal<void()>* GetSignal(SignalType type);
private:
	void LoggingSetup();
	void ErrorHandlingSetup();
	void MainLoop();
	RemoteShellErrorCode SetupRemoteShell(const std::string &host, int port);
	void KeepAliveRunner();
	void OnConnectionEstablished(); // from remoteShell
	void OnConnectionLost(); // from remoteShell
	void OnMotorError(); // from stateHolder

	std::string remoteHost;
	int remotePort;
	bool keepConnectionAlive;
	RemoteShell remoteShell;
	StateUpdater stateUpdater;
	std::unordered_map<SignalType, sigs::Signal<void()>> signals;
	std::thread remoteShellKeepAlive;
};

}


#endif //POWERPMAC_PPMACCORE_H
