//
// Created by urbschaj on 23.01.19.
//

#include <cstdint>
#include <vector>

#ifndef POWERPMAC_DATASTRUCTURES_H
#define POWERPMAC_DATASTRUCTURES_H

namespace ppmac {

	struct MotorInfo {
		float position;
		float acceleration;
		float maxVelocity;
		float slCw;
		float slCcw;
		bool invertDirection;
		bool invertEncoder;
	};

	struct PortInfo {
		uint32_t value;
	};

	struct GlobalInfo {
		bool abortAll;
		int32_t maxMotors;
		int32_t maxCoords;
		std::vector<bool> activePlcs; // vector bool sucks
	};
}

#endif //POWERPMAC_DATASTRUCTURES_H
