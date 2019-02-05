//
// Created by urbschaj on 24.01.19.
//

#ifndef POWERPMAC_DEFINES_H
#define POWERPMAC_DEFINES_H

#include <cstdint>

namespace ppmac
{
	enum class MotorID : int32_t {
		Motor0,
		Motor1,
		Motor2,
		Motor3,
		Motor4,
		Motor5,
		Motor6,
		Motor7,
		Motor8,
	};

	enum class IoID : int32_t {
		Port0,
		Port1,
		Port2,
		Port3,
		Port4,
		Port5,
		Port6,
		Port7,
		Port8,
	};

	enum class CoordID : int32_t {
		Coord0,
		Coord1,
		Coord2,
		Coord3,
		Coord4,
		Coord5,
		Coord6,
		Coord7,
		Coord8,
	};

	enum class MotorState : int32_t {
		Online,
		Offline,
		Init,
		Moving,
		Fault
	};

	enum class CoordState : int32_t {
		Online,
		Offline,
		Init,
		Moving,
		Fault
	};

	enum class PortState : int32_t {
		Online,
		Offline,
		Fault
	};


	template<typename T>
	struct int_with_tag {
		int_with_tag(int32_t value)
				: val(value)
		{}
		operator int32_t () {
			return val;
		}
		operator T () {
			return static_cast<T>(val);
		}
		int32_t val;
	};

	template<typename T>
	int_with_tag<T> make_typed_int(T val) {
		return int_with_tag<T>{val};
	}

	MotorID to_enum_motor(int32_t index);
	IoID to_enum_io(int32_t index);
	CoordID to_enum_coord(int32_t index);

	MotorID to_enum(int_with_tag<MotorID> index);
	IoID to_enum(int_with_tag<IoID> index);
	CoordID to_enum(int_with_tag<CoordID> index);

	int32_t from_enum(MotorID motor);
	int32_t from_enum(IoID motor);
	int32_t from_enum(CoordID motor);
}

#endif //POWERPMAC_DEFINES_H
