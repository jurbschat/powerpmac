/*----- PROTECTED REGION ID(PowerPMAC_ProgramsClass.h) ENABLED START -----*/
//=============================================================================
//
// file :        PowerPMAC_ProgramsClass.h
//
// description : Include for the PowerPMAC_Programs root class.
//               This class is the singleton class for
//                the PowerPMAC_Programs device class.
//               It contains all properties and methods which the 
//               PowerPMAC_Programs requires only once e.g. the commands.
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


#ifndef PowerPMAC_ProgramsClass_H
#define PowerPMAC_ProgramsClass_H

#include <tango.h>
#include <PowerPMAC_Programs.h>


/*----- PROTECTED REGION END -----*/	//	PowerPMAC_ProgramsClass.h


namespace PowerPMAC_Programs_ns
{
/*----- PROTECTED REGION ID(PowerPMAC_ProgramsClass::classes for dynamic creation) ENABLED START -----*/


/*----- PROTECTED REGION END -----*/	//	PowerPMAC_ProgramsClass::classes for dynamic creation

/**
 *	The PowerPMAC_ProgramsClass singleton definition
 */

#ifdef _TG_WINDOWS_
class __declspec(dllexport)  PowerPMAC_ProgramsClass : public Tango::DeviceClass
#else
class PowerPMAC_ProgramsClass : public Tango::DeviceClass
#endif
{
	/*----- PROTECTED REGION ID(PowerPMAC_ProgramsClass::Additionnal DServer data members) ENABLED START -----*/
	
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_ProgramsClass::Additionnal DServer data members

	public:
		//	write class properties data members
		Tango::DbData	cl_prop;
		Tango::DbData	cl_def_prop;
		Tango::DbData	dev_def_prop;
	
		//	Method prototypes
		static PowerPMAC_ProgramsClass *init(const char *);
		static PowerPMAC_ProgramsClass *instance();
		~PowerPMAC_ProgramsClass();
		Tango::DbDatum	get_class_property(string &);
		Tango::DbDatum	get_default_device_property(string &);
		Tango::DbDatum	get_default_class_property(string &);
	
	protected:
		PowerPMAC_ProgramsClass(string &);
		static PowerPMAC_ProgramsClass *_instance;
		void command_factory();
		void attribute_factory(vector<Tango::Attr *> &);
		void pipe_factory();
		void write_class_property();
		void set_default_property();
		void get_class_property();
		string get_cvstag();
		string get_cvsroot();
	
	private:
		void device_factory(const Tango::DevVarStringArray *);
		void create_static_attribute_list(vector<Tango::Attr *> &);
		void erase_dynamic_attributes(const Tango::DevVarStringArray *,vector<Tango::Attr *> &);
		vector<string>	defaultAttList;
		Tango::Attr *get_attr_object_by_name(vector<Tango::Attr *> &att_list, string attname);
};

}	//	End of namespace

#endif   //	PowerPMAC_Programs_H