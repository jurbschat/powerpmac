//
// Created by urbschaj on 23.01.19.
//

#ifndef POWERPMAC_COMMANDBUILDER_H
#define POWERPMAC_COMMANDBUILDER_H

#include "utility.h"
#include "throw.h"
#include "pmac/defines.h"

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
		void MakeMotorCommandInternalContinue(fmt::memory_buffer& buffer, Last last) {
			fmt::format_to(buffer, ",{}", static_cast<int32_t>(last));
		}
		template<typename Head, typename... Tail>
		void MakeMotorCommandInternalContinue(fmt::memory_buffer& buffer, Head head, Tail... tail) {
			fmt::format_to(buffer, ",{}", static_cast<int32_t>(head));
			MakeMotorCommandInternalContinue(buffer, tail...);
		}
		template<typename Head, typename... Tail>
		void MakeMotorCommandInternal(fmt::memory_buffer& buffer, Head head, Tail... tail) {
			fmt::format_to(buffer, "{}", static_cast<int32_t>(head));
			MakeMotorCommandInternalContinue(buffer, tail...);
		}
		template<typename Head>
		void MakeMotorCommandInternal(fmt::memory_buffer& buffer, Head head) {
			fmt::format_to(buffer, "{}", static_cast<int32_t>(head));
		}

		template<typename... motor_ids>
		fmt::memory_buffer MakeMotorCommand(const std::string& prefix, const std::string& postfix, motor_ids... motors) {
			fmt::memory_buffer buffer;
			fmt::format_to(buffer, "{}", prefix);
			MakeMotorCommandInternal(buffer, motors...);
			fmt::format_to(buffer, postfix);
			return buffer;
		}

		inline fmt::memory_buffer MakeMotorRangeCommand(const std::string& prefix, const std::string& postfix, MotorID::TYPE first, MotorID::TYPE last) {
			ValidateIdentifierRange(first, last);
			fmt::memory_buffer buffer;
			int32_t from = convert::from_enum(first);
			int32_t to = convert::from_enum(last);
			fmt::format_to(buffer, "{}{}", prefix, from);
			// skip first element. otherwise we either double the first element or have a leading comma
			for(int32_t i = from + 1; i <= to; i++) {
				fmt::format_to(buffer, ",{}", static_cast<int>(i));
			}
			fmt::format_to(buffer, postfix);
			return buffer;
		}

		template<typename... Args>
		fmt::memory_buffer MakePlain(const std::string& fmt, const Args&... args) {
			fmt::memory_buffer buffer;
			fmt::format_to(buffer, fmt, std::forward<Args>(args)...);
			return buffer;
		}
	}

	template<typename... motor_ids>
	std::string MotorPhase(motor_ids... motors) {
		detail::ValidateIdentifierList(motors...);
		return fmt::to_string(detail::MakeMotorCommand("#", "$", motors...));
	}

	template<typename... motor_ids>
	std::string MotorKill(motor_ids... motors) {
		detail::ValidateIdentifierList(motors...);
		return fmt::to_string(detail::MakeMotorCommand("#", "k", motors...));
	}

	template<typename... motor_ids>
	std::string MotorAbort(motor_ids... motors) {
		detail::ValidateIdentifierList(motors...);
		return fmt::to_string(detail::MakeMotorCommand("#", "a", motors...));
	}

	template<typename... motor_ids>
	std::string MotorJogToPosition(float position, motor_ids... motors) {
		detail::ValidateIdentifierList(motors...);
		fmt::memory_buffer buffer = detail::MakeMotorCommand("#", "", motors...);
		fmt::format_to(buffer, "jog={}", position);
		return fmt::to_string(buffer);
	}

	template<typename... motor_ids>
	std::string MotorGetPosition(motor_ids... motors) {
		detail::ValidateIdentifierList(motors...);
		fmt::memory_buffer buffer = detail::MakeMotorCommand("#", "p", motors...);
		return fmt::to_string(buffer);
	}

	template<typename... motor_ids>
	std::string MotorGetVelocity(motor_ids... motors) {
		detail::ValidateIdentifierList(motors...);
		fmt::memory_buffer buffer = detail::MakeMotorCommand("#", "v", motors...);
		return fmt::to_string(buffer);
	}
}

#endif //POWERPMAC_COMMANDBUILDER_H
