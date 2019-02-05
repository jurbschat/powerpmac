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
#include <pmac/datastructures.h>

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
//  Phase         |  phase
//  Home          |  home
//  Calibrate     |  calibrate
//  Enable        |  enable
//  Disable       |  disable
//  Stop          |  stop
//  Kill          |  kill
//================================================================

//================================================================
//  Attributes managed are:
//================================================================
//  Position           |  Tango::DevDouble	Scalar
//  Acceleration       |  Tango::DevDouble	Scalar
//  Velocity           |  Tango::DevDouble	Scalar
//  SoftCwLimit        |  Tango::DevDouble	Scalar
//  SoftCcwLimit       |  Tango::DevDouble	Scalar
//  EnableSoftLimit    |  Tango::DevBoolean	Scalar
//  SoftCwLimitFault   |  Tango::DevBoolean	Scalar
//  SoftCcwLimitFault  |  Tango::DevBoolean	Scalar
//  CwLimitFault       |  Tango::DevBoolean	Scalar
//  CcwLimitFault      |  Tango::DevBoolean	Scalar
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

	StopMotor();
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::delete_device
	delete[] attr_Acceleration_read;
	delete[] attr_Velocity_read;
	delete[] attr_SoftCwLimit_read;
	delete[] attr_SoftCcwLimit_read;
	delete[] attr_EnableSoftLimit_read;
	delete[] attr_SoftCwLimitFault_read;
	delete[] attr_SoftCcwLimitFault_read;
	delete[] attr_CwLimitFault_read;
	delete[] attr_CcwLimitFault_read;
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
	
	attr_Acceleration_read = new Tango::DevDouble[1];
	attr_Velocity_read = new Tango::DevDouble[1];
	attr_SoftCwLimit_read = new Tango::DevDouble[1];
	attr_SoftCcwLimit_read = new Tango::DevDouble[1];
	attr_EnableSoftLimit_read = new Tango::DevBoolean[1];
	attr_SoftCwLimitFault_read = new Tango::DevBoolean[1];
	attr_SoftCcwLimitFault_read = new Tango::DevBoolean[1];
	attr_CwLimitFault_read = new Tango::DevBoolean[1];
	attr_CcwLimitFault_read = new Tango::DevBoolean[1];
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::init_device) ENABLED START -----*/
	
	//	Initialize device

	motorId = static_cast<ppmac::MotorID>(motorIndex);

	ppmac::CoreInterface& ci = ppmac::GetCoreObject();

	connectionEstablished = ci.GetSignalConnectionEstablished().connect([this](){
		StartMotor();
	});

	connectionLost = ci.GetSignalConnectionLost().connect([this](){
		StopMotor();
	});

	motorStateChanged = ci.GetSignalMotorStatusChanged(motorId).connect([this](uint64_t newValue, uint64_t changed){
		MotorStateChanged(newValue, changed);
	});

	if(ci.IsConnected()) {
		StartMotor();
	} else {
		set_state(Tango::OFF);
	}

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
	dev_prop.push_back(Tango::DbDatum("MotorIndex"));
	dev_prop.push_back(Tango::DbDatum("DisableHardLimits"));

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

		//	Try to initialize MotorIndex from class property
		cl_prop = ds_class->get_class_property(dev_prop[++i].name);
		if (cl_prop.is_empty()==false)	cl_prop  >>  motorIndex;
		else {
			//	Try to initialize MotorIndex from default device value
			def_prop = ds_class->get_default_device_property(dev_prop[i].name);
			if (def_prop.is_empty()==false)	def_prop  >>  motorIndex;
		}
		//	And try to extract MotorIndex value from database
		if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  motorIndex;

		//	Try to initialize DisableHardLimits from class property
		cl_prop = ds_class->get_class_property(dev_prop[++i].name);
		if (cl_prop.is_empty()==false)	cl_prop  >>  disableHardLimits;
		else {
			//	Try to initialize DisableHardLimits from default device value
			def_prop = ds_class->get_default_device_property(dev_prop[i].name);
			if (def_prop.is_empty()==false)	def_prop  >>  disableHardLimits;
		}
		//	And try to extract DisableHardLimits value from database
		if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  disableHardLimits;

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
 *	Read attribute Position related method
 *	Description: 
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void PowerPMAC_Motor::read_Position(Tango::Attribute &attr)
{
	DEBUG_STREAM << "PowerPMAC_Motor::read_Position(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::read_Position) ENABLED START -----*/
	//	Set the attribute value

	try {
		ppmac::CoreInterface& ci = ppmac::GetCoreObject();
		auto pos = ci.GetMotorInfo(motorId).position;
		attr.set_value(&pos);
	} catch (ppmac::RuntimeError& e) {
		tu::TranslateException(e);
	}
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::read_Position
}
//--------------------------------------------------------
/**
 *	Write attribute Position related method
 *	Description: 
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void PowerPMAC_Motor::write_Position(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "PowerPMAC_Motor::write_Position(Tango::WAttribute &attr) entering... " << endl;
	//	Retrieve write value
	Tango::DevDouble	w_val;
	attr.get_write_value(w_val);
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::write_Position) ENABLED START -----*/

	try {
		ppmac::CoreInterface& ci = ppmac::GetCoreObject();
		auto cmd = ppmac::cmd::MotorJogToPosition(w_val, motorId);
		ci.ExecuteCommand(cmd);
		movingTimerHandle = ci.AddDeadTimer(std::chrono::milliseconds{50}, [this](){
			if(get_state() == Tango::MOVING) {
				set_state(Tango::ON);
				movingTimerHandle = INVALID_HANDLE;
			}
		});
		set_state(Tango::MOVING);
	} catch (ppmac::RuntimeError& e) {
		tu::TranslateException(e);
	}
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::write_Position
}
//--------------------------------------------------------
/**
 *	Read attribute Acceleration related method
 *	Description: 
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void PowerPMAC_Motor::read_Acceleration(Tango::Attribute &attr)
{
	DEBUG_STREAM << "PowerPMAC_Motor::read_Acceleration(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::read_Acceleration) ENABLED START -----*/
	//	Set the attribute value

	try {
		ppmac::CoreInterface& ci = ppmac::GetCoreObject();
		auto cmd = ppmac::cmd::MotorGetJogAcceleration(motorId);
		auto result = ci.ExecuteCommand(cmd);
		auto accel = tu::ParseDouble(result);
		attr.set_value(&accel);
	} catch (ppmac::RuntimeError& e) {
		tu::TranslateException(e);
	}
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::read_Acceleration
}
//--------------------------------------------------------
/**
 *	Write attribute Acceleration related method
 *	Description: 
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void PowerPMAC_Motor::write_Acceleration(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "PowerPMAC_Motor::write_Acceleration(Tango::WAttribute &attr) entering... " << endl;
	//	Retrieve write value
	Tango::DevDouble	w_val;
	attr.get_write_value(w_val);
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::write_Acceleration) ENABLED START -----*/

	try {
		ppmac::CoreInterface& ci = ppmac::GetCoreObject();
		auto cmd = ppmac::cmd::MotorSetJogAcceleration(w_val, motorId);
		ci.ExecuteCommand(cmd);
	} catch (ppmac::RuntimeError& e) {
		tu::TranslateException(e);
	}
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::write_Acceleration
}
//--------------------------------------------------------
/**
 *	Read attribute Velocity related method
 *	Description: 
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void PowerPMAC_Motor::read_Velocity(Tango::Attribute &attr)
{
	DEBUG_STREAM << "PowerPMAC_Motor::read_Velocity(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::read_Velocity) ENABLED START -----*/
	//	Set the attribute value

	try {
		ppmac::CoreInterface& ci = ppmac::GetCoreObject();
		auto cmd = ppmac::cmd::MotorGetJogSpeed(motorId);
		auto result = ci.ExecuteCommand(cmd);
		auto vel = tu::ParseDouble(result);
		attr.set_value(&vel);
	} catch (ppmac::RuntimeError& e) {
		tu::TranslateException(e);
	}
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::read_Velocity
}
//--------------------------------------------------------
/**
 *	Write attribute Velocity related method
 *	Description: 
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void PowerPMAC_Motor::write_Velocity(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "PowerPMAC_Motor::write_Velocity(Tango::WAttribute &attr) entering... " << endl;
	//	Retrieve write value
	Tango::DevDouble	w_val;
	attr.get_write_value(w_val);
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::write_Velocity) ENABLED START -----*/

	try {
		ppmac::CoreInterface& ci = ppmac::GetCoreObject();
		auto cmd = ppmac::cmd::MotorSetJogSpeed(w_val, motorId);
		ci.ExecuteCommand(cmd);
	} catch (ppmac::RuntimeError& e) {
		tu::TranslateException(e);
	}
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::write_Velocity
}
//--------------------------------------------------------
/**
 *	Read attribute SoftCwLimit related method
 *	Description: 
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void PowerPMAC_Motor::read_SoftCwLimit(Tango::Attribute &attr)
{
	DEBUG_STREAM << "PowerPMAC_Motor::read_SoftCwLimit(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::read_SoftCwLimit) ENABLED START -----*/
	//	Set the attribute value

	// we update from the actual pmac value, we do this to get state changes
	// while we are in a "limits not enabled mode"
	try {
		ppmac::CoreInterface& ci = ppmac::GetCoreObject();
		std::string result = ci.ExecuteCommand(ppmac::cmd::MotorGetSoftlimitPlus(motorId));
		auto limit = tu::ParseDouble(result);
		if(limit != 0) {
			*attr_SoftCwLimit_read = limit;
		}
	} catch (ppmac::RuntimeError& e) {
		tu::TranslateException(e);
	}

	attr.set_value(attr_SoftCwLimit_read);
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::read_SoftCwLimit
}
//--------------------------------------------------------
/**
 *	Write attribute SoftCwLimit related method
 *	Description: 
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void PowerPMAC_Motor::write_SoftCwLimit(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "PowerPMAC_Motor::write_SoftCwLimit(Tango::WAttribute &attr) entering... " << endl;
	//	Retrieve write value
	Tango::DevDouble	w_val;
	attr.get_write_value(w_val);
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::write_SoftCwLimit) ENABLED START -----*/

	*attr_SoftCwLimit_read = w_val;
	if(*attr_EnableSoftLimit_read) {
		try {
			ppmac::CoreInterface& ci = ppmac::GetCoreObject();
			ci.ExecuteCommand(ppmac::cmd::MotorSetSoftlimitPlus(w_val, motorId));
		} catch (ppmac::RuntimeError& e) {
			tu::TranslateException(e);
		}
	}
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::write_SoftCwLimit
}
//--------------------------------------------------------
/**
 *	Read attribute SoftCcwLimit related method
 *	Description: 
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void PowerPMAC_Motor::read_SoftCcwLimit(Tango::Attribute &attr)
{
	DEBUG_STREAM << "PowerPMAC_Motor::read_SoftCcwLimit(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::read_SoftCcwLimit) ENABLED START -----*/
	//	Set the attribute value

	// we update from the actual pmac value, we do this to get state changes
	// while we are in a "limits not enabled mode"
	try {
		ppmac::CoreInterface& ci = ppmac::GetCoreObject();
		std::string result = ci.ExecuteCommand(ppmac::cmd::MotorGetSoftlimitMinus(motorId));
		auto limit = tu::ParseDouble(result);
		if(limit != 0) {
			*attr_SoftCcwLimit_read = limit;
		}
	} catch (ppmac::RuntimeError& e) {
		tu::TranslateException(e);
	}

	attr.set_value(attr_SoftCcwLimit_read);
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::read_SoftCcwLimit
}
//--------------------------------------------------------
/**
 *	Write attribute SoftCcwLimit related method
 *	Description: 
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void PowerPMAC_Motor::write_SoftCcwLimit(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "PowerPMAC_Motor::write_SoftCcwLimit(Tango::WAttribute &attr) entering... " << endl;
	//	Retrieve write value
	Tango::DevDouble	w_val;
	attr.get_write_value(w_val);
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::write_SoftCcwLimit) ENABLED START -----*/

	*attr_SoftCcwLimit_read = w_val;
	if(*attr_EnableSoftLimit_read) {
		try {
			ppmac::CoreInterface& ci = ppmac::GetCoreObject();
			ci.ExecuteCommand(ppmac::cmd::MotorSetSoftlimitMinus(w_val, motorId));
		} catch (ppmac::RuntimeError& e) {
			tu::TranslateException(e);
		}
	}
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::write_SoftCcwLimit
}
//--------------------------------------------------------
/**
 *	Read attribute EnableSoftLimit related method
 *	Description: 
 *
 *	Data type:	Tango::DevBoolean
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void PowerPMAC_Motor::read_EnableSoftLimit(Tango::Attribute &attr)
{
	DEBUG_STREAM << "PowerPMAC_Motor::read_EnableSoftLimit(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::read_EnableSoftLimit) ENABLED START -----*/
	//	Set the attribute value
	attr.set_value(attr_EnableSoftLimit_read);
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::read_EnableSoftLimit
}
//--------------------------------------------------------
/**
 *	Write attribute EnableSoftLimit related method
 *	Description: 
 *
 *	Data type:	Tango::DevBoolean
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void PowerPMAC_Motor::write_EnableSoftLimit(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "PowerPMAC_Motor::write_EnableSoftLimit(Tango::WAttribute &attr) entering... " << endl;
	//	Retrieve write value
	Tango::DevBoolean	w_val;
	attr.get_write_value(w_val);
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::write_EnableSoftLimit) ENABLED START -----*/

	*attr_EnableSoftLimit_read = w_val;

	try {
		ppmac::CoreInterface& ci = ppmac::GetCoreObject();
		if(w_val == true) {
			ci.ExecuteCommand(ppmac::cmd::MotorSetSoftlimitMinus(*attr_SoftCcwLimit_read, motorId));
			ci.ExecuteCommand(ppmac::cmd::MotorSetSoftlimitPlus(*attr_SoftCwLimit_read, motorId));
		} else {
			ci.ExecuteCommand(ppmac::cmd::MotorSetSoftlimitMinus(0, motorId));
			ci.ExecuteCommand(ppmac::cmd::MotorSetSoftlimitPlus(0, motorId));
		}
	} catch (ppmac::RuntimeError& e) {
		tu::TranslateException(e);
	}
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::write_EnableSoftLimit
}
//--------------------------------------------------------
/**
 *	Read attribute SoftCwLimitFault related method
 *	Description: 
 *
 *	Data type:	Tango::DevBoolean
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void PowerPMAC_Motor::read_SoftCwLimitFault(Tango::Attribute &attr)
{
	DEBUG_STREAM << "PowerPMAC_Motor::read_SoftCwLimitFault(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::read_SoftCwLimitFault) ENABLED START -----*/

	try {
		ppmac::CoreInterface& ci = ppmac::GetCoreObject();
		bool onLimit = ci.GetMotorInfo(motorId).status.named.SoftPlusLimit;
		attr.set_value(&onLimit);
	} catch (ppmac::RuntimeError& e) {
		tu::TranslateException(e);
	}
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::read_SoftCwLimitFault
}
//--------------------------------------------------------
/**
 *	Read attribute SoftCcwLimitFault related method
 *	Description: 
 *
 *	Data type:	Tango::DevBoolean
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void PowerPMAC_Motor::read_SoftCcwLimitFault(Tango::Attribute &attr)
{
	DEBUG_STREAM << "PowerPMAC_Motor::read_SoftCcwLimitFault(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::read_SoftCcwLimitFault) ENABLED START -----*/
	//	Set the attribute value
	attr.set_value(attr_SoftCcwLimitFault_read);

	try {
		ppmac::CoreInterface& ci = ppmac::GetCoreObject();
		bool onLimit = ci.GetMotorInfo(motorId).status.named.SoftMinusLimit;
		attr.set_value(&onLimit);
	} catch (ppmac::RuntimeError& e) {
		tu::TranslateException(e);
	}
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::read_SoftCcwLimitFault
}
//--------------------------------------------------------
/**
 *	Read attribute CwLimitFault related method
 *	Description: 
 *
 *	Data type:	Tango::DevBoolean
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void PowerPMAC_Motor::read_CwLimitFault(Tango::Attribute &attr)
{
	DEBUG_STREAM << "PowerPMAC_Motor::read_CwLimitFault(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::read_CwLimitFault) ENABLED START -----*/
	//	Set the attribute value

	try {
		ppmac::CoreInterface& ci = ppmac::GetCoreObject();
		bool onLimit = ci.GetMotorInfo(motorId).status.named.PlusLimit;
		attr.set_value(&onLimit);
	} catch (ppmac::RuntimeError& e) {
		tu::TranslateException(e);
	}
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::read_CwLimitFault
}
//--------------------------------------------------------
/**
 *	Read attribute CcwLimitFault related method
 *	Description: 
 *
 *	Data type:	Tango::DevBoolean
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void PowerPMAC_Motor::read_CcwLimitFault(Tango::Attribute &attr)
{
	DEBUG_STREAM << "PowerPMAC_Motor::read_CcwLimitFault(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::read_CcwLimitFault) ENABLED START -----*/
	//	Set the attribute value

	try {
		ppmac::CoreInterface& ci = ppmac::GetCoreObject();
		bool onLimit = ci.GetMotorInfo(motorId).status.named.MinusLimit;
		attr.set_value(&onLimit);
	} catch (ppmac::RuntimeError& e) {
		tu::TranslateException(e);
	}
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::read_CcwLimitFault
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
 *	Command Phase related method
 *	Description: 
 *
 */
