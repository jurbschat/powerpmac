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

	inline std::exception_ptr GetNestedExceptionPtr(const std::exception& e) {
		auto nested = dynamic_cast<std::nested_exception const*>(&e);
		if(nested) {
			return nested->nested_ptr();
		}
		return nullptr;
	}

	inline void WriteException(fmt::memory_buffer& buffer, std::exception_ptr eptr, int32_t indent = 0, char continuation = 0)
	{
		// subtract two if we have a continuation character
		int spaces = indent - (continuation != 0 ? 2 : 0);
		// if we have a continuation character append it
		std::string indentStr = std::string(spaces, ' ') + (continuation != 0 ? "> " : "");
		try {
			std::rethrow_exception(eptr);
		} catch(...) {
			bool isCause = false;
			auto px = std::current_exception();
			while (px) {
				if(isCause) {
					fmt::format_to(buffer, "\n");
				}
				try {
					std::rethrow_exception(px);
				}
				catch (const RuntimeError & e) {
					fmt::format_to(buffer, "{}{}RuntimeError: [{}:{}] {}", indentStr, (isCause ? "<because> " : ""), e.GetFile(), e.GetLine(), e.what());
					px = GetNestedExceptionPtr(e);
				}
				catch (const std::bad_exception & e) {
					fmt::format_to(buffer, "{}{}std::bad_exception: {}", indentStr, (isCause ? "<because> " : ""), e.what());
					px = GetNestedExceptionPtr(e);
				}
				catch (const std::exception& e) {
					fmt::format_to(buffer, "{}{}std::exception: {}", indentStr, (isCause ? "<because> " : ""), e.what());
					px = GetNestedExceptionPtr(e);
				}
				catch (...) {
					fmt::format_to(buffer, "{}{}oops... unknown exception :(", indentStr, (isCause ? "<because> " : ""));
					break;
				}
				isCause = true;
			}
		}
	}

	inline std::string StringifyException(std::exception_ptr eptr, int32_t indent = 0, char continuation = 0)
	{
		fmt::memory_buffer buffer;
		WriteException(buffer, eptr, indent, continuation);
		return fmt::to_string(buffer);
	}
}

#pragma GCC diagnostic push

#endif //POWERPMAC_THROW_H

