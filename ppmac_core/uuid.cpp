//
// Created by urbschaj on 18.02.19.
//

#include "uuid.h"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.
#include <sstream>

namespace ppmac::uuid {

	const std::string& GetProgramLifetimeUUID() {
		static std::string uuid = GetUUID();
		return uuid;
	}
	std::string GetUUID() {
		std::stringstream ss;
		ss << boost::uuids::random_generator()();
		return ss.str();
	}

}
