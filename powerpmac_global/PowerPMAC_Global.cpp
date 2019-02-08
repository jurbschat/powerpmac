/*----- PROTECTED REGION ID(PowerPMAC_Global.cpp) ENABLED START -----*/
//=============================================================================
//
// file :        PowerPMAC_Global.cpp
//
// description : C++ source for the PowerPMAC_Global class and its commands.
//               The class is derived from Device. It represents the
//               CORBA servant object which will be accessed from the
//               network. All commands which can be executed on the
//               PowerPMAC_Global are implemented in this file.
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


#include <PowerPMAC_Global.h>
#include <PowerPMAC_GlobalClass.h>
#include "coreinterface.h"
#include "exception.h"
#include "tangoutil.h"
#include "commandbuilder.h"
#include <fmt/format.h>
#include <fmt/printf.h>

#include <unordered_map>

/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Global.cpp

/**
 *  PowerPMAC_Global class description:
 *    
 */

//================================================================
//  The following table gives the correspondence
//  between command and method names.
//
//  Command name    |  Method name
//================================================================
//  State           |  Inherited (no method)
//  Status          |  Inherited (no method)
//  ResetAmp        |  reset_amp
//  ExecuteCommand  |  execute_command
//  Reset           |  reset
//  Reboot          |  reboot
//================================================================

//================================================================
//  Attributes managed are:
//================================================================
//  MaxMotors     |  Tango::DevLong	Scalar
//  MaxCoords     |  Tango::DevLong	Scalar
//  AbortAll      |  Tango::DevBoolean	Scalar
//  CpuTemp       |  Tango::DevDouble	Scalar
//  AmpOverTemp   |  Tango::DevBoolean	Scalar
//  Firmware      |  Tango::DevString	Scalar
//  SystemType    |  Tango::DevString	Scalar
//  CpuType       |  Tango::DevString	Scalar
//  CpuFrequency  |  Tango::DevLong	Scalar
//  Uptime        |  Tango::DevString	Scalar
//================================================================

