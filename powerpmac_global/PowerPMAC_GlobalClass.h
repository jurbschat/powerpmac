/*----- PROTECTED REGION ID(PowerPMAC_GlobalClass.h) ENABLED START -----*/
//=============================================================================
//
// file :        PowerPMAC_GlobalClass.h
//
// description : Include for the PowerPMAC_Global root class.
//               This class is the singleton class for
//                the PowerPMAC_Global device class.
//               It contains all properties and methods which the 
//               PowerPMAC_Global requires only once e.g. the commands.
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


#ifndef PowerPMAC_GlobalClass_H
#define PowerPMAC_GlobalClass_H

#include <tango.h>
#include <PowerPMAC_Global.h>


/*----- PROTECTED REGION END -----*/	//	PowerPMAC_GlobalClass.h


namespace PowerPMAC_Global_ns
{
/*----- PROTECTED REGION ID(PowerPMAC_GlobalClass::classes for dynamic creation) ENABLED START -----*/


/*----- PROTECTED REGION END -----*/	//	PowerPMAC_GlobalClass::classes for dynamic creation

//=========================================
//	Define classes for attributes
//=========================================
//	Attribute MaxMotors class definition
class MaxMotorsAttrib: public Tango::Attr
{
public:
	MaxMotorsAttrib():Attr("MaxMotors",
			Tango::DEV_LONG, Tango::READ) {};
	~MaxMotorsAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<PowerPMAC_Global *>(dev))->read_MaxMotors(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<PowerPMAC_Global *>(dev))->is_MaxMotors_allowed(ty);}
};

//	Attribute MaxCoords class definition
class MaxCoordsAttrib: public Tango::Attr
{
public:
	MaxCoordsAttrib():Attr("MaxCoords",
			Tango::DEV_LONG, Tango::READ) {};
	~MaxCoordsAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<PowerPMAC_Global *>(dev))->read_MaxCoords(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<PowerPMAC_Global *>(dev))->is_MaxCoords_allowed(ty);}
};

//	Attribute AbortAll class definition
class AbortAllAttrib: public Tango::Attr
{
public:
	AbortAllAttrib():Attr("AbortAll",
			Tango::DEV_BOOLEAN, Tango::READ) {};
	~AbortAllAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<PowerPMAC_Global *>(dev))->read_AbortAll(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<PowerPMAC_Global *>(dev))->is_AbortAll_allowed(ty);}
};

//	Attribute CpuTemp class definition
class CpuTempAttrib: public Tango::Attr
{
public:
	CpuTempAttrib():Attr("CpuTemp",
			Tango::DEV_DOUBLE, Tango::READ) {};
	~CpuTempAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<PowerPMAC_Global *>(dev))->read_CpuTemp(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<PowerPMAC_Global *>(dev))->is_CpuTemp_allowed(ty);}
};

//	Attribute AmpOverTemp class definition
class AmpOverTempAttrib: public Tango::Attr
{
public:
	AmpOverTempAttrib():Attr("AmpOverTemp",
			Tango::DEV_BOOLEAN, Tango::READ) {};
	~AmpOverTempAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<PowerPMAC_Global *>(dev))->read_AmpOverTemp(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<PowerPMAC_Global *>(dev))->is_AmpOverTemp_allowed(ty);}
};

//	Attribute Firmware class definition
class FirmwareAttrib: public Tango::Attr
{
public:
	FirmwareAttrib():Attr("Firmware",
			Tango::DEV_STRING, Tango::READ) {};
	~FirmwareAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<PowerPMAC_Global *>(dev))->read_Firmware(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<PowerPMAC_Global *>(dev))->is_Firmware_allowed(ty);}
};

//	Attribute SystemType class definition
class SystemTypeAttrib: public Tango::Attr
{
public:
	SystemTypeAttrib():Attr("SystemType",
			Tango::DEV_STRING, Tango::READ) {};
	~SystemTypeAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<PowerPMAC_Global *>(dev))->read_SystemType(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<PowerPMAC_Global *>(dev))->is_SystemType_allowed(ty);}
};

//	Attribute CpuType class definition
class CpuTypeAttrib: public Tango::Attr
{
public:
	CpuTypeAttrib():Attr("CpuType",
			Tango::DEV_STRING, Tango::READ) {};
	~CpuTypeAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<PowerPMAC_Global *>(dev))->read_CpuType(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<PowerPMAC_Global *>(dev))->is_CpuType_allowed(ty);}
};

//	Attribute CpuFrequency class definition
class CpuFrequencyAttrib: public Tango::Attr
{
public:
	CpuFrequencyAttrib():Attr("CpuFrequency",
			Tango::DEV_LONG, Tango::READ) {};
	~CpuFrequencyAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<PowerPMAC_Global *>(dev))->read_CpuFrequency(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<PowerPMAC_Global *>(dev))->is_CpuFrequency_allowed(ty);}
};

//	Attribute Uptime class definition
class UptimeAttrib: public Tango::Attr
{
public:
	UptimeAttrib():Attr("Uptime",
			Tango::DEV_STRING, Tango::READ) {};
	~UptimeAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<PowerPMAC_Global *>(dev))->read_Uptime(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<PowerPMAC_Global *>(dev))->is_Uptime_allowed(ty);}
};

