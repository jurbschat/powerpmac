//
// Created by urbschaj on 29.01.19.
//

#include "coreinterface.h"

int main() {
	ppmac::CoreInterface& ci = ppmac::GetCoreObject();
	ci.Initialize("192.168.56.96", 22);
	return 0;
}