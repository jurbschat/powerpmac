//
// Created by urbschaj on 24.01.19.
//

#ifndef POWERPMAC_DEFINES_H
#define POWERPMAC_DEFINES_H

#include <cstdint>
#include <type_safe/strong_typedef.hpp>
#include <fmt/format.h>

namespace ppmac
{
	struct MotorID : type_safe::strong_typedef<MotorID, int32_t>,
		type_safe::strong_typedef_op::relational_comparison<MotorID>,
		type_safe::strong_typedef_op::equality_comparison<MotorID>,
		type_safe::strong_typedef_op::integer_arithmetic<MotorID>
	{
		using strong_typedef::strong_typedef;
	};

	struct CoordID : type_safe::strong_typedef<CoordID, int32_t>,
		type_safe::strong_typedef_op::relational_comparison<CoordID>,
		type_safe::strong_typedef_op::equality_comparison<CoordID>,
		type_safe::strong_typedef_op::integer_arithmetic<CoordID>
	{
		using strong_typedef::strong_typedef;
	};

	struct CompensationTableID : type_safe::strong_typedef<CompensationTableID, int32_t>,
	    type_safe::strong_typedef_op::relational_comparison<CompensationTableID>,
	    type_safe::strong_typedef_op::equality_comparison<CompensationTableID>,
	    type_safe::strong_typedef_op::integer_arithmetic<CompensationTableID>
	{
		using strong_typedef::strong_typedef;
	};

	struct IoID : type_safe::strong_typedef<IoID, int32_t>,
         type_safe::strong_typedef_op::relational_comparison<IoID>,
         type_safe::strong_typedef_op::equality_comparison<IoID>,
         type_safe::strong_typedef_op::integer_arithmetic<IoID>
	{
		using strong_typedef::strong_typedef;
	};

	struct PlcID : type_safe::strong_typedef<PlcID, int32_t>,
		type_safe::strong_typedef_op::relational_comparison<PlcID>,
		type_safe::strong_typedef_op::equality_comparison<PlcID>,
		type_safe::strong_typedef_op::integer_arithmetic<PlcID>
	{
		using strong_typedef::strong_typedef;
	};
}
namespace fmt {
	template <>
	struct formatter<ppmac::MotorID> {
		template <typename ParseContext>
		constexpr auto parse(ParseContext &ctx) {
			return ctx.begin();
		}
		template <typename FormatContext>
		auto format(const ppmac::MotorID &d, FormatContext &ctx) {
			return format_to(ctx.out(), "{}", int32_t(d));
		}
	};

	template <>
	struct formatter<ppmac::CoordID> {
		template <typename ParseContext>
		constexpr auto parse(ParseContext &ctx) {
			return ctx.begin();
		}
		template <typename FormatContext>
		auto format(const ppmac::CoordID &d, FormatContext &ctx) {
			return format_to(ctx.out(), "{}", int32_t(d));
		}
	};

	template <>
	struct formatter<ppmac::CompensationTableID> {
		template <typename ParseContext>
		constexpr auto parse(ParseContext &ctx) {
			return ctx.begin();
		}
		template <typename FormatContext>
		auto format(const ppmac::CompensationTableID &d, FormatContext &ctx) {
			return format_to(ctx.out(), "{}", int32_t(d));
		}
	};

	template <>
	struct formatter<ppmac::IoID> {
		template <typename ParseContext>
		constexpr auto parse(ParseContext &ctx) {
			return ctx.begin();
		}
		template <typename FormatContext>
		auto format(const ppmac::IoID &d, FormatContext &ctx) {
			return format_to(ctx.out(), "{}", int32_t(d));
		}
	};

	template <>
	struct formatter<ppmac::PlcID> {
		template <typename ParseContext>
		constexpr auto parse(ParseContext &ctx) {
			return ctx.begin();
		}
		template <typename FormatContext>
		auto format(const ppmac::PlcID &d, FormatContext &ctx) {
			return format_to(ctx.out(), "{}", int32_t(d));
		}
	};
}

#endif //POWERPMAC_DEFINES_H
