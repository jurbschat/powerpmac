//
// Created by urbschaj on 29.01.19.
//

#include "coreinterface.h"
#include "core.h"
#include "pmac/defines.h"
#include "threading.h"

int main() {

	ppmac::SetThisThreadName("main");

	ppmac::Core* ci = static_cast<ppmac::Core*>(&ppmac::GetCoreObject());
	ci->Initialize(ppmac::InitObject{
		"192.168.56.96",
		//.host = "192.168.83.130",
		22,
		"131.169.131.127", // cfeld-pcx34931
		5555,
		false
	});

	const ppmac::MotorID myMotor = ppmac::MotorID(2);
	auto s1 = ci->Signals().StatusChanged(myMotor, [&](uint64_t newState, uint64_t changed){
		//uint64_t status = ci->GetMotorInfoAndStartTimer(myMotor).status.registerValue;
		(void)changed;
		if(!ppmac::bits::AllBitsSet(newState, ppmac::motorNeededStatusBits)) {
			SPDLOG_DEBUG("missing states: " + ppmac::states::GetMotorStateNamesForFlagMatch(newState, ppmac::motorNeededStatusBits, 0x0));
			SPDLOG_DEBUG("motor not initialized correctly");
		}
		if(ppmac::bits::AnyBitSet(newState, ppmac::motorHardErrorStatusBits)) {
			SPDLOG_DEBUG("fatal states: " + ppmac::states::GetMotorStateNamesForFlagMatch(newState, ppmac::motorHardErrorStatusBits));
			SPDLOG_DEBUG("disabling motor, manual intervention needed");
		}
		if(ppmac::bits::AnyBitSet(newState, ppmac::motorSoftErrorStatusBits)) {
			SPDLOG_DEBUG("error states: " + ppmac::states::GetMotorStateNamesForFlagMatch(newState, ppmac::motorSoftErrorStatusBits));
			SPDLOG_DEBUG("motor error, should fix itselves");
		}
	});
	auto s2 = ci->Signals().CtrlChanged(myMotor, [&](uint64_t newState, uint64_t changed){
		if(ppmac::bits::isSet(changed, ppmac::AuxMotorStatusBits::ServoCtrl)) {
			SPDLOG_DEBUG("control changed: {}", newState);
		}
	});
	auto s3 = ci->Signals().ConnectionEstablished([&](){
		SPDLOG_DEBUG("connection established");
	});
	auto s4 = ci->Signals().ConnectionLost([&](){
		SPDLOG_DEBUG("connection lost");
	});
	int i = 0;
	while(true) {
		while(!ci->IsConnected()) {
			std::this_thread::sleep_for(std::chrono::milliseconds{500});
		}
		while(ci->IsConnected()) {
			i++;
			//SPDLOG_DEBUG("uptime: {}", ci->GetGlobalInfoAndStartTimer().uptime);
			//fmt::print("pos: {}\n", ci->GetMotorInfoAndStartTimer(ppmac::MotorID::Motor4).position);
			/*auto coordInfo = ci->GetCoordInfo(ppmac::CoordID::Coord1);
			for(int i = 0; i < ppmac::AvailableAxis::maxAxis; i++) {
				if(ppmac::bits::isSet(coordInfo.availableAxis, i)) {
					SPDLOG_DEBUG("coord pos {}: {}", ppmac::AvailableAxis::MapAxisToChar(i), ci->GetCoordInfo(ppmac::CoordID::Coord1).position.array[i]);
				}
			}*/
			auto motorInfo = ci->GetMotorInfo(myMotor);
			SPDLOG_DEBUG("motor pos {}", motorInfo.position);
			std::this_thread::sleep_for(std::chrono::milliseconds{500});
			/*if(i % 3 == 0) {
				ci->ForceReconnect();
			}*/
			if(i == 3) {
				goto out;
			}
		}
	}
out:
	SPDLOG_DEBUG("end");
	ppmac::FreeCore();
	std::this_thread::sleep_for(std::chrono::seconds{1});
	return 0;
}