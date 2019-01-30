//
// Created by urbschaj on 30.01.19.
//

#ifndef POWERPMAC_INTERVALTIMER_H
#define POWERPMAC_INTERVALTIMER_H

#include "libs/slot_map.h"
#include <chrono>
#include <functional>

namespace ppmac {

	struct UpdateTime {
		using TimePoint = std::chrono::high_resolution_clock::time_point;
		UpdateTime(std::chrono::microseconds interval, std::function<void()> callback)
			: interval(interval), lastUpdate{TimePoint{}}, callback(callback)
		{}
		std::chrono::microseconds interval;
		TimePoint lastUpdate;
		std::function<void()> callback;
	};

	// the timers will always be updates from largest to smallest
	class IntervalTimer {
	public:
		HandleType AddTimer(UpdateTime ut) {
			auto handle = updateTimes.insert(ut);
			UpdateMinInterval();
			return handle;
		}
		void RemoveTimer(HandleType handle) {
			updateTimes.erase(handle);
			UpdateMinInterval();
		}
		void Update() {
			auto now = std::chrono::high_resolution_clock::now();
			for(auto& ut : updateTimes) {
				if(now - ut.lastUpdate >= ut.interval) {
					if(ut.callback) {
						ut.callback();
					}
					ut.lastUpdate = now;
				}
			}
		}
		std::chrono::microseconds GetMinInterval() const {
			return lowestUpdateInterval;
		}
	private:
		void UpdateMinInterval() {
			if(!updateTimes.empty()) {
				// sort largest first
				std::sort(updateTimes.begin(), updateTimes.end(), [](auto& lhs, auto& rhs){
					return lhs.interval > rhs.interval;
				});
				auto last = --updateTimes.end();
				lowestUpdateInterval = last->interval;
			} else {
				lowestUpdateInterval = std::chrono::milliseconds{100};
			}
		}
		std::chrono::microseconds lowestUpdateInterval;
		stdext::slot_map<UpdateTime> updateTimes;
	};
}

#endif //POWERPMAC_INTERVALTIMER_H
