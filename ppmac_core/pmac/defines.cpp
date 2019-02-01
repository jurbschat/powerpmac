//
// Created by urbschaj on 25.01.19.
//

#include "defines.h"
#include "enumadapt.h"
#include "../throw.h"

#include <wise_enum.h>

namespace ppmac {

	MotorID::TYPE to_enum(int_with_tag<MotorID::TYPE> index) {
		int32_t maxEnum = wise_enum::size<MotorID::TYPE>;
		if(index < 0 || index > maxEnum - 1) {
			THROW_RUNTIME_ERROR("invalid motor index");
		}
		return index;
	}

	IoID::TYPE to_enum(int_with_tag<IoID::TYPE> index) {
		int32_t size = wise_enum::size<IoID::TYPE>;
		if(index < 0 || index > size - 1) {
			THROW_RUNTIME_ERROR("invalid motor index");
		}
		return index;
	}

	CoordID::TYPE to_enum(int_with_tag<CoordID::TYPE> index) {
		int32_t size = wise_enum::size<CoordID::TYPE>;
		if(index < 0 || index > size - 1) {
			THROW_RUNTIME_ERROR("invalid motor index");
		}
		return index;
	}

	int32_t from_enum(MotorID::TYPE motor) {
		return static_cast<int32_t>(motor);
	}

	int32_t from_enum(IoID::TYPE motor) {
		return static_cast<int32_t>(motor);
	}

	int32_t from_enum(CoordID::TYPE motor) {
		return static_cast<int32_t>(motor);
	}

}