//	Attribute ActiveCompensationTables class definition
class ActiveCompensationTablesAttrib: public Tango::Attr
{
public:
	ActiveCompensationTablesAttrib():Attr("ActiveCompensationTables",
			Tango::DEV_LONG, Tango::READ_WRITE) {};
	~ActiveCompensationTablesAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<PowerPMAC_Global *>(dev))->read_ActiveCompensationTables(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<PowerPMAC_Global *>(dev))->write_ActiveCompensationTables(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<PowerPMAC_Global *>(dev))->is_ActiveCompensationTables_allowed(ty);}
};

//	Attribute BrickLVMonitoring class definition
class BrickLVMonitoringAttrib: public Tango::Attr
{
public:
	BrickLVMonitoringAttrib():Attr("BrickLVMonitoring",
			Tango::DEV_BOOLEAN, Tango::READ_WRITE) {};
	~BrickLVMonitoringAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<PowerPMAC_Global *>(dev))->read_BrickLVMonitoring(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<PowerPMAC_Global *>(dev))->write_BrickLVMonitoring(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<PowerPMAC_Global *>(dev))->is_BrickLVMonitoring_allowed(ty);}
};

//	Attribute AmpStatus class definition
class AmpStatusAttrib: public Tango::SpectrumAttr
{
public:
	AmpStatusAttrib():SpectrumAttr("AmpStatus",
			Tango::DEV_STRING, Tango::READ, 8) {};
	~AmpStatusAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<PowerPMAC_Global *>(dev))->read_AmpStatus(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<PowerPMAC_Global *>(dev))->is_AmpStatus_allowed(ty);}
};


//=========================================
//	Define classes for commands
//=========================================
//	Command ResetAmp class definition
class ResetAmpClass : public Tango::Command
{
public:
	ResetAmpClass(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out,
				   const char        *in_desc,
				   const char        *out_desc,
				   Tango::DispLevel  level)
	:Command(name,in,out,in_desc,out_desc, level)	{};

	ResetAmpClass(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out)
	:Command(name,in,out)	{};
	~ResetAmpClass() {};
	
	virtual CORBA::Any *execute (Tango::DeviceImpl *dev, const CORBA::Any &any);
	virtual bool is_allowed (Tango::DeviceImpl *dev, const CORBA::Any &any)
	{return (static_cast<PowerPMAC_Global *>(dev))->is_ResetAmp_allowed(any);}
};

//	Command ExecuteCommand class definition
class ExecuteCommandClass : public Tango::Command
{
public:
	ExecuteCommandClass(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out,
				   const char        *in_desc,
				   const char        *out_desc,
				   Tango::DispLevel  level)
	:Command(name,in,out,in_desc,out_desc, level)	{};

	ExecuteCommandClass(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out)
	:Command(name,in,out)	{};
	~ExecuteCommandClass() {};
	
	virtual CORBA::Any *execute (Tango::DeviceImpl *dev, const CORBA::Any &any);
	virtual bool is_allowed (Tango::DeviceImpl *dev, const CORBA::Any &any)
	{return (static_cast<PowerPMAC_Global *>(dev))->is_ExecuteCommand_allowed(any);}
};

//	Command Reset class definition
class ResetClass : public Tango::Command
{
public:
	ResetClass(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out,
				   const char        *in_desc,
				   const char        *out_desc,
				   Tango::DispLevel  level)
	:Command(name,in,out,in_desc,out_desc, level)	{};

	ResetClass(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out)
	:Command(name,in,out)	{};
	~ResetClass() {};
	
	virtual CORBA::Any *execute (Tango::DeviceImpl *dev, const CORBA::Any &any);
	virtual bool is_allowed (Tango::DeviceImpl *dev, const CORBA::Any &any)
	{return (static_cast<PowerPMAC_Global *>(dev))->is_Reset_allowed(any);}
};

//	Command Reboot class definition
class RebootClass : public Tango::Command
{
public:
	RebootClass(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out,
				   const char        *in_desc,
				   const char        *out_desc,
				   Tango::DispLevel  level)
	:Command(name,in,out,in_desc,out_desc, level)	{};

	RebootClass(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out)
	:Command(name,in,out)	{};
	~RebootClass() {};
	
	virtual CORBA::Any *execute (Tango::DeviceImpl *dev, const CORBA::Any &any);
	virtual bool is_allowed (Tango::DeviceImpl *dev, const CORBA::Any &any)
	{return (static_cast<PowerPMAC_Global *>(dev))->is_Reboot_allowed(any);}
};


/**
 *	The PowerPMAC_GlobalClass singleton definition
 */

#ifdef _TG_WINDOWS_
class __declspec(dllexport)  PowerPMAC_GlobalClass : public Tango::DeviceClass
#else
class PowerPMAC_GlobalClass : public Tango::DeviceClass
#endif
{
	/*----- PROTECTED REGION ID(PowerPMAC_GlobalClass::Additionnal DServer data members) ENABLED START -----*/
	
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_GlobalClass::Additionnal DServer data members

	public:
		//	write class properties data members
		Tango::DbData	cl_prop;
		Tango::DbData	cl_def_prop;
		Tango::DbData	dev_def_prop;
	
		//	Method prototypes
		static PowerPMAC_GlobalClass *init(const char *);
		static PowerPMAC_GlobalClass *instance();
		~PowerPMAC_GlobalClass();
		Tango::DbDatum	get_class_property(string &);
		Tango::DbDatum	get_default_device_property(string &);
		Tango::DbDatum	get_default_class_property(string &);
	
	protected:
		PowerPMAC_GlobalClass(string &);
		static PowerPMAC_GlobalClass *_instance;
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

#endif   //	PowerPMAC_Global_H
