#pragma once

#include "eventconnectionbase.h"

namespace ppmac::es {

	template<typename T, typename U>
	class TypedConnection : public ConnectionBase
	{
	public:
		typedef T listner_type;
		typedef U event_type;
		typedef void (listner_type::*callback_type)(const event_type& e);

		TypedConnection(listner_type* listener, callback_type callback)
			: listener(listener), callback(callback)
		{}

		TypedConnection(const TypedConnection &other)
		{
			this->listener = other.listener;
			this->callback = other.callback;
		}

		TypedConnection &operator=(const TypedConnection &other)
		{
			this->listener = other.listener;
			this->callback = other.callback;
			return *this;
		}

		virtual ~TypedConnection() {}

		uint64_t EventID() const
		{
			return ClassID<event_type>::ID;
		}

		void Execute(const EventBase *base)
		{
			(listener->*callback)(*static_cast<const event_type*>(base));
		}

	private:
		listner_type *listener;
		callback_type callback;
	};
}