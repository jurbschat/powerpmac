//
// Created by urbschaj on 25.01.19.
//

#ifndef POWERPMAC_TANGOUTIL_H
#define POWERPMAC_TANGOUTIL_H

#include "ppmac_core/exception.h"

namespace tu {

	void TranslateException(const ppmac::RuntimeError& ex);
	float ParseFloat(const std::string& str);
	double ParseDouble(const std::string& str);
	int32_t ParseInt32(const std::string &str);
	uint32_t ParseUInt32(const std::string &str);
	int64_t ParseInt64(const std::string &str);
	uint64_t ParseUInt64(const std::string &str);
	uint32_t ParsePmacHex32(const std::string &str);
	uint64_t ParsePmacHex64(const std::string &str);

	void SetStringValue(char **ptr, const std::string& value, bool forceNoDelete = false);

	template<class VarType, class... Params>
	bool IsOneOf(const VarType& needle, const Params&... params)
	{
		return ((needle == params) || ...);
	}
}

#endif //POWERPMAC_TANGOUTIL_H
