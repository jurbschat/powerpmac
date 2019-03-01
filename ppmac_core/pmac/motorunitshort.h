//
// Created by urbschaj on 01.03.19.
//

#ifndef POWERPMAC_MOTORUNITSHORT_H
#define POWERPMAC_MOTORUNITSHORT_H

namespace ppmac {
	// this is only used for the name mapping via wise_enum
	enum class MotorUnitShort {
		None,
		ct,
		m,
		mm,
		um,
		nm,
		pm,
		in,
		mil,
		rev,
		rad,
		deg,
		grad,
		arcm,
		arcs,
		Reserved
	};
}

#endif //POWERPMAC_MOTORUNITSHORT_H
