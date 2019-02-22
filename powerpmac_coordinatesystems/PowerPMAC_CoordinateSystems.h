/*----- PROTECTED REGION ID(PowerPMAC_CoordinateSystems.h) ENABLED START -----*/
//=============================================================================
//
// file :        PowerPMAC_CoordinateSystems.h
//
// description : Include file for the PowerPMAC_CoordinateSystems class
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


#ifndef PowerPMAC_CoordinateSystems_H
#define PowerPMAC_CoordinateSystems_H

#include "libs/sigs.h"
#include "pmac/defines.h"
#include "config.h"
#include <tango.h>
#include <map>
/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CoordinateSystems.h

/**
 *  PowerPMAC_CoordinateSystems class description:
 *    
 */

namespace PowerPMAC_CoordinateSystems_ns
{
/*----- PROTECTED REGION ID(PowerPMAC_CoordinateSystems::Additional Class Declarations) ENABLED START -----*/

	class MyAttrib : public Tango::Attr
	{
	public:
		MyAttrib(int32_t axis, const string &att_name, std::function<double(int32_t axis)> read,
		         std::function<void(int32_t axis, double)> write,
		         std::function<bool(int32_t axis, Tango::AttReqType type)> allowed)
				:Attr(att_name.c_str(), Tango::DEV_DOUBLE, Tango::READ_WRITE),
				 axis_(axis),
				 read_(read),
				 write_(write),
				 allowed_(allowed)
		{};

		~MyAttrib() {};

		virtual void read(Tango::DeviceImpl *dev, Tango::Attribute &att) {
			(void)dev;
			//(static_cast<PowerPMAC_CoordinateSystems *>(dev))->read_X(att);
			Tango::DevDouble val = read_(axis_);
			att.set_value(&val);
		}

		virtual void write(Tango::DeviceImpl *dev, Tango::WAttribute &att) {
			(void)dev;
			//(static_cast<PowerPMAC_CoordinateSystems *>(dev))->write_X(att);
			Tango::DevDouble	w_val;
			att.get_write_value(w_val);
			write_(axis_, w_val);
		}

		virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty) {
			(void)dev;
			//return (static_cast<PowerPMAC_CoordinateSystems *>(dev))->is_X_allowed(ty);
			return allowed_(axis_, ty);
		}

		int32_t axis_;
		std::function<double(int32_t)> read_;
		std::function<void(int32_t, double)> write_;
		std::function<bool(int32_t, Tango::AttReqType type)> allowed_;
	};

/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CoordinateSystems::Additional Class Declarations

class PowerPMAC_CoordinateSystems : public TANGO_BASE_CLASS
{

/*----- PROTECTED REGION ID(PowerPMAC_CoordinateSystems::Data Members) ENABLED START -----*/

	// this is bound to exists but cant be a reference as pogo regenerates the
	// initializer list on each run. yeah who needs an initializer list...
	ppmac::CoordID coordId;
	sigs::Connection connectionEstablished;
	sigs::Connection connectionLost;
	sigs::Connection statusChanged;
	sigs::Connection coordChanged;
	std::map<int32_t, std::unique_ptr<MyAttrib>> attribs;
	ppmac::HandleType movingTimerHandle;
	uint64_t lastCoordState;

/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CoordinateSystems::Data Members

//	Device property data members
public:
	//	CoordinateIndex:	coordinate system id
	Tango::DevLong	coordinateIndex;

	bool	mandatoryNotDefined;

//	Attribute data members
public:
	Tango::DevLong	*attr_NumAxis_read;

//	Constructors and destructors
public:
	/**
	 * Constructs a newly device object.
	 *
	 *	@param cl	Class.
	 *	@param s 	Device Name
	 */
	PowerPMAC_CoordinateSystems(Tango::DeviceClass *cl,string &s);
	/**
	 * Constructs a newly device object.
	 *
	 *	@param cl	Class.
	 *	@param s 	Device Name
	 */
	PowerPMAC_CoordinateSystems(Tango::DeviceClass *cl,const char *s);
	/**
	 * Constructs a newly device object.
	 *
	 *	@param cl	Class.
	 *	@param s 	Device name
	 *	@param d	Device description.
	 */
	PowerPMAC_CoordinateSystems(Tango::DeviceClass *cl,const char *s,const char *d);
	/**
	 * The device object destructor.
	 */
	~PowerPMAC_CoordinateSystems() {delete_device();};


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
	 *	Method      : PowerPMAC_CoordinateSystems::read_attr_hardware()
	 *	Description : Hardware acquisition for attributes.
	 */
	//--------------------------------------------------------
	virtual void read_attr_hardware(vector<long> &attr_list);

/**
 *	Attribute NumAxis related methods
 *	Description: 
 *
 *	Data type:	Tango::DevLong
 *	Attr type:	Scalar
 */
	virtual void read_NumAxis(Tango::Attribute &attr);
	virtual bool is_NumAxis_allowed(Tango::AttReqType type);


	//--------------------------------------------------------
	/**
	 *	Method      : PowerPMAC_CoordinateSystems::add_dynamic_attributes()
	 *	Description : Add dynamic attributes if any.
	 */
	//--------------------------------------------------------
	void add_dynamic_attributes();




//	Command related methods
public:
	/**
	 *	Command Abort related method
	 *	Description: 
	 *
	 */
	virtual void abort();
	virtual bool is_Abort_allowed(const CORBA::Any &any);
	/**
	 *	Command RunMotionProgram related method
	 *	Description: 
	 *
	 *	@param argin 
	 */
	virtual void run_motion_program(Tango::DevString argin);
	virtual bool is_RunMotionProgram_allowed(const CORBA::Any &any);


	//--------------------------------------------------------
	/**
	 *	Method      : PowerPMAC_CoordinateSystems::add_dynamic_commands()
	 *	Description : Add dynamic commands if any.
	 */
	//--------------------------------------------------------
	void add_dynamic_commands();

/*----- PROTECTED REGION ID(PowerPMAC_CoordinateSystems::Additional Method prototypes) ENABLED START -----*/

	void StartCoordinateSystem();
	void StopCoordinateSystem();
	void CoordinateStateChanged(uint64_t newState, uint64_t changes);
	void CoordinateSystemChanged(int32_t axis);
	void UpdateAxisToMatchCurrent(int32_t axis);
	double ReadAxisAttrib(int32_t axis);
	void WriteAxisAttrib(int32_t axis, double value);
	bool IsAxisAttribAccessible(int32_t axis, Tango::AttReqType type);
	void ClearMoveStatusWaitTimer();

/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CoordinateSystems::Additional Method prototypes
};

/*----- PROTECTED REGION ID(PowerPMAC_CoordinateSystems::Additional Classes Definitions) ENABLED START -----*/


/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CoordinateSystems::Additional Classes Definitions

}	//	End of namespace

#endif   //	PowerPMAC_CoordinateSystems_H
