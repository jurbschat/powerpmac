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
			: interval(interval),
			lastUpdate{TimePoint{} + interval},
			callback(callback),
			expired(false),
			started(false)
		{}
		std::chrono::microseconds interval;
		TimePoint lastUpdate;
		std::function<void()> callback;
		bool expired;
		bool started;
	};

	// the timers will always be updates from largest to smallest
	class IntervalTimer {
	public:
		IntervalTimer()
			: lowestUpdateInterval{std::chrono::milliseconds{100}},
			  fuzzyOffset{0}
		{}

		IntervalTimer(float fuzzyOffset)
			: lowestUpdateInterval{std::chrono::milliseconds{100}},
			fuzzyOffset{fuzzyOffset}
		{}

		HandleType AddTimer(UpdateTime ut) {
			auto handle = updateTimes.insert(ut);
			UpdateMinInterval();
			return handle;
		}
		void SetFuzzyOffset(float offset) {
			fuzzyOffset = offset;
		}
		void RemoveTimer(HandleType handle) {
			updateTimes.erase(handle);
			UpdateMinInterval();
		}
		void Update() {
			auto now = std::chrono::high_resolution_clock::now();
			for(auto& ut : updateTimes) {
				if(!ut.started) {
					ut.lastUpdate = now;
					ut.started = true;
				}
				// we offset every update by X% of its interval.
				// if we have intervals of 1000ms, 100ms, 10ms, 1ms they would all execute on
				// 1s, we try to mitigate those spikes though the offset
				auto timeOffset = ut.interval * fuzzyOffset;
				if(now - ut.lastUpdate >= ut.interval + timeOffset) {
					if(ut.callback) {
						ut.expired = true;
						ut.callback();
					}
					ut.lastUpdate = now;
				}
			}
		}

		void RemoveExpired() {
			for(auto it = updateTimes.begin(); it != updateTimes.end(); /* empty */) {
				if(it->expired == true) {
					it = updateTimes.erase(it);
				} else {
					it++;
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
		float fuzzyOffset;
	};
}

#endif //POWERPMAC_INTERVALTIMER_H
