/*----- PROTECTED REGION ID(PowerPMAC_CoordinateSystems.cpp) ENABLED START -----*/
//=============================================================================
//
// file :        PowerPMAC_CoordinateSystems.cpp
//
// description : C++ source for the PowerPMAC_CoordinateSystems class and its commands.
//               The class is derived from Device. It represents the
//               CORBA servant object which will be accessed from the
//               network. All commands which can be executed on the
//               PowerPMAC_CoordinateSystems are implemented in this file.
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


#include <PowerPMAC_CoordinateSystems.h>
#include <PowerPMAC_CoordinateSystemsClass.h>
#include "ppmaccoreinterface.h"

/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CoordinateSystems.cpp

/**
 *  PowerPMAC_CoordinateSystems class description:
 *    
 */

//================================================================
//  The following table gives the correspondence
//  between command and method names.
//
//  Command name  |  Method name
//================================================================
//  State         |  Inherited (no method)
//  Status        |  Inherited (no method)
//================================================================

//================================================================
//  Attributes managed is:
//================================================================
//================================================================

namespace PowerPMAC_CoordinateSystems_ns
{
/*----- PROTECTED REGION ID(PowerPMAC_CoordinateSystems::namespace_starting) ENABLED START -----*/

//	static initializations

/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CoordinateSystems::namespace_starting

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_CoordinateSystems::PowerPMAC_CoordinateSystems()
 *	Description : Constructors for a Tango device
 *                implementing the classPowerPMAC_CoordinateSystems
 */
//--------------------------------------------------------
PowerPMAC_CoordinateSystems::PowerPMAC_CoordinateSystems(Tango::DeviceClass *cl, string &s)
 : TANGO_BASE_CLASS(cl, s.c_str())
{
	/*----- PROTECTED REGION ID(PowerPMAC_CoordinateSystems::constructor_1) ENABLED START -----*/
	init_device();
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CoordinateSystems::constructor_1
}
//--------------------------------------------------------
PowerPMAC_CoordinateSystems::PowerPMAC_CoordinateSystems(Tango::DeviceClass *cl, const char *s)
 : TANGO_BASE_CLASS(cl, s)
{
	/*----- PROTECTED REGION ID(PowerPMAC_CoordinateSystems::constructor_2) ENABLED START -----*/
	init_device();
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CoordinateSystems::constructor_2
}
//--------------------------------------------------------
PowerPMAC_CoordinateSystems::PowerPMAC_CoordinateSystems(Tango::DeviceClass *cl, const char *s, const char *d)
 : TANGO_BASE_CLASS(cl, s, d)
{
	/*----- PROTECTED REGION ID(PowerPMAC_CoordinateSystems::constructor_3) ENABLED START -----*/
	init_device();
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CoordinateSystems::constructor_3
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_CoordinateSystems::delete_device()
 *	Description : will be called at device destruction or at init command
 */
//--------------------------------------------------------
void PowerPMAC_CoordinateSystems::delete_device()
{
	DEBUG_STREAM << "PowerPMAC_CoordinateSystems::delete_device() " << device_name << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_CoordinateSystems::delete_device) ENABLED START -----*/
	
	//	Delete device allocated objects
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CoordinateSystems::delete_device
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_CoordinateSystems::init_device()
 *	Description : will be called at device initialization.
 */
//--------------------------------------------------------
void PowerPMAC_CoordinateSystems::init_device()
{
	DEBUG_STREAM << "PowerPMAC_CoordinateSystems::init_device() create device " << device_name << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_CoordinateSystems::init_device_before) ENABLED START -----*/
	
	//	Initialization before get_device_property() call
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CoordinateSystems::init_device_before
	
	//	No device property to be read from database
	
	/*----- PROTECTED REGION ID(PowerPMAC_CoordinateSystems::init_device) ENABLED START -----*/
	
	//	Initialize device

	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CoordinateSystems::init_device
}


//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_CoordinateSystems::always_executed_hook()
 *	Description : method always executed before any command is executed
 */
//--------------------------------------------------------
void PowerPMAC_CoordinateSystems::always_executed_hook()
{
	DEBUG_STREAM << "PowerPMAC_CoordinateSystems::always_executed_hook()  " << device_name << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_CoordinateSystems::always_executed_hook) ENABLED START -----*/
	
	//	code always executed before all requests
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CoordinateSystems::always_executed_hook
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_CoordinateSystems::read_attr_hardware()
 *	Description : Hardware acquisition for attributes
 */
//--------------------------------------------------------
void PowerPMAC_CoordinateSystems::read_attr_hardware(TANGO_UNUSED(vector<long> &attr_list))
{
	DEBUG_STREAM << "PowerPMAC_CoordinateSystems::read_attr_hardware(vector<long> &attr_list) entering... " << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_CoordinateSystems::read_attr_hardware) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CoordinateSystems::read_attr_hardware
}


//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_CoordinateSystems::add_dynamic_attributes()
 *	Description : Create the dynamic attributes if any
 *                for specified device.
 */
//--------------------------------------------------------
void PowerPMAC_CoordinateSystems::add_dynamic_attributes()
{
	/*----- PROTECTED REGION ID(PowerPMAC_CoordinateSystems::add_dynamic_attributes) ENABLED START -----*/
	
	//	Add your own code to create and add dynamic attributes if any
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CoordinateSystems::add_dynamic_attributes
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_CoordinateSystems::add_dynamic_commands()
 *	Description : Create the dynamic commands if any
 *                for specified device.
 */
//--------------------------------------------------------
void PowerPMAC_CoordinateSystems::add_dynamic_commands()
{
	/*----- PROTECTED REGION ID(PowerPMAC_CoordinateSystems::add_dynamic_commands) ENABLED START -----*/
	
	//	Add your own code to create and add dynamic commands if any
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CoordinateSystems::add_dynamic_commands
}

/*----- PROTECTED REGION ID(PowerPMAC_CoordinateSystems::namespace_ending) ENABLED START -----*/

//	Additional Methods

/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CoordinateSystems::namespace_ending
} //	namespace
