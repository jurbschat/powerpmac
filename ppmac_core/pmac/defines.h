//
// Created by urbschaj on 24.01.19.
//

#ifndef POWERPMAC_DEFINES_H
#define POWERPMAC_DEFINES_H

#include <cstdint>

namespace ppmac
{
	enum class MotorID : int32_t {
		INVALID = -1,
		Motor0 = 0,
		Motor1,
		Motor2,
		Motor3,
		Motor4,
		Motor5,
		Motor6,
		Motor7,
		Motor8,
		Motor9,
		Motor10,
		Motor11,
		Motor12,
		Motor13,
		Motor14,
		Motor15,
		Motor16,
		Motor17,
		Motor18,
		Motor19,
		Motor20,
		Motor21,
		Motor22,
		Motor23,
		Motor24,
		Motor25,
		Motor26,
		Motor27,
		Motor28,
		Motor29,
		Motor30,
		Motor31
	};

	enum class IoID : int32_t {
		INVALID = -1,
		Port0 = 0
	};

	enum class CoordID : int32_t {
		INVALID = -1,
		Coord0 = 0,
		Coord1,
		Coord2,
		Coord3,
		Coord4,
		Coord5,
		Coord6,
		Coord7,
		Coord8,
		Coord9,
		Coord10,
		Coord11,
		Coord12,
		Coord13,
		Coord14,
		Coord15,
		Coord16,
		Coord17,
		Coord18,
		Coord19,
		Coord20,
		Coord21,
		Coord22,
		Coord23,
		Coord24,
		Coord25,
		Coord26,
		Coord27,
		Coord28,
		Coord29,
		Coord30,
		Coord31
	};

	enum class CompensationTableID : int32_t {
		INVALID = -1,
		Table0 = 0,
		Table1,
		Table2,
		Table3,
		Table4,
		Table5,
		Table6,
		Table7,
		Table8,
		Table9,
		Table10,
		Table11,
		Table12,
		Table13,
		Table14,
		Table15,
		Table16,
		Table17,
		Table18,
		Table19,
		Table20,
		Table21,
		Table22,
		Table23,
		Table24,
		Table25,
		Table26,
		Table27,
		Table28,
		Table29,
		Table30,
		Table31
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
	CompensationTableID to_enum_comp_table(int32_t index);

	MotorID to_enum(int_with_tag<MotorID> index);
	IoID to_enum(int_with_tag<IoID> index);
	CoordID to_enum(int_with_tag<CoordID> index);
	CompensationTableID to_enum(int_with_tag<CompensationTableID> index);

	int32_t from_enum(MotorID motor);
	int32_t from_enum(IoID io);
	int32_t from_enum(CoordID coord);
	int32_t from_enum(CompensationTableID table);
}

#endif //POWERPMAC_DEFINES_H
