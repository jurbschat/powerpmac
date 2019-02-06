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

	template<typename T, typename... Args>
	struct ObjectPointers {
		ObjectPointers(stdext::span<T> data, Args&&... args)
				: data(data),
				  memberPointer(std::forward<Args>(args)...)
		{}
		stdext::span<T> data;
		std::tuple<Args...> memberPointer;
	};

	template<typename T, typename... Args>
	ObjectPointers<T, Args...> MakeObjectPointers(stdext::span<T> data, Args&&... args) {
		return ObjectPointers<T, Args...>{data, std::forward<Args>(args)...};
	}

	template<typename PtrHolder, typename ParserType>
	struct CommandQuery
	{
		using Parser = ParserType;

		CommandQuery(const std::string& cmd, int32_t rangeStart, PtrHolder pointers, Parser parser)
			: command(cmd),
			  rangeStart(rangeStart),
			  pointers{pointers},
			  parser{parser}
		{}

		std::string command;
		size_t rangeStart;
		PtrHolder pointers;
		Parser parser;
	};

	template<typename PtrHolder, typename ParserType>
	CommandQuery<PtrHolder, ParserType> MakeCommandQuery(const std::string& cmd, int32_t rangeStart, PtrHolder pointers, ParserType parser) {
		return CommandQuery<PtrHolder, ParserType>{cmd, rangeStart, pointers, parser};
	}

	inline auto GeneralGetInfo(stdext::span<GlobalInfo> data) {
		// type; vers; cpu; Sys.CpuFreq; Sys.CpuTemp
		fmt::memory_buffer buffer = builder::detail::MakePlain("Sys.MaxMotors; Sys.maxCoords; Sys.pAbortAll; Sys.CpuTemp; BrickLV.OverTemp; Sys.Time");
		return MakeCommandQuery(
			fmt::to_string(buffer),
			0,
			MakeObjectPointers(
				data,
				&GlobalInfo::maxMotors,
				&GlobalInfo::maxCoords,
				&GlobalInfo::abortAll,
				&GlobalInfo::temp,
				&GlobalInfo::brickOvertemp,
				&GlobalInfo::uptime
			),
			[](const std::string& str){
				return parser::Parse1D<parser::DoubleParser>(str, boost::is_any_of("\r\n"));
			}
		);
	}

	inline auto MotorGetPositionRange(stdext::span<MotorInfo> data, int32_t first, int32_t last) {
		builder::ValidateIdentifierRange(first, last);
		fmt::memory_buffer buffer = builder::detail::MakePrefixPostfixRangeCommand("#", "pvf", first, last);
		return MakeCommandQuery(
			fmt::to_string(buffer),
			first,
			MakeObjectPointers(
				data,
				&MotorInfo::position,
				&MotorInfo::velocity,
				&MotorInfo::followingError
			),
			[](const std::string& str){
				return parser::Parse2D<parser::DoubleParser>(str, boost::is_any_of("\r\n"), boost::is_space());
			}
		);
	}

	inline auto MotorGetStatusRange(stdext::span<MotorInfo> data, int32_t first, int32_t last) {
		builder::ValidateIdentifierRange(first, last);
		fmt::memory_buffer buffer = builder::detail::MakePrefixPostfixRangeCommand("#", "?", first, last);
		return MakeCommandQuery(
			fmt::to_string(buffer),
			first,
			MakeObjectPointers(
				data,
				&MotorInfo::status
			),
			[](const std::string& str){
				return parser::Parse1D<parser::Hex64Parser>(str, boost::is_space());
			}
		);
	}

	inline auto MotorGetOtherRange(stdext::span<MotorInfo> data, int32_t first, int32_t last) {
		builder::ValidateIdentifierRange(first, last);
		boost::container::small_vector<std::tuple<int>, 32> tuples;
		for(int i = first; i < (last - first); i++) {
			tuples.push_back((std::make_tuple(i)));
		}
		fmt::memory_buffer buffer = builder::detail::MakeMultiCommand("Motor[{}].PosSf", stdext::make_span(tuples));
		return MakeCommandQuery(
			fmt::to_string(buffer),
			first,
			MakeObjectPointers(
				data,
				&MotorInfo::conversion
				//&MotorInfo::unitType
			),
			[](const std::string& str){
				return parser::Parse1D<parser::DoubleParser>(str, boost::is_any_of("\r\n"));
			}
		);
	}

}

#endif //POWERPMAC_COMMANDQUERY_H
