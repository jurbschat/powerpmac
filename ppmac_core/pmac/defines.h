//
// Created by urbschaj on 24.01.19.
//

#ifndef POWERPMAC_DEFINES_H
#define POWERPMAC_DEFINES_H

#include <cstdint>

namespace ppmac
{
	namespace MotorID {
		enum TYPE : int32_t {
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
	}

	namespace IoID {
		enum TYPE : int32_t {
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
	}

	namespace CoordID {
		enum TYPE : int32_t {
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
	}

	namespace MotorState {
		enum class TYPE : int32_t {
			Online,
			Offline,
			Init,
			Moving,
			Fault
		};
	}

	namespace CoordState {
		enum class TYPE : int32_t {
			Online,
			Offline,
			Init,
			Moving,
			Fault
		};
	}

	namespace PortState {
		enum class TYPE : int32_t {
			Online,
			Offline,
			Fault
		};
	}

	template<typename T>
	struct int_with_tag {
		int_with_tag(int32_t value)
				: val(value)
		{}
		/*operator int32_t () {
			return val;
		}*/
		operator T () {
			return static_cast<T>(val);
		}
		int32_t val;
	};
	MotorID::TYPE to_enum(int_with_tag<MotorID::TYPE> index);
	IoID::TYPE to_enum(int_with_tag<IoID::TYPE> index);
	CoordID::TYPE to_enum(int_with_tag<CoordID::TYPE> index);
	int32_t from_enum(MotorID::TYPE motor);
	int32_t from_enum(IoID::TYPE motor);
	int32_t from_enum(CoordID::TYPE motor);
}

#endif //POWERPMAC_DEFINES_H
