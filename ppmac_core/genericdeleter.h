//
// Created by urbschaj on 14.01.19.
//

#include "libs/slot_map.h"
#include "config.h"

#ifndef POWERPMAC_GENERICDELETER_H
#define POWERPMAC_GENERICDELETER_H

namespace ppmac {

	class genericdeleter
	{
	public:
		genericdeleter() noexcept {}
		genericdeleter(std::function<void(HandleType handle)> deleter) noexcept
			: deleter(deleter)
		{}
		genericdeleter(genericdeleter&& other) noexcept
		{
			deleter = std::move(other.deleter);
		}
		void operator()(HandleType handle) const {
			if(deleter) {
				deleter(handle);
			}
		}
		genericdeleter& operator=(genericdeleter&& other) noexcept {
			deleter = std::move(other.deleter);
			return *this;
		}
		genericdeleter& operator=(const genericdeleter&) = delete;
		genericdeleter(const genericdeleter&) = delete;
	private:
		std::function<void(HandleType handle)> deleter;
	};

}

#endif //POWERPMAC_GENERICDELETER_H
