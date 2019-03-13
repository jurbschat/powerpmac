//
// Created by urbschaj on 01.03.19.
//

#ifndef POWERPMAC_MYATTRIBUTE_H
#define POWERPMAC_MYATTRIBUTE_H

#include <tango.h>

namespace PowerPMAC_CoordinateSystems_ns
{

	class MyAttrib : public Tango::Attr {
	public:
		MyAttrib(int32_t axis, const string &att_name);

		~MyAttrib();

		virtual void read(Tango::DeviceImpl *dev, Tango::Attribute &att);
		virtual void write(Tango::DeviceImpl *dev, Tango::WAttribute &att);
		virtual bool is_allowed(Tango::DeviceImpl *dev, Tango::AttReqType ty);

		int32_t axis_;
	};

}

#endif //POWERPMAC_MYATTRIBUTE_H
