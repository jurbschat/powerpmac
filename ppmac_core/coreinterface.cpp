//
// Created by urbschaj on 10.01.19.
//

#include "coreinterface.h"
#include "core.h"

#include <iostream>
#include <memory>

namespace ppmac
{
	std::unique_ptr<Core> core;

	CoreInterface& GetCoreObject() {
		if(!core) {
			core = std::make_unique<Core>();
		}
		return *core;
	}

	void FreeCore() {
		core.release();
	}
}
