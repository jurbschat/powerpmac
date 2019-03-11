#pragma once

#include <cstdint>

namespace ppmac::es {

	class EventBase
	{
	public:
		virtual ~EventBase() {};
		virtual uint64_t EventID() const = 0;
		virtual int GetProcessOrder() const = 0;
	protected:
		EventBase() {}
	};

}