//
// Created by urbschaj on 07.03.19.
//

#include <thread>

#ifndef POWERPMAC_THREADING_H
#define POWERPMAC_THREADING_H

namespace ppmac {

	void SetThisThreadName(const std::string& name);

	template<typename T>
	std::thread MakeThread(const std::string& name, T t) {
		auto runner = [&name, t](){
			SetThisThreadName(name);
			t();
		};
		return std::thread(runner);
	}
}

#endif //POWERPMAC_THREADING_H