//--------------------------------------------------------
void PowerPMAC_Motor::phase()
{
	DEBUG_STREAM << "PowerPMAC_Motor::Phase()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::phase) ENABLED START -----*/

	try {
		ppmac::CoreInterface& ci = ppmac::GetCoreObject();
		ci.ExecuteCommand(ppmac::cmd::MotorPhase(motorId));
	} catch (ppmac::RuntimeError& e) {
		tu::TranslateException(e);
	}
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::phase
}
//--------------------------------------------------------
/**
 *	Command Home related method
 *	Description: 
 *
 */
//--------------------------------------------------------
void PowerPMAC_Motor::home()
{
	DEBUG_STREAM << "PowerPMAC_Motor::Home()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::home) ENABLED START -----*/

	try {
		ppmac::CoreInterface& ci = ppmac::GetCoreObject();
		ci.ExecuteCommand(ppmac::cmd::MotorHome(motorId));
	} catch (ppmac::RuntimeError& e) {
		tu::TranslateException(e);
	}
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::home
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

	try {
		ppmac::CoreInterface& ci = ppmac::GetCoreObject();
		ci.ExecuteCommand(ppmac::cmd::MotorZeroPosition(motorId));
	} catch (ppmac::RuntimeError& e) {
		tu::TranslateException(e);
	}
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::calibrate
}
//--------------------------------------------------------
/**
 *	Command Enable related method
 *	Description: 
 *
 */