namespace PowerPMAC_Global_ns
{
/*----- PROTECTED REGION ID(PowerPMAC_Global::namespace_starting) ENABLED START -----*/

//	static initializations

/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Global::namespace_starting

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_Global::PowerPMAC_Global()
 *	Description : Constructors for a Tango device
 *                implementing the classPowerPMAC_Global
 */
//--------------------------------------------------------
PowerPMAC_Global::PowerPMAC_Global(Tango::DeviceClass *cl, string &s)
 : TANGO_BASE_CLASS(cl, s.c_str())
{
	/*----- PROTECTED REGION ID(PowerPMAC_Global::constructor_1) ENABLED START -----*/
	init_device();
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Global::constructor_1
}
//--------------------------------------------------------
PowerPMAC_Global::PowerPMAC_Global(Tango::DeviceClass *cl, const char *s)
 : TANGO_BASE_CLASS(cl, s)
{
	/*----- PROTECTED REGION ID(PowerPMAC_Global::constructor_2) ENABLED START -----*/
	init_device();
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Global::constructor_2
}
//--------------------------------------------------------
PowerPMAC_Global::PowerPMAC_Global(Tango::DeviceClass *cl, const char *s, const char *d)
 : TANGO_BASE_CLASS(cl, s, d)
{
	/*----- PROTECTED REGION ID(PowerPMAC_Global::constructor_3) ENABLED START -----*/
	init_device();
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Global::constructor_3
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_Global::delete_device()
 *	Description : will be called at device destruction or at init command
 */
//--------------------------------------------------------
void PowerPMAC_Global::delete_device()
{
	DEBUG_STREAM << "PowerPMAC_Global::delete_device() " << device_name << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_Global::delete_device) ENABLED START -----*/
	
	//	Delete device allocated objects
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Global::delete_device
	delete[] attr_MaxMotors_read;
	delete[] attr_MaxCoords_read;
	delete[] attr_AbortAll_read;
	delete[] attr_CpuTemp_read;
	delete[] attr_AmpOverTemp_read;
	delete[] attr_Firmware_read;
	delete[] attr_SystemType_read;
	delete[] attr_CpuType_read;
	delete[] attr_CpuFrequency_read;
	delete[] attr_Uptime_read;
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_Global::init_device()
 *	Description : will be called at device initialization.
 */
//--------------------------------------------------------
void PowerPMAC_Global::init_device()
{
	DEBUG_STREAM << "PowerPMAC_Global::init_device() create device " << device_name << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_Global::init_device_before) ENABLED START -----*/
	
	//	Initialization before get_device_property() call
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Global::init_device_before
	

	//	Get the device properties from database
	get_device_property();
	
	attr_MaxMotors_read = new Tango::DevLong[1];
	attr_MaxCoords_read = new Tango::DevLong[1];
	attr_AbortAll_read = new Tango::DevBoolean[1];
	attr_CpuTemp_read = new Tango::DevDouble[1];
	attr_AmpOverTemp_read = new Tango::DevBoolean[1];
	attr_Firmware_read = new Tango::DevString[1];
	attr_SystemType_read = new Tango::DevString[1];
	attr_CpuType_read = new Tango::DevString[1];
	attr_CpuFrequency_read = new Tango::DevLong[1];
	attr_Uptime_read = new Tango::DevString[1];
	/*----- PROTECTED REGION ID(PowerPMAC_Global::init_device) ENABLED START -----*/

	*attr_MaxMotors_read = 0;
	*attr_MaxCoords_read = 0;
	*attr_AbortAll_read = true;
	*attr_CpuTemp_read = 0;
	*attr_AmpOverTemp_read = true;
	*attr_Firmware_read = nullptr;
	*attr_SystemType_read = nullptr;
	*attr_CpuType_read = nullptr;
	*attr_CpuFrequency_read = 0;
	*attr_Uptime_read = nullptr;

	ppmac::CoreInterface& ci = ppmac::GetCoreObject();

	// we set the power pmac address and start the automatic
	// connect/reconnect machinery.
	ci.Initialize(host, port);

	connectionEstablished = ci.GetSignalConnectionEstablished().connect([this](){
		StartGlobal();
	});

	connectionLost = ci.GetSignalConnectionLost().connect([this](){
		StopGlobal();
	});

	if(ci.IsConnected()) {
		StartGlobal();
	} else {
		set_state(Tango::OFF);
	}
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Global::init_device
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_Global::get_device_property()
 *	Description : Read database to initialize property data members.
 */
//--------------------------------------------------------
void PowerPMAC_Global::get_device_property()
{
	/*----- PROTECTED REGION ID(PowerPMAC_Global::get_device_property_before) ENABLED START -----*/
	
	//	Initialize property data members
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Global::get_device_property_before


	//	Read device properties from database.
	Tango::DbData	dev_prop;
	dev_prop.push_back(Tango::DbDatum("host"));
	dev_prop.push_back(Tango::DbDatum("port"));

	//	is there at least one property to be read ?
	if (dev_prop.size()>0)
	{
		//	Call database and extract values
		if (Tango::Util::instance()->_UseDb==true)
			get_db_device()->get_property(dev_prop);
	
		//	get instance on PowerPMAC_GlobalClass to get class property
		Tango::DbDatum	def_prop, cl_prop;
		PowerPMAC_GlobalClass	*ds_class =
			(static_cast<PowerPMAC_GlobalClass *>(get_device_class()));
		int	i = -1;

		//	Try to initialize host from class property
		cl_prop = ds_class->get_class_property(dev_prop[++i].name);
		if (cl_prop.is_empty()==false)	cl_prop  >>  host;
		else {
			//	Try to initialize host from default device value
			def_prop = ds_class->get_default_device_property(dev_prop[i].name);
			if (def_prop.is_empty()==false)	def_prop  >>  host;
		}
		//	And try to extract host value from database
		if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  host;

		//	Try to initialize port from class property
		cl_prop = ds_class->get_class_property(dev_prop[++i].name);
		if (cl_prop.is_empty()==false)	cl_prop  >>  port;
		else {
			//	Try to initialize port from default device value
			def_prop = ds_class->get_default_device_property(dev_prop[i].name);
			if (def_prop.is_empty()==false)	def_prop  >>  port;
		}
		//	And try to extract port value from database
		if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  port;

	}

	/*----- PROTECTED REGION ID(PowerPMAC_Global::get_device_property_after) ENABLED START -----*/
	
	//	Check device property data members init
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Global::get_device_property_after
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_Global::always_executed_hook()
 *	Description : method always executed before any command is executed
 */
//--------------------------------------------------------
void PowerPMAC_Global::always_executed_hook()
{
	DEBUG_STREAM << "PowerPMAC_Global::always_executed_hook()  " << device_name << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_Global::always_executed_hook) ENABLED START -----*/
	
	//	code always executed before all requests
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Global::always_executed_hook
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_Global::read_attr_hardware()
 *	Description : Hardware acquisition for attributes
 */
//--------------------------------------------------------
void PowerPMAC_Global::read_attr_hardware(TANGO_UNUSED(vector<long> &attr_list))
{
	DEBUG_STREAM << "PowerPMAC_Global::read_attr_hardware(vector<long> &attr_list) entering... " << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_Global::read_attr_hardware) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Global::read_attr_hardware
}
//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_Global::write_attr_hardware()
 *	Description : Hardware writing for attributes
 */
//--------------------------------------------------------
void PowerPMAC_Global::write_attr_hardware(TANGO_UNUSED(vector<long> &attr_list))
{
	DEBUG_STREAM << "PowerPMAC_Global::write_attr_hardware(vector<long> &attr_list) entering... " << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_Global::write_attr_hardware) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Global::write_attr_hardware
}

//--------------------------------------------------------
/**
 *	Read attribute MaxMotors related method
 *	Description: 
 *
 *	Data type:	Tango::DevLong
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void PowerPMAC_Global::read_MaxMotors(Tango::Attribute &attr)
{
	DEBUG_STREAM << "PowerPMAC_Global::read_MaxMotors(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_Global::read_MaxMotors) ENABLED START -----*/
	//	Set the attribute value

