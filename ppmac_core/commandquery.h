//
// Created by urbschaj on 24.01.19.
//

#ifndef POWERPMAC_COMMANDQUERY_H
#define POWERPMAC_COMMANDQUERY_H

#include "commandbuilder.h"
#include "resultparser.h"
#include "utility.h"
#include "pmac/datastructures.h"
#include "libs/span.hpp"
#include <vector>
#include <tuple>
#include <boost/container/small_vector.hpp>

namespace ppmac::query {

	namespace builder
	{
		template<typename T>
		void ValidateIdentifierRange(T first, T last) {
			//int32_t from = from_enum(first);
			//int32_t to = from_enum(last);
			if(first < 0 || first > last) {
				THROW_RUNTIME_ERROR("invalid range [{}:{}]", first, last);
			}
		}

		template<typename... Args>
		void ValidateIdentifierList(Args... args) {
			bool sorted = PackIsSorted(args...);
			if(!sorted) {
				auto values = PackAsArray<int32_t>(args...);
				THROW_RUNTIME_ERROR("invalid list [{}]", values);
			}
		}

		namespace detail
		{
			template<typename Last>
			void MakePrefixPostfixCommandInternalContinue(fmt::memory_buffer& buffer, Last last) {
				fmt::format_to(buffer, ",{}", static_cast<int32_t>(last));
			}
			template<typename Head, typename... Tail>
			void MakePrefixPostfixCommandInternalContinue(fmt::memory_buffer& buffer, Head head, Tail... tail) {
				fmt::format_to(buffer, ",{}", static_cast<int32_t>(head));
				MakePrefixPostfixCommandInternal(buffer, tail...);
			}
			template<typename Head, typename... Tail>
			void MakePrefixPostfixCommandInternal(fmt::memory_buffer& buffer, Head head, Tail... tail) {
				fmt::format_to(buffer, "{}", static_cast<int32_t>(head));
				MakePrefixPostfixCommandInternalContinue(buffer, tail...);
			}
			template<typename Head>
			void MakePrefixPostfixCommandInternal(fmt::memory_buffer &buffer, Head head) {
				fmt::format_to(buffer, "{}", static_cast<int32_t>(head));
			}

			template<typename... motor_ids>
			fmt::memory_buffer MakePrefixPostfixCommand(const std::string &prefix, const std::string &postfix,
			                                            motor_ids... motors) {
				ValidateIdentifierList(motors...);
				fmt::memory_buffer buffer;
				fmt::format_to(buffer, "{}", prefix);
				MakePrefixPostfixCommandInternal(buffer, motors...);
				fmt::format_to(buffer, postfix);
				return buffer;
			}

			template <typename T, std::size_t ... Is>
			void tuple_format_helper(fmt::memory_buffer& buffer, const std::string& format, const T& tpl, std::index_sequence<Is...>)
			{
				fmt::format_to(buffer, format, std::get<Is>(tpl)...);
			}

			template <std::size_t N, typename T>
			void tuple_format_helper(fmt::memory_buffer& buffer, const std::string& format, const T& tpl)
			{
				tuple_format_helper(buffer, format, tpl, std::make_index_sequence<N>());
			}

			template<typename... Ts, long N>
			fmt::memory_buffer MakeMultiCommand(const std::string& formatString, const stdext::span<std::tuple<Ts...>, N>& args) {
				//ValidateIdentifierList(motors...);
				fmt::memory_buffer buffer;
				for (auto& tpl : args) {
					if(buffer.size() == 0) {
						tuple_format_helper<sizeof...(Ts)>(buffer, formatString, tpl);
					} else {
						fmt::format_to(buffer, ";");
						tuple_format_helper<sizeof...(Ts)>(buffer, formatString, tpl);
					}
				}
				return buffer;
			}

			template<typename... Ts>
			fmt::memory_buffer MakeCommand(const std::string& formatString, const std::tuple<Ts...> args) {
				fmt::memory_buffer buffer;
				tuple_format_helper<sizeof...(Ts)>(buffer, formatString, args);
				return buffer;
			}

			inline fmt::memory_buffer MakePrefixPostfixRangeCommand(const std::string &prefix, const std::string &postfix,
			                                                        int32_t first, int32_t last) {
				ValidateIdentifierRange(first, last);
				fmt::memory_buffer buffer;
				//int32_t from = from_enum(first);
				//int32_t to = from_enum(last);
				if(first != last) {
					fmt::format_to(buffer, "{}{}..{}{}", prefix, first, last, postfix);
				} else {
					// single element range
					fmt::format_to(buffer, "{}{}{}", prefix, first, postfix);
				}
				return buffer;
			}

			template<typename... Args>
			fmt::memory_buffer MakePlain(const std::string& fmt, const Args&... args) {
				fmt::memory_buffer buffer;
				fmt::format_to(buffer, fmt, std::forward<Args>(args)...);
				return buffer;
			}

			template<int N, typename... Ts>
			using NthTypeOf = typename std::tuple_element<N, std::tuple<Ts...>>::type;

