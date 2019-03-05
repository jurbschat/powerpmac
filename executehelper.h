//
// Created by urbschaj on 05.03.19.
//

#ifndef POWERPMAC_EXECUTEHELPER_H
#define POWERPMAC_EXECUTEHELPER_H

#include "resultparser.h"

namespace tu {
	template<typename T>
	T ExecuteCommand(ppmac::CoreInterface& ci, const std::string& str) {
		auto result = ci.ExecuteCommand(str);
		auto out = ppmac::parser::parser_traits<T>::convert(result);
		return out;
	}
}

#endif //POWERPMAC_EXECUTEHELPER_H
