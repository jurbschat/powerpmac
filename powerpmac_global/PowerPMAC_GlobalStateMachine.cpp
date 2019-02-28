/*----- PROTECTED REGION ID(PowerPMAC_GlobalStateMachine.cpp) ENABLED START -----*/
//=============================================================================
//
// file :        PowerPMAC_GlobalStateMachine.cpp
//
// description : State machine file for the PowerPMAC_Global class
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

#include <PowerPMAC_Global.h>

/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Global::PowerPMAC_GlobalStateMachine.cpp

//================================================================
//  States  |  Description
//================================================================
//  ON      |  
//  OFF     |  
//  FAULT   |  


namespace PowerPMAC_Global_ns
{
//=================================================
//		Attributes Allowed Methods
//=================================================

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_Global::is_MaxMotors_allowed()
 *	Description : Execution allowed for MaxMotors attribute
 */
//--------------------------------------------------------
bool PowerPMAC_Global::is_MaxMotors_allowed(TANGO_UNUSED(Tango::AttReqType type))
{

	//	Not any excluded states for MaxMotors attribute in read access.
	/*----- PROTECTED REGION ID(PowerPMAC_Global::MaxMotorsStateAllowed_READ) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Global::MaxMotorsStateAllowed_READ
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_Global::is_MaxCoords_allowed()
 *	Description : Execution allowed for MaxCoords attribute
 */
//--------------------------------------------------------
bool PowerPMAC_Global::is_MaxCoords_allowed(TANGO_UNUSED(Tango::AttReqType type))
{

	//	Not any excluded states for MaxCoords attribute in read access.
	/*----- PROTECTED REGION ID(PowerPMAC_Global::MaxCoordsStateAllowed_READ) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Global::MaxCoordsStateAllowed_READ
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_Global::is_AbortAll_allowed()
 *	Description : Execution allowed for AbortAll attribute
 */
//--------------------------------------------------------
bool PowerPMAC_Global::is_AbortAll_allowed(TANGO_UNUSED(Tango::AttReqType type))
{

	//	Not any excluded states for AbortAll attribute in read access.
	/*----- PROTECTED REGION ID(PowerPMAC_Global::AbortAllStateAllowed_READ) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Global::AbortAllStateAllowed_READ
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_Global::is_CpuTemp_allowed()
 *	Description : Execution allowed for CpuTemp attribute
 */
//--------------------------------------------------------
bool PowerPMAC_Global::is_CpuTemp_allowed(TANGO_UNUSED(Tango::AttReqType type))
{

	//	Not any excluded states for CpuTemp attribute in read access.
	/*----- PROTECTED REGION ID(PowerPMAC_Global::CpuTempStateAllowed_READ) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Global::CpuTempStateAllowed_READ
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_Global::is_AmpOverTemp_allowed()
 *	Description : Execution allowed for AmpOverTemp attribute
 */
//--------------------------------------------------------
bool PowerPMAC_Global::is_AmpOverTemp_allowed(TANGO_UNUSED(Tango::AttReqType type))
{

	//	Not any excluded states for AmpOverTemp attribute in read access.
	/*----- PROTECTED REGION ID(PowerPMAC_Global::AmpOverTempStateAllowed_READ) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Global::AmpOverTempStateAllowed_READ
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_Global::is_Firmware_allowed()
 *	Description : Execution allowed for Firmware attribute
 */
//--------------------------------------------------------
bool PowerPMAC_Global::is_Firmware_allowed(TANGO_UNUSED(Tango::AttReqType type))
{

	//	Not any excluded states for Firmware attribute in read access.
	/*----- PROTECTED REGION ID(PowerPMAC_Global::FirmwareStateAllowed_READ) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Global::FirmwareStateAllowed_READ
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_Global::is_SystemType_allowed()
 *	Description : Execution allowed for SystemType attribute
 */
//--------------------------------------------------------
bool PowerPMAC_Global::is_SystemType_allowed(TANGO_UNUSED(Tango::AttReqType type))
{

	//	Not any excluded states for SystemType attribute in read access.
	/*----- PROTECTED REGION ID(PowerPMAC_Global::SystemTypeStateAllowed_READ) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Global::SystemTypeStateAllowed_READ
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_Global::is_CpuType_allowed()
 *	Description : Execution allowed for CpuType attribute
 */
//--------------------------------------------------------
bool PowerPMAC_Global::is_CpuType_allowed(TANGO_UNUSED(Tango::AttReqType type))
{

	//	Not any excluded states for CpuType attribute in read access.
	/*----- PROTECTED REGION ID(PowerPMAC_Global::CpuTypeStateAllowed_READ) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Global::CpuTypeStateAllowed_READ
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_Global::is_CpuFrequency_allowed()
 *	Description : Execution allowed for CpuFrequency attribute
 */
//--------------------------------------------------------
bool PowerPMAC_Global::is_CpuFrequency_allowed(TANGO_UNUSED(Tango::AttReqType type))
{

	//	Not any excluded states for CpuFrequency attribute in read access.
	/*----- PROTECTED REGION ID(PowerPMAC_Global::CpuFrequencyStateAllowed_READ) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Global::CpuFrequencyStateAllowed_READ
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_Global::is_Uptime_allowed()
 *	Description : Execution allowed for Uptime attribute
 */
//--------------------------------------------------------
bool PowerPMAC_Global::is_Uptime_allowed(TANGO_UNUSED(Tango::AttReqType type))
{

	//	Not any excluded states for Uptime attribute in read access.
	/*----- PROTECTED REGION ID(PowerPMAC_Global::UptimeStateAllowed_READ) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Global::UptimeStateAllowed_READ
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_Global::is_AmpStatus_allowed()
 *	Description : Execution allowed for AmpStatus attribute
 */
//--------------------------------------------------------
bool PowerPMAC_Global::is_AmpStatus_allowed(TANGO_UNUSED(Tango::AttReqType type))
{

	//	Not any excluded states for AmpStatus attribute in read access.
	/*----- PROTECTED REGION ID(PowerPMAC_Global::AmpStatusStateAllowed_READ) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Global::AmpStatusStateAllowed_READ
	return true;
}


//=================================================
//		Commands Allowed Methods
//=================================================

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_Global::is_ResetAmp_allowed()
 *	Description : Execution allowed for ResetAmp attribute
 */
//--------------------------------------------------------
bool PowerPMAC_Global::is_ResetAmp_allowed(TANGO_UNUSED(const CORBA::Any &any))
{
	//	Compare device state with not allowed states.
	if (get_state()==Tango::OFF ||
		get_state()==Tango::FAULT)
	{
	/*----- PROTECTED REGION ID(PowerPMAC_Global::ResetAmpStateAllowed) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Global::ResetAmpStateAllowed
		return false;
	}
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_Global::is_ExecuteCommand_allowed()
 *	Description : Execution allowed for ExecuteCommand attribute
 */
//--------------------------------------------------------
bool PowerPMAC_Global::is_ExecuteCommand_allowed(TANGO_UNUSED(const CORBA::Any &any))
{
	//	Compare device state with not allowed states.
	if (get_state()==Tango::OFF ||
		get_state()==Tango::FAULT)
	{
	/*----- PROTECTED REGION ID(PowerPMAC_Global::ExecuteCommandStateAllowed) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Global::ExecuteCommandStateAllowed
		return false;
	}
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_Global::is_Reset_allowed()
 *	Description : Execution allowed for Reset attribute
 */
//--------------------------------------------------------
bool PowerPMAC_Global::is_Reset_allowed(TANGO_UNUSED(const CORBA::Any &any))
{
	//	Compare device state with not allowed states.
	if (get_state()==Tango::OFF ||
		get_state()==Tango::FAULT)
	{
	/*----- PROTECTED REGION ID(PowerPMAC_Global::ResetStateAllowed) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Global::ResetStateAllowed
		return false;
	}
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_Global::is_Reboot_allowed()
 *	Description : Execution allowed for Reboot attribute
 */
//--------------------------------------------------------
bool PowerPMAC_Global::is_Reboot_allowed(TANGO_UNUSED(const CORBA::Any &any))
{
	//	Compare device state with not allowed states.
	if (get_state()==Tango::OFF ||
		get_state()==Tango::FAULT)
	{
	/*----- PROTECTED REGION ID(PowerPMAC_Global::RebootStateAllowed) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Global::RebootStateAllowed
		return false;
	}
	return true;
}


/*----- PROTECTED REGION ID(PowerPMAC_Global::PowerPMAC_GlobalStateAllowed.AdditionalMethods) ENABLED START -----*/

//	Additional Methods

/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Global::PowerPMAC_GlobalStateAllowed.AdditionalMethods

}	//	End of namespace
