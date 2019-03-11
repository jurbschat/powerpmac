#include "globaleventsystem.h"

namespace ppmac::es {

	TSEventSystem::TSEventSystem()
		: eventQueue(&cache)
	{}

	void TSEventSystem::ProcessQueue() {
		std::lock_guard<std::recursive_mutex> lock(mutex);
		ProcessQueue();
	}

	void TSEventSystem::Disconnect(ConnectionBase* connection)
	{
		std::lock_guard<std::recursive_mutex> lock(mutex);
		Disconnect(connection);
	}

}