//--------------------------------------------------------
void PowerPMAC_Motor::enable()
{
	DEBUG_STREAM << "PowerPMAC_Motor::Enable()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::enable) ENABLED START -----*/
	
	//	Add your own code
	StartMotor();
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::enable
}
//--------------------------------------------------------
/**
 *	Command Disable related method
 *	Description: 
 *
 */
//--------------------------------------------------------
void PowerPMAC_Motor::disable()
{
	DEBUG_STREAM << "PowerPMAC_Motor::Disable()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::disable) ENABLED START -----*/

	StopMotor();
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::disable
}
//--------------------------------------------------------
/**
 *	Command Stop related method
 *	Description: 
 *
 */
//--------------------------------------------------------
void PowerPMAC_Motor::stop()
{
	DEBUG_STREAM << "PowerPMAC_Motor::Stop()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::stop) ENABLED START -----*/

	try {
		ppmac::CoreInterface& ci = ppmac::GetCoreObject();
		ci.ExecuteCommand(ppmac::cmd::MotorAbort(motorId));
	} catch (ppmac::RuntimeError& e) {
		tu::TranslateException(e);
	}
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::stop
}
//--------------------------------------------------------
/**
 *	Command Kill related method
 *	Description: 
 *
 */
//--------------------------------------------------------
void PowerPMAC_Motor::kill()
{
	DEBUG_STREAM << "PowerPMAC_Motor::Kill()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::kill) ENABLED START -----*/

	try {
		ppmac::CoreInterface& ci = ppmac::GetCoreObject();
		ci.ExecuteCommand(ppmac::cmd::MotorKill(motorId));
	} catch (ppmac::RuntimeError& e) {
		tu::TranslateException(e);
	}
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::kill
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

void PowerPMAC_Motor::StartMotor()
{
	if(disableHardLimits) {
		try {
			ppmac::CoreInterface& ci = ppmac::GetCoreObject();
			auto getLimitCmd = ppmac::cmd::MotorGetHardLimitAddr(motorId);
			hardLimitAddress = ci.ExecuteCommand(getLimitCmd);
			auto zeroLimitsCmd = ppmac::cmd::MotorSetHardLimits(0, motorId);
			ci.ExecuteCommand(zeroLimitsCmd);
			fmt::print("disabling hard limits (was: {})\n", hardLimitAddress);
		} catch (ppmac::RuntimeError& e) {
			tu::TranslateException(e);
		}
	}

	set_state(Tango::ON);
}

void PowerPMAC_Motor::StopMotor()
{
	if(disableHardLimits) {
		// restore the limits if the device goes down
		try {
			ppmac::CoreInterface& ci = ppmac::GetCoreObject();
			auto cmd = ppmac::cmd::MotorSetHardLimits(hardLimitAddress, motorId);
			ci.ExecuteCommand(cmd);
			fmt::print("restoring hard limits to: {}\n", hardLimitAddress);
			if(movingTimerHandle != INVALID_HANDLE) {
				ci.RemoveDeadTimer(movingTimerHandle);
				movingTimerHandle = INVALID_HANDLE;
			}
		} catch (ppmac::RuntimeError& e) {
			tu::TranslateException(e);
		}
	}

	set_state(Tango::OFF);
}

void PowerPMAC_Motor::MotorStateChanged(uint64_t newState, uint64_t changes)
{
	try {
		if(ppmac::bits::rising(newState, changes, ppmac::MotorStatusBits::DestVelZero)) {
			set_state(Tango::ON);
			fmt::print("set state to ON\n");
		}
		else if(ppmac::bits::falling(newState, changes, ppmac::MotorStatusBits::DestVelZero)) {
			set_state(Tango::MOVING);
			ppmac::CoreInterface& ci = ppmac::GetCoreObject();
			if(movingTimerHandle != INVALID_HANDLE) {
				fmt::print("clearing move timer timeout!\n");
				ci.RemoveDeadTimer(movingTimerHandle);
				movingTimerHandle = INVALID_HANDLE;
			}
			fmt::print("set state to MOVING\n");
		}
		lastMotorState = newState;
	} catch (ppmac::RuntimeError& e) {
		tu::TranslateException(e);
	}
}

/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::namespace_ending
} //	namespace