			template<typename T, typename... Args>
			struct first {
				using type = T;
			};

		} // detail

		/*template<typename... Args>
		auto MakeArgList(Args... args) {
			//using type = typename detail::first<Args...>::type;
			//std::array<type, sizeof...(Args)> arr = {args...};
			std::array<typename std::common_type<Args...>::type , sizeof...(Args)> arr = {args...};
			return arr;
		}

		template<typename... motor_ids>
		std::string MotorPhase(motor_ids... motors) {
			return fmt::to_string(detail::MakePrefixPostfixCommand("#", "$", motors...));
		}

		template<typename... motor_ids>
		std::string MotorKill(motor_ids... motors) {
			return fmt::to_string(detail::MakePrefixPostfixCommand("#", "k", motors...));
		}

		template<typename... motor_ids>
		std::string MotorAbort(motor_ids... motors) {
			return fmt::to_string(detail::MakePrefixPostfixCommand("#", "a", motors...));
		}

		template<typename... motor_ids>
		std::string MotorJogToPosition(float position, motor_ids... motors) {
			fmt::memory_buffer buffer = detail::MakePrefixPostfixCommand("#", "", motors...);
			fmt::format_to(buffer, "jog={}", position);
			return fmt::to_string(buffer);
		}

		template<typename... motor_ids>
		std::string MotorGetPosition(motor_ids... motors) {
			fmt::memory_buffer buffer = detail::MakePrefixPostfixCommand("#", "p", motors...);
			return fmt::to_string(buffer);
		}

		template<typename... motor_ids>
		std::string MotorGetVelocity(motor_ids... motors) {
			fmt::memory_buffer buffer = detail::MakePrefixPostfixCommand("#", "v", motors...);
			return fmt::to_string(buffer);
		}

		template<long N>
		std::string MotorSetConversion(const stdext::span<std::tuple<int, float>, N>& tuples)
		{
			fmt::memory_buffer buffer = detail::MakeMultiCommand("Motor[{}].PosSf={}", tuples);
			return fmt::to_string(buffer);
		}*/
	}

	template<typename P, typename T>
	struct ObjectPointerInfo {
		ObjectPointerInfo(T ptr)
		: ptr(ptr)
		{}
		using parser_type = P;
		T ptr;
	};

	template<typename P, typename T>
	ObjectPointerInfo<P, T> MakeObjectPtrInfo(T ptr) {
		return ObjectPointerInfo<P, T>(ptr);
	}

	template<typename T, typename... Args>
	struct ObjectPointerList {
		ObjectPointerList(stdext::span<T> data, Args&&... args)
			: data(data),
			memberPointer(std::forward<Args>(args)...)
		{}
		stdext::span<T> data;
		std::tuple<Args...> memberPointer;
	};

	template<typename T, typename... Args>
	ObjectPointerList<T, Args...> MakeObjectPointerList(stdext::span<T> data, Args &&... args) {
		return ObjectPointerList<T, Args...>{data, std::forward<Args>(args)...};
	}

	template<typename PtrHolder, typename ResultSplitter>
	struct CommandQuery
	{
		using Splitter = ResultSplitter;

		CommandQuery(const std::string& cmd, int32_t rangeStart, int32_t rangeSize, PtrHolder pointers, Splitter splitter)
			: command(cmd),
			  rangeStart(rangeStart),
			  rangeSize(rangeSize),
			  pointers{pointers},
			  splitter{splitter}
		{}

		std::string command;
		size_t rangeStart;
		size_t rangeSize;
		PtrHolder pointers;
		Splitter splitter;
	};

	template<typename PtrHolder, typename ResultSplitter>
	CommandQuery<PtrHolder, ResultSplitter> MakeCommandQuery(const std::string& cmd, int32_t rangeStart, int32_t rangeSize, PtrHolder pointers, ResultSplitter splitter) {
		return CommandQuery<PtrHolder, ResultSplitter>{cmd, rangeStart, rangeSize, pointers, splitter};
	}

	/*
	 * retuns a a query that will update general info like max motors, abortAll etc...
	 */
	inline auto GeneralGetInfo(stdext::span<GlobalInfo> data) {
		fmt::memory_buffer buffer = builder::detail::MakePlain("Sys.MaxMotors; Sys.maxCoords; Sys.AbortAll; Sys.CpuTemp; BrickLV.OverTemp; Sys.Time; Sys.CpuFreq; type; vers; cpu;");
		return MakeCommandQuery(
			fmt::to_string(buffer),
			0, 1,
			MakeObjectPointerList(
				data,
				MakeObjectPtrInfo<parser::IntParser>(&GlobalInfo::maxMotors),
				MakeObjectPtrInfo<parser::IntParser>(&GlobalInfo::maxCoords),
				MakeObjectPtrInfo<parser::IntParser>(&GlobalInfo::abortAll),
				MakeObjectPtrInfo<parser::DoubleParser>(&GlobalInfo::temp),
				MakeObjectPtrInfo<parser::IntParser>(&GlobalInfo::brickOvertemp),
				MakeObjectPtrInfo<parser::DoubleParser>(&GlobalInfo::uptime),
				MakeObjectPtrInfo<parser::Int64Parser>(&GlobalInfo::cpuFrequency),
				MakeObjectPtrInfo<parser::NoneParser>(&GlobalInfo::type),
				MakeObjectPtrInfo<parser::NoneParser>(&GlobalInfo::firmware),
				MakeObjectPtrInfo<parser::NoneParser>(&GlobalInfo::cpuType)
			),
			[](const std::string& str){
				return parser::Split1D(str, boost::is_any_of("\r\n"));
			}
		);
	}

