//
// Created by urbschaj on 31.01.19.
//

#ifndef POWERPMAC_COREINTERFACEINTERNAL_H
#define POWERPMAC_COREINTERFACEINTERNAL_H

namespace ppmac {

	struct CoreNotifyInterface {
		virtual void OnConnectionEstablished() = 0;
		virtual void OnConnectionLost() = 0;
		virtual void OnMotorStateChanged(int32_t motorIndex, uint64_t newState, uint64_t changes) = 0;
		virtual void OnMotorCtrlChanged(int32_t motorIndex, uint64_t newState, uint64_t changes) = 0;
		virtual void OnCoordStateChanged(int32_t coordIndex, uint64_t newState, uint64_t changes) = 0;
		virtual void OnCoordAxisChanged(int32_t coordIndex, uint32_t availableAxis) = 0;
		virtual void OnStateupdaterInitialized() = 0;
	};

}

#endif //POWERPMAC_COREINTERFACEINTERNAL_H
