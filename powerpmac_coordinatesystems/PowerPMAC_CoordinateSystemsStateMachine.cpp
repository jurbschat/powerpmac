/*----- PROTECTED REGION ID(PowerPMAC_CoordinateSystemsStateMachine.cpp) ENABLED START -----*/
//=============================================================================
//
// file :        PowerPMAC_CoordinateSystemsStateMachine.cpp
//
// description : State machine file for the PowerPMAC_CoordinateSystems class
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

/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CoordinateSystems::PowerPMAC_CoordinateSystemsStateMachine.cpp

//================================================================
//  States  |  Description
//================================================================
//  ON      |  
//  OFF     |  
//  FAULT   |  
//  MOVING  |  


namespace PowerPMAC_CoordinateSystems_ns
{
//=================================================
//		Attributes Allowed Methods
//=================================================

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_CoordinateSystems::is_NumAxis_allowed()
 *	Description : Execution allowed for NumAxis attribute
 */
//--------------------------------------------------------
bool PowerPMAC_CoordinateSystems::is_NumAxis_allowed(TANGO_UNUSED(Tango::AttReqType type))
{

	//	Not any excluded states for NumAxis attribute in read access.
	/*----- PROTECTED REGION ID(PowerPMAC_CoordinateSystems::NumAxisStateAllowed_READ) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CoordinateSystems::NumAxisStateAllowed_READ
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_CoordinateSystems::is_X_allowed()
 *	Description : Execution allowed for X attribute
 */
//--------------------------------------------------------
bool PowerPMAC_CoordinateSystems::is_X_allowed(TANGO_UNUSED(Tango::AttReqType type))
{
	//	Check access type.
	if ( type!=Tango::READ_REQ )
	{
		//	Compare device state with not allowed states for WRITE 
		if (get_state()==Tango::OFF ||
			get_state()==Tango::FAULT ||
			get_state()==Tango::MOVING)
		{
		/*----- PROTECTED REGION ID(PowerPMAC_CoordinateSystems::XStateAllowed_WRITE) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CoordinateSystems::XStateAllowed_WRITE
			return false;
		}
		return true;
	}
	else

	//	Not any excluded states for X attribute in read access.
	/*----- PROTECTED REGION ID(PowerPMAC_CoordinateSystems::XStateAllowed_READ) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CoordinateSystems::XStateAllowed_READ
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_CoordinateSystems::is_Y_allowed()
 *	Description : Execution allowed for Y attribute
 */
//--------------------------------------------------------
bool PowerPMAC_CoordinateSystems::is_Y_allowed(TANGO_UNUSED(Tango::AttReqType type))
{
	//	Check access type.
	if ( type!=Tango::READ_REQ )
	{
		//	Compare device state with not allowed states for WRITE 
		if (get_state()==Tango::OFF ||
			get_state()==Tango::FAULT ||
			get_state()==Tango::MOVING)
		{
		/*----- PROTECTED REGION ID(PowerPMAC_CoordinateSystems::YStateAllowed_WRITE) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CoordinateSystems::YStateAllowed_WRITE
			return false;
		}
		return true;
	}
	else

	//	Not any excluded states for Y attribute in read access.
	/*----- PROTECTED REGION ID(PowerPMAC_CoordinateSystems::YStateAllowed_READ) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CoordinateSystems::YStateAllowed_READ
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_CoordinateSystems::is_Z_allowed()
 *	Description : Execution allowed for Z attribute
 */
//--------------------------------------------------------
bool PowerPMAC_CoordinateSystems::is_Z_allowed(TANGO_UNUSED(Tango::AttReqType type))
{
	//	Check access type.
	if ( type!=Tango::READ_REQ )
	{
		//	Compare device state with not allowed states for WRITE 
		if (get_state()==Tango::OFF ||
			get_state()==Tango::FAULT ||
			get_state()==Tango::MOVING)
		{
		/*----- PROTECTED REGION ID(PowerPMAC_CoordinateSystems::ZStateAllowed_WRITE) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CoordinateSystems::ZStateAllowed_WRITE
			return false;
		}
		return true;
	}
	else

	//	Not any excluded states for Z attribute in read access.
	/*----- PROTECTED REGION ID(PowerPMAC_CoordinateSystems::ZStateAllowed_READ) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CoordinateSystems::ZStateAllowed_READ
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_CoordinateSystems::is_W_allowed()
 *	Description : Execution allowed for W attribute
 */
//--------------------------------------------------------
bool PowerPMAC_CoordinateSystems::is_W_allowed(TANGO_UNUSED(Tango::AttReqType type))
{
	//	Check access type.
	if ( type!=Tango::READ_REQ )
	{
		//	Compare device state with not allowed states for WRITE 
		if (get_state()==Tango::OFF ||
			get_state()==Tango::FAULT ||
			get_state()==Tango::MOVING)
		{
		/*----- PROTECTED REGION ID(PowerPMAC_CoordinateSystems::WStateAllowed_WRITE) ENABLED START -----*/
		
		/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CoordinateSystems::WStateAllowed_WRITE
			return false;
		}
		return true;
	}
	else

	//	Not any excluded states for W attribute in read access.
	/*----- PROTECTED REGION ID(PowerPMAC_CoordinateSystems::WStateAllowed_READ) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CoordinateSystems::WStateAllowed_READ
	return true;
}


//=================================================
//		Commands Allowed Methods
//=================================================

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_CoordinateSystems::is_Abort_allowed()
 *	Description : Execution allowed for Abort attribute
 */
//--------------------------------------------------------
bool PowerPMAC_CoordinateSystems::is_Abort_allowed(TANGO_UNUSED(const CORBA::Any &any))
{
	//	Not any excluded states for Abort command.
	/*----- PROTECTED REGION ID(PowerPMAC_CoordinateSystems::AbortStateAllowed) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CoordinateSystems::AbortStateAllowed
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_CoordinateSystems::is_RunMotionProgram_allowed()
 *	Description : Execution allowed for RunMotionProgram attribute
 */
//--------------------------------------------------------
bool PowerPMAC_CoordinateSystems::is_RunMotionProgram_allowed(TANGO_UNUSED(const CORBA::Any &any))
{
	//	Not any excluded states for RunMotionProgram command.
	/*----- PROTECTED REGION ID(PowerPMAC_CoordinateSystems::RunMotionProgramStateAllowed) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CoordinateSystems::RunMotionProgramStateAllowed
	return true;
}


/*----- PROTECTED REGION ID(PowerPMAC_CoordinateSystems::PowerPMAC_CoordinateSystemsStateAllowed.AdditionalMethods) ENABLED START -----*/

//	Additional Methods

/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CoordinateSystems::PowerPMAC_CoordinateSystemsStateAllowed.AdditionalMethods

}	//	End of namespace
