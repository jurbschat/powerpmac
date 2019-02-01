//
// Created by urbschaj on 31.01.19.
//

#ifndef POWERPMAC_COREINTERFACEINTERNAL_H
#define POWERPMAC_COREINTERFACEINTERNAL_H

namespace ppmac {

	struct CoreInterfaceInternal {
		virtual void OnConnectionEstablished() = 0;
		virtual void OnConnectionLost() = 0;
		virtual void OnMotorError() = 0;
	};

}

#endif //POWERPMAC_COREINTERFACEINTERNAL_H
