//
// Created by urbschaj on 31.01.19.
//

#include "tangoutil.h"
#include "resultparser.h"

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

	uint32_t ParsePmacHex32(const std::string &str) {
		return ppmac::parser::Hex32Parser::convert(str);
	}

	uint64_t ParsePmacHex64(const std::string &str) {
		return ppmac::parser::Hex64Parser::convert(str);
	}

}