	inline auto GeneralGetPlcStatus(stdext::span<PlcInfo> data, int32_t first, int32_t last) {
		builder::ValidateIdentifierRange(first, last);
		boost::container::small_vector<std::tuple<int>, 32> tuples;
		// we want to include the whole range e.g. 1..2 sould be 1 and 2 not only 1
		for(int i = first; i <= (last - first); i++) {
			tuples.push_back((std::make_tuple(i)));
		}
		fmt::memory_buffer buffer = builder::detail::MakeMultiCommand("Plc[{0}].Active; Plc[{0}].Running", stdext::make_span(tuples));
		return MakeCommandQuery(
			fmt::to_string(buffer),
			first, last+1,
			MakeObjectPointerList(
				data,
				//MakeObjectPtrInfo<parser::NoneParser>(&PlcInfo::name),
				//MakeObjectPtrInfo<parser::IntParser>(&PlcInfo::id),
				MakeObjectPtrInfo<parser::IntParser>(&PlcInfo::active),
				MakeObjectPtrInfo<parser::IntParser>(&PlcInfo::running)
			),
			[](const std::string& str){
				return parser::Split1D(str, boost::is_any_of("\r\n"));
			}
		);
	}

	/*
	 * this query updates all raw motor values. (poition, velocity, following error and motor statuses)
	 */
	inline auto MotorGetInfoRange(stdext::span<MotorInfo> data, int32_t first, int32_t last) {
		builder::ValidateIdentifierRange(first, last);
		fmt::memory_buffer buffer = builder::detail::MakePrefixPostfixRangeCommand("#", "pvf?", first, last);
		return MakeCommandQuery(
			fmt::to_string(buffer),
			first, last+1,
			MakeObjectPointerList(
				data,
				MakeObjectPtrInfo<parser::DoubleParser>(&MotorInfo::position),
				MakeObjectPtrInfo<parser::DoubleParser>(&MotorInfo::velocity),
				MakeObjectPtrInfo<parser::DoubleParser>(&MotorInfo::followingError),
				MakeObjectPtrInfo<parser::Hex64Parser>(&MotorInfo::status)
			),
			[](const std::string& str){
				return parser::Split2D(str, boost::is_any_of("\r\n"), boost::is_space());
			}
		);
	}

	/*
	 * this query updates all raw motor values. (poition, velocity, following error and motor statuses)
	 */
	inline auto CoordGetInfoRange(stdext::span<CoordInfo> data, int32_t first, int32_t last) {
		builder::ValidateIdentifierRange(first, last);
		fmt::memory_buffer buffer = builder::detail::MakePrefixPostfixRangeCommand("&", "pvf?", first, last);
		return MakeCommandQuery(
			fmt::to_string(buffer),
			first, last+1,
			MakeObjectPointerList(
				data,
				MakeObjectPtrInfo<parser::CoordDoubleParser>(&CoordInfo::position),
				MakeObjectPtrInfo<parser::CoordDoubleParser>(&CoordInfo::velocity),
				MakeObjectPtrInfo<parser::CoordDoubleParser>(&CoordInfo::followingError),
				MakeObjectPtrInfo<parser::Hex64Parser>(&CoordInfo::status)
			),
			[](const std::string& str){
				return parser::Split2D(str, boost::is_any_of("\r\n"), boost::is_space());
			}
		);
	}

	/*
	 * gets motor conversion info, e.g. mapping of motor units to engineering units and the unit type
	 */
	inline auto MotorGetConversionInfoRange(stdext::span<MotorInfo> data, int32_t first, int32_t last) {
		builder::ValidateIdentifierRange(first, last);
		boost::container::small_vector<std::tuple<int>, 32> tuples;
		for(int i = first; i < (last - first); i++) {
			tuples.push_back((std::make_tuple(i)));
		}
		fmt::memory_buffer buffer = builder::detail::MakeMultiCommand("Motor[{0}].PosSf; Motor[{0}].PosUnit", stdext::make_span(tuples));
		return MakeCommandQuery(
			fmt::to_string(buffer),
			first, last+1,
			MakeObjectPointerList(
				data,
				MakeObjectPtrInfo<parser::DoubleParser>(&MotorInfo::conversion),
				MakeObjectPtrInfo<parser::DoubleParser>(&MotorInfo::unitType)
			),
			[](const std::string& str){
				return parser::Split1D(str, boost::is_any_of("\r\n"));
			}
		);
	}

}

#endif //POWERPMAC_COMMANDQUERY_H
