//
// Created by urbschaj on 01.03.19.
//
#include "MyAttribute.h"
#include "PowerPMAC_CoordinateSystems.h"

namespace PowerPMAC_CoordinateSystems_ns
{

	MyAttrib::MyAttrib(int32_t axis, const string &att_name)
			: Attr(att_name.c_str(), Tango::DEV_DOUBLE, Tango::READ_WRITE), axis_(axis) {};

	MyAttrib::~MyAttrib() {

	};

	void MyAttrib::read(Tango::DeviceImpl *dev, Tango::Attribute &att) {
		Tango::DevDouble val = (static_cast<PowerPMAC_CoordinateSystems *>(dev))->ReadAxisAttrib(axis_);
		att.set_value(&val);
	}

	void MyAttrib::write(Tango::DeviceImpl *dev, Tango::WAttribute &att) {
		Tango::DevDouble w_val;
		att.get_write_value(w_val);
		(static_cast<PowerPMAC_CoordinateSystems *>(dev))->WriteAxisAttrib(axis_, w_val);
	}

	bool MyAttrib::is_allowed(Tango::DeviceImpl *dev, Tango::AttReqType ty) {
		return (static_cast<PowerPMAC_CoordinateSystems *>(dev))->IsAxisAttribAccessible(axis_, ty);
	}

}