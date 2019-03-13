/*----- PROTECTED REGION ID(PowerPMAC_Motor.h) ENABLED START -----*/
//=============================================================================
//
// file :        PowerPMAC_Motor.h
//
// description : Include file for the PowerPMAC_Motor class
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


#ifndef PowerPMAC_Motor_H
#define PowerPMAC_Motor_H

#include "config.h"
#include "pmac/defines.h"
#include "libs/sigs.h"
#include "scopedsignal.h"
#include <tango.h>


/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor.h

/**
 *  PowerPMAC_Motor class description:
 *    
 */

namespace PowerPMAC_Motor_ns
{
/*----- PROTECTED REGION ID(PowerPMAC_Motor::Additional Class Declarations) ENABLED START -----*/

//	Additional Class Declarations

/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::Additional Class Declarations

class PowerPMAC_Motor : public TANGO_BASE_CLASS
{

/*----- PROTECTED REGION ID(PowerPMAC_Motor::Data Members) ENABLED START -----*/

//	Add your own data members
private:
	ppmac::MotorID motorID;
	ppmac::ScopedSignal connectionEstablished;
	ppmac::ScopedSignal connectionLost;
	ppmac::ScopedSignal motorStateChanged;
	ppmac::ScopedSignal motorCtrlChanged;
	uint64_t lastMotorState;
	std::string hardLimitAddress;
	ppmac::HandleType movingTimerHandle;
	bool started;

/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::Data Members

//	Device property data members
public:
	//	MotorIndex:	index of the motor
	Tango::DevULong	motorIndex;
	//	DisableHardLimits:	
	Tango::DevBoolean	disableHardLimits;

	bool	mandatoryNotDefined;

//	Attribute data members
public:
	Tango::DevDouble	*attr_Position_read;
	Tango::DevDouble	*attr_Acceleration_read;
	Tango::DevDouble	*attr_Velocity_read;
	Tango::DevDouble	*attr_HomeOffset_read;
	Tango::DevDouble	*attr_SoftCwLimit_read;
	Tango::DevDouble	*attr_SoftCcwLimit_read;
	Tango::DevBoolean	*attr_SoftLimitEnable_read;
	Tango::DevBoolean	*attr_SoftCwLimitFault_read;
	Tango::DevBoolean	*attr_SoftCcwLimitFault_read;
	Tango::DevBoolean	*attr_CwLimitFault_read;
	Tango::DevBoolean	*attr_CcwLimitFault_read;
	Tango::DevString	*attr_MotorStates_read;

//	Constructors and destructors
public:
	/**
	 * Constructs a newly device object.
	 *
	 *	@param cl	Class.
	 *	@param s 	Device Name
	 */
	PowerPMAC_Motor(Tango::DeviceClass *cl,string &s);
	/**
	 * Constructs a newly device object.
	 *
	 *	@param cl	Class.
	 *	@param s 	Device Name
	 */
	PowerPMAC_Motor(Tango::DeviceClass *cl,const char *s);
	/**
	 * Constructs a newly device object.
	 *
	 *	@param cl	Class.
	 *	@param s 	Device name
	 *	@param d	Device description.
	 */
	PowerPMAC_Motor(Tango::DeviceClass *cl,const char *s,const char *d);
	/**
	 * The device object destructor.
	 */
	~PowerPMAC_Motor() {delete_device();};


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
	 *	Method      : PowerPMAC_Motor::read_attr_hardware()
	 *	Description : Hardware acquisition for attributes.
	 */
	//--------------------------------------------------------
	virtual void read_attr_hardware(vector<long> &attr_list);
	//--------------------------------------------------------
	/*
	 *	Method      : PowerPMAC_Motor::write_attr_hardware()
	 *	Description : Hardware writing for attributes.
	 */
	//--------------------------------------------------------
	virtual void write_attr_hardware(vector<long> &attr_list);

/**
 *	Attribute Position related methods
 *	Description: 
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
	virtual void read_Position(Tango::Attribute &attr);
	virtual void write_Position(Tango::WAttribute &attr);
	virtual bool is_Position_allowed(Tango::AttReqType type);
/**
 *	Attribute Acceleration related methods
 *	Description: 
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
	virtual void read_Acceleration(Tango::Attribute &attr);
	virtual void write_Acceleration(Tango::WAttribute &attr);
	virtual bool is_Acceleration_allowed(Tango::AttReqType type);
/**
 *	Attribute Velocity related methods
 *	Description: 
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
	virtual void read_Velocity(Tango::Attribute &attr);
	virtual void write_Velocity(Tango::WAttribute &attr);
	virtual bool is_Velocity_allowed(Tango::AttReqType type);
/**
 *	Attribute HomeOffset related methods
 *	Description: 
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
	virtual void read_HomeOffset(Tango::Attribute &attr);
	virtual void write_HomeOffset(Tango::WAttribute &attr);
	virtual bool is_HomeOffset_allowed(Tango::AttReqType type);
/**
 *	Attribute SoftCwLimit related methods
 *	Description: 
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
	virtual void read_SoftCwLimit(Tango::Attribute &attr);
	virtual void write_SoftCwLimit(Tango::WAttribute &attr);
	virtual bool is_SoftCwLimit_allowed(Tango::AttReqType type);
/**
 *	Attribute SoftCcwLimit related methods
 *	Description: 
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
	virtual void read_SoftCcwLimit(Tango::Attribute &attr);
	virtual void write_SoftCcwLimit(Tango::WAttribute &attr);
	virtual bool is_SoftCcwLimit_allowed(Tango::AttReqType type);
/**
 *	Attribute SoftLimitEnable related methods
 *	Description: 
 *
 *	Data type:	Tango::DevBoolean
 *	Attr type:	Scalar
 */
	virtual void read_SoftLimitEnable(Tango::Attribute &attr);
	virtual void write_SoftLimitEnable(Tango::WAttribute &attr);
	virtual bool is_SoftLimitEnable_allowed(Tango::AttReqType type);
/**
 *	Attribute SoftCwLimitFault related methods
 *	Description: 
 *
 *	Data type:	Tango::DevBoolean
 *	Attr type:	Scalar
 */
	virtual void read_SoftCwLimitFault(Tango::Attribute &attr);
	virtual bool is_SoftCwLimitFault_allowed(Tango::AttReqType type);
/**
 *	Attribute SoftCcwLimitFault related methods
 *	Description: 
 *
 *	Data type:	Tango::DevBoolean
 *	Attr type:	Scalar
 */
	virtual void read_SoftCcwLimitFault(Tango::Attribute &attr);
	virtual bool is_SoftCcwLimitFault_allowed(Tango::AttReqType type);
/**
 *	Attribute CwLimitFault related methods
 *	Description: 
 *
 *	Data type:	Tango::DevBoolean
 *	Attr type:	Scalar
 */
	virtual void read_CwLimitFault(Tango::Attribute &attr);
	virtual bool is_CwLimitFault_allowed(Tango::AttReqType type);
/**
 *	Attribute CcwLimitFault related methods
 *	Description: 
 *
 *	Data type:	Tango::DevBoolean
 *	Attr type:	Scalar
 */
	virtual void read_CcwLimitFault(Tango::Attribute &attr);
	virtual bool is_CcwLimitFault_allowed(Tango::AttReqType type);
/**
 *	Attribute MotorStates related methods
 *	Description: 
 *
 *	Data type:	Tango::DevString
 *	Attr type:	Scalar
 */
	virtual void read_MotorStates(Tango::Attribute &attr);
	virtual bool is_MotorStates_allowed(Tango::AttReqType type);


