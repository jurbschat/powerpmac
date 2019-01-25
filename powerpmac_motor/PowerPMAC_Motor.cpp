/*----- PROTECTED REGION ID(PowerPMAC_Motor.cpp) ENABLED START -----*/
//=============================================================================
//
// file :        PowerPMAC_Motor.cpp
//
// description : C++ source for the PowerPMAC_Motor class and its commands.
//               The class is derived from Device. It represents the
//               CORBA servant object which will be accessed from the
//               network. All commands which can be executed on the
//               PowerPMAC_Motor are implemented in this file.
//
// project :     
//
// This file is part of Tango device class.
// 
// Tango is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// Tango is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with Tango.  If not, see <http://www.gnu.org/licenses/>.
// 
//
//
//=============================================================================
//                This file is generated by POGO
//        (Program Obviously used to Generate tango Object)
//=============================================================================


#include <PowerPMAC_Motor.h>
#include <PowerPMAC_MotorClass.h>

#include "coreinterface.h"
#include "commandbuilder.h"
#include "tangoutil.h"

/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor.cpp

/**
 *  PowerPMAC_Motor class description:
 *    
 */

//================================================================
//  The following table gives the correspondence
//  between command and method names.
//
//  Command name  |  Method name
//================================================================
//  State         |  Inherited (no method)
//  Status        |  Inherited (no method)
//  PhaseMotor    |  phase_motor
//  HomeMotor     |  home_motor
//  Calibrate     |  calibrate
//================================================================

//================================================================
//  Attributes managed are:
//================================================================
//  position          |  Tango::DevFloat	Scalar
//  acceleration      |  Tango::DevFloat	Scalar
//  maxvelocity       |  Tango::DevFloat	Scalar
//  sl_cw             |  Tango::DevFloat	Scalar
//  sl_ccw            |  Tango::DevFloat	Scalar
//  sl_cw_fault       |  Tango::DevBoolean	Scalar
//  sl_ccw_fault      |  Tango::DevBoolean	Scalar
//  limit_cw_fault    |  Tango::DevBoolean	Scalar
//  limit_ccw_fault   |  Tango::DevBoolean	Scalar
//  invert_direction  |  Tango::DevBoolean	Scalar
//  invert_encoder    |  Tango::DevBoolean	Scalar
//================================================================

namespace PowerPMAC_Motor_ns
{
/*----- PROTECTED REGION ID(PowerPMAC_Motor::namespace_starting) ENABLED START -----*/

//	static initializations

/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::namespace_starting

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_Motor::PowerPMAC_Motor()
 *	Description : Constructors for a Tango device
 *                implementing the classPowerPMAC_Motor
 */
//--------------------------------------------------------
PowerPMAC_Motor::PowerPMAC_Motor(Tango::DeviceClass *cl, string &s)
 : TANGO_BASE_CLASS(cl, s.c_str())
{
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::constructor_1) ENABLED START -----*/
	init_device();
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::constructor_1
}
//--------------------------------------------------------
PowerPMAC_Motor::PowerPMAC_Motor(Tango::DeviceClass *cl, const char *s)
 : TANGO_BASE_CLASS(cl, s)
{
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::constructor_2) ENABLED START -----*/
	init_device();
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::constructor_2
}
//--------------------------------------------------------
PowerPMAC_Motor::PowerPMAC_Motor(Tango::DeviceClass *cl, const char *s, const char *d)
 : TANGO_BASE_CLASS(cl, s, d)
{
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::constructor_3) ENABLED START -----*/
	init_device();
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::constructor_3
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_Motor::delete_device()
 *	Description : will be called at device destruction or at init command
 */
//--------------------------------------------------------
void PowerPMAC_Motor::delete_device()
{
	DEBUG_STREAM << "PowerPMAC_Motor::delete_device() " << device_name << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::delete_device) ENABLED START -----*/
	
	//	Delete device allocated objects
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::delete_device
	delete[] attr_acceleration_read;
	delete[] attr_maxvelocity_read;
	delete[] attr_sl_cw_read;
	delete[] attr_sl_ccw_read;
	delete[] attr_sl_cw_fault_read;
	delete[] attr_sl_ccw_fault_read;
	delete[] attr_limit_cw_fault_read;
	delete[] attr_limit_ccw_fault_read;
	delete[] attr_invert_direction_read;
	delete[] attr_invert_encoder_read;
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_Motor::init_device()
 *	Description : will be called at device initialization.
 */
