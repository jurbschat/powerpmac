//
// Created by urbschaj on 25.01.19.
//

#include "exception.h"
#include <string>
#include <fmt/format.h>

#ifndef POWERPMAC_THROW_H
#define POWERPMAC_THROW_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"

// get an unique name so he have no shadowing warning
#define THROW_RUNTIME_ERROR(fmtString, ...)                                  \
{                                                                            \
	std::string ghdndEMR = fmt::format(fmtString, ##__VA_ARGS__);            \
	throw ::ppmac::RuntimeError(__FILE__, __FUNCTION__, __LINE__, ghdndEMR); \
}

#pragma GCC diagnostic push

#endif //POWERPMAC_THROW_H

