//
// Created by urbschaj on 14.01.19.
//

#ifndef POWERPMAC_CONFIG_H
#define POWERPMAC_CONFIG_H

namespace ppmac {
	using byte = unsigned char;
	constexpr char RESPONSE_TERMINATOR = 0x06;
	const int MAX_MOTORS = 256;
	const int MAX_PORTS = 256;
}

#endif //POWERPMAC_CONFIG_H
