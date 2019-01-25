//
// Created by urbschaj on 25.01.19.
//

#ifndef POWERPMAC_TANGOUTIL_H
#define POWERPMAC_TANGOUTIL_H

#include "exception.h"
#include <sstream>
#include <tango.h>

namespace tu {

	void TranslateException(const ppmac::RuntimeError& ex) {
		std::stringstream ss;
		ss << ex.GetFunction() << "(" << ex.GetFile() << ":" << ex.GetLine() << ")";
		Tango::Except::throw_exception("core errro", ex.what(), ss.str());
	};
}

#endif //POWERPMAC_TANGOUTIL_H
