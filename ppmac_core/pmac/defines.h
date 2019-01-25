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

	namespace PortID {
		enum TYPE : int32_t {
			Port0,
			Port1,
			Port2,
			Port3,
			Port4,
			Port5,
			Port6,
			Port7,
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

	namespace PortState {
		enum class TYPE : int32_t {
			Online,
			Offline,
			Fault
		};
	}

	namespace convert {
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
		PortID::TYPE to_enum(int_with_tag<PortID::TYPE> index);
		int32_t from_enum(MotorID::TYPE motor);
		int32_t from_enum(PortID::TYPE motor);
	}
}

#endif //POWERPMAC_DEFINES_H
