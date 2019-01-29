//
// Created by urbschaj on 22.01.19.
//

#ifndef POWERPMAC_EXCEPTION_H
#define POWERPMAC_EXCEPTION_H

#include <exception>
#include <string>

namespace ppmac {

	class RuntimeError : public std::exception {
	public:
		RuntimeError(const char* file, const char* function, int line, std::string msg)
			: file(file), function(function), line(line), msg(msg)
		{}

		const char* GetFile() const noexcept {
			return file;
		}
		const char* GetFunction() const noexcept {
			return function;
		}
		int GetLine() const noexcept {
			return line;
		}

		const char* what() const noexcept {
			return msg.c_str();
		}

	private:
		const char* file;
		const char* function;
		int line;
		std::string msg;
	};

}

#endif //POWERPMAC_EXCEPTION_H
