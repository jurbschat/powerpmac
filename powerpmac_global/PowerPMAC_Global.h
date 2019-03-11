/*----- PROTECTED REGION ID(PowerPMAC_Global.h) ENABLED START -----*/
//=============================================================================
//
// file :        PowerPMAC_Global.h
//
// description : Include file for the PowerPMAC_Global class
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


#ifndef PowerPMAC_Global_H
#define PowerPMAC_Global_H

#include "libs/sigs.h"
#include <tango.h>


/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Global.h

/**
 *  PowerPMAC_Global class description:
 *    
 */

namespace PowerPMAC_Global_ns
{
/*----- PROTECTED REGION ID(PowerPMAC_Global::Additional Class Declarations) ENABLED START -----*/

//	Additional Class Declarations

/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Global::Additional Class Declarations

class PowerPMAC_Global : public TANGO_BASE_CLASS
{

/*----- PROTECTED REGION ID(PowerPMAC_Global::Data Members) ENABLED START -----*/

//	Add your own data members
private:
	sigs::Connection connectionEstablished;
	sigs::Connection connectionLost;

/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Global::Data Members

//	Device property data members
public:
	//	host:	
	string	host;
	//	port:	
	Tango::DevUShort	port;
	//	loggingHost:	
	string	loggingHost;
	//	loggingPort:	
	Tango::DevLong	loggingPort;
	//	dumpCommunication:	dump all communication to the power pmac, this is only a debugging helper
	Tango::DevBoolean	dumpCommunication;

	bool	mandatoryNotDefined;

//	Attribute data members
public:
	Tango::DevLong	*attr_MaxMotors_read;
	Tango::DevLong	*attr_MaxCoords_read;
	Tango::DevBoolean	*attr_AbortAll_read;
	Tango::DevDouble	*attr_CpuTemp_read;
	Tango::DevBoolean	*attr_AmpOverTemp_read;
	Tango::DevString	*attr_Firmware_read;
	Tango::DevString	*attr_SystemType_read;
	Tango::DevString	*attr_CpuType_read;
	Tango::DevLong	*attr_CpuFrequency_read;
	Tango::DevString	*attr_Uptime_read;
	Tango::DevLong	*attr_ActiveCompensationTables_read;
	Tango::DevString	*attr_AmpStatus_read;

//	Constructors and destructors
public:
	/**
	 * Constructs a newly device object.
	 *
	 *	@param cl	Class.
	 *	@param s 	Device Name
	 */
	PowerPMAC_Global(Tango::DeviceClass *cl,string &s);
	/**
	 * Constructs a newly device object.
	 *
	 *	@param cl	Class.
	 *	@param s 	Device Name
	 */
	PowerPMAC_Global(Tango::DeviceClass *cl,const char *s);
	/**
	 * Constructs a newly device object.
	 *
	 *	@param cl	Class.
	 *	@param s 	Device name
	 *	@param d	Device description.
	 */
	PowerPMAC_Global(Tango::DeviceClass *cl,const char *s,const char *d);
	/**
	 * The device object destructor.
	 */
	~PowerPMAC_Global() {delete_device();};


//	Miscellaneous methods
public:
	/*
	 *	will be called at device destruction or at init command.
	 */
	void delete_device();
	/*
	 *	Initialize the device
	 */
	virtual void init_device();
	/*
	 *	Read the device properties from database
	 */
	void get_device_property();
	/*
	 *	Always executed method before execution command method.
	 */
	virtual void always_executed_hook();

