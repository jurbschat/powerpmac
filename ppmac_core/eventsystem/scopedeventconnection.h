#pragma once

#include "eventconnectionbase.h"
#include "eventqueue.h"

#include <memory>
#include <functional>

namespace ppmac::es {

	class ScopedEventConnection
	{
	public:
		template<typename Queue, typename T, typename U>
		ScopedEventConnection(Queue& queue, T* listener, void (T::*fctSig)(const U& e))
			: handle(queue.Connect(listener, fctSig), [&queue](ConnectionBase* con) { queue.Disconnect(con); })
		{}

		template<typename Queue>
		ScopedEventConnection(Queue& queue, ConnectionBase* connection)
			: handle(connection, [&queue](ConnectionBase* con) { queue.Disconnect(con); })
		{}

		ConnectionBase* Get() {
			return handle.get();
		}
	private:
		std::unique_ptr<ConnectionBase, std::function<void(ConnectionBase*)>> handle;
	};


}