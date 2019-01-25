//
// Created by urbschaj on 21.01.19.
//
#include <chrono>
#include <experimental/optional>

#ifndef POWERPMAC_STOPWATCH_H
#define POWERPMAC_STOPWATCH_H

namespace ppmac {

	class StopWatch {
	public:
		using TimeUnit = std::chrono::milliseconds;
		using Clock = std::chrono::high_resolution_clock;
		using TimePoint = std::experimental::optional<std::chrono::time_point<Clock>>;

		StopWatch(bool _start = false) noexcept {
			if(_start) {
				start();
			}
		}

		void start() noexcept {
			started = Clock::now();
			stopped = TimePoint{};
		}

		void stop() noexcept {
			stopped = Clock::now();
		}

		TimeUnit elapsed() noexcept {
			if(started && stopped) {
				return std::chrono::duration_cast<TimeUnit>(*stopped - *started);
			}
			else if(started) {
				return std::chrono::duration_cast<TimeUnit>(Clock::now() - *started);
			}
			return TimeUnit{};
		}

		void reset() noexcept {
			started = TimePoint{};
			stopped = TimePoint{};
		}

	private:
		TimePoint started;
		TimePoint stopped;
	};

}

#endif //POWERPMAC_STOPWATCH_H
