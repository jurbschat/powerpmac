/*----- PROTECTED REGION ID(PowerPMAC_CompensationTableStateMachine.cpp) ENABLED START -----*/
//=============================================================================
//
// file :        PowerPMAC_CompensationTableStateMachine.cpp
//
// description : State machine file for the PowerPMAC_CompensationTable class
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

#include <PowerPMAC_CompensationTable.h>

/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CompensationTable::PowerPMAC_CompensationTableStateMachine.cpp

//================================================================
//  States  |  Description
//================================================================
//  ON      |  
//  OFF     |  


namespace PowerPMAC_CompensationTable_ns
{
//=================================================
//		Attributes Allowed Methods
//=================================================

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_CompensationTable::is_SourceMotor_allowed()
 *	Description : Execution allowed for SourceMotor attribute
 */
//--------------------------------------------------------
bool PowerPMAC_CompensationTable::is_SourceMotor_allowed(TANGO_UNUSED(Tango::AttReqType type))
{
	//	Check access type.
	if ( type!=Tango::READ_REQ )
	{
		//	Compare device state with not allowed states for WRITE 
		if (get_state()==Tango::OFF)
		{
		/*----- PROTECTED REGION ID(PowerPMAC_CompensationTable::SourceMotorStateAllowed_WRITE) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CompensationTable::SourceMotorStateAllowed_WRITE
			return false;
		}
		return true;
	}
	else

	//	Check access type.
	if ( type==Tango::READ_REQ )
	{
		//	Compare device state with not allowed states for READ 
		if (get_state()==Tango::OFF)
		{
		/*----- PROTECTED REGION ID(PowerPMAC_CompensationTable::SourceMotorStateAllowed_READ) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CompensationTable::SourceMotorStateAllowed_READ
			return false;
		}
		return true;
	}
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_CompensationTable::is_TargetMotor_allowed()
 *	Description : Execution allowed for TargetMotor attribute
 */
//--------------------------------------------------------
bool PowerPMAC_CompensationTable::is_TargetMotor_allowed(TANGO_UNUSED(Tango::AttReqType type))
{
	//	Check access type.
	if ( type!=Tango::READ_REQ )
	{
		//	Compare device state with not allowed states for WRITE 
		if (get_state()==Tango::OFF)
		{
		/*----- PROTECTED REGION ID(PowerPMAC_CompensationTable::TargetMotorStateAllowed_WRITE) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CompensationTable::TargetMotorStateAllowed_WRITE
			return false;
		}
		return true;
	}
	else

	//	Check access type.
	if ( type==Tango::READ_REQ )
	{
		//	Compare device state with not allowed states for READ 
		if (get_state()==Tango::OFF)
		{
		/*----- PROTECTED REGION ID(PowerPMAC_CompensationTable::TargetMotorStateAllowed_READ) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CompensationTable::TargetMotorStateAllowed_READ
			return false;
		}
		return true;
	}
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_CompensationTable::is_From_allowed()
 *	Description : Execution allowed for From attribute
 */
//--------------------------------------------------------
bool PowerPMAC_CompensationTable::is_From_allowed(TANGO_UNUSED(Tango::AttReqType type))
{
	//	Check access type.
	if ( type!=Tango::READ_REQ )
	{
		//	Compare device state with not allowed states for WRITE 
		if (get_state()==Tango::OFF)
		{
		/*----- PROTECTED REGION ID(PowerPMAC_CompensationTable::FromStateAllowed_WRITE) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CompensationTable::FromStateAllowed_WRITE
			return false;
		}
		return true;
	}
	else

	//	Check access type.
	if ( type==Tango::READ_REQ )
	{
		//	Compare device state with not allowed states for READ 
		if (get_state()==Tango::OFF)
		{
		/*----- PROTECTED REGION ID(PowerPMAC_CompensationTable::FromStateAllowed_READ) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CompensationTable::FromStateAllowed_READ
			return false;
		}
		return true;
	}
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_CompensationTable::is_To_allowed()
 *	Description : Execution allowed for To attribute
 */
//--------------------------------------------------------
bool PowerPMAC_CompensationTable::is_To_allowed(TANGO_UNUSED(Tango::AttReqType type))
{
	//	Check access type.
	if ( type!=Tango::READ_REQ )
	{
		//	Compare device state with not allowed states for WRITE 
		if (get_state()==Tango::OFF)
		{
		/*----- PROTECTED REGION ID(PowerPMAC_CompensationTable::ToStateAllowed_WRITE) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CompensationTable::ToStateAllowed_WRITE
			return false;
		}
		return true;
	}
	else

	//	Check access type.
	if ( type==Tango::READ_REQ )
	{
		//	Compare device state with not allowed states for READ 
		if (get_state()==Tango::OFF)
		{
		/*----- PROTECTED REGION ID(PowerPMAC_CompensationTable::ToStateAllowed_READ) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CompensationTable::ToStateAllowed_READ
			return false;
		}
		return true;
	}
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_CompensationTable::is_CompensationTable_allowed()
 *	Description : Execution allowed for CompensationTable attribute
 */
//--------------------------------------------------------
bool PowerPMAC_CompensationTable::is_CompensationTable_allowed(TANGO_UNUSED(Tango::AttReqType type))
{
	//	Check access type.
	if ( type!=Tango::READ_REQ )
	{
		//	Compare device state with not allowed states for WRITE 
		if (get_state()==Tango::OFF)
		{
		/*----- PROTECTED REGION ID(PowerPMAC_CompensationTable::CompensationTableStateAllowed_WRITE) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CompensationTable::CompensationTableStateAllowed_WRITE
			return false;
		}
		return true;
	}
	else

	//	Check access type.
	if ( type==Tango::READ_REQ )
	{
		//	Compare device state with not allowed states for READ 
		if (get_state()==Tango::OFF)
		{
		/*----- PROTECTED REGION ID(PowerPMAC_CompensationTable::CompensationTableStateAllowed_READ) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CompensationTable::CompensationTableStateAllowed_READ
			return false;
		}
		return true;
	}
	return true;
}


//=================================================
//		Commands Allowed Methods
//=================================================

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_CompensationTable::is_ResetTarget_allowed()
 *	Description : Execution allowed for ResetTarget attribute
 */
//--------------------------------------------------------
bool PowerPMAC_CompensationTable::is_ResetTarget_allowed(TANGO_UNUSED(const CORBA::Any &any))
{
	//	Not any excluded states for ResetTarget command.
	/*----- PROTECTED REGION ID(PowerPMAC_CompensationTable::ResetTargetStateAllowed) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CompensationTable::ResetTargetStateAllowed
	return true;
}


/*----- PROTECTED REGION ID(PowerPMAC_CompensationTable::PowerPMAC_CompensationTableStateAllowed.AdditionalMethods) ENABLED START -----*/

//	Additional Methods

/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CompensationTable::PowerPMAC_CompensationTableStateAllowed.AdditionalMethods

}	//	End of namespace
