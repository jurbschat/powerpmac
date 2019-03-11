//
// Created by urbschaj on 31.01.19.
//

#ifndef POWERPMAC_COREINTERFACEINTERNAL_H
#define POWERPMAC_COREINTERFACEINTERNAL_H

#include "pmac/defines.h"

namespace ppmac {

	struct CoreNotifyInterface {
		virtual void OnMotorStateChanged(MotorID motorIndex, uint64_t newState, uint64_t changes) = 0;
		virtual void OnMotorCtrlChanged(MotorID motorIndex, uint64_t newState, uint64_t changes) = 0;
		virtual void OnCoordStateChanged(CoordID coordIndex, uint64_t newState, uint64_t changes) = 0;
		virtual void OnCoordAxisChanged(CoordID coordIndex, uint32_t availableAxis) = 0;
		virtual void OnCompensationTablesChanged(CompensationTableID compensationTable, bool active) = 0;
	};

}

#endif //POWERPMAC_COREINTERFACEINTERNAL_H
