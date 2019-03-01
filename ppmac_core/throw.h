//
// Created by urbschaj on 25.01.19.
//

// #pragma GCC system_header

#include "exception.h"
#include "utility.h"
#include <string>
#include <fmt/format.h>

#ifndef POWERPMAC_THROW_H
#define POWERPMAC_THROW_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpragmas"
#pragma GCC diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"

#define __SHORT_FILE__ (ppmac::file_name(__FILE__))

// get an unique name so he have no shadowing warning
#define THROW_RUNTIME_ERROR(fmtString, ...)                                  \
{                                                                            \
	std::string ghdndEMR = fmt::format(fmtString, ##__VA_ARGS__);            \
	throw ::ppmac::RuntimeError(__SHORT_FILE__, __FUNCTION__, __LINE__, ghdndEMR); \
}

#define RETHROW_RUNTIME_ERROR(fmtString, ...)                                   \
{                                                                               \
	std::string GHdndEMR = fmt::format(fmtString, ##__VA_ARGS__);               \
	std::throw_with_nested(                                                     \
			::ppmac::RuntimeError(__SHORT_FILE__, __FUNCTION__, __LINE__, GHdndEMR)   \
	);                                                                          \
}

namespace ppmac {

	std::exception_ptr GetNestedExceptionPtr(const std::exception& e);
	void WriteException(fmt::memory_buffer& buffer, std::exception_ptr eptr, int32_t indent = 0, char continuation = 0);
	std::string StringifyException(std::exception_ptr eptr, int32_t indent = 0, char continuation = 0);

}

#pragma GCC diagnostic push

#endif //POWERPMAC_THROW_H