//--------------------------------------------------------
void PowerPMAC_Motor::init_device()
{
	DEBUG_STREAM << "PowerPMAC_Motor::init_device() create device " << device_name << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::init_device_before) ENABLED START -----*/
	
	//	Initialization before get_device_property() call
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::init_device_before
	

	//	Get the device properties from database
	get_device_property();
	
	attr_acceleration_read = new Tango::DevFloat[1];
	attr_maxvelocity_read = new Tango::DevFloat[1];
	attr_sl_cw_read = new Tango::DevFloat[1];
	attr_sl_ccw_read = new Tango::DevFloat[1];
	attr_sl_cw_fault_read = new Tango::DevBoolean[1];
	attr_sl_ccw_fault_read = new Tango::DevBoolean[1];
	attr_limit_cw_fault_read = new Tango::DevBoolean[1];
	attr_limit_ccw_fault_read = new Tango::DevBoolean[1];
	attr_invert_direction_read = new Tango::DevBoolean[1];
	attr_invert_encoder_read = new Tango::DevBoolean[1];
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::init_device) ENABLED START -----*/
	
	//	Initialize device

	ppmac::CoreInterface& ci = ppmac::GetCoreObject();

	ci.RegisterConnectionEstablished([](){

	});
	ci.RegisterConnectionLost([](const std::string& reason){
		(void)reason;
	});
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::init_device
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_Motor::get_device_property()
 *	Description : Read database to initialize property data members.
 */
//--------------------------------------------------------
void PowerPMAC_Motor::get_device_property()
{
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::get_device_property_before) ENABLED START -----*/
	
	//	Initialize property data members
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::get_device_property_before


	//	Read device properties from database.
	Tango::DbData	dev_prop;
	dev_prop.push_back(Tango::DbDatum("motorIndex"));

	//	is there at least one property to be read ?
	if (dev_prop.size()>0)
	{
		//	Call database and extract values
		if (Tango::Util::instance()->_UseDb==true)
			get_db_device()->get_property(dev_prop);
	
		//	get instance on PowerPMAC_MotorClass to get class property
		Tango::DbDatum	def_prop, cl_prop;
		PowerPMAC_MotorClass	*ds_class =
			(static_cast<PowerPMAC_MotorClass *>(get_device_class()));
		int	i = -1;

		//	Try to initialize motorIndex from class property
		cl_prop = ds_class->get_class_property(dev_prop[++i].name);
		if (cl_prop.is_empty()==false)	cl_prop  >>  motorIndex;
		else {
			//	Try to initialize motorIndex from default device value
			def_prop = ds_class->get_default_device_property(dev_prop[i].name);
			if (def_prop.is_empty()==false)	def_prop  >>  motorIndex;
		}
		//	And try to extract motorIndex value from database
		if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  motorIndex;

	}

	/*----- PROTECTED REGION ID(PowerPMAC_Motor::get_device_property_after) ENABLED START -----*/
	
	//	Check device property data members init
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::get_device_property_after
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_Motor::always_executed_hook()
 *	Description : method always executed before any command is executed
 */
//--------------------------------------------------------
void PowerPMAC_Motor::always_executed_hook()
{
	DEBUG_STREAM << "PowerPMAC_Motor::always_executed_hook()  " << device_name << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::always_executed_hook) ENABLED START -----*/
	
	//	code always executed before all requests
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::always_executed_hook
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_Motor::read_attr_hardware()
 *	Description : Hardware acquisition for attributes
 */
//--------------------------------------------------------
void PowerPMAC_Motor::read_attr_hardware(TANGO_UNUSED(vector<long> &attr_list))
{
	DEBUG_STREAM << "PowerPMAC_Motor::read_attr_hardware(vector<long> &attr_list) entering... " << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::read_attr_hardware) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::read_attr_hardware
}
//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_Motor::write_attr_hardware()
 *	Description : Hardware writing for attributes
 */
