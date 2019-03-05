//
// Created by urbschaj on 25.01.19.
//

#include "defines.h"
#include "enumadapt.h"
#include "../throw.h"
#include <spdlog/spdlog.h>

#include <wise_enum.h>

namespace ppmac {

	MotorID to_enum(int_with_tag<MotorID> index) {
		int32_t size = wise_enum::size<MotorID>;
		if(index < 0 || index > size - 1) {
			SPDLOG_WARN("invalid MotorID: {}", index.val);
			return MotorID::INVALID;
		}
		return index;
	}

	IoID to_enum(int_with_tag<IoID> index) {
		int32_t size = wise_enum::size<IoID>;
		if(index < 0 || index > size - 1) {
			SPDLOG_WARN("invalid IoID: {}", index.val);
			return IoID::INVALID;
		}
		return index;
	}

	CoordID to_enum(int_with_tag<CoordID> index) {
		int32_t size = wise_enum::size<CoordID>;
		if(index < 0 || index > size - 1) {
			SPDLOG_WARN("invalid CoordID: {}", index.val);
			return CoordID::INVALID;
		}
		return index;
	}

	CompensationTableID to_enum(int_with_tag<CompensationTableID> index) {
		int32_t size = wise_enum::size<CompensationTableID>;
		if(index < 0 || index > size - 1) {
			SPDLOG_WARN("invalid CompensationTableID: {}", index.val);
			return CompensationTableID::INVALID;
		}
		return index;
	}

	MotorID to_enum_motor(int32_t index) {
		return to_enum(int_with_tag<MotorID>(index));
	}

	IoID to_enum_io(int32_t index) {
		return to_enum(int_with_tag<IoID>(index));
	}

	CoordID to_enum_coord(int32_t index) {
		return to_enum(int_with_tag<CoordID>(index));
	}

	CompensationTableID to_enum_comp_table(int32_t index) {
		return to_enum(int_with_tag<CompensationTableID>(index));
	}

	int32_t from_enum(MotorID motor) {
		return static_cast<int32_t>(motor);
	}

	int32_t from_enum(IoID io) {
		return static_cast<int32_t>(io);
	}

	int32_t from_enum(CoordID coord) {
		return static_cast<int32_t>(coord);
	}

	int32_t from_enum(CompensationTableID comp) {
		return static_cast<int32_t>(comp);
	}

}
