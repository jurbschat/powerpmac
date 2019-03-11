//
// Created by urbschaj on 08.03.19.
//

#include "eventsystem/event.h"

#ifndef POWERPMAC_EVENTS_H
#define POWERPMAC_EVENTS_H

namespace ppmac {

	struct ConnectionLostEvent : public es::Event<ConnectionLostEvent> {};
	struct ConnectionEstablishedEvent : public es::Event<ConnectionEstablishedEvent> {};
	struct MotorStateChangedEvent : public es::Event<MotorStateChangedEvent> {};
	struct MotorCtrlChangedEvent : public es::Event<MotorCtrlChangedEvent> {};
	struct CoordStateChangedEvent : public es::Event<CoordStateChangedEvent> {};
	struct CoordAxisChangedEvent : public es::Event<CoordAxisChangedEvent> {};
	struct CompensationTableChangedEvent : public es::Event<CompensationTableChangedEvent> {};
	struct StateUpdaterInitializedEvent : public es::Event<StateUpdaterInitializedEvent> {};

}

#endif //POWERPMAC_EVENTS_H