	try {
		ppmac::CoreInterface& ci = ppmac::GetCoreObject();
		auto motors = ci.GetGlobalInfo().maxMotors;
		attr.set_value(&motors);
	} catch (ppmac::RuntimeError& e) {
		tu::TranslateException(e);
	}
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Global::read_MaxMotors
}
//--------------------------------------------------------
/**
 *	Read attribute MaxCoords related method
 *	Description: 
 *
 *	Data type:	Tango::DevLong
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void PowerPMAC_Global::read_MaxCoords(Tango::Attribute &attr)
{
	DEBUG_STREAM << "PowerPMAC_Global::read_MaxCoords(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_Global::read_MaxCoords) ENABLED START -----*/
	//	Set the attribute value

	try {
		ppmac::CoreInterface& ci = ppmac::GetCoreObject();
		auto coords = ci.GetGlobalInfo().maxCoords;
		attr.set_value(&coords);
	} catch (ppmac::RuntimeError& e) {
		tu::TranslateException(e);
	}
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Global::read_MaxCoords
}
//--------------------------------------------------------
/**
 *	Read attribute AbortAll related method
 *	Description: 
 *
 *	Data type:	Tango::DevBoolean
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void PowerPMAC_Global::read_AbortAll(Tango::Attribute &attr)
{
	DEBUG_STREAM << "PowerPMAC_Global::read_AbortAll(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_Global::read_AbortAll) ENABLED START -----*/
	//	Set the attribute value

	try {
		ppmac::CoreInterface& ci = ppmac::GetCoreObject();
		auto aa = ci.GetGlobalInfo().abortAll; // stinkt
		attr.set_value(&aa);
	} catch (ppmac::RuntimeError& e) {
		tu::TranslateException(e);
	}
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Global::read_AbortAll
}
//--------------------------------------------------------
/**
 *	Write attribute AbortAll related method
 *	Description: 
 *
 *	Data type:	Tango::DevBoolean
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void PowerPMAC_Global::write_AbortAll(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "PowerPMAC_Global::write_AbortAll(Tango::WAttribute &attr) entering... " << endl;
	//	Retrieve write value
	Tango::DevBoolean	w_val;
	attr.get_write_value(w_val);
	/*----- PROTECTED REGION ID(PowerPMAC_Global::write_AbortAll) ENABLED START -----*/

	try {
		ppmac::CoreInterface& ci = ppmac::GetCoreObject();
		ci.ExecuteCommand(ppmac::cmd::GlobalSetAbortAll(w_val));
	} catch (ppmac::RuntimeError& e) {
		tu::TranslateException(e);
	}
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Global::write_AbortAll
}
//--------------------------------------------------------
/**
 *	Read attribute CpuTemp related method
 *	Description: 
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void PowerPMAC_Global::read_CpuTemp(Tango::Attribute &attr)
{
	DEBUG_STREAM << "PowerPMAC_Global::read_CpuTemp(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_Global::read_CpuTemp) ENABLED START -----*/
	//	Set the attribute value


	try {
		ppmac::CoreInterface& ci = ppmac::GetCoreObject();
		auto motors = ci.GetGlobalInfo().temp;
		attr.set_value(&motors);
	} catch (ppmac::RuntimeError& e) {
		tu::TranslateException(e);
	}
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Global::read_CpuTemp
}
//--------------------------------------------------------
/**
 *	Read attribute AmpOverTemp related method
 *	Description: 
 *
 *	Data type:	Tango::DevBoolean
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void PowerPMAC_Global::read_AmpOverTemp(Tango::Attribute &attr)
{
	DEBUG_STREAM << "PowerPMAC_Global::read_AmpOverTemp(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_Global::read_AmpOverTemp) ENABLED START -----*/
	//	Set the attribute value

	try {
		ppmac::CoreInterface& ci = ppmac::GetCoreObject();
		auto ot = ci.GetGlobalInfo().brickOvertemp;
		attr.set_value(&ot);
	} catch (ppmac::RuntimeError& e) {
		tu::TranslateException(e);
	}
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Global::read_AmpOverTemp
}
//--------------------------------------------------------
/**
 *	Read attribute Firmware related method
 *	Description: 
 *
 *	Data type:	Tango::DevString
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void PowerPMAC_Global::read_Firmware(Tango::Attribute &attr)
{
	DEBUG_STREAM << "PowerPMAC_Global::read_Firmware(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_Global::read_Firmware) ENABLED START -----*/
	//	Set the attribute value

	try {
		ppmac::CoreInterface& ci = ppmac::GetCoreObject();
		auto firmware = ci.GetGlobalInfo().firmware;
		SetStringValue(attr_Firmware_read, firmware);
		attr.set_value(attr_Firmware_read);
	} catch (ppmac::RuntimeError& e) {
		tu::TranslateException(e);
	}
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Global::read_Firmware
}
//--------------------------------------------------------
/**
 *	Read attribute SystemType related method
 *	Description: 
 *
 *	Data type:	Tango::DevString
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void PowerPMAC_Global::read_SystemType(Tango::Attribute &attr)
{
	DEBUG_STREAM << "PowerPMAC_Global::read_SystemType(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_Global::read_SystemType) ENABLED START -----*/
	//	Set the attribute value

	try {
		ppmac::CoreInterface& ci = ppmac::GetCoreObject();
		auto system = ci.GetGlobalInfo().type;
		SetStringValue(attr_SystemType_read, system);
		attr.set_value(attr_SystemType_read);
	} catch (ppmac::RuntimeError& e) {
		tu::TranslateException(e);
	}
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Global::read_SystemType
}
//--------------------------------------------------------
/**
 *	Read attribute CpuType related method
 *	Description: 
 *
 *	Data type:	Tango::DevString
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void PowerPMAC_Global::read_CpuType(Tango::Attribute &attr)
{
	DEBUG_STREAM << "PowerPMAC_Global::read_CpuType(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_Global::read_CpuType) ENABLED START -----*/
	//	Set the attribute value

	try {
		ppmac::CoreInterface& ci = ppmac::GetCoreObject();
		auto cpuType = ci.GetGlobalInfo().cpuType;
		SetStringValue(attr_CpuType_read, cpuType);
		attr.set_value(attr_CpuType_read);
	} catch (ppmac::RuntimeError& e) {
		tu::TranslateException(e);
	}

	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Global::read_CpuType
}
//--------------------------------------------------------
/**
 *	Read attribute CpuFrequency related method
 *	Description: 
 *
 *	Data type:	Tango::DevLong
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void PowerPMAC_Global::read_CpuFrequency(Tango::Attribute &attr)
{
	DEBUG_STREAM << "PowerPMAC_Global::read_CpuFrequency(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_Global::read_CpuFrequency) ENABLED START -----*/
	//	Set the attribute value

	try {
		ppmac::CoreInterface& ci = ppmac::GetCoreObject();
		// convert to mhz
		int32_t freq = ci.GetGlobalInfo().cpuFrequency / (1000 * 1000);
		attr.set_value(&freq);
	} catch (ppmac::RuntimeError& e) {
		tu::TranslateException(e);
	}
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Global::read_CpuFrequency
}
//--------------------------------------------------------
/**
 *	Read attribute Uptime related method
 *	Description: 
 *
 *	Data type:	Tango::DevString
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void PowerPMAC_Global::read_Uptime(Tango::Attribute &attr)
{
	DEBUG_STREAM << "PowerPMAC_Global::read_Uptime(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_Global::read_Uptime) ENABLED START -----*/
	//	Set the attribute value

	try {
		ppmac::CoreInterface& ci = ppmac::GetCoreObject();
		auto ut = ci.GetGlobalInfo().uptime;
		int64_t seconds = std::floor(ut);
		int32_t minutes = seconds / 60;
		int32_t hours = minutes / 60;
		int32_t days = hours / 24;
		auto timeString = fmt::format("{}D {}:{}:{}", days, (hours%24), (minutes%60), (seconds%60));
		SetStringValue(attr_Uptime_read, timeString);
		attr.set_value(attr_Uptime_read);
	} catch (ppmac::RuntimeError& e) {
		tu::TranslateException(e);
	}
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Global::read_Uptime
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_Global::add_dynamic_attributes()
 *	Description : Create the dynamic attributes if any
 *                for specified device.
 */
