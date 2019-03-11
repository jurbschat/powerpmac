#pragma once

#include "event.h"
#include <unordered_map>
#include <vector>

namespace ppmac::es {

	class EventCache
	{
	public:
		EventCache() {}

		~EventCache() {
			for (auto it : cache) {
				for (auto elem : it.second) {
					delete elem;
				}
			}
		}

		template<typename T>
		T *FetchEvent() {
			auto& list = cache[ClassID<T>::ID];
			if (list.empty()) {
				list.push_back(new T());
			}
			auto elem = list.back();
			list.pop_back();
			return static_cast<T*>(elem);
		}

		void ReturnEvent(EventBase* event) {
			auto& list = cache[event->EventID()];
			list.push_back(event);
		}

		static EventCache& GetGlobalEventCache() {
			static EventCache instance;
			return instance;
		}
	private:
		std::unordered_map<uint64_t, std::vector<EventBase*>> cache;
	};
}