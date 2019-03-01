//
// Created by urbschaj on 01.03.19.
//

#include "throw.h"

namespace ppmac {

	std::exception_ptr GetNestedExceptionPtr(const std::exception& e) {
		auto nested = dynamic_cast<std::nested_exception const*>(&e);
		if(nested) {
			return nested->nested_ptr();
		}
		return nullptr;
	}

	void WriteException(fmt::memory_buffer& buffer, std::exception_ptr eptr, int32_t indent, char continuation)
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

	std::string StringifyException(std::exception_ptr eptr, int32_t indent, char continuation)
	{
		fmt::memory_buffer buffer;
		WriteException(buffer, eptr, indent, continuation);
		return fmt::to_string(buffer);
	}
}