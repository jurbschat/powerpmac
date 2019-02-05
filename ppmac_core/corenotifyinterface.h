//
// Created by urbschaj on 31.01.19.
//

#ifndef POWERPMAC_COREINTERFACEINTERNAL_H
#define POWERPMAC_COREINTERFACEINTERNAL_H

namespace ppmac {

	struct CoreNotifyInterface {
		virtual void OnConnectionEstablished() = 0;
		virtual void OnConnectionLost() = 0;
		virtual void OnMotorStateChanged(int32_t index, uint64_t oldState, uint64_t newState) = 0;
	};

}

#endif //POWERPMAC_COREINTERFACEINTERNAL_H
