//
// Created by urbschaj on 23.01.19.
//

#ifndef POWERPMAC_COMMANDBUILDER_H
#define POWERPMAC_COMMANDBUILDER_H

#include "utility.h"
#include "throw.h"
#include "pmac/defines.h"
#include "libs/span.hpp"

#include <fmt/format.h>
#include <fmt/ranges.h>
#include <cstddef>

namespace ppmac::cmd {

	namespace detail {

		template<typename T>
		void ValidateIdentifierRange(T first, T last) {
			int32_t from = convert::from_enum(first);
			int32_t to = convert::from_enum(last);
			if(from < 0 || from > to) {
				THROW_RUNTIME_ERROR("invalid range [{}:{}]", from, to);
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
		                                                        MotorID::TYPE first, MotorID::TYPE last) {
			ValidateIdentifierRange(first, last);
			fmt::memory_buffer buffer;
			int32_t from = convert::from_enum(first);
			int32_t to = convert::from_enum(last);
			if(from != to) {
				fmt::format_to(buffer, "{}{}..{}{}", prefix, from, to, postfix);
			} else {
				// single element range
				fmt::format_to(buffer, "{}{}{}", prefix, from, postfix);
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


	template<typename... Args>
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

	inline std::string MotorSetConversion(float value, MotorID::TYPE motor)
	{
		fmt::memory_buffer buffer = detail::MakeCommand("Motor[{}].PosSf={}", std::make_tuple(static_cast<int>(motor), value));
		return fmt::to_string(buffer);
	}

	template<long N>
	std::string MotorSetConversion(const stdext::span<std::tuple<int, float>, N>& tuples)
	{
		fmt::memory_buffer buffer = detail::MakeMultiCommand("Motor[{}].PosSf={}", tuples);
		return fmt::to_string(buffer);
	}
}

#endif //POWERPMAC_COMMANDBUILDER_H
