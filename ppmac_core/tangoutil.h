//
// Created by urbschaj on 25.01.19.
//

#ifndef POWERPMAC_TANGOUTIL_H
#define POWERPMAC_TANGOUTIL_H

#include "exception.h"

namespace tu {

	void TranslateException(const ppmac::RuntimeError& ex);
	float ParseFloat(const std::string& str);
	double ParseDouble(const std::string& str);
	uint32_t ParsePmacHex32(const std::string &str);
	uint64_t ParsePmacHex64(const std::string &str);
}

#endif //POWERPMAC_TANGOUTIL_H
