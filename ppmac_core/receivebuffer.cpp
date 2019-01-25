//
// Created by urbschaj on 23.01.19.
//

#include "receivebuffer.h"
#include <boost/algorithm/string.hpp>

namespace ppmac {

	ReceiveBuffer::ReceiveBuffer() {}

	void ReceiveBuffer::AddData(stdext::span<char> data) {
		buffer.insert(buffer.end(), data.begin(), data.end());
	}

	std::experimental::optional<std::string> ReceiveBuffer::ExtractMessage() {
		auto it = std::find(buffer.begin(), buffer.end(), RESPONSE_TERMINATOR);
		if(it != buffer.end()) {
			std::string output(buffer.begin(), it);
			buffer.erase(buffer.begin(), ++it); // erase including the terminator
			boost::algorithm::trim_left(buffer);
			return output;
		}
		return std::experimental::optional<std::string>{};
	}

	bool ReceiveBuffer::HasMessage() {
		return std::find(buffer.begin(), buffer.end(), RESPONSE_TERMINATOR) != buffer.end();
	}

	void ReceiveBuffer::Clear() {
		buffer.clear();
	}
}
