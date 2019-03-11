//
// Created by urbschaj on 08.03.19.
//

#ifndef POWERPMAC_EVENTSYSTEM_H
#define POWERPMAC_EVENTSYSTEM_H

#include "libs/blockingconcurrentqueue.h"
#include <memory>

namespace ppmac::es {

	enum class EventType {

	};

	struct EventBase {};

	template<typename T>
	struct Event : EventBase {
		T data;
	};

	class EventSystem {
	public:
		void Process() {
			for (auto& f : events) {
				f();
			}
		}

		template<typename T, typename Callback>
		void RegisterEvent(std::function<void()> cb) {
			cb()
		}
		template<typename T>
		void AddEvent(T event) {
			events.push_back(std::make_unique<Event>(event));
		}
	private:
		moodycamel::BlockingConcurrentQueue<std::function<void()>> events;
	};

}

#endif //POWERPMAC_EVENTSYSTEM_H
