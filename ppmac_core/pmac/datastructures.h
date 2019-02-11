//
// Created by urbschaj on 23.01.19.
//

#include <cstdint>
#include <vector>
#include <cstring>
#include <endian.h>
#include <string>

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

	namespace bits {
		template<typename T, void* = std::enable_if<std::is_unsigned<T>::value, void>::value >
		T set(T value, uint32_t bitIndex) {
			value = value | (1ull << bitIndex);
			return value;
		}
		template<typename T>
		T reset(T value, uint32_t bitIndex) {
			value = value & ~(1ull << bitIndex);
			return value;
		}
		template<typename T>
		bool isSet(const T &value, uint32_t bitIndex) {
			return value & (1ull << bitIndex);
		}
		template<typename T>
		T toggle(T value, uint32_t bitIndex) {
			value = value ^ (1ull << bitIndex);
			return value;
		}

		template<typename T>
		bool rising(T state, T change, uint32_t bitIndex) {
			return isSet(state, bitIndex) && isSet(change, bitIndex);
		}

		template<typename T>
		bool falling(T state, T change, uint32_t bitIndex) {
			return !isSet(state, bitIndex) && isSet(change, bitIndex);
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
		} array;
		struct {
			// Motor[x].Status[1]
			unsigned int RESERVED_1_0 : 1;
			unsigned int RESERVED_1_1 : 1;
			unsigned int RESERVED_1_2 : 1;
			unsigned int RESERVED_1_3 : 1;
			unsigned int RESERVED_1_4 : 1;
			unsigned int RESERVED_1_5 : 1;
			unsigned int RESERVED_1_6 : 1;
			unsigned int RESERVED_1_7 : 1;
			unsigned int RESERVED_1_8 : 1;
			unsigned int RESERVED_1_9 : 1;
			unsigned int RESERVED_1_10 : 1;
			unsigned int RESERVED_1_11 : 1;
			unsigned int RESERVED_1_12 : 1;
			unsigned int RESERVED_1_13 : 1;
			unsigned int RESERVED_1_14 : 1;
			unsigned int RESERVED_1_15 : 1;
			unsigned int RESERVED_1_16 : 1;
			unsigned int RESERVED_1_17 : 1;
			unsigned int RESERVED_1_18 : 1;
			unsigned int RESERVED_1_19 : 1;
			unsigned int RESERVED_1_20 : 1;
			unsigned int RESERVED_1_21 : 1;
			unsigned int RESERVED_1_22 : 1;
			unsigned int RESERVED_1_23 : 1;
			unsigned int RESERVED_1_24 : 1;
			unsigned int RESERVED_1_25 : 1;
			unsigned int RESERVED_1_26 : 1;
			unsigned int SoftLimitDir : 1;
			unsigned int BlDir : 1;
			unsigned int DacLimit : 1;
			unsigned int SoftLimit : 1;
			unsigned int Csolve : 1;
			// Motor[x].Status[0]
			unsigned int RESERVED_0_0 : 1;
			unsigned int RESERVED_0_1 : 1;
			unsigned int RESERVED_0_2 : 1;
			unsigned int RESERVED_0_3 : 1;
			unsigned int SpindleMotor0 : 1;
			unsigned int SpindleMotor1 : 1;
			unsigned int GantryHomed : 1;
			unsigned int TriggerSpeedSel : 1;
			unsigned int PhaseFound : 1;
			unsigned int BlockRequest : 1;
			unsigned int RESERVED_10 : 1;
			unsigned int InPos : 1;
			unsigned int AmpEna : 1;
			unsigned int ClosedLoop : 1;
			unsigned int DestVelZero : 1;
			unsigned int HomeComplete : 1;
			unsigned int RESERVED_16 : 1;
			unsigned int AuxFault : 1;
			unsigned int EncLoss : 1;
			unsigned int AmpWarn : 1;
			unsigned int TriggerNotFound : 1;
			unsigned int I2tFault : 1;
			unsigned int SoftPlusLimit : 1;
			unsigned int SoftMinusLimit : 1;
			unsigned int AmpFault : 1;
			unsigned int LimitStop : 1;
			unsigned int FeWarn : 1;
			unsigned int FeFatal : 1;
			unsigned int PlusLimit : 1;
			unsigned int MinusLimit : 1;
			unsigned int HomeInProgress : 1;
			unsigned int TriggerMove : 1;
		} named;
		uint64_t registerValue;
	};

	namespace MotorStatusBits {
		enum TYPE : uint64_t {
			RESERVED_1_0 = 0,
			RESERVED_1_1 = 1,
			RESERVED_1_2 = 2,
			RESERVED_1_3 = 3,
			RESERVED_1_4 = 4,
			RESERVED_1_5 = 5,
			RESERVED_1_6 = 6,
			RESERVED_1_7 = 7,
			RESERVED_1_8 = 8,
			RESERVED_1_9 = 9,
			RESERVED_1_10 = 10,
			RESERVED_1_11 = 11,
			RESERVED_1_12 = 12,
			RESERVED_1_13 = 13,
			RESERVED_1_14 = 14,
			RESERVED_1_15 = 15,
			RESERVED_1_16 = 16,
			RESERVED_1_17 = 17,
			RESERVED_1_18 = 18,
			RESERVED_1_19 = 19,
			RESERVED_1_20 = 20,
			RESERVED_1_21 = 21,
			RESERVED_1_22 = 22,
			RESERVED_1_23 = 23,
			RESERVED_1_24 = 24,
			RESERVED_1_25 = 25,
			RESERVED_1_26 = 26,
			SoftLimitDir = 27,
			BlDir = 28,
			DacLimit = 29,
			SoftLimit = 30,
			Csolve = 31,
			RESERVED_0_0 = 32,
			RESERVED_0_1 = 33,
			RESERVED_0_2 = 34,
			RESERVED_0_3 = 35,
			SpindleMotor0 = 36,
			SpindleMotor1 = 37,
			GantryHomed = 38,
			TriggerSpeedSel = 39,
			PhaseFound = 40,
			BlockRequest = 41,
			RESERVED_10 = 42,
			InPos = 43,
			AmpEna = 44,
			ClosedLoop = 45,
			DestVelZero = 46,
			HomeComplete = 47,
			RESERVED_16 = 48,
			AuxFault = 49,
			EncLoss = 50,
			AmpWarn = 51,
			TriggerNotFound = 52,
			I2tFault = 53,
			SoftPlusLimit = 54,
			SoftMinusLimit = 55,
			AmpFault = 56,
			LimitStop = 57,
			FeWarn = 58,
			FeFatal = 59,
			PlusLimit = 60,
			MinusLimit = 61,
			HomeInProgress = 62,
			TriggerMove = 63
		};
	}

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
			unsigned int AddedDwellDis : 1; // bit 0
			unsigned int SharpCornerStop : 1;
			unsigned int CC3Active : 1;
			unsigned int EndDelayActive : 1;
			unsigned int CCMoveType0 : 1;
			unsigned int CCMoveType1 : 1;
			unsigned int CCOffReq : 1;
			unsigned int CCAddedArc : 1;
			unsigned int LHStatus : 8;
			unsigned int SegStopReq : 1;
			unsigned int SegEnabled : 1;
			unsigned int SegMoveDccel : 1;
			unsigned int SegMoveAccel : 1;
			unsigned int SegMove0 : 1;
			unsigned int SegMove1 : 1;
			unsigned int MoveMode0 : 1;
			unsigned int MoveMode1 : 1;
			unsigned int CCMode0 : 1;
			unsigned int CCMode1: 1;
			unsigned int ContMotion: 1;
			unsigned int BlockAcive : 1;
			unsigned int FeedHold0 : 1;
			unsigned int FeedHold1 : 1;
			unsigned int LinToPvtBuf : 1;
			unsigned int Csolve : 1; // bit 31
			// Coord[x].Status[0]
			unsigned int ErrorStatus : 8; // bit 0
			unsigned int TimersEnabled : 1;
			unsigned int BlockRequest : 1;
			unsigned int RESERVED_10 : 1;
			unsigned int InPos : 1;
			unsigned int AmpEna : 1;
			unsigned int ClosedLoop : 1;
			unsigned int DestVelZero : 1;
			unsigned int HomeComplete : 1;
			unsigned int TimerEnabled : 1;
			unsigned int AuxFault : 1;
			unsigned int EncLoss : 1;
			unsigned int AmpWarn : 1;
			unsigned int TriggerNotFound : 1;
			unsigned int I2tFault : 1;
			unsigned int SoftPlusLimit : 1;
			unsigned int SoftMinusLimit : 1;
			unsigned int AmpFault : 1;
			unsigned int LimitStop : 1;
			unsigned int FeFatal : 1;
			unsigned int FeWarn : 1;
			unsigned int PlusLimit : 1;
			unsigned int MinusLimit : 1;
			unsigned int HomeInProgress : 1;
			unsigned int TriggerMove : 1; // bit 31
		} named;
		uint64_t registerValue;
	};

	namespace CoordStatusBits {
		enum TYPE : uint64_t {
			AddedDwellDis = 0,
			SharpCornerStop = 1,
			CC3Active = 2,
			EndDelayActive = 3,
			CCMoveType0 = 4,
			CCMoveType1 = 5,
			CCOffReq = 6,
			CCAddedArc = 7,
			LHStatus = 8, // 8 bit wide
			SegStopReq = 16,
			SegEnabled = 17,
			SegMoveDccel = 18,
			SegMoveAccel = 19,
			SegMove0 = 20,
			SegMove1 = 21,
			MoveMode0 = 22,
			MoveMode1 = 23,
			CCMode0 = 24,
			CCMode1 = 25,
			ContMotion = 26,
			BlockAcive = 27,
			FeedHold0 = 28,
			FeedHold1 = 29,
			LinToPvtBuf = 30,
			Csolve = 31,
			ErrorStatus = 32, // 8 bits wide
			TimersEnabled = 40,
			BlockRequest = 41,
			RESERVED_10 = 42,
			InPos = 43,
			AmpEna = 44,
			ClosedLoop = 45,
			DestVelZero = 46,
			HomeComplete = 47,
			TimerEnabled = 48,
			AuxFault = 49,
			EncLoss = 50,
			AmpWarn = 51,
			TriggerNotFound = 52,
			I2tFault = 53,
			SoftPlusLimit = 54,
			SoftMinusLimit = 55,
			AmpFault = 56,
			LimitStop = 57,
			FeFatal = 58,
			FeWarn = 59,
			PlusLimit = 60,
			MinusLimit = 61,
			HomeInProgress = 62,
			TriggerMove = 63
		};
	}

	struct MotorInfo {
		double position;
		double velocity;
		double followingError;
		double desiredVelocity;
		double acceleration;
		double conversion;
		//double slCw;
		//double slCcw;
		//bool invertDirection;
		//bool invertEncoder;
		int unitType;
		MotorStatusUnion status;
		MotorStatusUnion prevStatus;
	};

	struct CoordInfo {
		CoordStatusUnion status;
		CoordStatusUnion prevStatus;
	};

	struct IOInfo {
		// something
	};

	struct PlcInfo {
		std::string name;
		int32_t id;
		bool active;
		bool running;
	};

	struct GlobalInfo {
		bool abortAll;
		int32_t maxMotors;
		int32_t maxCoords;
		double temp;
		bool brickOvertemp;
		double uptime;
		std::string type;
		std::string firmware;
		std::string cpuType;
		int64_t cpuFrequency;
		std::vector<PlcInfo> plcs;
	};
}

#endif //POWERPMAC_DATASTRUCTURES_H
