//
// Created by urbschaj on 13.03.19.
//

#ifndef POWERPMAC_SCOPEDSIGNAL_H
#define POWERPMAC_SCOPEDSIGNAL_H

#include "libs/sigs.h"
#include <functional>

namespace ppmac {
	struct ScopedSignal {
		ScopedSignal() {}
		ScopedSignal(sigs::Connection c, std::function<void(sigs::Connection)> d)
				: conn(c), deleter(d)
		{}
		ScopedSignal(const ScopedSignal& c) = delete;
		ScopedSignal(ScopedSignal&& c) = default;
		ScopedSignal& operator=(const ScopedSignal& c) = delete;
		ScopedSignal& operator=(ScopedSignal&& c) = default;
		~ScopedSignal() {
			reset();
		}
		void reset() {
			if(deleter) {
				deleter(conn);
			}
			conn = nullptr;
			deleter = nullptr;
		}
		sigs::Connection conn;
		std::function<void(sigs::Connection)> deleter;
	};
}

#endif //POWERPMAC_SCOPEDSIGNAL_H
