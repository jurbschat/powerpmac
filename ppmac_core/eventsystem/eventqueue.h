#pragma once

#include "event.h"
#include "eventcache.h"
#include "eventconnection.h"
#include "recursivecheck.h"

#include <vector>
#include <unordered_map>
#include <memory>
#include <algorithm>


namespace ppmac::es {

	class EventQueue
	{
	public:
		EventQueue();
		EventQueue(EventCache* cache);
		~EventQueue();
		template<typename T, typename U>
		ConnectionBase* Connect(T* listener, void (T::*fctSig)(const U& e));
		void Disconnect(ConnectionBase* connection);
		template<typename T>
		void PostEvent(const T& e);
		void ExecuteEvent(const EventBase& event);
		void ExecuteEvent(const EventBase* event);
		void ProcessQueue();

	private:
		void HandleChanges();
		ConnectionBase* ConnectInternal(std::unique_ptr<ConnectionBase> connection);
		void DisconnectInternal(ConnectionBase* connection);
		void ProcessEvent(const EventBase* event);

		EventCache* cache;
		RecursiveCheck isProcessingEvent;
		
		std::unordered_map<uint64_t, std::vector<std::unique_ptr<ConnectionBase>>> eventListener;
		std::vector<std::unique_ptr<ConnectionBase>> newListener;
		std::vector<ConnectionBase*> removedListeners;

		std::vector<EventBase*> events;
		std::vector<EventBase*> newEvents;
	};

	template<typename T, typename U>
	ConnectionBase* EventQueue::Connect(T* listener, void (T::*fctSig)(const U& e))
	{
		auto connection = std::make_unique<TypedConnection<T, U>>(listener, fctSig);

		if (isProcessingEvent) {
			auto conPtr = connection.get();
			newListener.push_back(std::move(connection));
			return conPtr;
		}

		return ConnectInternal(std::move(connection));
	}

	template<typename T>
	void EventQueue::PostEvent(const T& e)
	{
		auto event = cache->FetchEvent<T>();
		*event = e;

		auto pred = [](const EventBase* val, const EventBase* elem)
		{
			return val->GetProcessOrder() < elem->GetProcessOrder();
		};

		if (isProcessingEvent) 
		{
			newEvents.insert(std::upper_bound(newEvents.begin(), newEvents.end(), event, pred), event);
			return;
		}
		events.insert(std::upper_bound(events.begin(), events.end(), event, pred), event);
	}

}