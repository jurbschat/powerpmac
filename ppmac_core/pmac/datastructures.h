//
// Created by urbschaj on 23.01.19.
//

#include <vector>
#include <string>
#include <array>
#include <cstdint>
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

	namespace bits {
		template<
	        typename T,
	        typename = std::enable_if_t<std::is_unsigned<T>::value>
		>
		T set(T value, uint32_t bitIndex) {
			value = value | (1ull << bitIndex);
			return value;
		}
		template<typename T>
		T reset(T value, uint32_t bitIndex) {
			value = value & ~(1ull << bitIndex);
			return value;
		}
		template<
			typename T,
			typename = std::enable_if_t<std::is_unsigned<T>::value>
		>
		T set(T value, uint32_t bitIndex, bool set) {
			if(set) {
				return bits::set(value, bitIndex);
			} else {
				return bits::reset(value, bitIndex);
			}
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

		bool AllBitsSet(uint64_t state, uint64_t check);
		bool AnyBitSet(uint64_t state, uint64_t check);
	}

	namespace states {
		std::string GetMotorStateNamesForFlagMatch(uint64_t state, uint64_t significantBits, uint64_t expectedState = 0xFFFFFFFFFFFFFFFF);
		std::string GetCoordStateNamesForFlagMatch(uint64_t state, uint64_t significantBits, uint64_t expectedState = 0xFFFFFFFFFFFFFFFF);
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
			unsigned int FeFatal : 1;
			unsigned int FeWarn : 1;
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
			FeFatal = 58,
			FeWarn = 59,
			PlusLimit = 60,
			MinusLimit = 61,
			HomeInProgress = 62,
			TriggerMove = 63
		};
	}

	namespace AuxMotorStatusBits {
		enum TYPE : uint64_t {
			ServoCtrl = 0,
		};
	}

	// contains a list of stats bits that we count as "error" state
	// these should not need a manual reset
	const uint64_t motorSoftErrorStatusBits =
			//(1ull << MotorStatusBits::AmpWarn) |
			//(1ull << MotorStatusBits::SoftPlusLimit) |
			//(1ull << MotorStatusBits::SoftMinusLimit) |
			//(1ull << MotorStatusBits::LimitStop) |
			//(1ull << MotorStatusBits::PlusLimit) |
			//(1ull << MotorStatusBits::MinusLimit) |
			(1ull << MotorStatusBits::AmpFault) |
			(1ull << MotorStatusBits::I2tFault) |
			(1ull << MotorStatusBits::FeFatal);

	// contains a list of stats bits that we count as "fatal" state
	// these need some kind of reset
	const uint64_t motorHardErrorStatusBits =
			(1ull << MotorStatusBits::EncLoss);

	// contains a list of stats bits that we count as "fatal" state
	// these need some kind of reset
	const uint64_t motorNeededStatusBits =
			(1ull << MotorStatusBits::AmpEna) |
			(1ull << MotorStatusBits::PhaseFound);

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

	// contains a list of stats bits that we count as "error" state
	// these should not need a manual reset
	const uint64_t coordSoftErrorStatusBits =
			//(1ull << CoordStatusBits::AmpWarn) |
			//(1ull << CoordStatusBits::SoftPlusLimit) |
			//(1ull << CoordStatusBits::SoftMinusLimit) |
			//(1ull << CoordStatusBits::LimitStop) |
			//(1ull << CoordStatusBits::PlusLimit) |
			//(1ull << CoordStatusBits::MinusLimit) |
			(1ull << CoordStatusBits::AmpFault) |
			(1ull << CoordStatusBits::I2tFault) |
			(1ull << CoordStatusBits::FeFatal);

	// contains a list of stats bits that we count as "fatal" state
	// these need some kind of reset
	const uint64_t coordHardErrorStatusBits =
			(1ull << CoordStatusBits::EncLoss);

	// contains a list of stats bits that we count as "fatal" state
	// these need some kind of reset
	const uint64_t coordNeededStatusBits =
			(1ull << CoordStatusBits::AmpEna);

	enum class MotorUnit {
		None,
		FeedbackUnit,
		Meter,
		Millimeter,
		MicroMeter,
		NanoMeter,
		PicoMeter,
		Inch,
		Mil,
		Revolution,
		Radian,
		Degree,
		Gradian,
		ArcMinute,
		ArcSecond,
		Reserved
	};

	std::string GetMotorUnitString(ppmac::MotorUnit motorUnit);

	struct MotorInfo {
		double position;
		double velocity;
		double followingError;
		double conversion;
		MotorStatusUnion status;
		MotorStatusUnion prevStatus;
		bool servoCtrl;
		bool prevServoCtrl;
		//MotorUnit unit;
	};

	union Coord26Axis {
		struct {
			double A;
			double B;
			double C;
			double D;
			double E;
			double F;
			double G;
			double H;
			double I;
			double J;
			double K;
			double L;
			double M;
			double N;
			double O;
			double P;
			double Q;
			double R;
			double S;
			double T;
			double U;
			double V;
			double W;
			double X;
			double Y;
			double Z;
		} named;
		std::array<double, 26> array;
	};

	namespace AvailableAxis {
		enum TYPE : uint32_t {
			A = (1 << 0),
			B = (1 << 1),
			C = (1 << 2),
			D = (1 << 3),
			E = (1 << 4),
			F = (1 << 5),
			G = (1 << 6),
			H = (1 << 7),
			I = (1 << 8),
			J = (1 << 9),
			K = (1 << 10),
			L = (1 << 11),
			M = (1 << 12),
			N = (1 << 13),
			O = (1 << 14),
			P = (1 << 15),
			Q = (1 << 16),
			R = (1 << 17),
			S = (1 << 18),
			T = (1 << 19),
			U = (1 << 20),
			V = (1 << 21),
			W = (1 << 22),
			X = (1 << 23),
			Y = (1 << 24),
			Z = (1 << 25)
		};
		const int32_t maxAxis = 26;

		static inline int32_t MapNameToAxis(char axis) {
			if(axis >= 'A' && axis <= 'Z') {
				return axis - 'A';
			} else if(axis >= 'a' && axis <= 'z') {
				return axis - 'a';
			}
			return -1;
		};

		static inline char MapAxisToChar(int32_t axis) {
			if(axis >= 0 && axis < 26) {
				return 'A' + static_cast<char>(axis);
			}
			return '\0';
		};

		static inline const char* MapAxisToString(int32_t axis) {
			const char* const axisNames[] = {  "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
										 "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"  };
			if(axis >= 0 && axis < static_cast<int32_t>(sizeof(axisNames))) {
				return axisNames[axis];
			}
			return "";
		};

		/*static inline TYPE MapAxisToEnum(char axis) {
			if(axis >= 'A' && axis <= 'Z') {
				return axis - 'A';
			} else if(axis >= 'a' && axis <= 'z') {
				return axis - 'a';
			}
			return -1;
		};
		static inline int32_t MapEnumToAxis(TYPE value) {
			if(axis >= 'A' && axis <= 'Z') {
				return axis - 'A';
			} else if(axis >= 'a' && axis <= 'z') {
				return axis - 'a';
			}
			return -1;
		};*/
	}

	// we only support coordinate systems with up to 8 axis
	struct CoordInfo {
		Coord26Axis position;
		Coord26Axis velocity;
		Coord26Axis followingError;
		CoordStatusUnion status;
		CoordStatusUnion prevStatus;
		uint32_t availableAxis;
		uint32_t prevAvailableAxis;
	};


	struct CoordAxisDefinitionInfo {
		std::string axisName;
		int32_t coordId;
		int32_t motorId;
	};

	struct MultiAxisMoveInfo {
		int32_t axis;
		double pos;
	};

	struct IOInfo {
		// ios are currently directly queried by the device server and are not
		// queried by the core
	};

	enum class PmacExecutableType {
		INVALID = -1,
		PLC = 0,
		PROG,
		SUBPROG
	};

	struct PmacExecutableInfo {
		std::string name;
		int32_t id;
		PmacExecutableType type;
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
		int32_t activeCompensationTables;
		int32_t prevActiveCompensationTables;
	};
}

#endif //POWERPMAC_DATASTRUCTURES_H
