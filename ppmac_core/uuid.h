//
// Created by urbschaj on 18.02.19.
//

#ifndef POWERPMAC_UUID_H
#define POWERPMAC_UUID_H

#include <string>

namespace ppmac::uuid {

	const std::string& GetProgramLifetimeUUID();
	std::string GetUUID();

}


#endif //POWERPMAC_UUID_H
