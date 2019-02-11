//
// Created by urbschaj on 29.01.19.
//

#include "coreinterface.h"
#include "core.h"

int main() {

	ppmac::Core* ci = (ppmac::Core*)&ppmac::GetCoreObject();
	ci->Initialize("192.168.56.96", 22);
	while(!ci->IsConnected()) {
		std::this_thread::sleep_for(std::chrono::milliseconds{500});
	}
	while(true) {
		fmt::print("up: {}\n", ci->GetGlobalInfo().uptime);
		fmt::print("pos: {}\n", ci->GetMotorInfo(ppmac::MotorID::Motor4).position);
		std::this_thread::sleep_for(std::chrono::milliseconds{500});
	}
	std::this_thread::sleep_for(std::chrono::seconds{6000});
	return 0;
}