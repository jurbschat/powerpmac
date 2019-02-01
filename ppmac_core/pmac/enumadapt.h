//
// Created by urbschaj on 24.01.19.
//

#ifndef POWERPMAC_ENUMADAPT_H
#define POWERPMAC_ENUMADAPT_H

#include "defines.h"

#include <wise_enum.h>


WISE_ENUM_ADAPT(ppmac::MotorID::TYPE, Motor0, Motor1, Motor2, Motor3, Motor4, Motor5, Motor6, Motor7, Motor8);
WISE_ENUM_ADAPT(ppmac::IoID::TYPE, Port0, Port1, Port2, Port3, Port4, Port5, Port6, Port7, Port8);
WISE_ENUM_ADAPT(ppmac::CoordID::TYPE, Coord0, Coord1, Coord2, Coord3, Coord4, Coord5, Coord6, Coord7, Coord8);
WISE_ENUM_ADAPT(ppmac::MotorState::TYPE, Online, Offline, Init, Moving, Fault);
WISE_ENUM_ADAPT(ppmac::PortState::TYPE, Online, Offline, Fault);


#endif //POWERPMAC_ENUMADAPT_H