//--------------------------------------------------------
void PowerPMAC_Motor::write_attr_hardware(TANGO_UNUSED(vector<long> &attr_list))
{
	DEBUG_STREAM << "PowerPMAC_Motor::write_attr_hardware(vector<long> &attr_list) entering... " << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::write_attr_hardware) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::write_attr_hardware
}

//--------------------------------------------------------
/**
 *	Read attribute position related method
 *	Description: 
 *
 *	Data type:	Tango::DevFloat
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void PowerPMAC_Motor::read_position(Tango::Attribute &attr)
{
	DEBUG_STREAM << "PowerPMAC_Motor::read_position(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::read_position) ENABLED START -----*/
	//	Set the attribute value

	ppmac::CoreInterface& ci = ppmac::GetCoreObject();
	try {
		float pos = ci.GetMotorInfo(static_cast<ppmac::MotorID::TYPE>(motorIndex)).position;
		attr.set_value(&pos);
	}
	catch(ppmac::RuntimeError& e) {
		tu::TranslateException(e);
	}
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::read_position
}
//--------------------------------------------------------
/**
 *	Write attribute position related method
 *	Description: 
 *
 *	Data type:	Tango::DevFloat
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void PowerPMAC_Motor::write_position(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "PowerPMAC_Motor::write_position(Tango::WAttribute &attr) entering... " << endl;
	//	Retrieve write value
	Tango::DevFloat	w_val;
	attr.get_write_value(w_val);
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::write_position) ENABLED START -----*/

	ppmac::CoreInterface& ci = ppmac::GetCoreObject();
	try {
		auto cmd = ppmac::cmd::MotorJogToPosition(w_val, static_cast<ppmac::MotorID::TYPE>(motorIndex));
		ci.ExecuteCommand(fmt::to_string(cmd));
	}
	catch(ppmac::RuntimeError& e) {
		tu::TranslateException(e);
	}
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::write_position
}
//--------------------------------------------------------
/**
 *	Read attribute acceleration related method
 *	Description: 
 *
 *	Data type:	Tango::DevFloat
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void PowerPMAC_Motor::read_acceleration(Tango::Attribute &attr)
{
	DEBUG_STREAM << "PowerPMAC_Motor::read_acceleration(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::read_acceleration) ENABLED START -----*/
	//	Set the attribute value
	attr.set_value(attr_acceleration_read);
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::read_acceleration
}
//--------------------------------------------------------
/**
 *	Write attribute acceleration related method
 *	Description: 
 *
 *	Data type:	Tango::DevFloat
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void PowerPMAC_Motor::write_acceleration(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "PowerPMAC_Motor::write_acceleration(Tango::WAttribute &attr) entering... " << endl;
	//	Retrieve write value
	Tango::DevFloat	w_val;
	attr.get_write_value(w_val);
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::write_acceleration) ENABLED START -----*/
	
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::write_acceleration
}
//--------------------------------------------------------
/**
 *	Read attribute maxvelocity related method
 *	Description: 
 *
 *	Data type:	Tango::DevFloat
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void PowerPMAC_Motor::read_maxvelocity(Tango::Attribute &attr)
{
	DEBUG_STREAM << "PowerPMAC_Motor::read_maxvelocity(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::read_maxvelocity) ENABLED START -----*/
	//	Set the attribute value
	attr.set_value(attr_maxvelocity_read);
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::read_maxvelocity
}
//--------------------------------------------------------
/**
 *	Write attribute maxvelocity related method
 *	Description: 
 *
 *	Data type:	Tango::DevFloat
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void PowerPMAC_Motor::write_maxvelocity(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "PowerPMAC_Motor::write_maxvelocity(Tango::WAttribute &attr) entering... " << endl;
	//	Retrieve write value
	Tango::DevFloat	w_val;
	attr.get_write_value(w_val);
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::write_maxvelocity) ENABLED START -----*/
	
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::write_maxvelocity
}
//--------------------------------------------------------
/**
 *	Read attribute sl_cw related method
 *	Description: 
 *
 *	Data type:	Tango::DevFloat
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void PowerPMAC_Motor::read_sl_cw(Tango::Attribute &attr)
{
	DEBUG_STREAM << "PowerPMAC_Motor::read_sl_cw(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::read_sl_cw) ENABLED START -----*/
	//	Set the attribute value
	attr.set_value(attr_sl_cw_read);
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::read_sl_cw
}
//--------------------------------------------------------
/**
 *	Write attribute sl_cw related method
 *	Description: 
 *
 *	Data type:	Tango::DevFloat
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void PowerPMAC_Motor::write_sl_cw(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "PowerPMAC_Motor::write_sl_cw(Tango::WAttribute &attr) entering... " << endl;
	//	Retrieve write value
	Tango::DevFloat	w_val;
	attr.get_write_value(w_val);
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::write_sl_cw) ENABLED START -----*/
	
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::write_sl_cw
}
//--------------------------------------------------------
/**
 *	Read attribute sl_ccw related method
 *	Description: 
 *
 *	Data type:	Tango::DevFloat
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void PowerPMAC_Motor::read_sl_ccw(Tango::Attribute &attr)
{
	DEBUG_STREAM << "PowerPMAC_Motor::read_sl_ccw(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::read_sl_ccw) ENABLED START -----*/
	//	Set the attribute value
	attr.set_value(attr_sl_ccw_read);
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::read_sl_ccw
}
//--------------------------------------------------------
/**
 *	Write attribute sl_ccw related method
 *	Description: 
 *
 *	Data type:	Tango::DevFloat
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void PowerPMAC_Motor::write_sl_ccw(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "PowerPMAC_Motor::write_sl_ccw(Tango::WAttribute &attr) entering... " << endl;
	//	Retrieve write value
	Tango::DevFloat	w_val;
	attr.get_write_value(w_val);
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::write_sl_ccw) ENABLED START -----*/
	
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::write_sl_ccw
}
//--------------------------------------------------------
/**
 *	Read attribute sl_cw_fault related method
 *	Description: 
 *
 *	Data type:	Tango::DevBoolean
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void PowerPMAC_Motor::read_sl_cw_fault(Tango::Attribute &attr)
{
	DEBUG_STREAM << "PowerPMAC_Motor::read_sl_cw_fault(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::read_sl_cw_fault) ENABLED START -----*/
	//	Set the attribute value
	attr.set_value(attr_sl_cw_fault_read);
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::read_sl_cw_fault
}
//--------------------------------------------------------
/**
 *	Read attribute sl_ccw_fault related method
 *	Description: 
 *
 *	Data type:	Tango::DevBoolean
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void PowerPMAC_Motor::read_sl_ccw_fault(Tango::Attribute &attr)
{
	DEBUG_STREAM << "PowerPMAC_Motor::read_sl_ccw_fault(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::read_sl_ccw_fault) ENABLED START -----*/
	//	Set the attribute value
	attr.set_value(attr_sl_ccw_fault_read);
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::read_sl_ccw_fault
}
//--------------------------------------------------------
/**
 *	Read attribute limit_cw_fault related method
 *	Description: 
 *
 *	Data type:	Tango::DevBoolean
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void PowerPMAC_Motor::read_limit_cw_fault(Tango::Attribute &attr)
{
	DEBUG_STREAM << "PowerPMAC_Motor::read_limit_cw_fault(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::read_limit_cw_fault) ENABLED START -----*/
	//	Set the attribute value
	attr.set_value(attr_limit_cw_fault_read);
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::read_limit_cw_fault
}
//--------------------------------------------------------
/**
 *	Read attribute limit_ccw_fault related method
 *	Description: 
 *
 *	Data type:	Tango::DevBoolean
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void PowerPMAC_Motor::read_limit_ccw_fault(Tango::Attribute &attr)
{
	DEBUG_STREAM << "PowerPMAC_Motor::read_limit_ccw_fault(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::read_limit_ccw_fault) ENABLED START -----*/
	//	Set the attribute value
	attr.set_value(attr_limit_ccw_fault_read);
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::read_limit_ccw_fault
}
//--------------------------------------------------------
/**
 *	Read attribute invert_direction related method
 *	Description: 
 *
 *	Data type:	Tango::DevBoolean
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void PowerPMAC_Motor::read_invert_direction(Tango::Attribute &attr)
{
	DEBUG_STREAM << "PowerPMAC_Motor::read_invert_direction(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::read_invert_direction) ENABLED START -----*/
	//	Set the attribute value
	attr.set_value(attr_invert_direction_read);
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::read_invert_direction
}
//--------------------------------------------------------
/**
 *	Write attribute invert_direction related method
 *	Description: 
 *
 *	Data type:	Tango::DevBoolean
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void PowerPMAC_Motor::write_invert_direction(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "PowerPMAC_Motor::write_invert_direction(Tango::WAttribute &attr) entering... " << endl;
	//	Retrieve write value
	Tango::DevBoolean	w_val;
	attr.get_write_value(w_val);
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::write_invert_direction) ENABLED START -----*/
	
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::write_invert_direction
}
//--------------------------------------------------------
/**
 *	Read attribute invert_encoder related method
 *	Description: 
 *
 *	Data type:	Tango::DevBoolean
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void PowerPMAC_Motor::read_invert_encoder(Tango::Attribute &attr)
{
	DEBUG_STREAM << "PowerPMAC_Motor::read_invert_encoder(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::read_invert_encoder) ENABLED START -----*/
	//	Set the attribute value
	attr.set_value(attr_invert_encoder_read);
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::read_invert_encoder
}
//--------------------------------------------------------
/**
 *	Write attribute invert_encoder related method
 *	Description: 
 *
 *	Data type:	Tango::DevBoolean
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void PowerPMAC_Motor::write_invert_encoder(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "PowerPMAC_Motor::write_invert_encoder(Tango::WAttribute &attr) entering... " << endl;
	//	Retrieve write value
	Tango::DevBoolean	w_val;
	attr.get_write_value(w_val);
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::write_invert_encoder) ENABLED START -----*/
	
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::write_invert_encoder
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_Motor::add_dynamic_attributes()
 *	Description : Create the dynamic attributes if any
 *                for specified device.
 */
