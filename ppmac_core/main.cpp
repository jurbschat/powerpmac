//
// Created by urbschaj on 29.01.19.
//

#include "coreinterface.h"
#include "core.h"

int main() {

	ppmac::Core* ci = (ppmac::Core*)&ppmac::GetCoreObject();
	ci->Initialize("192.168.56.96", 22);
	//std::this_thread::sleep_for(std::chrono::seconds{5});
	return 0;
}