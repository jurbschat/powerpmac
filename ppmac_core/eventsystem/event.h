#pragma once

#include "eventbase.h"
#include "classid.h"

namespace ppmac::es {

	template<typename T, int _processOrder = 0>
	class Event : public EventBase
	{
	public:
		using event_type = T;
		static const int processOrder = _processOrder;

		virtual ~Event() {}
		uint64_t EventID() const {
			return ClassID<T>::ID;
		}

		int GetProcessOrder() const {
			return processOrder;
		}
	protected:
		Event() {}
	};
}