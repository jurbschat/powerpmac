//
// Created by urbschaj on 07.03.19.
//

#include "threading.h"
#include <sys/prctl.h>

namespace ppmac {

	void SetThisThreadName(const std::string& name) {
		//prctl(PR_SET_NAME, name.c_str(), 0, 0, 0);
		//pthread_setname_np(pthread_self(), name.c_str());
	}
}
