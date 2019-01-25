//
// Created by urbschaj on 10.01.19.
//

#include "coreinterface.h"
#include "core.h"

#include <iostream>

namespace ppmac
{
	CoreInterface& GetCoreObject() {
		static Core core;
		return core;
	}
}
