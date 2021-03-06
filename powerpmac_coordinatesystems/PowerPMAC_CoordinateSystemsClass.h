/*----- PROTECTED REGION ID(PowerPMAC_CoordinateSystemsClass.h) ENABLED START -----*/
//=============================================================================
//
// file :        PowerPMAC_CoordinateSystemsClass.h
//
// description : Include for the PowerPMAC_CoordinateSystems root class.
//               This class is the singleton class for
//                the PowerPMAC_CoordinateSystems device class.
//               It contains all properties and methods which the 
//               PowerPMAC_CoordinateSystems requires only once e.g. the commands.
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


#ifndef PowerPMAC_CoordinateSystemsClass_H
#define PowerPMAC_CoordinateSystemsClass_H

#include <tango.h>
#include <PowerPMAC_CoordinateSystems.h>


/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CoordinateSystemsClass.h


namespace PowerPMAC_CoordinateSystems_ns
{
/*----- PROTECTED REGION ID(PowerPMAC_CoordinateSystemsClass::classes for dynamic creation) ENABLED START -----*/


/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CoordinateSystemsClass::classes for dynamic creation

//=========================================
//	Define classes for attributes
//=========================================
//	Attribute NumAxis class definition
class NumAxisAttrib: public Tango::Attr
{
public:
	NumAxisAttrib():Attr("NumAxis",
			Tango::DEV_LONG, Tango::READ) {};
	~NumAxisAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<PowerPMAC_CoordinateSystems *>(dev))->read_NumAxis(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<PowerPMAC_CoordinateSystems *>(dev))->is_NumAxis_allowed(ty);}
};

//	Attribute CoordStates class definition
class CoordStatesAttrib: public Tango::Attr
{
public:
	CoordStatesAttrib():Attr("CoordStates",
			Tango::DEV_STRING, Tango::READ) {};
	~CoordStatesAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<PowerPMAC_CoordinateSystems *>(dev))->read_CoordStates(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<PowerPMAC_CoordinateSystems *>(dev))->is_CoordStates_allowed(ty);}
};

//	Attribute AxisMapping class definition
class AxisMappingAttrib: public Tango::SpectrumAttr
{
public:
	AxisMappingAttrib():SpectrumAttr("AxisMapping",
			Tango::DEV_STRING, Tango::READ, 26) {};
	~AxisMappingAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<PowerPMAC_CoordinateSystems *>(dev))->read_AxisMapping(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<PowerPMAC_CoordinateSystems *>(dev))->is_AxisMapping_allowed(ty);}
};


//=========================================
//	Define classes for commands
//=========================================
//	Command Abort class definition
class AbortClass : public Tango::Command
{
public:
	AbortClass(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out,
				   const char        *in_desc,
				   const char        *out_desc,
				   Tango::DispLevel  level)
	:Command(name,in,out,in_desc,out_desc, level)	{};

	AbortClass(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out)
	:Command(name,in,out)	{};
	~AbortClass() {};
	
	virtual CORBA::Any *execute (Tango::DeviceImpl *dev, const CORBA::Any &any);
	virtual bool is_allowed (Tango::DeviceImpl *dev, const CORBA::Any &any)
	{return (static_cast<PowerPMAC_CoordinateSystems *>(dev))->is_Abort_allowed(any);}
};

//	Command RunMotionProgram class definition
class RunMotionProgramClass : public Tango::Command
{
public:
	RunMotionProgramClass(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out,
				   const char        *in_desc,
				   const char        *out_desc,
				   Tango::DispLevel  level)
	:Command(name,in,out,in_desc,out_desc, level)	{};

	RunMotionProgramClass(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out)
	:Command(name,in,out)	{};
	~RunMotionProgramClass() {};
	
	virtual CORBA::Any *execute (Tango::DeviceImpl *dev, const CORBA::Any &any);
	virtual bool is_allowed (Tango::DeviceImpl *dev, const CORBA::Any &any)
	{return (static_cast<PowerPMAC_CoordinateSystems *>(dev))->is_RunMotionProgram_allowed(any);}
};

//	Command MultiAxisMove class definition
class MultiAxisMoveClass : public Tango::Command
{
public:
	MultiAxisMoveClass(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out,
				   const char        *in_desc,
				   const char        *out_desc,
				   Tango::DispLevel  level)
	:Command(name,in,out,in_desc,out_desc, level)	{};

	MultiAxisMoveClass(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out)
	:Command(name,in,out)	{};
	~MultiAxisMoveClass() {};
	
	virtual CORBA::Any *execute (Tango::DeviceImpl *dev, const CORBA::Any &any);
	virtual bool is_allowed (Tango::DeviceImpl *dev, const CORBA::Any &any)
	{return (static_cast<PowerPMAC_CoordinateSystems *>(dev))->is_MultiAxisMove_allowed(any);}
};


/**
 *	The PowerPMAC_CoordinateSystemsClass singleton definition
 */

#ifdef _TG_WINDOWS_
class __declspec(dllexport)  PowerPMAC_CoordinateSystemsClass : public Tango::DeviceClass
#else
class PowerPMAC_CoordinateSystemsClass : public Tango::DeviceClass
#endif
{
	/*----- PROTECTED REGION ID(PowerPMAC_CoordinateSystemsClass::Additionnal DServer data members) ENABLED START -----*/
	
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CoordinateSystemsClass::Additionnal DServer data members

	public:
		//	write class properties data members
		Tango::DbData	cl_prop;
		Tango::DbData	cl_def_prop;
		Tango::DbData	dev_def_prop;
	
		//	Method prototypes
		static PowerPMAC_CoordinateSystemsClass *init(const char *);
		static PowerPMAC_CoordinateSystemsClass *instance();
		~PowerPMAC_CoordinateSystemsClass();
		Tango::DbDatum	get_class_property(string &);
		Tango::DbDatum	get_default_device_property(string &);
		Tango::DbDatum	get_default_class_property(string &);
	
	protected:
		PowerPMAC_CoordinateSystemsClass(string &);
		static PowerPMAC_CoordinateSystemsClass *_instance;
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

#endif   //	PowerPMAC_CoordinateSystems_H
