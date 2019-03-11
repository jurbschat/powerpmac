#include "eventqueue.h"

namespace ppmac::es {

	EventQueue::EventQueue() 
		: EventQueue(&EventCache::GetGlobalEventCache())
	{}

	EventQueue::EventQueue(EventCache* cache) 
		: cache(cache)
	{}

	EventQueue::~EventQueue()
	{
		for (auto event : events) {
			cache->ReturnEvent(event);
		}
		events.clear();
		for (auto event : newEvents) {
			cache->ReturnEvent(event);
		}
		newEvents.clear();
	}

	void EventQueue::Disconnect(ConnectionBase* conID)
	{
		if (isProcessingEvent) {
			removedListeners.push_back(conID);
			return;
		}

		DisconnectInternal(conID);
	}

	void EventQueue::ExecuteEvent(const EventBase* event)
	{
		isProcessingEvent.Push();
		ProcessEvent(event);
		isProcessingEvent.Pop();
		HandleChanges();
	}

	void EventQueue::ExecuteEvent(const EventBase& event)
	{
		ExecuteEvent(&event);
	}

	void EventQueue::ProcessQueue()
	{
		isProcessingEvent.Push();
		for (auto event : events) {
			ProcessEvent(event);
			cache->ReturnEvent(event);
		}
		events.clear();
		isProcessingEvent.Pop();
		HandleChanges();
	}

	void EventQueue::HandleChanges()
	{
		if (isProcessingEvent)
			return;

		for (auto& con : newListener) {
			ConnectInternal(std::move(con));
		}
		newListener.clear();

		for (auto con : removedListeners) {
			DisconnectInternal(con);
		}
		removedListeners.clear();


		auto pred = [](const EventBase* val, const EventBase* elem) {
			return val->GetProcessOrder() < elem->GetProcessOrder();
		};

		for (auto evnt : newEvents) {
			events.insert(std::upper_bound(events.begin(), events.end(), evnt, pred), evnt);
		}

		newEvents.clear();
	}

	ConnectionBase* EventQueue::ConnectInternal(std::unique_ptr<ConnectionBase> connection)
	{
		auto eventID = connection->EventID();
		auto conPtr = connection.get();
		eventListener[eventID].push_back(std::move(connection));
		return conPtr;
	}

	void EventQueue::DisconnectInternal(ConnectionBase* connection)
	{
		auto it = eventListener.find(connection->EventID());
		if (it == eventListener.end()) {
			//LOG_WARN("invalid disconnect, event type never registered");
			return;
		}
		if (it->second.empty()) {
			//LOG_WARN("invalid disconnect, all events for type already disconnected");
		}

		auto& list = eventListener[connection->EventID()];
		auto prevSize = list.size();
		list.erase(std::remove_if(list.begin(), list.end(), [connection](const std::unique_ptr<ConnectionBase>& con)
		{
			return connection == con.get();
		}), std::end(list));

		if (prevSize == list.size()) {
			//LOG_WARN("invalid disconnect, event was not registered");
		}

	}

	void EventQueue::ProcessEvent(const EventBase* event)
	{
		isProcessingEvent.Push();
		auto listeners = eventListener.find(event->EventID());
		if (listeners != std::end(eventListener)) {
			std::vector<std::unique_ptr<ConnectionBase>> &list = listeners->second;
			for (auto it = std::begin(list); it != std::end(list); it++)
			{
				std::unique_ptr<ConnectionBase>& connection = *it;
				if(connection->IsEnabled()) {
					connection->Execute(event);
				}
			}
		}
		isProcessingEvent.Pop();
	}
}