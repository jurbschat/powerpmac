//
// Created by urbschaj on 14.01.19.
//

#include <utility>

#ifndef POWERPMAC_CONFIG_H
#define POWERPMAC_CONFIG_H

namespace ppmac {
	using byte = unsigned char;
	constexpr char RESPONSE_TERMINATOR = 0x06;
	const int MAX_MOTORS = 256;
	const int MAX_PORTS = 256;
	const int MAX_PLC = 256;
	const int MAX_COORDS = 256;
	using HandleType = std::pair<unsigned, unsigned>;
	static const ppmac::HandleType INVALID_HANDLE = ppmac::HandleType{0xFFFFFFFF, 0xFFFFFFFF};
	namespace config {
		extern bool dumpAllCommunication;
	}
}

#endif //POWERPMAC_CONFIG_H