	//--------------------------------------------------------
	/**
	 *	Method      : PowerPMAC_Motor::add_dynamic_attributes()
	 *	Description : Add dynamic attributes if any.
	 */
	//--------------------------------------------------------
	void add_dynamic_attributes();




//	Command related methods
public:
	/**
	 *	Command Phase related method
	 *	Description: 
	 *
	 */
	virtual void phase();
	virtual bool is_Phase_allowed(const CORBA::Any &any);
	/**
	 *	Command Home related method
	 *	Description: 
	 *
	 */
	virtual void home();
	virtual bool is_Home_allowed(const CORBA::Any &any);
	/**
	 *	Command Calibrate related method
	 *	Description: 
	 *
	 */
	virtual void calibrate();
	virtual bool is_Calibrate_allowed(const CORBA::Any &any);
	/**
	 *	Command EnableServoCtrl related method
	 *	Description: 
	 *
	 */
	virtual void enable_servo_ctrl();
	virtual bool is_EnableServoCtrl_allowed(const CORBA::Any &any);
	/**
	 *	Command DisableServoCtrl related method
	 *	Description: 
	 *
	 */
	virtual void disable_servo_ctrl();
	virtual bool is_DisableServoCtrl_allowed(const CORBA::Any &any);
	/**
	 *	Command Stop related method
	 *	Description: 
	 *
	 */
	virtual void stop();
	virtual bool is_Stop_allowed(const CORBA::Any &any);
	/**
	 *	Command Kill related method
	 *	Description: 
	 *
	 */
	virtual void kill();
	virtual bool is_Kill_allowed(const CORBA::Any &any);
	/**
	 *	Command ActivateAndReset related method
	 *	Description: 
	 *
	 */
	virtual void activate_and_reset();
	virtual bool is_ActivateAndReset_allowed(const CORBA::Any &any);


	//--------------------------------------------------------
	/**
	 *	Method      : PowerPMAC_Motor::add_dynamic_commands()
	 *	Description : Add dynamic commands if any.
	 */
	//--------------------------------------------------------
	void add_dynamic_commands();

/*----- PROTECTED REGION ID(PowerPMAC_Motor::Additional Method prototypes) ENABLED START -----*/

//	Additional Method prototypes
	void StartMotor();
	void StopMotor();
	void MotorStateChanged(uint64_t newValue, uint64_t changes);
	void MotorCtrlChanged(uint64_t newValue, uint64_t changes);
	void ClearMoveStatusWaitTimer();
	void UpdateStateFromCurrentStatus(uint64_t motorStatus);

/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::Additional Method prototypes
};

/*----- PROTECTED REGION ID(PowerPMAC_Motor::Additional Classes Definitions) ENABLED START -----*/

//	Additional Classes Definitions

/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::Additional Classes Definitions

}	//	End of namespace

#endif   //	PowerPMAC_Motor_H
