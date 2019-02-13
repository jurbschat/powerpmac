//
// Created by urbschaj on 31.01.19.
//

#include "tangoutil.h"
#include "ppmac_core/resultparser.h"

#include <sstream>
#include <tango.h>

namespace tu {

	void TranslateException(const ppmac::RuntimeError& ex) {
		std::stringstream ss;
		ss << ex.GetFunction() << "(" << ex.GetFile() << ":" << ex.GetLine() << ")";
		Tango::Except::throw_exception("core errro", ex.what(), ss.str());
	};

	float ParseFloat(const std::string& str) {
		return ppmac::parser::FloatParser::convert(str);
	}

	double ParseDouble(const std::string& str) {
		return ppmac::parser::DoubleParser::convert(str);
	}

	int32_t ParseInt32(const std::string &str) {
		return ppmac::parser::IntParser::convert(str);
	}

	uint32_t ParseUInt32(const std::string &str) {
		return ppmac::parser::UIntParser::convert(str);
	}

	int64_t ParseInt64(const std::string &str) {
		return ppmac::parser::Int64Parser::convert(str);
	}

	uint64_t ParseUInt64(const std::string &str) {
		return ppmac::parser::UInt64Parser::convert(str);
	}

	uint32_t ParsePmacHex32(const std::string &str) {
		return ppmac::parser::Hex32Parser::convert(str);
	}

	uint64_t ParsePmacHex64(const std::string &str) {
		return ppmac::parser::Hex64Parser::convert(str);
	}

	void SetStringValue(char **ptr, const std::string& value, bool forceNoDelete)
	{
		if(*ptr == nullptr || forceNoDelete) {
			*ptr = CORBA::string_dup(value.c_str());
		}  else {
			CORBA::string_free(*ptr);
			*ptr = CORBA::string_dup(value.c_str());
		}
	}

}

