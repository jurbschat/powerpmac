/*----- PROTECTED REGION ID(PowerPMAC_CompensationTableClass.cpp) ENABLED START -----*/
//=============================================================================
//
// file :        PowerPMAC_CompensationTableClass.cpp
//
// description : C++ source for the PowerPMAC_CompensationTableClass.
//               A singleton class derived from DeviceClass.
//               It implements the command and attribute list
//               and all properties and methods required
//               by the PowerPMAC_CompensationTable once per process.
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


#include <PowerPMAC_CompensationTableClass.h>

/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CompensationTableClass.cpp

//-------------------------------------------------------------------
/**
 *	Create PowerPMAC_CompensationTableClass singleton and
 *	return it in a C function for Python usage
 */
//-------------------------------------------------------------------
extern "C" {
#ifdef _TG_WINDOWS_

__declspec(dllexport)

#endif

	Tango::DeviceClass *_create_PowerPMAC_CompensationTable_class(const char *name) {
		return PowerPMAC_CompensationTable_ns::PowerPMAC_CompensationTableClass::init(name);
	}
}

namespace PowerPMAC_CompensationTable_ns
{
//===================================================================
//	Initialize pointer for singleton pattern
//===================================================================
PowerPMAC_CompensationTableClass *PowerPMAC_CompensationTableClass::_instance = NULL;

//--------------------------------------------------------
/**
 * method : 		PowerPMAC_CompensationTableClass::PowerPMAC_CompensationTableClass(string &s)
 * description : 	constructor for the PowerPMAC_CompensationTableClass
 *
 * @param s	The class name
 */
//--------------------------------------------------------
PowerPMAC_CompensationTableClass::PowerPMAC_CompensationTableClass(string &s):Tango::DeviceClass(s)
{
	cout2 << "Entering PowerPMAC_CompensationTableClass constructor" << endl;
	set_default_property();
	write_class_property();

	/*----- PROTECTED REGION ID(PowerPMAC_CompensationTableClass::constructor) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CompensationTableClass::constructor

	cout2 << "Leaving PowerPMAC_CompensationTableClass constructor" << endl;
}

//--------------------------------------------------------
/**
 * method : 		PowerPMAC_CompensationTableClass::~PowerPMAC_CompensationTableClass()
 * description : 	destructor for the PowerPMAC_CompensationTableClass
 */
//--------------------------------------------------------
PowerPMAC_CompensationTableClass::~PowerPMAC_CompensationTableClass()
{
	/*----- PROTECTED REGION ID(PowerPMAC_CompensationTableClass::destructor) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CompensationTableClass::destructor

	_instance = NULL;
}


//--------------------------------------------------------
/**
 * method : 		PowerPMAC_CompensationTableClass::init
 * description : 	Create the object if not already done.
 *                  Otherwise, just return a pointer to the object
 *
 * @param	name	The class name
 */
//--------------------------------------------------------
PowerPMAC_CompensationTableClass *PowerPMAC_CompensationTableClass::init(const char *name)
{
	if (_instance == NULL)
	{
		try
		{
			string s(name);
			_instance = new PowerPMAC_CompensationTableClass(s);
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
 * method : 		PowerPMAC_CompensationTableClass::instance
 * description : 	Check if object already created,
 *                  and return a pointer to the object
 */
//--------------------------------------------------------
PowerPMAC_CompensationTableClass *PowerPMAC_CompensationTableClass::instance()
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

//===================================================================
//	Properties management
//===================================================================
//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_CompensationTableClass::get_class_property()
 *	Description : Get the class property for specified name.
 */
//--------------------------------------------------------
Tango::DbDatum PowerPMAC_CompensationTableClass::get_class_property(string &prop_name)
{
	for (unsigned int i=0 ; i<cl_prop.size() ; i++)
		if (cl_prop[i].name == prop_name)
			return cl_prop[i];
	//	if not found, returns  an empty DbDatum
	return Tango::DbDatum(prop_name);
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_CompensationTableClass::get_default_device_property()
 *	Description : Return the default value for device property.
 */
//--------------------------------------------------------
Tango::DbDatum PowerPMAC_CompensationTableClass::get_default_device_property(string &prop_name)
{
	for (unsigned int i=0 ; i<dev_def_prop.size() ; i++)
		if (dev_def_prop[i].name == prop_name)
			return dev_def_prop[i];
	//	if not found, return  an empty DbDatum
	return Tango::DbDatum(prop_name);
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_CompensationTableClass::get_default_class_property()
 *	Description : Return the default value for class property.
 */
//--------------------------------------------------------
Tango::DbDatum PowerPMAC_CompensationTableClass::get_default_class_property(string &prop_name)
{
	for (unsigned int i=0 ; i<cl_def_prop.size() ; i++)
		if (cl_def_prop[i].name == prop_name)
			return cl_def_prop[i];
	//	if not found, return  an empty DbDatum
	return Tango::DbDatum(prop_name);
}


//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_CompensationTableClass::set_default_property()
 *	Description : Set default property (class and device) for wizard.
 *                For each property, add to wizard property name and description.
 *                If default value has been set, add it to wizard property and
 *                store it in a DbDatum.
 */
//--------------------------------------------------------
void PowerPMAC_CompensationTableClass::set_default_property()
{
	string	prop_name;
	string	prop_desc;
	string	prop_def;
	vector<string>	vect_data;

	//	Set Default Class Properties

	//	Set Default device Properties
	prop_name = "TableID";
	prop_desc = "The table id specifies the slot that this device server will use for its compensation table. \nThere are 256 slots but every slot takes computation time, therefore ids should be used \nconsecutive starting from 0 as we can only enable an amount of tables, not specific ids.\nE.g.: three device servers with the ids 0, 1 and 2 means we have to enable three tables,\ntwo device servers with the ids 5 and 7 means we have to enable 7 compensation \ntables on the pmac.";
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
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_CompensationTableClass::write_class_property()
 *	Description : Set class description fields as property in database
 */
//--------------------------------------------------------
void PowerPMAC_CompensationTableClass::write_class_property()
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
 *	Method      : PowerPMAC_CompensationTableClass::device_factory()
 *	Description : Create the device object(s)
 *                and store them in the device list
 */
//--------------------------------------------------------
void PowerPMAC_CompensationTableClass::device_factory(const Tango::DevVarStringArray *devlist_ptr)
{
	/*----- PROTECTED REGION ID(PowerPMAC_CompensationTableClass::device_factory_before) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CompensationTableClass::device_factory_before

	//	Create devices and add it into the device list
	for (unsigned long i=0 ; i<devlist_ptr->length() ; i++)
	{
		cout4 << "Device name : " << (*devlist_ptr)[i].in() << endl;
		device_list.push_back(new PowerPMAC_CompensationTable(this, (*devlist_ptr)[i]));
	}

	//	Manage dynamic attributes if any
	erase_dynamic_attributes(devlist_ptr, get_class_attr()->get_attr_list());

	//	Export devices to the outside world
	for (unsigned long i=1 ; i<=devlist_ptr->length() ; i++)
	{
		//	Add dynamic attributes if any
		PowerPMAC_CompensationTable *dev = static_cast<PowerPMAC_CompensationTable *>(device_list[device_list.size()-i]);
		dev->add_dynamic_attributes();

		//	Check before if database used.
		if ((Tango::Util::_UseDb == true) && (Tango::Util::_FileDb == false))
			export_device(dev);
		else
			export_device(dev, dev->get_name().c_str());
	}

	/*----- PROTECTED REGION ID(PowerPMAC_CompensationTableClass::device_factory_after) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CompensationTableClass::device_factory_after
}
//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_CompensationTableClass::attribute_factory()
 *	Description : Create the attribute object(s)
 *                and store them in the attribute list
 */
//--------------------------------------------------------
void PowerPMAC_CompensationTableClass::attribute_factory(vector<Tango::Attr *> &att_list)
{
	/*----- PROTECTED REGION ID(PowerPMAC_CompensationTableClass::attribute_factory_before) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CompensationTableClass::attribute_factory_before
	//	Attribute : SourceMotor
	SourceMotorAttrib	*sourcemotor = new SourceMotorAttrib();
	Tango::UserDefaultAttrProp	sourcemotor_prop;
	//	description	not set for SourceMotor
	//	label	not set for SourceMotor
	//	unit	not set for SourceMotor
	//	standard_unit	not set for SourceMotor
	//	display_unit	not set for SourceMotor
	//	format	not set for SourceMotor
	//	max_value	not set for SourceMotor
	//	min_value	not set for SourceMotor
	//	max_alarm	not set for SourceMotor
	//	min_alarm	not set for SourceMotor
	//	max_warning	not set for SourceMotor
	//	min_warning	not set for SourceMotor
	//	delta_t	not set for SourceMotor
	//	delta_val	not set for SourceMotor
	
	sourcemotor->set_default_properties(sourcemotor_prop);
	//	Not Polled
	sourcemotor->set_disp_level(Tango::OPERATOR);
	//	Not Memorized
	att_list.push_back(sourcemotor);

	//	Attribute : TargetMotor
	TargetMotorAttrib	*targetmotor = new TargetMotorAttrib();
	Tango::UserDefaultAttrProp	targetmotor_prop;
	//	description	not set for TargetMotor
	//	label	not set for TargetMotor
	//	unit	not set for TargetMotor
	//	standard_unit	not set for TargetMotor
	//	display_unit	not set for TargetMotor
	//	format	not set for TargetMotor
	//	max_value	not set for TargetMotor
	//	min_value	not set for TargetMotor
	//	max_alarm	not set for TargetMotor
	//	min_alarm	not set for TargetMotor
	//	max_warning	not set for TargetMotor
	//	min_warning	not set for TargetMotor
	//	delta_t	not set for TargetMotor
	//	delta_val	not set for TargetMotor
	
	targetmotor->set_default_properties(targetmotor_prop);
	//	Not Polled
	targetmotor->set_disp_level(Tango::OPERATOR);
	//	Not Memorized
	att_list.push_back(targetmotor);

	//	Attribute : From
	FromAttrib	*from = new FromAttrib();
	Tango::UserDefaultAttrProp	from_prop;
	//	description	not set for From
	//	label	not set for From
	//	unit	not set for From
	//	standard_unit	not set for From
	//	display_unit	not set for From
	//	format	not set for From
	//	max_value	not set for From
	//	min_value	not set for From
	//	max_alarm	not set for From
	//	min_alarm	not set for From
	//	max_warning	not set for From
	//	min_warning	not set for From
	//	delta_t	not set for From
	//	delta_val	not set for From
	
	from->set_default_properties(from_prop);
	//	Not Polled
	from->set_disp_level(Tango::OPERATOR);
	//	Not Memorized
	att_list.push_back(from);

	//	Attribute : To
	ToAttrib	*to = new ToAttrib();
	Tango::UserDefaultAttrProp	to_prop;
	//	description	not set for To
	//	label	not set for To
	//	unit	not set for To
	//	standard_unit	not set for To
	//	display_unit	not set for To
	//	format	not set for To
	//	max_value	not set for To
	//	min_value	not set for To
	//	max_alarm	not set for To
	//	min_alarm	not set for To
	//	max_warning	not set for To
	//	min_warning	not set for To
	//	delta_t	not set for To
	//	delta_val	not set for To
	
	to->set_default_properties(to_prop);
	//	Not Polled
	to->set_disp_level(Tango::OPERATOR);
	//	Not Memorized
	att_list.push_back(to);

	//	Attribute : CompensationTable
	CompensationTableAttrib	*compensationtable = new CompensationTableAttrib();
	Tango::UserDefaultAttrProp	compensationtable_prop;
	//	description	not set for CompensationTable
	//	label	not set for CompensationTable
	//	unit	not set for CompensationTable
	//	standard_unit	not set for CompensationTable
	//	display_unit	not set for CompensationTable
	//	format	not set for CompensationTable
	//	max_value	not set for CompensationTable
	//	min_value	not set for CompensationTable
	//	max_alarm	not set for CompensationTable
	//	min_alarm	not set for CompensationTable
	//	max_warning	not set for CompensationTable
	//	min_warning	not set for CompensationTable
	//	delta_t	not set for CompensationTable
	//	delta_val	not set for CompensationTable
	
	compensationtable->set_default_properties(compensationtable_prop);
	//	Not Polled
	compensationtable->set_disp_level(Tango::OPERATOR);
	//	Not Memorized
	att_list.push_back(compensationtable);


	//	Create a list of static attributes
	create_static_attribute_list(get_class_attr()->get_attr_list());
	/*----- PROTECTED REGION ID(PowerPMAC_CompensationTableClass::attribute_factory_after) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CompensationTableClass::attribute_factory_after
}
//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_CompensationTableClass::pipe_factory()
 *	Description : Create the pipe object(s)
 *                and store them in the pipe list
 */
//--------------------------------------------------------
void PowerPMAC_CompensationTableClass::pipe_factory()
{
	/*----- PROTECTED REGION ID(PowerPMAC_CompensationTableClass::pipe_factory_before) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CompensationTableClass::pipe_factory_before
	/*----- PROTECTED REGION ID(PowerPMAC_CompensationTableClass::pipe_factory_after) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CompensationTableClass::pipe_factory_after
}
//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_CompensationTableClass::command_factory()
 *	Description : Create the command object(s)
 *                and store them in the command list
 */
//--------------------------------------------------------
void PowerPMAC_CompensationTableClass::command_factory()
{
	/*----- PROTECTED REGION ID(PowerPMAC_CompensationTableClass::command_factory_before) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CompensationTableClass::command_factory_before


	/*----- PROTECTED REGION ID(PowerPMAC_CompensationTableClass::command_factory_after) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CompensationTableClass::command_factory_after
}

//===================================================================
//	Dynamic attributes related methods
//===================================================================

//--------------------------------------------------------
/**
 * method : 		PowerPMAC_CompensationTableClass::create_static_attribute_list
 * description : 	Create the a list of static attributes
 *
 * @param	att_list	the ceated attribute list
 */
//--------------------------------------------------------
void PowerPMAC_CompensationTableClass::create_static_attribute_list(vector<Tango::Attr *> &att_list)
{
	for (unsigned long i=0 ; i<att_list.size() ; i++)
	{
		string att_name(att_list[i]->get_name());
		transform(att_name.begin(), att_name.end(), att_name.begin(), ::tolower);
		defaultAttList.push_back(att_name);
	}

	cout2 << defaultAttList.size() << " attributes in default list" << endl;

	/*----- PROTECTED REGION ID(PowerPMAC_CompensationTableClass::create_static_att_list) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CompensationTableClass::create_static_att_list
}


//--------------------------------------------------------
/**
 * method : 		PowerPMAC_CompensationTableClass::erase_dynamic_attributes
 * description : 	delete the dynamic attributes if any.
 *
 * @param	devlist_ptr	the device list pointer
 * @param	list of all attributes
 */
//--------------------------------------------------------
void PowerPMAC_CompensationTableClass::erase_dynamic_attributes(const Tango::DevVarStringArray *devlist_ptr, vector<Tango::Attr *> &att_list)
{
	Tango::Util *tg = Tango::Util::instance();

	for (unsigned long i=0 ; i<devlist_ptr->length() ; i++)
	{
		Tango::DeviceImpl *dev_impl = tg->get_device_by_name(((string)(*devlist_ptr)[i]).c_str());
		PowerPMAC_CompensationTable *dev = static_cast<PowerPMAC_CompensationTable *> (dev_impl);

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
	/*----- PROTECTED REGION ID(PowerPMAC_CompensationTableClass::erase_dynamic_attributes) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CompensationTableClass::erase_dynamic_attributes
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_CompensationTableClass::get_attr_by_name()
 *	Description : returns Tango::Attr * object found by name
 */
//--------------------------------------------------------
Tango::Attr *PowerPMAC_CompensationTableClass::get_attr_object_by_name(vector<Tango::Attr *> &att_list, string attname)
{
	vector<Tango::Attr *>::iterator it;
	for (it=att_list.begin() ; it<att_list.end() ; ++it)
		if ((*it)->get_name()==attname)
			return (*it);
	//	Attr does not exist
	return NULL;
}


/*----- PROTECTED REGION ID(PowerPMAC_CompensationTableClass::Additional Methods) ENABLED START -----*/

/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CompensationTableClass::Additional Methods
} //	namespace
