//
// Created by urbschaj on 24.01.19.
//

#ifndef POWERPMAC_COMMANDQUERY_H
#define POWERPMAC_COMMANDQUERY_H

#include "commandbuilder.h"
#include "utility.h"
#include "pmac/datastructures.h"
#include "libs/span.hpp"
#include <vector>
#include <tuple>

namespace ppmac::query {

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
	struct CommandQuery
	{
		CommandQuery(const std::string& cmd, int32_t rangeStart, stdext::span<T> data, Args&&... args)
			: command(cmd),
			  rangeStart(rangeStart),
			  pointers{data, std::forward<Args>(args)...}
		{}

		std::string command;
		size_t rangeStart;
		ObjectPointers<T, Args...> pointers;
	};

	inline auto GeneralGetInfo(stdext::span<GlobalInfo> data) {
		fmt::memory_buffer buffer = cmd::detail::MakePlain("Sys.MaxMotors; Sys.maxCoords; Sys.pAbortAll; PowerBrick[0].PhaseFreq; PowerBrick[1].PhaseFreq");
		return CommandQuery{fmt::to_string(buffer), 0, data,
					  &GlobalInfo::maxMotors,
					  &GlobalInfo::maxCoords,
					  &GlobalInfo::abortAll,
					  &GlobalInfo::Gate30,
					  &GlobalInfo::Gate31
		};
	}

	inline auto MotorGetPositionRange(stdext::span<MotorInfo> data, MotorID::TYPE first, MotorID::TYPE last) {
		cmd::detail::ValidateIdentifierRange(first, last);
		fmt::memory_buffer buffer = cmd::detail::MakeMotorRangeCommand("#", "pvf", first, last);
		return CommandQuery{fmt::to_string(buffer), first, data, &MotorInfo::position, &MotorInfo::velocity, &MotorInfo::followingError};
	}

	inline auto MotorGetStatusRange(stdext::span<MotorInfo> data,MotorID::TYPE first, MotorID::TYPE last) {
		cmd::detail::ValidateIdentifierRange(first, last);
		fmt::memory_buffer buffer = cmd::detail::MakeMotorRangeCommand("#", "?", first, last);
		return CommandQuery{fmt::to_string(buffer), first, data, &MotorInfo::status};
	}

}

#endif //POWERPMAC_COMMANDQUERY_H
