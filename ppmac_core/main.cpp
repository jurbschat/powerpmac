//
// Created by urbschaj on 29.01.19.
//

#include "coreinterface.h"
#include "core.h"

int main() {

	ppmac::Core* ci = static_cast<ppmac::Core*>(&ppmac::GetCoreObject());
	ci->Initialize(ppmac::InitObject{
		.host = "192.168.56.96",
		.port = 22,
		//.logginHost = "131.169.131.127", // cfeld-pcx34931
		//.loggingPort = 5555
	});
	while(true) {
		while(!ci->IsConnected()) {
			std::this_thread::sleep_for(std::chrono::milliseconds{500});
		}
		while(ci->IsConnected()) {
			SPDLOG_DEBUG("uptime: {}", ci->GetGlobalInfo().uptime);
			//fmt::print("pos: {}\n", ci->GetMotorInfo(ppmac::MotorID::Motor4).position);
			auto coordInfo = ci->GetCoordInfo(ppmac::CoordID::Coord1);
			for(int i = 0; i < ppmac::AvailableAxis::maxAxis; i++) {
				if(ppmac::bits::isSet(coordInfo.availableAxis, i)) {
					SPDLOG_DEBUG("coord pos {}: {}", ppmac::AvailableAxis::MapAxisToChar(i), ci->GetCoordInfo(ppmac::CoordID::Coord1).position.array[i]);
				}
			}
			std::this_thread::sleep_for(std::chrono::milliseconds{500});
		}
	}
	std::this_thread::sleep_for(std::chrono::seconds{6000});
	return 0;
}