//--------------------------------------------------------
void PowerPMAC_Motor::add_dynamic_attributes()
{
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::add_dynamic_attributes) ENABLED START -----*/
	
	//	Add your own code to create and add dynamic attributes if any
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::add_dynamic_attributes
}

//--------------------------------------------------------
/**
 *	Command PhaseMotor related method
 *	Description: 
 *
 */
//--------------------------------------------------------
void PowerPMAC_Motor::phase_motor()
{
	DEBUG_STREAM << "PowerPMAC_Motor::PhaseMotor()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::phase_motor) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::phase_motor
}
//--------------------------------------------------------
/**
 *	Command HomeMotor related method
 *	Description: 
 *
 */
//--------------------------------------------------------
void PowerPMAC_Motor::home_motor()
{
	DEBUG_STREAM << "PowerPMAC_Motor::HomeMotor()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::home_motor) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::home_motor
}
//--------------------------------------------------------
/**
 *	Command Calibrate related method
 *	Description: 
 *
 */
//--------------------------------------------------------
void PowerPMAC_Motor::calibrate()
{
	DEBUG_STREAM << "PowerPMAC_Motor::Calibrate()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::calibrate) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::calibrate
}
//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_Motor::add_dynamic_commands()
 *	Description : Create the dynamic commands if any
 *                for specified device.
 */
//--------------------------------------------------------
void PowerPMAC_Motor::add_dynamic_commands()
{
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::add_dynamic_commands) ENABLED START -----*/
	
	//	Add your own code to create and add dynamic commands if any
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::add_dynamic_commands
}

/*----- PROTECTED REGION ID(PowerPMAC_Motor::namespace_ending) ENABLED START -----*/

//	Additional Methods

/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::namespace_ending
} //	namespace
