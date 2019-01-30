/*----- PROTECTED REGION ID(PowerPMAC_MotorClass.h) ENABLED START -----*/
//=============================================================================
//
// file :        PowerPMAC_MotorClass.h
//
// description : Include for the PowerPMAC_Motor root class.
//               This class is the singleton class for
//                the PowerPMAC_Motor device class.
//               It contains all properties and methods which the 
//               PowerPMAC_Motor requires only once e.g. the commands.
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


#ifndef PowerPMAC_MotorClass_H
#define PowerPMAC_MotorClass_H

#include <tango.h>
#include <PowerPMAC_Motor.h>


/*----- PROTECTED REGION END -----*/	//	PowerPMAC_MotorClass.h


namespace PowerPMAC_Motor_ns
{
/*----- PROTECTED REGION ID(PowerPMAC_MotorClass::classes for dynamic creation) ENABLED START -----*/


/*----- PROTECTED REGION END -----*/	//	PowerPMAC_MotorClass::classes for dynamic creation

//=========================================
//	Define classes for attributes
//=========================================
//	Attribute position class definition
class positionAttrib: public Tango::Attr
{
public:
	positionAttrib():Attr("position",
			Tango::DEV_FLOAT, Tango::READ_WRITE) {};
	~positionAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<PowerPMAC_Motor *>(dev))->read_position(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<PowerPMAC_Motor *>(dev))->write_position(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<PowerPMAC_Motor *>(dev))->is_position_allowed(ty);}
};

//	Attribute acceleration class definition
class accelerationAttrib: public Tango::Attr
{
public:
	accelerationAttrib():Attr("acceleration",
			Tango::DEV_FLOAT, Tango::READ_WRITE) {};
	~accelerationAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<PowerPMAC_Motor *>(dev))->read_acceleration(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<PowerPMAC_Motor *>(dev))->write_acceleration(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<PowerPMAC_Motor *>(dev))->is_acceleration_allowed(ty);}
};

//	Attribute max_velocity class definition
class max_velocityAttrib: public Tango::Attr
{
public:
	max_velocityAttrib():Attr("max_velocity",
			Tango::DEV_FLOAT, Tango::READ_WRITE) {};
	~max_velocityAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<PowerPMAC_Motor *>(dev))->read_max_velocity(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<PowerPMAC_Motor *>(dev))->write_max_velocity(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<PowerPMAC_Motor *>(dev))->is_max_velocity_allowed(ty);}
};

//	Attribute sl_cw class definition
class sl_cwAttrib: public Tango::Attr
{
public:
	sl_cwAttrib():Attr("sl_cw",
			Tango::DEV_FLOAT, Tango::READ_WRITE) {};
	~sl_cwAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<PowerPMAC_Motor *>(dev))->read_sl_cw(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<PowerPMAC_Motor *>(dev))->write_sl_cw(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<PowerPMAC_Motor *>(dev))->is_sl_cw_allowed(ty);}
};

//	Attribute sl_ccw class definition
class sl_ccwAttrib: public Tango::Attr
{
public:
	sl_ccwAttrib():Attr("sl_ccw",
			Tango::DEV_FLOAT, Tango::READ_WRITE) {};
	~sl_ccwAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<PowerPMAC_Motor *>(dev))->read_sl_ccw(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<PowerPMAC_Motor *>(dev))->write_sl_ccw(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<PowerPMAC_Motor *>(dev))->is_sl_ccw_allowed(ty);}
};

//	Attribute sl_cw_fault class definition
class sl_cw_faultAttrib: public Tango::Attr
{
public:
	sl_cw_faultAttrib():Attr("sl_cw_fault",
			Tango::DEV_BOOLEAN, Tango::READ) {};
	~sl_cw_faultAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<PowerPMAC_Motor *>(dev))->read_sl_cw_fault(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<PowerPMAC_Motor *>(dev))->is_sl_cw_fault_allowed(ty);}
};

//	Attribute sl_ccw_fault class definition
class sl_ccw_faultAttrib: public Tango::Attr
{
public:
	sl_ccw_faultAttrib():Attr("sl_ccw_fault",
			Tango::DEV_BOOLEAN, Tango::READ) {};
	~sl_ccw_faultAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<PowerPMAC_Motor *>(dev))->read_sl_ccw_fault(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<PowerPMAC_Motor *>(dev))->is_sl_ccw_fault_allowed(ty);}
};

//	Attribute limit_cw_fault class definition
class limit_cw_faultAttrib: public Tango::Attr
{
public:
	limit_cw_faultAttrib():Attr("limit_cw_fault",
			Tango::DEV_BOOLEAN, Tango::READ) {};
	~limit_cw_faultAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<PowerPMAC_Motor *>(dev))->read_limit_cw_fault(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<PowerPMAC_Motor *>(dev))->is_limit_cw_fault_allowed(ty);}
};

//	Attribute limit_ccw_fault class definition
class limit_ccw_faultAttrib: public Tango::Attr
{
public:
	limit_ccw_faultAttrib():Attr("limit_ccw_fault",
			Tango::DEV_BOOLEAN, Tango::READ) {};
	~limit_ccw_faultAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<PowerPMAC_Motor *>(dev))->read_limit_ccw_fault(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<PowerPMAC_Motor *>(dev))->is_limit_ccw_fault_allowed(ty);}
};

