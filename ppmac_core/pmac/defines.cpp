//
// Created by urbschaj on 25.01.19.
//

#include "defines.h"
#include "enumadapt.h"
#include "../throw.h"

#include <wise_enum.h>

namespace ppmac::convert {

	MotorID::TYPE to_enum(int_with_tag<MotorID::TYPE> index) {
		int32_t maxEnum = wise_enum::size<MotorID::TYPE>;
		if(index < 0 || index > maxEnum - 1) {
			THROW_RUNTIME_ERROR("invalid motor index");
		}
		return index;
	}

	PortID::TYPE to_enum(int_with_tag<PortID::TYPE> index) {
		int32_t size = wise_enum::size<PortID::TYPE>;
		if(index < 0 || index > size - 1) {
			THROW_RUNTIME_ERROR("invalid motor index");
		}
		return index;
	}

	int32_t from_enum(MotorID::TYPE motor) {
		return static_cast<int32_t>(motor);
	}


	int32_t from_enum(PortID::TYPE motor) {
		return static_cast<int32_t>(motor);
	}

}