//--------------------------------------------------------
void PowerPMAC_Global::add_dynamic_attributes()
{
	/*----- PROTECTED REGION ID(PowerPMAC_Global::add_dynamic_attributes) ENABLED START -----*/
	
	//	Add your own code to create and add dynamic attributes if any
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Global::add_dynamic_attributes
}

//--------------------------------------------------------
/**
 *	Command ResetAmp related method
 *	Description: 
 *
 */
//--------------------------------------------------------
void PowerPMAC_Global::reset_amp()
{
	DEBUG_STREAM << "PowerPMAC_Global::ResetAmp()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_Global::reset_amp) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Global::reset_amp
}
//--------------------------------------------------------
/**
 *	Command ExecuteCommand related method
 *	Description: 
 *
 *	@param argin 
 *	@returns 
 */
//--------------------------------------------------------
Tango::DevString PowerPMAC_Global::execute_command(Tango::DevString argin)
{
	Tango::DevString argout;
	DEBUG_STREAM << "PowerPMAC_Global::ExecuteCommand()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_Global::execute_command) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Global::execute_command
	return argout;
}
//--------------------------------------------------------
/**
 *	Command Reset related method
 *	Description: 
 *
 */
//--------------------------------------------------------
void PowerPMAC_Global::reset()
{
	DEBUG_STREAM << "PowerPMAC_Global::Reset()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_Global::reset) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Global::reset
}
//--------------------------------------------------------
/**
 *	Command Reboot related method
 *	Description: 
 *
 */
