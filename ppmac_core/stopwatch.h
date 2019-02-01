//
// Created by urbschaj on 21.01.19.
//
#include <chrono>
#include <experimental/optional>

#ifndef POWERPMAC_STOPWATCH_H
#define POWERPMAC_STOPWATCH_H

namespace ppmac {

	template<typename TimeUnit = std::chrono::milliseconds, typename Clock = std::chrono::high_resolution_clock>
	class StopWatch {
	public:
		//using TimeUnit = std::chrono::milliseconds;
		//using Clock = std::chrono::high_resolution_clock;
		using TimePoint = std::experimental::optional<std::chrono::time_point<Clock>>;
		using DoubleDuration = std::chrono::duration<double>;

		StopWatch(bool _start = false) noexcept {
			if(_start) {
				Start();
			}
		}

		void Start() noexcept {
			if(!started) {
				started = Clock::now();
			}
			stopped = TimePoint{};
		}

		void Stop() noexcept {
			if(!stopped) {
				stopped = Clock::now();
			}
		}

		void Restart() {
			started = Clock::now();
			stopped = TimePoint{};
		}

		void Reset() noexcept {
			started = TimePoint{};
			stopped = TimePoint{};
		}

		template<typename ReportTu = TimeUnit>
		ReportTu Elapsed() noexcept {
			if(started && stopped) {
				auto duration = *stopped - *started;
				return std::chrono::duration_cast<ReportTu>(duration);
			}
			else if(started) {
				auto duration = Clock::now() - *started;
				return std::chrono::duration_cast<ReportTu>(duration);
			}
			return std::chrono::seconds::zero();
		}

		/*template<>
		double Elapsed<double>() noexcept {
			if(started && stopped) {
				auto duration = *stopped - *started;
				return std::chrono::duration_cast<DoubleDuration>(duration).count();
			}
			else if(started) {
				auto duration = Clock::now() - *started;
				return std::chrono::duration_cast<DoubleDuration>(duration).count();
			}
			return 0;
		}*/

		template<typename TU>
		static double ToDouble(TU t) {
			return std::chrono::duration_cast<DoubleDuration>(t).count();
		}

		TimePoint GetStarted() {
			return started;
		}

		TimePoint GetStopped() {
			return stopped;
		}

	private:
		TimePoint started;
		TimePoint stopped;
	};

}

#endif //POWERPMAC_STOPWATCH_H
