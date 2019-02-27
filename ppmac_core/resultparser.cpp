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
}