#pragma once

#include "eventqueue.h"
#include <mutex>

namespace ppmac::es {

	class TSEventSystem
	{
	public:
		TSEventSystem();
		void ProcessQueue();
		template<typename T, typename U>
		ConnectionBase* Connect(T* listener, void (T::*fctSig)(const U& e)) {
			std::lock_guard<std::recursive_mutex> lock(mutex);
			return eventQueue.Connect(listener, fctSig);
		}
		void Disconnect(ConnectionBase* connection);
		template<typename T>
		void PostEvent(const T& event) {
			std::lock_guard<std::recursive_mutex> lock(mutex);
			eventQueue.PostEvent(event);
		}
		
	private:
		TSEventSystem(const TSEventSystem &other) = delete;
		TSEventSystem operator=(const TSEventSystem &other) = delete;

		EventCache cache;
		EventQueue eventQueue;
		std::recursive_mutex mutex;
	};


}