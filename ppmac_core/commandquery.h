//
// Created by urbschaj on 24.01.19.
//

#ifndef POWERPMAC_COMMANDQUERY_H
#define POWERPMAC_COMMANDQUERY_H

#include "commandbuilder.h"
#include "utility.h"
#include "pmac/datastructures.h"
#include <vector>
#include <tuple>

namespace ppmac::query {

	template<typename... Args>
	struct CommandQuery
	{
		CommandQuery(const fmt::memory_buffer& buffer, int32_t first, Args&&... args)
			: command(fmt::to_string(buffer)),
			first(first),
			targets(std::forward<Args>(args)...)
		{}

		std::string command;
		int32_t first;
		std::tuple<Args...> targets;
	};

	inline auto GeneralGetInfo() {
		fmt::memory_buffer buffer = cmd::detail::MakePlain("Sys.MaxMotors;Sys.maxCoords;Sys.pAbortAll");
		return CommandQuery{buffer, 0, &GlobalInfo::maxMotors, &GlobalInfo::maxCoords, &GlobalInfo::abortAll};
	}

	inline auto MotorGetPositionRange(MotorID::TYPE first, MotorID::TYPE last) {
		cmd::detail::ValidateIdentifierRange(first, last);
		fmt::memory_buffer buffer = cmd::detail::MakeMotorRangeCommand("#", "p", first, last);
		return CommandQuery{buffer, convert::from_enum(first), &MotorInfo::position};
	}

	//TODO: this is a bug, add v to get two values
	inline auto MotorGetInfoRange(MotorID::TYPE first, MotorID::TYPE last) {
		cmd::detail::ValidateIdentifierRange(first, last);
		fmt::memory_buffer buffer = cmd::detail::MakeMotorRangeCommand("#", "p", first, last);
		return CommandQuery{buffer, convert::from_enum(first), &MotorInfo::position, &MotorInfo::acceleration};
	}

}

#endif //POWERPMAC_COMMANDQUERY_H
