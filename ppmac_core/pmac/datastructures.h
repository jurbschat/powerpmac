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

	union MotorStatusUnion{
		MotorStatusUnion() {
			memset( this, 0, sizeof( MotorStatusUnion ));
		}
		MotorStatusUnion(uint64_t value)
			: registerValue(detail::FixByteOrder(value))
		{}
		struct {
			uint32_t status1;
			uint32_t status0;
		} status;
		struct {
			// Motor[x].Status[1]
			uint8_t RESERVED_1_0 : 1;
			uint8_t RESERVED_1_1 : 1;
			uint8_t RESERVED_1_2 : 1;
			uint8_t RESERVED_1_3 : 1;
			uint8_t RESERVED_1_4 : 1;
			uint8_t RESERVED_1_5 : 1;
			uint8_t RESERVED_1_6 : 1;
			uint8_t RESERVED_1_7 : 1;
			uint8_t RESERVED_1_8 : 1;
			uint8_t RESERVED_1_9 : 1;
			uint8_t RESERVED_1_10 : 1;
			uint8_t RESERVED_1_11 : 1;
			uint8_t RESERVED_1_12 : 1;
			uint8_t RESERVED_1_13 : 1;
			uint8_t RESERVED_1_14 : 1;
			uint8_t RESERVED_1_15 : 1;
			uint8_t RESERVED_1_16 : 1;
			uint8_t RESERVED_1_17 : 1;
			uint8_t RESERVED_1_18 : 1;
			uint8_t RESERVED_1_19 : 1;
			uint8_t RESERVED_1_20 : 1;
			uint8_t RESERVED_1_21 : 1;
			uint8_t RESERVED_1_22 : 1;
			uint8_t RESERVED_1_23 : 1;
			uint8_t RESERVED_1_24 : 1;
			uint8_t RESERVED_1_25 : 1;
			uint8_t RESERVED_1_26 : 1;
			uint8_t SoftLimitDir : 1;
			uint8_t BlDir : 1;
			uint8_t DacLimit : 1;
			uint8_t SoftLimit : 1;
			uint8_t Csolve : 1;
			// Motor[x].Status[0]
			uint8_t RESERVED_0_0 : 1;
			uint8_t RESERVED_0_1 : 1;
			uint8_t RESERVED_0_2 : 1;
			uint8_t RESERVED_0_3 : 1;
			uint8_t SpindleMotor0 : 1;
			uint8_t SpindleMotor1 : 1;
			uint8_t GantryHomed : 1;
			uint8_t TriggerSpeedSel : 1;
			uint8_t PhaseFound : 1;
			uint8_t BlockRequest : 1;
			uint8_t RESERVED_10 : 1;
			uint8_t InPos : 1;
			uint8_t AmpEna : 1;
			uint8_t ClosedLoop : 1;
			uint8_t DestVelZero : 1;
			uint8_t HomeComplete : 1;
			uint8_t RESERVED_16 : 1;
			uint8_t AuxFault : 1;
			uint8_t EncLoss : 1;
			uint8_t AmpWarn : 1;
			uint8_t TriggerNotFound : 1;
			uint8_t I2tFault : 1;
			uint8_t SoftPlusLimit : 1;
			uint8_t SoftMinusLimit : 1;
			uint8_t AmpFault : 1;
			uint8_t LimitStop : 1;
			uint8_t FeWarn : 1;
			uint8_t FeFatal : 1;
			uint8_t PlusLimit : 1;
			uint8_t MinusLimit : 1;
			uint8_t HomeInProgress : 1;
			uint8_t TriggerMove : 1;
		} named;
		uint64_t registerValue;
	};

	union CoordStatusUnion{
		CoordStatusUnion() {
			memset( this, 0, sizeof( CoordStatusUnion ));
		}
		CoordStatusUnion(uint64_t value)
				: registerValue(detail::FixByteOrder(value))
		{}
		struct {
			uint32_t status1;
			uint32_t status0;
		} status;
		struct {
			// Motor[x].Status[1]
			uint8_t AddedDwellDis : 1; // bit 0
			uint8_t SharpCornerStop : 1;
			uint8_t CC3Active : 1;
			uint8_t EndDelayActive : 1;
			uint8_t CCMoveType0 : 1;
			uint8_t CCMoveType1 : 1;
			uint8_t CCOffReq : 1;
			uint8_t CCAddedArc : 1;
			uint8_t LHStatus : 8;
			uint8_t SegStopReq : 1;
			uint8_t SegEnabled : 1;
			uint8_t SegMoveDccel : 1;
			uint8_t SegMoveAccel : 1;
			uint8_t SegMove0 : 1;
			uint8_t SegMove1 : 1;
			uint8_t MoveMode0 : 1;
			uint8_t MoveMode1 : 1;
			uint8_t CCMode0 : 1;
			uint8_t CCMode1: 1;
			uint8_t ContMotion: 1;
			uint8_t BlockAcive : 1;
			uint8_t FeedHold0 : 1;
			uint8_t FeedHold1 : 1;
			uint8_t LinToPvtBuf : 1;
			uint8_t Csolve : 1; // bit 31
			// Coord[x].Status[0]
			uint8_t ErrorStatus : 8; // bit 0
			uint8_t TimersEnabled : 1;
			uint8_t BlockRequest : 1;
			uint8_t RESERVED_10 : 1;
			uint8_t InPos : 1;
			uint8_t AmpEna : 1;
			uint8_t ClosedLoop : 1;
			uint8_t DestVelZero : 1;
			uint8_t HomeComplete : 1;
			uint8_t TimerEnabled : 1;
			uint8_t AuxFault : 1;
			uint8_t EncLoss : 1;
			uint8_t AmpWarn : 1;
			uint8_t TriggerNotFound : 1;
			uint8_t I2tFault : 1;
			uint8_t SoftPlusLimit : 1;
			uint8_t SoftMinusLimit : 1;
			uint8_t AmpFault : 1;
			uint8_t LimitStop : 1;
			uint8_t FeFatal : 1;
			uint8_t FeWarn : 1;
			uint8_t PlusLimit : 1;
			uint8_t MinusLimit : 1;
			uint8_t HomeInProgress : 1;
			uint8_t TriggerMove : 1; // bit 31
		} named;
		uint64_t registerValue;
	};

	struct MotorInfo {
		float position;
		float velocity;
		float followingError;
		float maxVelocity;
		float acceleration;
		float conversion;
		float slCw;
		float slCcw;
		bool invertDirection;
		bool invertEncoder;
		MotorStatusUnion status;
	};

	struct CoordInfo {
		CoordStatusUnion status;
	};

	struct PortInfo {
		// something
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
