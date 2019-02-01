//
// Created by urbschaj on 24.01.19.
//

#include "utility.h"
#include <memory>
#include <string>
#include <array>

namespace ppmac {

	std::string ExecuteWithReturn(const char* cmd) {
		std::array<char, 128> buffer;
		std::string result;
		std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
		if (!pipe) {
			return "<unable to execute>";
		}
		while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
			result += buffer.data();
		}
		return result;
	}

}