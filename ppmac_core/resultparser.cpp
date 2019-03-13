//
// Created by urbschaj on 25.02.19.
//

#include "resultparser.h"
#include <boost/regex.hpp>

namespace ppmac::parser {

	namespace detail {

		bool CheckForError(const std::string& str) {
			auto pos = str.find("error");
			return pos != std::string::npos;
		}

		void ThrowIfError(const std::string& str) {
			if(CheckForError(str)) {
				THROW_RUNTIME_ERROR("response contained error '{}'", str);
			}
		}

		std::experimental::optional<std::pair<int32_t, std::string>> GetError(const std::string& str) {
			boost::regex rgx(R"(error\W*#(\d+):\W*(.*))");
			boost::smatch what;
			if(boost::regex_search(str, what, rgx)) {
				int32_t errorCode = IntParser::convert(what[1]);
				std::string errorString = what[2];
				return std::pair<int32_t, std::string>{errorCode, errorString};
			}
			return std::experimental::optional<std::pair<int32_t, std::string>>{};
		}
	}

	CoordAxisDefinitionInfo ParseCoordAxisQueryResult(const std::string& str) {
		boost::regex rgx(R"((?:&(\d+))?#(\d+)->(\w+))");
		boost::smatch what;
		if(boost::regex_search(str, what, rgx)) {
			int32_t coordId = 0;
			if(what[1].matched) {
				coordId = IntParser::convert(what[1]);
			}
			auto motorId = IntParser::convert(what[2]);
			auto axisName = what[3];
			return CoordAxisDefinitionInfo{ axisName, coordId, motorId };
		}
		return CoordAxisDefinitionInfo{};
	}

	std::vector<MultiAxisMoveInfo> ParseMultiAxisMove(const std::string& str) {
		std::vector<MultiAxisMoveInfo> out;
		boost::regex rgx(R"(([a-zA-Z])([+-]?\d+(?:(?:\.\d+))?)?)");
		boost::smatch what;
		std::string::const_iterator start = str.begin();
		std::string::const_iterator end = str.end();
		while(boost::regex_search(start, end, what, rgx)) {
			std::string axisName = what[1];
			if(!what[2].matched) {
				THROW_RUNTIME_ERROR("axis '{}' has no position definition", axisName);
			}
			int32_t axisNumber = AvailableAxis::MapNameToAxis(axisName[0]);
			double pos = DoubleParser::convert(what[2]);
			out.push_back(MultiAxisMoveInfo{ axisNumber, pos });
			start = what[0].second;
		}
		std::sort(out.begin(), out.end(), [](auto& lhs, auto& rhs){
			return lhs.axis < rhs.axis;
		});
		auto it = std::adjacent_find( out.begin(), out.end(), [](auto& lhs, auto& rhs){
			return lhs.axis == rhs.axis;
		});
		if(it != out.end()) {
			THROW_RUNTIME_ERROR("multiple definitions of axis '{}'", AvailableAxis::MapAxisToChar(it->axis));
		}
		return out;
	}
}