//	Attribute conversion_factor class definition
class conversion_factorAttrib: public Tango::Attr
{
public:
	conversion_factorAttrib():Attr("conversion_factor",
			Tango::DEV_FLOAT, Tango::READ_WRITE) {};
	~conversion_factorAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<PowerPMAC_Motor *>(dev))->read_conversion_factor(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<PowerPMAC_Motor *>(dev))->write_conversion_factor(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<PowerPMAC_Motor *>(dev))->is_conversion_factor_allowed(ty);}
};

//	Attribute invert_direction class definition
class invert_directionAttrib: public Tango::Attr
{
public:
	invert_directionAttrib():Attr("invert_direction",
			Tango::DEV_BOOLEAN, Tango::READ_WRITE) {};
	~invert_directionAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<PowerPMAC_Motor *>(dev))->read_invert_direction(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<PowerPMAC_Motor *>(dev))->write_invert_direction(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<PowerPMAC_Motor *>(dev))->is_invert_direction_allowed(ty);}
};

//	Attribute invert_encoder class definition
class invert_encoderAttrib: public Tango::Attr
{
public:
	invert_encoderAttrib():Attr("invert_encoder",
			Tango::DEV_BOOLEAN, Tango::READ_WRITE) {};
	~invert_encoderAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<PowerPMAC_Motor *>(dev))->read_invert_encoder(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<PowerPMAC_Motor *>(dev))->write_invert_encoder(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<PowerPMAC_Motor *>(dev))->is_invert_encoder_allowed(ty);}
};


//=========================================
//	Define classes for commands
//=========================================
//	Command PhaseMotor class definition
class PhaseMotorClass : public Tango::Command
{
public:
	PhaseMotorClass(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out,
				   const char        *in_desc,
				   const char        *out_desc,
				   Tango::DispLevel  level)
	:Command(name,in,out,in_desc,out_desc, level)	{};

	PhaseMotorClass(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out)
	:Command(name,in,out)	{};
	~PhaseMotorClass() {};
	
	virtual CORBA::Any *execute (Tango::DeviceImpl *dev, const CORBA::Any &any);
	virtual bool is_allowed (Tango::DeviceImpl *dev, const CORBA::Any &any)
	{return (static_cast<PowerPMAC_Motor *>(dev))->is_PhaseMotor_allowed(any);}
};

//	Command HomeMotor class definition
class HomeMotorClass : public Tango::Command
{
public:
	HomeMotorClass(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out,
				   const char        *in_desc,
				   const char        *out_desc,
				   Tango::DispLevel  level)
	:Command(name,in,out,in_desc,out_desc, level)	{};

	HomeMotorClass(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out)
	:Command(name,in,out)	{};
	~HomeMotorClass() {};
	
	virtual CORBA::Any *execute (Tango::DeviceImpl *dev, const CORBA::Any &any);
	virtual bool is_allowed (Tango::DeviceImpl *dev, const CORBA::Any &any)
	{return (static_cast<PowerPMAC_Motor *>(dev))->is_HomeMotor_allowed(any);}
};

//	Command Calibrate class definition
class CalibrateClass : public Tango::Command
{
public:
	CalibrateClass(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out,
				   const char        *in_desc,
				   const char        *out_desc,
				   Tango::DispLevel  level)
	:Command(name,in,out,in_desc,out_desc, level)	{};

	CalibrateClass(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out)
	:Command(name,in,out)	{};
	~CalibrateClass() {};
	
	virtual CORBA::Any *execute (Tango::DeviceImpl *dev, const CORBA::Any &any);
	virtual bool is_allowed (Tango::DeviceImpl *dev, const CORBA::Any &any)
	{return (static_cast<PowerPMAC_Motor *>(dev))->is_Calibrate_allowed(any);}
};


/**
 *	The PowerPMAC_MotorClass singleton definition
 */

#ifdef _TG_WINDOWS_
class __declspec(dllexport)  PowerPMAC_MotorClass : public Tango::DeviceClass
#else
class PowerPMAC_MotorClass : public Tango::DeviceClass
#endif
{
	/*----- PROTECTED REGION ID(PowerPMAC_MotorClass::Additionnal DServer data members) ENABLED START -----*/
	
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_MotorClass::Additionnal DServer data members

	public:
		//	write class properties data members
		Tango::DbData	cl_prop;
		Tango::DbData	cl_def_prop;
		Tango::DbData	dev_def_prop;
	
		//	Method prototypes
		static PowerPMAC_MotorClass *init(const char *);
		static PowerPMAC_MotorClass *instance();
		~PowerPMAC_MotorClass();
		Tango::DbDatum	get_class_property(string &);
		Tango::DbDatum	get_default_device_property(string &);
		Tango::DbDatum	get_default_class_property(string &);
	
	protected:
		PowerPMAC_MotorClass(string &);
		static PowerPMAC_MotorClass *_instance;
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

#endif   //	PowerPMAC_Motor_H
