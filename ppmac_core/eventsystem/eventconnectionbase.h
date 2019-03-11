#pragma once

#include <cstddef>

namespace ppmac::es {

	class EventBase;
	class ConnectionBase
	{
	public:
		ConnectionBase()
			: enabled(true)
		{}

		virtual ~ConnectionBase() { };
		virtual uint64_t EventID() const = 0;
		virtual void Execute(const EventBase *base) = 0;
		void Enable(bool en){ 
			enabled = en; 
		}
		bool IsEnabled() const {
			return enabled;
		}
	private:
		bool enabled;
	};
}
