/*----- PROTECTED REGION ID(PowerPMAC_MotorClass.cpp) ENABLED START -----*/
//=============================================================================
//
// file :        PowerPMAC_MotorClass.cpp
//
// description : C++ source for the PowerPMAC_MotorClass.
//               A singleton class derived from DeviceClass.
//               It implements the command and attribute list
//               and all properties and methods required
//               by the PowerPMAC_Motor once per process.
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


#include <PowerPMAC_MotorClass.h>
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-variable"

/*----- PROTECTED REGION END -----*/	//	PowerPMAC_MotorClass.cpp

//-------------------------------------------------------------------
/**
 *	Create PowerPMAC_MotorClass singleton and
 *	return it in a C function for Python usage
 */
//-------------------------------------------------------------------
extern "C" {
#ifdef _TG_WINDOWS_

__declspec(dllexport)

#endif

	Tango::DeviceClass *_create_PowerPMAC_Motor_class(const char *name) {
		return PowerPMAC_Motor_ns::PowerPMAC_MotorClass::init(name);
	}
}

namespace PowerPMAC_Motor_ns
{
//===================================================================
//	Initialize pointer for singleton pattern
//===================================================================
PowerPMAC_MotorClass *PowerPMAC_MotorClass::_instance = NULL;

//--------------------------------------------------------
/**
 * method : 		PowerPMAC_MotorClass::PowerPMAC_MotorClass(string &s)
 * description : 	constructor for the PowerPMAC_MotorClass
 *
 * @param s	The class name
 */
//--------------------------------------------------------
PowerPMAC_MotorClass::PowerPMAC_MotorClass(string &s):Tango::DeviceClass(s)
{
	cout2 << "Entering PowerPMAC_MotorClass constructor" << endl;
	set_default_property();
	write_class_property();

	/*----- PROTECTED REGION ID(PowerPMAC_MotorClass::constructor) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_MotorClass::constructor

	cout2 << "Leaving PowerPMAC_MotorClass constructor" << endl;
}

//--------------------------------------------------------
/**
 * method : 		PowerPMAC_MotorClass::~PowerPMAC_MotorClass()
 * description : 	destructor for the PowerPMAC_MotorClass
 */
//--------------------------------------------------------
PowerPMAC_MotorClass::~PowerPMAC_MotorClass()
{
	/*----- PROTECTED REGION ID(PowerPMAC_MotorClass::destructor) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_MotorClass::destructor

	_instance = NULL;
}


//--------------------------------------------------------
/**
 * method : 		PowerPMAC_MotorClass::init
 * description : 	Create the object if not already done.
 *                  Otherwise, just return a pointer to the object
 *
 * @param	name	The class name
 */
//--------------------------------------------------------
PowerPMAC_MotorClass *PowerPMAC_MotorClass::init(const char *name)
{
	if (_instance == NULL)
	{
		try
		{
			string s(name);
			_instance = new PowerPMAC_MotorClass(s);
		}
		catch (bad_alloc &)
		{
			throw;
		}
	}
	return _instance;
}

//--------------------------------------------------------
/**
 * method : 		PowerPMAC_MotorClass::instance
 * description : 	Check if object already created,
 *                  and return a pointer to the object
 */
//--------------------------------------------------------
PowerPMAC_MotorClass *PowerPMAC_MotorClass::instance()
{
	if (_instance == NULL)
	{
		cerr << "Class is not initialised !!" << endl;
		exit(-1);
	}
	return _instance;
}



//===================================================================
//	Command execution method calls
//===================================================================
//--------------------------------------------------------
/**
 * method : 		PhaseClass::execute()
 * description : 	method to trigger the execution of the command.
 *
 * @param	device	The device on which the command must be executed
 * @param	in_any	The command input data
 *
 *	returns The command output data (packed in the Any object)
 */
//--------------------------------------------------------
CORBA::Any *PhaseClass::execute(Tango::DeviceImpl *device, TANGO_UNUSED(const CORBA::Any &in_any))
{
	cout2 << "PhaseClass::execute(): arrived" << endl;
	((static_cast<PowerPMAC_Motor *>(device))->phase());
	return new CORBA::Any();
}

//--------------------------------------------------------
/**
 * method : 		HomeClass::execute()
 * description : 	method to trigger the execution of the command.
 *
 * @param	device	The device on which the command must be executed
 * @param	in_any	The command input data
 *
 *	returns The command output data (packed in the Any object)
 */
//--------------------------------------------------------
CORBA::Any *HomeClass::execute(Tango::DeviceImpl *device, TANGO_UNUSED(const CORBA::Any &in_any))
{
	cout2 << "HomeClass::execute(): arrived" << endl;
	((static_cast<PowerPMAC_Motor *>(device))->home());
	return new CORBA::Any();
}

//--------------------------------------------------------
/**
 * method : 		CalibrateClass::execute()
 * description : 	method to trigger the execution of the command.
 *
 * @param	device	The device on which the command must be executed
 * @param	in_any	The command input data
 *
 *	returns The command output data (packed in the Any object)
 */
//--------------------------------------------------------
CORBA::Any *CalibrateClass::execute(Tango::DeviceImpl *device, TANGO_UNUSED(const CORBA::Any &in_any))
{
	cout2 << "CalibrateClass::execute(): arrived" << endl;
	((static_cast<PowerPMAC_Motor *>(device))->calibrate());
	return new CORBA::Any();
}

//--------------------------------------------------------
/**
 * method : 		EnableClass::execute()
 * description : 	method to trigger the execution of the command.
 *
 * @param	device	The device on which the command must be executed
 * @param	in_any	The command input data
 *
 *	returns The command output data (packed in the Any object)
 */
//--------------------------------------------------------
CORBA::Any *EnableClass::execute(Tango::DeviceImpl *device, TANGO_UNUSED(const CORBA::Any &in_any))
{
	cout2 << "EnableClass::execute(): arrived" << endl;
	((static_cast<PowerPMAC_Motor *>(device))->enable());
	return new CORBA::Any();
}

//--------------------------------------------------------
/**
 * method : 		DisableClass::execute()
 * description : 	method to trigger the execution of the command.
 *
 * @param	device	The device on which the command must be executed
 * @param	in_any	The command input data
 *
 *	returns The command output data (packed in the Any object)
 */
//--------------------------------------------------------
CORBA::Any *DisableClass::execute(Tango::DeviceImpl *device, TANGO_UNUSED(const CORBA::Any &in_any))
{
	cout2 << "DisableClass::execute(): arrived" << endl;
	((static_cast<PowerPMAC_Motor *>(device))->disable());
	return new CORBA::Any();
}

//--------------------------------------------------------
/**
 * method : 		StopClass::execute()
 * description : 	method to trigger the execution of the command.
 *
 * @param	device	The device on which the command must be executed
 * @param	in_any	The command input data
 *
 *	returns The command output data (packed in the Any object)
 */
//--------------------------------------------------------
CORBA::Any *StopClass::execute(Tango::DeviceImpl *device, TANGO_UNUSED(const CORBA::Any &in_any))
{
	cout2 << "StopClass::execute(): arrived" << endl;
	((static_cast<PowerPMAC_Motor *>(device))->stop());
	return new CORBA::Any();
}

//--------------------------------------------------------
/**
 * method : 		KillClass::execute()
 * description : 	method to trigger the execution of the command.
 *
 * @param	device	The device on which the command must be executed
 * @param	in_any	The command input data
 *
 *	returns The command output data (packed in the Any object)
 */
//--------------------------------------------------------
CORBA::Any *KillClass::execute(Tango::DeviceImpl *device, TANGO_UNUSED(const CORBA::Any &in_any))
{
	cout2 << "KillClass::execute(): arrived" << endl;
	((static_cast<PowerPMAC_Motor *>(device))->kill());
	return new CORBA::Any();
}

//--------------------------------------------------------
/**
 * method : 		ActivateAndResetClass::execute()
 * description : 	method to trigger the execution of the command.
 *
 * @param	device	The device on which the command must be executed
 * @param	in_any	The command input data
 *
 *	returns The command output data (packed in the Any object)
 */
//--------------------------------------------------------
CORBA::Any *ActivateAndResetClass::execute(Tango::DeviceImpl *device, TANGO_UNUSED(const CORBA::Any &in_any))
{
	cout2 << "ActivateAndResetClass::execute(): arrived" << endl;
	((static_cast<PowerPMAC_Motor *>(device))->activate_and_reset());
	return new CORBA::Any();
}


//===================================================================
//	Properties management
//===================================================================
//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_MotorClass::get_class_property()
 *	Description : Get the class property for specified name.
 */
//--------------------------------------------------------
Tango::DbDatum PowerPMAC_MotorClass::get_class_property(string &prop_name)
{
	for (unsigned int i=0 ; i<cl_prop.size() ; i++)
		if (cl_prop[i].name == prop_name)
			return cl_prop[i];
	//	if not found, returns  an empty DbDatum
	return Tango::DbDatum(prop_name);
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_MotorClass::get_default_device_property()
 *	Description : Return the default value for device property.
 */
//--------------------------------------------------------
Tango::DbDatum PowerPMAC_MotorClass::get_default_device_property(string &prop_name)
{
	for (unsigned int i=0 ; i<dev_def_prop.size() ; i++)
		if (dev_def_prop[i].name == prop_name)
			return dev_def_prop[i];
	//	if not found, return  an empty DbDatum
	return Tango::DbDatum(prop_name);
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_MotorClass::get_default_class_property()
 *	Description : Return the default value for class property.
 */
//--------------------------------------------------------
Tango::DbDatum PowerPMAC_MotorClass::get_default_class_property(string &prop_name)
{
	for (unsigned int i=0 ; i<cl_def_prop.size() ; i++)
		if (cl_def_prop[i].name == prop_name)
			return cl_def_prop[i];
	//	if not found, return  an empty DbDatum
	return Tango::DbDatum(prop_name);
}


//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_MotorClass::set_default_property()
 *	Description : Set default property (class and device) for wizard.
 *                For each property, add to wizard property name and description.
 *                If default value has been set, add it to wizard property and
 *                store it in a DbDatum.
 */
//--------------------------------------------------------
void PowerPMAC_MotorClass::set_default_property()
{
	string	prop_name;
	string	prop_desc;
	string	prop_def;
	vector<string>	vect_data;

	//	Set Default Class Properties

	//	Set Default device Properties
	prop_name = "MotorIndex";
	prop_desc = "index of the motor";
	prop_def  = "";
	vect_data.clear();
	if (prop_def.length()>0)
	{
		Tango::DbDatum	data(prop_name);
		data << vect_data ;
		dev_def_prop.push_back(data);
		add_wiz_dev_prop(prop_name, prop_desc,  prop_def);
	}
	else
		add_wiz_dev_prop(prop_name, prop_desc);
	prop_name = "DisableHardLimits";
	prop_desc = "";
	prop_def  = "false";
	vect_data.clear();
	vect_data.push_back("false");
	if (prop_def.length()>0)
	{
		Tango::DbDatum	data(prop_name);
		data << vect_data ;
		dev_def_prop.push_back(data);
		add_wiz_dev_prop(prop_name, prop_desc,  prop_def);
	}
	else
		add_wiz_dev_prop(prop_name, prop_desc);
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_MotorClass::write_class_property()
 *	Description : Set class description fields as property in database
 */
//--------------------------------------------------------
void PowerPMAC_MotorClass::write_class_property()
{
	//	First time, check if database used
	if (Tango::Util::_UseDb == false)
		return;

	Tango::DbData	data;
	string	classname = get_name();
	string	header;
	string::size_type	start, end;

	//	Put title
	Tango::DbDatum	title("ProjectTitle");
	string	str_title("");
	title << str_title;
	data.push_back(title);

	//	Put Description
	Tango::DbDatum	description("Description");
	vector<string>	str_desc;
	str_desc.push_back("");
	description << str_desc;
	data.push_back(description);

	//  Put inheritance
	Tango::DbDatum	inher_datum("InheritedFrom");
	vector<string> inheritance;
	inheritance.push_back("TANGO_BASE_CLASS");
	inher_datum << inheritance;
	data.push_back(inher_datum);

	//	Call database and and values
	get_db_class()->put_property(data);
}

//===================================================================
//	Factory methods
//===================================================================

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_MotorClass::device_factory()
 *	Description : Create the device object(s)
 *                and store them in the device list
 */
//--------------------------------------------------------
void PowerPMAC_MotorClass::device_factory(const Tango::DevVarStringArray *devlist_ptr)
{
	/*----- PROTECTED REGION ID(PowerPMAC_MotorClass::device_factory_before) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_MotorClass::device_factory_before

	//	Create devices and add it into the device list
	for (unsigned long i=0 ; i<devlist_ptr->length() ; i++)
	{
		cout4 << "Device name : " << (*devlist_ptr)[i].in() << endl;
		device_list.push_back(new PowerPMAC_Motor(this, (*devlist_ptr)[i]));
	}

	//	Manage dynamic attributes if any
	erase_dynamic_attributes(devlist_ptr, get_class_attr()->get_attr_list());

	//	Export devices to the outside world
	for (unsigned long i=1 ; i<=devlist_ptr->length() ; i++)
	{
		//	Add dynamic attributes if any
		PowerPMAC_Motor *dev = static_cast<PowerPMAC_Motor *>(device_list[device_list.size()-i]);
		dev->add_dynamic_attributes();

		//	Check before if database used.
		if ((Tango::Util::_UseDb == true) && (Tango::Util::_FileDb == false))
			export_device(dev);
		else
			export_device(dev, dev->get_name().c_str());
	}

	/*----- PROTECTED REGION ID(PowerPMAC_MotorClass::device_factory_after) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_MotorClass::device_factory_after
}
//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_MotorClass::attribute_factory()
 *	Description : Create the attribute object(s)
 *                and store them in the attribute list
 */
//--------------------------------------------------------
void PowerPMAC_MotorClass::attribute_factory(vector<Tango::Attr *> &att_list)
{
	/*----- PROTECTED REGION ID(PowerPMAC_MotorClass::attribute_factory_before) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_MotorClass::attribute_factory_before
	//	Attribute : Position
	PositionAttrib	*position = new PositionAttrib();
	Tango::UserDefaultAttrProp	position_prop;
	//	description	not set for Position
	//	label	not set for Position
	//	unit	not set for Position
	//	standard_unit	not set for Position
	//	display_unit	not set for Position
	position_prop.set_format("%10.3f");
	//	max_value	not set for Position
	//	min_value	not set for Position
	//	max_alarm	not set for Position
	//	min_alarm	not set for Position
	//	max_warning	not set for Position
	//	min_warning	not set for Position
	//	delta_t	not set for Position
	//	delta_val	not set for Position
	
	position->set_default_properties(position_prop);
	//	Not Polled
	position->set_disp_level(Tango::OPERATOR);
	//	Not Memorized
	att_list.push_back(position);

	//	Attribute : Acceleration
	AccelerationAttrib	*acceleration = new AccelerationAttrib();
	Tango::UserDefaultAttrProp	acceleration_prop;
	//	description	not set for Acceleration
	//	label	not set for Acceleration
	//	unit	not set for Acceleration
	//	standard_unit	not set for Acceleration
	//	display_unit	not set for Acceleration
	acceleration_prop.set_format("%10.3f");
	//	max_value	not set for Acceleration
	//	min_value	not set for Acceleration
	//	max_alarm	not set for Acceleration
	//	min_alarm	not set for Acceleration
	//	max_warning	not set for Acceleration
	//	min_warning	not set for Acceleration
	//	delta_t	not set for Acceleration
	//	delta_val	not set for Acceleration
	
	acceleration->set_default_properties(acceleration_prop);
	//	Not Polled
	acceleration->set_disp_level(Tango::OPERATOR);
	//	Not Memorized
	att_list.push_back(acceleration);

	//	Attribute : Velocity
	VelocityAttrib	*velocity = new VelocityAttrib();
	Tango::UserDefaultAttrProp	velocity_prop;
	//	description	not set for Velocity
	//	label	not set for Velocity
	//	unit	not set for Velocity
	//	standard_unit	not set for Velocity
	//	display_unit	not set for Velocity
	velocity_prop.set_format("%10.3f");
	//	max_value	not set for Velocity
	//	min_value	not set for Velocity
	//	max_alarm	not set for Velocity
	//	min_alarm	not set for Velocity
	//	max_warning	not set for Velocity
	//	min_warning	not set for Velocity
	//	delta_t	not set for Velocity
	//	delta_val	not set for Velocity
	
	velocity->set_default_properties(velocity_prop);
	//	Not Polled
	velocity->set_disp_level(Tango::OPERATOR);
	//	Not Memorized
	att_list.push_back(velocity);

	//	Attribute : HomeOffset
	HomeOffsetAttrib	*homeoffset = new HomeOffsetAttrib();
	Tango::UserDefaultAttrProp	homeoffset_prop;
	//	description	not set for HomeOffset
	//	label	not set for HomeOffset
	//	unit	not set for HomeOffset
	homeoffset_prop.set_standard_unit("units");
	//	display_unit	not set for HomeOffset
	homeoffset_prop.set_format("%10.3f");
	//	max_value	not set for HomeOffset
	//	min_value	not set for HomeOffset
	//	max_alarm	not set for HomeOffset
	//	min_alarm	not set for HomeOffset
	//	max_warning	not set for HomeOffset
	//	min_warning	not set for HomeOffset
	//	delta_t	not set for HomeOffset
	//	delta_val	not set for HomeOffset
	
	homeoffset->set_default_properties(homeoffset_prop);
	//	Not Polled
	homeoffset->set_disp_level(Tango::OPERATOR);
	//	Not Memorized
	att_list.push_back(homeoffset);

	//	Attribute : SoftCwLimit
	SoftCwLimitAttrib	*softcwlimit = new SoftCwLimitAttrib();
	Tango::UserDefaultAttrProp	softcwlimit_prop;
	//	description	not set for SoftCwLimit
	//	label	not set for SoftCwLimit
	//	unit	not set for SoftCwLimit
	//	standard_unit	not set for SoftCwLimit
	//	display_unit	not set for SoftCwLimit
	softcwlimit_prop.set_format("%10.3f");
	//	max_value	not set for SoftCwLimit
	//	min_value	not set for SoftCwLimit
	//	max_alarm	not set for SoftCwLimit
	//	min_alarm	not set for SoftCwLimit
	//	max_warning	not set for SoftCwLimit
	//	min_warning	not set for SoftCwLimit
	//	delta_t	not set for SoftCwLimit
	//	delta_val	not set for SoftCwLimit
	
	softcwlimit->set_default_properties(softcwlimit_prop);
	//	Not Polled
	softcwlimit->set_disp_level(Tango::OPERATOR);
	//	Not Memorized
	att_list.push_back(softcwlimit);

	//	Attribute : SoftCcwLimit
	SoftCcwLimitAttrib	*softccwlimit = new SoftCcwLimitAttrib();
	Tango::UserDefaultAttrProp	softccwlimit_prop;
	//	description	not set for SoftCcwLimit
	//	label	not set for SoftCcwLimit
	//	unit	not set for SoftCcwLimit
	//	standard_unit	not set for SoftCcwLimit
	//	display_unit	not set for SoftCcwLimit
	softccwlimit_prop.set_format("%10.3f");
	//	max_value	not set for SoftCcwLimit
	//	min_value	not set for SoftCcwLimit
	//	max_alarm	not set for SoftCcwLimit
	//	min_alarm	not set for SoftCcwLimit
	//	max_warning	not set for SoftCcwLimit
	//	min_warning	not set for SoftCcwLimit
	//	delta_t	not set for SoftCcwLimit
	//	delta_val	not set for SoftCcwLimit
	
	softccwlimit->set_default_properties(softccwlimit_prop);
	//	Not Polled
	softccwlimit->set_disp_level(Tango::OPERATOR);
	//	Not Memorized
	att_list.push_back(softccwlimit);

	//	Attribute : SoftLimitEnable
	SoftLimitEnableAttrib	*softlimitenable = new SoftLimitEnableAttrib();
	Tango::UserDefaultAttrProp	softlimitenable_prop;
	//	description	not set for SoftLimitEnable
	//	label	not set for SoftLimitEnable
	//	unit	not set for SoftLimitEnable
	//	standard_unit	not set for SoftLimitEnable
	//	display_unit	not set for SoftLimitEnable
	//	format	not set for SoftLimitEnable
	//	max_value	not set for SoftLimitEnable
	//	min_value	not set for SoftLimitEnable
	//	max_alarm	not set for SoftLimitEnable
	//	min_alarm	not set for SoftLimitEnable
	//	max_warning	not set for SoftLimitEnable
	//	min_warning	not set for SoftLimitEnable
	//	delta_t	not set for SoftLimitEnable
	//	delta_val	not set for SoftLimitEnable
	
	softlimitenable->set_default_properties(softlimitenable_prop);
	//	Not Polled
	softlimitenable->set_disp_level(Tango::OPERATOR);
	//	Not Memorized
	att_list.push_back(softlimitenable);

	//	Attribute : SoftCwLimitFault
	SoftCwLimitFaultAttrib	*softcwlimitfault = new SoftCwLimitFaultAttrib();
	Tango::UserDefaultAttrProp	softcwlimitfault_prop;
	//	description	not set for SoftCwLimitFault
	//	label	not set for SoftCwLimitFault
	//	unit	not set for SoftCwLimitFault
	//	standard_unit	not set for SoftCwLimitFault
	//	display_unit	not set for SoftCwLimitFault
	//	format	not set for SoftCwLimitFault
	//	max_value	not set for SoftCwLimitFault
	//	min_value	not set for SoftCwLimitFault
	//	max_alarm	not set for SoftCwLimitFault
	//	min_alarm	not set for SoftCwLimitFault
	//	max_warning	not set for SoftCwLimitFault
	//	min_warning	not set for SoftCwLimitFault
	//	delta_t	not set for SoftCwLimitFault
	//	delta_val	not set for SoftCwLimitFault
	
	softcwlimitfault->set_default_properties(softcwlimitfault_prop);
	//	Not Polled
	softcwlimitfault->set_disp_level(Tango::OPERATOR);
	//	Not Memorized
	att_list.push_back(softcwlimitfault);

	//	Attribute : SoftCcwLimitFault
	SoftCcwLimitFaultAttrib	*softccwlimitfault = new SoftCcwLimitFaultAttrib();
	Tango::UserDefaultAttrProp	softccwlimitfault_prop;
	//	description	not set for SoftCcwLimitFault
	//	label	not set for SoftCcwLimitFault
	//	unit	not set for SoftCcwLimitFault
	//	standard_unit	not set for SoftCcwLimitFault
	//	display_unit	not set for SoftCcwLimitFault
	//	format	not set for SoftCcwLimitFault
	//	max_value	not set for SoftCcwLimitFault
	//	min_value	not set for SoftCcwLimitFault
	//	max_alarm	not set for SoftCcwLimitFault
	//	min_alarm	not set for SoftCcwLimitFault
	//	max_warning	not set for SoftCcwLimitFault
	//	min_warning	not set for SoftCcwLimitFault
	//	delta_t	not set for SoftCcwLimitFault
	//	delta_val	not set for SoftCcwLimitFault
	
	softccwlimitfault->set_default_properties(softccwlimitfault_prop);
	//	Not Polled
	softccwlimitfault->set_disp_level(Tango::OPERATOR);
	//	Not Memorized
	att_list.push_back(softccwlimitfault);

	//	Attribute : CwLimitFault
	CwLimitFaultAttrib	*cwlimitfault = new CwLimitFaultAttrib();
	Tango::UserDefaultAttrProp	cwlimitfault_prop;
	//	description	not set for CwLimitFault
	//	label	not set for CwLimitFault
	//	unit	not set for CwLimitFault
	//	standard_unit	not set for CwLimitFault
	//	display_unit	not set for CwLimitFault
	//	format	not set for CwLimitFault
	//	max_value	not set for CwLimitFault
	//	min_value	not set for CwLimitFault
	//	max_alarm	not set for CwLimitFault
	//	min_alarm	not set for CwLimitFault
	//	max_warning	not set for CwLimitFault
	//	min_warning	not set for CwLimitFault
	//	delta_t	not set for CwLimitFault
	//	delta_val	not set for CwLimitFault
	
	cwlimitfault->set_default_properties(cwlimitfault_prop);
	//	Not Polled
	cwlimitfault->set_disp_level(Tango::OPERATOR);
	//	Not Memorized
	att_list.push_back(cwlimitfault);

	//	Attribute : CcwLimitFault
	CcwLimitFaultAttrib	*ccwlimitfault = new CcwLimitFaultAttrib();
	Tango::UserDefaultAttrProp	ccwlimitfault_prop;
	//	description	not set for CcwLimitFault
	//	label	not set for CcwLimitFault
	//	unit	not set for CcwLimitFault
	//	standard_unit	not set for CcwLimitFault
	//	display_unit	not set for CcwLimitFault
	//	format	not set for CcwLimitFault
	//	max_value	not set for CcwLimitFault
	//	min_value	not set for CcwLimitFault
	//	max_alarm	not set for CcwLimitFault
	//	min_alarm	not set for CcwLimitFault
	//	max_warning	not set for CcwLimitFault
	//	min_warning	not set for CcwLimitFault
	//	delta_t	not set for CcwLimitFault
	//	delta_val	not set for CcwLimitFault
	
	ccwlimitfault->set_default_properties(ccwlimitfault_prop);
	//	Not Polled
	ccwlimitfault->set_disp_level(Tango::OPERATOR);
	//	Not Memorized
	att_list.push_back(ccwlimitfault);

	//	Attribute : MotorStates
	MotorStatesAttrib	*motorstates = new MotorStatesAttrib();
	Tango::UserDefaultAttrProp	motorstates_prop;
	//	description	not set for MotorStates
	//	label	not set for MotorStates
	//	unit	not set for MotorStates
	//	standard_unit	not set for MotorStates
	//	display_unit	not set for MotorStates
	//	format	not set for MotorStates
	//	max_value	not set for MotorStates
	//	min_value	not set for MotorStates
	//	max_alarm	not set for MotorStates
	//	min_alarm	not set for MotorStates
	//	max_warning	not set for MotorStates
	//	min_warning	not set for MotorStates
	//	delta_t	not set for MotorStates
	//	delta_val	not set for MotorStates
	
	motorstates->set_default_properties(motorstates_prop);
	//	Not Polled
	motorstates->set_disp_level(Tango::EXPERT);
	//	Not Memorized
	att_list.push_back(motorstates);


	//	Create a list of static attributes
	create_static_attribute_list(get_class_attr()->get_attr_list());
	/*----- PROTECTED REGION ID(PowerPMAC_MotorClass::attribute_factory_after) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_MotorClass::attribute_factory_after
}
//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_MotorClass::pipe_factory()
 *	Description : Create the pipe object(s)
 *                and store them in the pipe list
 */
//--------------------------------------------------------
void PowerPMAC_MotorClass::pipe_factory()
{
	/*----- PROTECTED REGION ID(PowerPMAC_MotorClass::pipe_factory_before) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_MotorClass::pipe_factory_before
	/*----- PROTECTED REGION ID(PowerPMAC_MotorClass::pipe_factory_after) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_MotorClass::pipe_factory_after
}
//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_MotorClass::command_factory()
 *	Description : Create the command object(s)
 *                and store them in the command list
 */
//--------------------------------------------------------
void PowerPMAC_MotorClass::command_factory()
{
	/*----- PROTECTED REGION ID(PowerPMAC_MotorClass::command_factory_before) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_MotorClass::command_factory_before


	//	Command Phase
	PhaseClass	*pPhaseCmd =
		new PhaseClass("Phase",
			Tango::DEV_VOID, Tango::DEV_VOID,
			"",
			"",
			Tango::OPERATOR);
	command_list.push_back(pPhaseCmd);

	//	Command Home
	HomeClass	*pHomeCmd =
		new HomeClass("Home",
			Tango::DEV_VOID, Tango::DEV_VOID,
			"",
			"",
			Tango::OPERATOR);
	command_list.push_back(pHomeCmd);

	//	Command Calibrate
	CalibrateClass	*pCalibrateCmd =
		new CalibrateClass("Calibrate",
			Tango::DEV_VOID, Tango::DEV_VOID,
			"",
			"",
			Tango::OPERATOR);
	command_list.push_back(pCalibrateCmd);

	//	Command Enable
	EnableClass	*pEnableCmd =
		new EnableClass("Enable",
			Tango::DEV_VOID, Tango::DEV_VOID,
			"",
			"",
			Tango::EXPERT);
	command_list.push_back(pEnableCmd);

	//	Command Disable
	DisableClass	*pDisableCmd =
		new DisableClass("Disable",
			Tango::DEV_VOID, Tango::DEV_VOID,
			"",
			"",
			Tango::EXPERT);
	command_list.push_back(pDisableCmd);

	//	Command Stop
	StopClass	*pStopCmd =
		new StopClass("Stop",
			Tango::DEV_VOID, Tango::DEV_VOID,
			"",
			"",
			Tango::OPERATOR);
	command_list.push_back(pStopCmd);

	//	Command Kill
	KillClass	*pKillCmd =
		new KillClass("Kill",
			Tango::DEV_VOID, Tango::DEV_VOID,
			"",
			"",
			Tango::OPERATOR);
	command_list.push_back(pKillCmd);

	//	Command ActivateAndReset
	ActivateAndResetClass	*pActivateAndResetCmd =
		new ActivateAndResetClass("ActivateAndReset",
			Tango::DEV_VOID, Tango::DEV_VOID,
			"",
			"",
			Tango::OPERATOR);
	command_list.push_back(pActivateAndResetCmd);

	/*----- PROTECTED REGION ID(PowerPMAC_MotorClass::command_factory_after) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_MotorClass::command_factory_after
}

//===================================================================
//	Dynamic attributes related methods
//===================================================================

//--------------------------------------------------------
/**
 * method : 		PowerPMAC_MotorClass::create_static_attribute_list
 * description : 	Create the a list of static attributes
 *
 * @param	att_list	the ceated attribute list
 */
//--------------------------------------------------------
void PowerPMAC_MotorClass::create_static_attribute_list(vector<Tango::Attr *> &att_list)
{
	for (unsigned long i=0 ; i<att_list.size() ; i++)
	{
		string att_name(att_list[i]->get_name());
		transform(att_name.begin(), att_name.end(), att_name.begin(), ::tolower);
		defaultAttList.push_back(att_name);
	}

	cout2 << defaultAttList.size() << " attributes in default list" << endl;

	/*----- PROTECTED REGION ID(PowerPMAC_MotorClass::create_static_att_list) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_MotorClass::create_static_att_list
}


//--------------------------------------------------------
/**
 * method : 		PowerPMAC_MotorClass::erase_dynamic_attributes
 * description : 	delete the dynamic attributes if any.
 *
 * @param	devlist_ptr	the device list pointer
 * @param	list of all attributes
 */
//--------------------------------------------------------
void PowerPMAC_MotorClass::erase_dynamic_attributes(const Tango::DevVarStringArray *devlist_ptr, vector<Tango::Attr *> &att_list)
{
	Tango::Util *tg = Tango::Util::instance();

	for (unsigned long i=0 ; i<devlist_ptr->length() ; i++)
	{
		Tango::DeviceImpl *dev_impl = tg->get_device_by_name(((string)(*devlist_ptr)[i]).c_str());
		PowerPMAC_Motor *dev = static_cast<PowerPMAC_Motor *> (dev_impl);

		vector<Tango::Attribute *> &dev_att_list = dev->get_device_attr()->get_attribute_list();
		vector<Tango::Attribute *>::iterator ite_att;
		for (ite_att=dev_att_list.begin() ; ite_att != dev_att_list.end() ; ++ite_att)
		{
			string att_name((*ite_att)->get_name_lower());
			if ((att_name == "state") || (att_name == "status"))
				continue;
			vector<string>::iterator ite_str = find(defaultAttList.begin(), defaultAttList.end(), att_name);
			if (ite_str == defaultAttList.end())
			{
				cout2 << att_name << " is a UNWANTED dynamic attribute for device " << (*devlist_ptr)[i] << endl;
				Tango::Attribute &att = dev->get_device_attr()->get_attr_by_name(att_name.c_str());
				dev->remove_attribute(att_list[att.get_attr_idx()], true, false);
				--ite_att;
			}
		}
	}
	/*----- PROTECTED REGION ID(PowerPMAC_MotorClass::erase_dynamic_attributes) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_MotorClass::erase_dynamic_attributes
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_MotorClass::get_attr_by_name()
 *	Description : returns Tango::Attr * object found by name
 */
//--------------------------------------------------------
Tango::Attr *PowerPMAC_MotorClass::get_attr_object_by_name(vector<Tango::Attr *> &att_list, string attname)
{
	vector<Tango::Attr *>::iterator it;
	for (it=att_list.begin() ; it<att_list.end() ; ++it)
		if ((*it)->get_name()==attname)
			return (*it);
	//	Attr does not exist
	return NULL;
}


/*----- PROTECTED REGION ID(PowerPMAC_MotorClass::Additional Methods) ENABLED START -----*/

/*----- PROTECTED REGION END -----*/	//	PowerPMAC_MotorClass::Additional Methods
} //	namespace