	/*
	 *	Check if mandatory property has been set
	 */
	 void check_mandatory_property(Tango::DbDatum &class_prop, Tango::DbDatum &dev_prop);

//	Attribute methods
public:
	//--------------------------------------------------------
	/*
	 *	Method      : PowerPMAC_Global::read_attr_hardware()
	 *	Description : Hardware acquisition for attributes.
	 */
	//--------------------------------------------------------
	virtual void read_attr_hardware(vector<long> &attr_list);
	//--------------------------------------------------------
	/*
	 *	Method      : PowerPMAC_Global::write_attr_hardware()
	 *	Description : Hardware writing for attributes.
	 */
	//--------------------------------------------------------
	virtual void write_attr_hardware(vector<long> &attr_list);

/**
 *	Attribute MaxMotors related methods
 *	Description: 
 *
 *	Data type:	Tango::DevLong
 *	Attr type:	Scalar
 */
	virtual void read_MaxMotors(Tango::Attribute &attr);
	virtual bool is_MaxMotors_allowed(Tango::AttReqType type);
/**
 *	Attribute MaxCoords related methods
 *	Description: 
 *
 *	Data type:	Tango::DevLong
 *	Attr type:	Scalar
 */
	virtual void read_MaxCoords(Tango::Attribute &attr);
	virtual bool is_MaxCoords_allowed(Tango::AttReqType type);
/**
 *	Attribute AbortAll related methods
 *	Description: 
 *
 *	Data type:	Tango::DevBoolean
 *	Attr type:	Scalar
 */
	virtual void read_AbortAll(Tango::Attribute &attr);
	virtual bool is_AbortAll_allowed(Tango::AttReqType type);
/**
 *	Attribute CpuTemp related methods
 *	Description: 
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
	virtual void read_CpuTemp(Tango::Attribute &attr);
	virtual bool is_CpuTemp_allowed(Tango::AttReqType type);
/**
 *	Attribute AmpOverTemp related methods
 *	Description: 
 *
 *	Data type:	Tango::DevBoolean
 *	Attr type:	Scalar
 */
	virtual void read_AmpOverTemp(Tango::Attribute &attr);
	virtual bool is_AmpOverTemp_allowed(Tango::AttReqType type);
/**
 *	Attribute Firmware related methods
 *	Description: 
 *
 *	Data type:	Tango::DevString
 *	Attr type:	Scalar
 */
	virtual void read_Firmware(Tango::Attribute &attr);
	virtual bool is_Firmware_allowed(Tango::AttReqType type);
/**
 *	Attribute SystemType related methods
 *	Description: 
 *
 *	Data type:	Tango::DevString
 *	Attr type:	Scalar
 */
	virtual void read_SystemType(Tango::Attribute &attr);
	virtual bool is_SystemType_allowed(Tango::AttReqType type);
/**
 *	Attribute CpuType related methods
 *	Description: 
 *
 *	Data type:	Tango::DevString
 *	Attr type:	Scalar
 */
	virtual void read_CpuType(Tango::Attribute &attr);
	virtual bool is_CpuType_allowed(Tango::AttReqType type);
/**
 *	Attribute CpuFrequency related methods
 *	Description: 
 *
 *	Data type:	Tango::DevLong
 *	Attr type:	Scalar
 */
	virtual void read_CpuFrequency(Tango::Attribute &attr);
	virtual bool is_CpuFrequency_allowed(Tango::AttReqType type);
/**
 *	Attribute Uptime related methods
 *	Description: 
 *
 *	Data type:	Tango::DevString
 *	Attr type:	Scalar
 */
	virtual void read_Uptime(Tango::Attribute &attr);
	virtual bool is_Uptime_allowed(Tango::AttReqType type);
/**
 *	Attribute ActiveCompensationTables related methods
 *	Description: 
 *
 *	Data type:	Tango::DevLong
 *	Attr type:	Scalar
 */
	virtual void read_ActiveCompensationTables(Tango::Attribute &attr);
	virtual void write_ActiveCompensationTables(Tango::WAttribute &attr);
	virtual bool is_ActiveCompensationTables_allowed(Tango::AttReqType type);
/**
 *	Attribute AmpStatus related methods
 *	Description: 
 *
 *	Data type:	Tango::DevString
 *	Attr type:	Spectrum max = 8
 */
	virtual void read_AmpStatus(Tango::Attribute &attr);
	virtual bool is_AmpStatus_allowed(Tango::AttReqType type);


	//--------------------------------------------------------
	/**
	 *	Method      : PowerPMAC_Global::add_dynamic_attributes()
	 *	Description : Add dynamic attributes if any.
	 */
	//--------------------------------------------------------
	void add_dynamic_attributes();




//	Command related methods
public:
	/**
	 *	Command ResetAmp related method
	 *	Description: 
	 *
	 *	@returns 
	 */
	virtual Tango::DevString reset_amp();
	virtual bool is_ResetAmp_allowed(const CORBA::Any &any);
	/**
	 *	Command ExecuteCommand related method
	 *	Description: 
	 *
	 *	@param argin 
	 *	@returns 
	 */
	virtual Tango::DevString execute_command(Tango::DevString argin);
	virtual bool is_ExecuteCommand_allowed(const CORBA::Any &any);
	/**
	 *	Command Reset related method
	 *	Description: 
	 *
	 */
	virtual void reset();
	virtual bool is_Reset_allowed(const CORBA::Any &any);
	/**
	 *	Command Reboot related method
	 *	Description: 
	 *
	 */
	virtual void reboot();
	virtual bool is_Reboot_allowed(const CORBA::Any &any);
	/**
	 *	Command ReloadPLC related method
	 *	Description: 
	 *
	 */
	virtual void reload_plc();
	virtual bool is_ReloadPLC_allowed(const CORBA::Any &any);


	//--------------------------------------------------------
	/**
	 *	Method      : PowerPMAC_Global::add_dynamic_commands()
	 *	Description : Add dynamic commands if any.
	 */
	//--------------------------------------------------------
	void add_dynamic_commands();

/*----- PROTECTED REGION ID(PowerPMAC_Global::Additional Method prototypes) ENABLED START -----*/

//	Additional Method prototypes
	void StartGlobal();
	void StopGlobal();
	void SetErrorState();


/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Global::Additional Method prototypes
};

/*----- PROTECTED REGION ID(PowerPMAC_Global::Additional Classes Definitions) ENABLED START -----*/

//	Additional Classes Definitions

/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Global::Additional Classes Definitions

}	//	End of namespace

#endif   //	PowerPMAC_Global_H