//--------------------------------------------------------
void PowerPMAC_Global::reboot()
{
	DEBUG_STREAM << "PowerPMAC_Global::Reboot()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_Global::reboot) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Global::reboot
}
//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_Global::add_dynamic_commands()
 *	Description : Create the dynamic commands if any
 *                for specified device.
 */
//--------------------------------------------------------
void PowerPMAC_Global::add_dynamic_commands()
{
	/*----- PROTECTED REGION ID(PowerPMAC_Global::add_dynamic_commands) ENABLED START -----*/
	
	//	Add your own code to create and add dynamic commands if any
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Global::add_dynamic_commands
}

/*----- PROTECTED REGION ID(PowerPMAC_Global::namespace_ending) ENABLED START -----*/

void PowerPMAC_Global::StartGlobal() {
	set_state(Tango::ON);
}

void PowerPMAC_Global::StopGlobal() {
	set_state(Tango::OFF);
}

void PowerPMAC_Global::SetErrorState() {
	// get global error states and set them as
	// string message
	auto msg = fmt::format("", 1);
	set_status(msg.c_str());
}

void PowerPMAC_Global::SetStringValue(char **ptr, const std::string& value)
{
	if(*ptr == nullptr) {
		*ptr = CORBA::string_dup(value.c_str());
	}  else {
		CORBA::string_free(*ptr);
		*ptr = CORBA::string_dup(value.c_str());
	}
}
// //--------------------------------------------------------
// /**
//  *	Read attribute PhaseClock related method
//  *	Description: 
//  *
//  *	Data type:	Tango::DevDouble
//  *	Attr type:	Scalar
//  */
// //--------------------------------------------------------
// void PowerPMAC_Global::read_PhaseClock(Tango::Attribute &attr)
// {
// 	DEBUG_STREAM << "PowerPMAC_Global::read_PhaseClock(Tango::Attribute &attr) entering... " << endl;
// 	//	Set the attribute value
// 	attr.set_value(attr_PhaseClock_read);
// 	
// }

// //--------------------------------------------------------
// /**
//  *	Read attribute ServoClock related method
//  *	Description: 
//  *
//  *	Data type:	Tango::DevDouble
//  *	Attr type:	Scalar
//  */
// //--------------------------------------------------------
// void PowerPMAC_Global::read_ServoClock(Tango::Attribute &attr)
// {
// 	DEBUG_STREAM << "PowerPMAC_Global::read_ServoClock(Tango::Attribute &attr) entering... " << endl;
// 	//	Set the attribute value
// 	attr.set_value(attr_ServoClock_read);
// 	try {
// 		ppmac::CoreInterface& ci = ppmac::GetCoreObject();
// 		auto aa = ci.GetGlobalInfo().abortAll; // stinkt
// 		attr.set_value(&aa);
// 	} catch (ppmac::RuntimeError& e) {
// 		tu::TranslateException(e);
// 	}
// 	
// }


/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Global::namespace_ending
} //	namespace
