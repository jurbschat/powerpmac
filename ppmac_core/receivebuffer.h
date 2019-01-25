//
// Created by urbschaj on 23.01.19.
//

#include "config.h"
#include "libs/span.hpp"

#include <vector>
#include <string>
#include <experimental/optional>

#ifndef POWERPMAC_RECEIVEBUFFER_H
#define POWERPMAC_RECEIVEBUFFER_H

namespace ppmac {

	class ReceiveBuffer {
	public:
		ReceiveBuffer();
		void AddData(stdext::span<char> data);
		std::experimental::optional<std::string> ExtractMessage();
		bool HasMessage();
		void Clear();
	private:
		std::vector<char> buffer;
	};

}

#endif //POWERPMAC_RECEIVEBUFFER_H
