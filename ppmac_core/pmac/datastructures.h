//
// Created by urbschaj on 23.01.19.
//

#include <cstdint>
#include <vector>
#include <cstring>
#include <endian.h>

#ifndef POWERPMAC_DATASTRUCTURES_H
#define POWERPMAC_DATASTRUCTURES_H

namespace ppmac {

	namespace detail {
		inline uint64_t FixByteOrder(uint64_t value)
		{
			// we get get one int64 with the first gate in the upper half
			// and the second gate in the lower part. we now need to fix
			// byte order for both parts individually and combine them again
			if(__BYTE_ORDER == __LITTLE_ENDIAN) {
				return value;
			}
			else {
				static_assert(__BYTE_ORDER == __LITTLE_ENDIAN, "big endian support must be implemented");
				//
				//  !!! THIS WAS NEVER CHECKED !!!
				//
				int high = static_cast<uint32_t>(value >> 32);
				int low = static_cast<uint32_t>(value & 0xFFFFFFFFLL);
				// this fixes the actual bit access to be in order as expected
				high = htole32(high);
				low = htole32(low);
				// this fixes the state access to match
				uint64_t out = static_cast<uint64_t>(low) << 32 | high ;
				return out;
			}
		}
	}

	using MotorStatus = union StatusUnion{
		StatusUnion() {
			memset( this, 0, sizeof( StatusUnion ));
		}
		StatusUnion(uint64_t value)
			: value(detail::FixByteOrder(value))
		{}
		struct {
			uint32_t status1;
			uint32_t status0;
		} state;
		struct {
			// second
			uint8_t bit1_0 : 1;
			uint8_t bit1_1 : 1;
			uint8_t bit1_2 : 1;
			uint8_t bit1_3 : 1;
			uint8_t bit1_4 : 1;
			uint8_t bit1_5 : 1;
			uint8_t bit1_6 : 1;
			uint8_t bit1_7 : 1;
			uint8_t bit1_8 : 1;
			uint8_t bit1_9 : 1;
			uint8_t bit1_10 : 1;
			uint8_t bit1_11 : 1;
			uint8_t bit1_12 : 1;
			uint8_t bit1_13 : 1;
			uint8_t bit1_14 : 1;
			uint8_t bit1_15 : 1;
			uint8_t bit1_16 : 1;
			uint8_t bit1_17 : 1;
			uint8_t bit1_18 : 1;
			uint8_t bit1_19 : 1;
			uint8_t bit1_20 : 1;
			uint8_t bit1_21 : 1;
			uint8_t bit1_22 : 1;
			uint8_t bit1_23 : 1;
			uint8_t bit1_24 : 1;
			uint8_t bit1_25 : 1;
			uint8_t bit1_26 : 1;
			uint8_t bit1_27 : 1;
			uint8_t bit1_28 : 1;
			uint8_t bit1_29 : 1;
			uint8_t bit1_30 : 1;
			uint8_t bit1_31 : 1;
			// first
			uint8_t bit0_0 : 1;
			uint8_t bit0_1 : 1;
			uint8_t bit0_2 : 1;
			uint8_t bit0_3 : 1;
			uint8_t bit0_4 : 1;
			uint8_t bit0_5 : 1;
			uint8_t bit0_6 : 1;
			uint8_t bit0_7 : 1;
			uint8_t PhaseFound : 1;
			uint8_t bit0_9 : 1;
			uint8_t bit0_10 : 1;
			uint8_t bit0_11 : 1;
			uint8_t bit0_12 : 1;
			uint8_t bit0_13 : 1;
			uint8_t DestVelZero : 1;
			uint8_t bit0_15 : 1;
			uint8_t bit0_16 : 1;
			uint8_t bit0_17 : 1;
			uint8_t bit0_18 : 1;
			uint8_t bit0_19 : 1;
			uint8_t bit0_20 : 1;
			uint8_t bit0_21 : 1;
			uint8_t bit0_22 : 1;
			uint8_t bit0_23 : 1;
			uint8_t AmpFault : 1;
			uint8_t bit0_25 : 1;
			uint8_t bit0_26 : 1;
			uint8_t bit0_27 : 1;
			uint8_t bit0_28 : 1;
			uint8_t bit0_29 : 1;
			uint8_t bit0_30 : 1;
			uint8_t bit0_31 : 1;

		} named;
		uint64_t value;
	};

	struct MotorInfo {
		float position;
		float velocity;
		float followingError;
		float maxVelocity;
		float acceleration;
		float slCw;
		float slCcw;
		bool invertDirection;
		bool invertEncoder;
		MotorStatus status;
	};

	struct PortInfo {
		uint32_t value;
	};

	struct GlobalInfo {
		bool abortAll;
		int32_t maxMotors;
		int32_t maxCoords;
		uint32_t Gate30;
		uint32_t Gate31;
		std::vector<bool> activePlcs; // vector bool sucks
	};
}

#endif //POWERPMAC_DATASTRUCTURES_H
