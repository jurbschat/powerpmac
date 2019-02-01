/*----- PROTECTED REGION ID(PowerPMAC_IO.h) ENABLED START -----*/
//=============================================================================
//
// file :        PowerPMAC_IO.h
//
// description : Include file for the PowerPMAC_IO class
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


#ifndef PowerPMAC_IO_H
#define PowerPMAC_IO_H

#include "libs/sigs.h"
#include <tango.h>


/*----- PROTECTED REGION END -----*/	//	PowerPMAC_IO.h

/**
 *  PowerPMAC_IO class description:
 *    
 */

namespace PowerPMAC_IO_ns
{
/*----- PROTECTED REGION ID(PowerPMAC_IO::Additional Class Declarations) ENABLED START -----*/

//	Additional Class Declarations

/*----- PROTECTED REGION END -----*/	//	PowerPMAC_IO::Additional Class Declarations

class PowerPMAC_IO : public TANGO_BASE_CLASS
{

/*----- PROTECTED REGION ID(PowerPMAC_IO::Data Members) ENABLED START -----*/

//	Add your own data members
private:
	sigs::Connection connectionEstablished;
	sigs::Connection connectionLost;

/*----- PROTECTED REGION END -----*/	//	PowerPMAC_IO::Data Members



//	Constructors and destructors
public:
	/**
	 * Constructs a newly device object.
	 *
	 *	@param cl	Class.
	 *	@param s 	Device Name
	 */
	PowerPMAC_IO(Tango::DeviceClass *cl,string &s);
	/**
	 * Constructs a newly device object.
	 *
	 *	@param cl	Class.
	 *	@param s 	Device Name
	 */
	PowerPMAC_IO(Tango::DeviceClass *cl,const char *s);
	/**
	 * Constructs a newly device object.
	 *
	 *	@param cl	Class.
	 *	@param s 	Device name
	 *	@param d	Device description.
	 */
	PowerPMAC_IO(Tango::DeviceClass *cl,const char *s,const char *d);
	/**
	 * The device object destructor.
	 */
	~PowerPMAC_IO() {delete_device();};


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
	 *	Always executed method before execution command method.
	 */
	virtual void always_executed_hook();


//	Attribute methods
public:
	//--------------------------------------------------------
	/*
	 *	Method      : PowerPMAC_IO::read_attr_hardware()
	 *	Description : Hardware acquisition for attributes.
	 */
	//--------------------------------------------------------
	virtual void read_attr_hardware(vector<long> &attr_list);


	//--------------------------------------------------------
	/**
	 *	Method      : PowerPMAC_IO::add_dynamic_attributes()
	 *	Description : Add dynamic attributes if any.
	 */
	//--------------------------------------------------------
	void add_dynamic_attributes();




//	Command related methods
public:


	//--------------------------------------------------------
	/**
	 *	Method      : PowerPMAC_IO::add_dynamic_commands()
	 *	Description : Add dynamic commands if any.
	 */
	//--------------------------------------------------------
	void add_dynamic_commands();

/*----- PROTECTED REGION ID(PowerPMAC_IO::Additional Method prototypes) ENABLED START -----*/

//	Additional Method prototypes
	void StartIO();
	void StopIO();

/*----- PROTECTED REGION END -----*/	//	PowerPMAC_IO::Additional Method prototypes
};

/*----- PROTECTED REGION ID(PowerPMAC_IO::Additional Classes Definitions) ENABLED START -----*/

//	Additional Classes Definitions

/*----- PROTECTED REGION END -----*/	//	PowerPMAC_IO::Additional Classes Definitions

}	//	End of namespace

#endif   //	PowerPMAC_IO_H
