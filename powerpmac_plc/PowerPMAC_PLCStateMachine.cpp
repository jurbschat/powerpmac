/*----- PROTECTED REGION ID(PowerPMAC_PLCStateMachine.cpp) ENABLED START -----*/
//=============================================================================
//
// file :        PowerPMAC_PLCStateMachine.cpp
//
// description : State machine file for the PowerPMAC_PLC class
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

#include <PowerPMAC_PLC.h>

/*----- PROTECTED REGION END -----*/	//	PowerPMAC_PLC::PowerPMAC_PLCStateMachine.cpp

//================================================================
//  States   |  Description
//================================================================
//  ON       |  
//  OFF      |  
//  STANDBY  |  
//  FAULT    |  


namespace PowerPMAC_PLC_ns
{
//=================================================
//		Attributes Allowed Methods
//=================================================

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_PLC::is_active_allowed()
 *	Description : Execution allowed for active attribute
 */
//--------------------------------------------------------
bool PowerPMAC_PLC::is_active_allowed(TANGO_UNUSED(Tango::AttReqType type))
{

	//	Not any excluded states for active attribute in read access.
	/*----- PROTECTED REGION ID(PowerPMAC_PLC::activeStateAllowed_READ) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_PLC::activeStateAllowed_READ
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_PLC::is_running_allowed()
 *	Description : Execution allowed for running attribute
 */
//--------------------------------------------------------
bool PowerPMAC_PLC::is_running_allowed(TANGO_UNUSED(Tango::AttReqType type))
{

	//	Not any excluded states for running attribute in read access.
	/*----- PROTECTED REGION ID(PowerPMAC_PLC::runningStateAllowed_READ) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_PLC::runningStateAllowed_READ
	return true;
}


//=================================================
//		Commands Allowed Methods
//=================================================

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_PLC::is_Enable_allowed()
 *	Description : Execution allowed for Enable attribute
 */
//--------------------------------------------------------
bool PowerPMAC_PLC::is_Enable_allowed(TANGO_UNUSED(const CORBA::Any &any))
{
	//	Compare device state with not allowed states.
	if (get_state()==Tango::ON ||
		get_state()==Tango::STANDBY ||
		get_state()==Tango::FAULT)
	{
	/*----- PROTECTED REGION ID(PowerPMAC_PLC::EnableStateAllowed) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_PLC::EnableStateAllowed
		return false;
	}
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_PLC::is_Disable_allowed()
 *	Description : Execution allowed for Disable attribute
 */
//--------------------------------------------------------
bool PowerPMAC_PLC::is_Disable_allowed(TANGO_UNUSED(const CORBA::Any &any))
{
	//	Compare device state with not allowed states.
	if (get_state()==Tango::OFF ||
		get_state()==Tango::FAULT)
	{
	/*----- PROTECTED REGION ID(PowerPMAC_PLC::DisableStateAllowed) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_PLC::DisableStateAllowed
		return false;
	}
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_PLC::is_Pause_allowed()
 *	Description : Execution allowed for Pause attribute
 */
//--------------------------------------------------------
bool PowerPMAC_PLC::is_Pause_allowed(TANGO_UNUSED(const CORBA::Any &any))
{
	//	Compare device state with not allowed states.
	if (get_state()==Tango::FAULT)
	{
	/*----- PROTECTED REGION ID(PowerPMAC_PLC::PauseStateAllowed) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_PLC::PauseStateAllowed
		return false;
	}
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_PLC::is_Resume_allowed()
 *	Description : Execution allowed for Resume attribute
 */
//--------------------------------------------------------
bool PowerPMAC_PLC::is_Resume_allowed(TANGO_UNUSED(const CORBA::Any &any))
{
	//	Compare device state with not allowed states.
	if (get_state()==Tango::FAULT)
	{
	/*----- PROTECTED REGION ID(PowerPMAC_PLC::ResumeStateAllowed) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_PLC::ResumeStateAllowed
		return false;
	}
	return true;
}


/*----- PROTECTED REGION ID(PowerPMAC_PLC::PowerPMAC_PLCStateAllowed.AdditionalMethods) ENABLED START -----*/

//	Additional Methods

/*----- PROTECTED REGION END -----*/	//	PowerPMAC_PLC::PowerPMAC_PLCStateAllowed.AdditionalMethods

}	//	End of namespace