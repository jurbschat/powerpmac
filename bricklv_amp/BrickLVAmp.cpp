/*----- PROTECTED REGION ID(BrickLVAmp.cpp) ENABLED START -----*/
//=============================================================================
//
// file :        BrickLVAmp.cpp
//
// description : C++ source for the BrickLVAmp class and its commands.
//               The class is derived from Device. It represents the
//               CORBA servant object which will be accessed from the
//               network. All commands which can be executed on the
//               BrickLVAmp are implemented in this file.
//
// project :     BrickLV AMP Control
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


#include <BrickLVAmp.h>
#include <BrickLVAmpClass.h>

/*----- PROTECTED REGION END -----*/	//	BrickLVAmp.cpp

/**
 *  BrickLVAmp class description:
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

namespace BrickLVAmp_ns
{
/*----- PROTECTED REGION ID(BrickLVAmp::namespace_starting) ENABLED START -----*/

//	static initializations

/*----- PROTECTED REGION END -----*/	//	BrickLVAmp::namespace_starting

//--------------------------------------------------------
/**
 *	Method      : BrickLVAmp::BrickLVAmp()
 *	Description : Constructors for a Tango device
 *                implementing the classBrickLVAmp
 */
//--------------------------------------------------------
BrickLVAmp::BrickLVAmp(Tango::DeviceClass *cl, string &s)
 : TANGO_BASE_CLASS(cl, s.c_str())
{
	/*----- PROTECTED REGION ID(BrickLVAmp::constructor_1) ENABLED START -----*/
	init_device();
	
	/*----- PROTECTED REGION END -----*/	//	BrickLVAmp::constructor_1
}
//--------------------------------------------------------
BrickLVAmp::BrickLVAmp(Tango::DeviceClass *cl, const char *s)
 : TANGO_BASE_CLASS(cl, s)
{
	/*----- PROTECTED REGION ID(BrickLVAmp::constructor_2) ENABLED START -----*/
	init_device();
	
	/*----- PROTECTED REGION END -----*/	//	BrickLVAmp::constructor_2
}
//--------------------------------------------------------
BrickLVAmp::BrickLVAmp(Tango::DeviceClass *cl, const char *s, const char *d)
 : TANGO_BASE_CLASS(cl, s, d)
{
	/*----- PROTECTED REGION ID(BrickLVAmp::constructor_3) ENABLED START -----*/
	init_device();
	
	/*----- PROTECTED REGION END -----*/	//	BrickLVAmp::constructor_3
}

//--------------------------------------------------------
/**
 *	Method      : BrickLVAmp::delete_device()
 *	Description : will be called at device destruction or at init command
 */
//--------------------------------------------------------
void BrickLVAmp::delete_device()
{
	DEBUG_STREAM << "BrickLVAmp::delete_device() " << device_name << endl;
	/*----- PROTECTED REGION ID(BrickLVAmp::delete_device) ENABLED START -----*/
	
	//	Delete device allocated objects
	
	/*----- PROTECTED REGION END -----*/	//	BrickLVAmp::delete_device
}

//--------------------------------------------------------
/**
 *	Method      : BrickLVAmp::init_device()
 *	Description : will be called at device initialization.
 */
//--------------------------------------------------------
void BrickLVAmp::init_device()
{
	DEBUG_STREAM << "BrickLVAmp::init_device() create device " << device_name << endl;
	/*----- PROTECTED REGION ID(BrickLVAmp::init_device_before) ENABLED START -----*/
	
	//	Initialization before get_device_property() call
	
	/*----- PROTECTED REGION END -----*/	//	BrickLVAmp::init_device_before
	
	//	No device property to be read from database
	
	/*----- PROTECTED REGION ID(BrickLVAmp::init_device) ENABLED START -----*/
	
	//	Initialize device
	
	/*----- PROTECTED REGION END -----*/	//	BrickLVAmp::init_device
}


//--------------------------------------------------------
/**
 *	Method      : BrickLVAmp::always_executed_hook()
 *	Description : method always executed before any command is executed
 */
//--------------------------------------------------------
void BrickLVAmp::always_executed_hook()
{
	DEBUG_STREAM << "BrickLVAmp::always_executed_hook()  " << device_name << endl;
	/*----- PROTECTED REGION ID(BrickLVAmp::always_executed_hook) ENABLED START -----*/
	
	//	code always executed before all requests
	
	/*----- PROTECTED REGION END -----*/	//	BrickLVAmp::always_executed_hook
}

//--------------------------------------------------------
/**
 *	Method      : BrickLVAmp::read_attr_hardware()
 *	Description : Hardware acquisition for attributes
 */
//--------------------------------------------------------
void BrickLVAmp::read_attr_hardware(TANGO_UNUSED(vector<long> &attr_list))
{
	DEBUG_STREAM << "BrickLVAmp::read_attr_hardware(vector<long> &attr_list) entering... " << endl;
	/*----- PROTECTED REGION ID(BrickLVAmp::read_attr_hardware) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	BrickLVAmp::read_attr_hardware
}


//--------------------------------------------------------
/**
 *	Method      : BrickLVAmp::add_dynamic_attributes()
 *	Description : Create the dynamic attributes if any
 *                for specified device.
 */
//--------------------------------------------------------
void BrickLVAmp::add_dynamic_attributes()
{
	/*----- PROTECTED REGION ID(BrickLVAmp::add_dynamic_attributes) ENABLED START -----*/
	
	//	Add your own code to create and add dynamic attributes if any
	
	/*----- PROTECTED REGION END -----*/	//	BrickLVAmp::add_dynamic_attributes
}

//--------------------------------------------------------
/**
 *	Method      : BrickLVAmp::add_dynamic_commands()
 *	Description : Create the dynamic commands if any
 *                for specified device.
 */
//--------------------------------------------------------
void BrickLVAmp::add_dynamic_commands()
{
	/*----- PROTECTED REGION ID(BrickLVAmp::add_dynamic_commands) ENABLED START -----*/
	
	//	Add your own code to create and add dynamic commands if any
	
	/*----- PROTECTED REGION END -----*/	//	BrickLVAmp::add_dynamic_commands
}

/*----- PROTECTED REGION ID(BrickLVAmp::namespace_ending) ENABLED START -----*/

//	Additional Methods

/*----- PROTECTED REGION END -----*/	//	BrickLVAmp::namespace_ending
} //	namespace
