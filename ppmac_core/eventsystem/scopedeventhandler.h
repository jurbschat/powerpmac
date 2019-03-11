#pragma once

#include "scopedeventconnection.h"
#include "globaleventsystem.h"
#include "../common/log/logging.h"
#include <vector>

namespace ppmac::es {

	class ScopedEventHandler
	{
	public:
		ScopedEventHandler(EventQueue& queue) 
			: queue(queue)
		{}

		~ScopedEventHandler() {
			connections.clear();
		}

		template<typename T, typename U>
		void RegisterEvent(T* listener, void (T::*fctSig)(const U& e)) {
			connections.push_back(ScopedEventConnection(queue, listener, fctSig));
		}

		template<typename T, typename U>
		void RegisterGlobalEvent(T* listener, void (T::*fctSig)(const U& e)) {
			connections.push_back(ScopedEventConnection(GlobalEventSystem::GetInstance(), listener, fctSig));
		}

		void RegisterConnection(ScopedEventConnection con) {
			connections.push_back(std::move(con));
		}

		void ClearRegisteredEvents() {
			connections.clear();
		}

		const std::vector<ScopedEventConnection>& GetEventConnections() const
		{
			return connections;
		}

		std::vector<ScopedEventConnection>& GetEventConnections()
		{
			return connections;
		}

		void EnableAllConnections(bool enable) {
			for (auto& c : connections) {
				c.Get()->Enable(enable);
			}
		}
	private:
		EventQueue& queue;
		std::vector<ScopedEventConnection> connections;
	};


}
