/*----- PROTECTED REGION ID(PowerPMAC_MotorStateMachine.cpp) ENABLED START -----*/
//=============================================================================
//
// file :        PowerPMAC_MotorStateMachine.cpp
//
// description : State machine file for the PowerPMAC_Motor class
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

#include <PowerPMAC_Motor.h>

/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::PowerPMAC_MotorStateMachine.cpp

//================================================================
//  States  |  Description
//================================================================
//  ON      |  
//  OFF     |  
//  INIT    |  
//  MOVING  |  
//  FAULT   |  


namespace PowerPMAC_Motor_ns
{
//=================================================
//		Attributes Allowed Methods
//=================================================

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_Motor::is_position_allowed()
 *	Description : Execution allowed for position attribute
 */
//--------------------------------------------------------
bool PowerPMAC_Motor::is_position_allowed(TANGO_UNUSED(Tango::AttReqType type))
{
	//	Not any excluded states for position attribute in Write access.
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::positionStateAllowed_WRITE) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::positionStateAllowed_WRITE

	//	Not any excluded states for position attribute in read access.
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::positionStateAllowed_READ) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::positionStateAllowed_READ
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_Motor::is_acceleration_allowed()
 *	Description : Execution allowed for acceleration attribute
 */
//--------------------------------------------------------
bool PowerPMAC_Motor::is_acceleration_allowed(TANGO_UNUSED(Tango::AttReqType type))
{
	//	Not any excluded states for acceleration attribute in Write access.
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::accelerationStateAllowed_WRITE) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::accelerationStateAllowed_WRITE

	//	Not any excluded states for acceleration attribute in read access.
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::accelerationStateAllowed_READ) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::accelerationStateAllowed_READ
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_Motor::is_max_velocity_allowed()
 *	Description : Execution allowed for max_velocity attribute
 */
//--------------------------------------------------------
bool PowerPMAC_Motor::is_max_velocity_allowed(TANGO_UNUSED(Tango::AttReqType type))
{
	//	Not any excluded states for max_velocity attribute in Write access.
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::max_velocityStateAllowed_WRITE) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::max_velocityStateAllowed_WRITE

	//	Not any excluded states for max_velocity attribute in read access.
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::max_velocityStateAllowed_READ) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::max_velocityStateAllowed_READ
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_Motor::is_sl_cw_allowed()
 *	Description : Execution allowed for sl_cw attribute
 */
//--------------------------------------------------------
bool PowerPMAC_Motor::is_sl_cw_allowed(TANGO_UNUSED(Tango::AttReqType type))
{
	//	Not any excluded states for sl_cw attribute in Write access.
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::sl_cwStateAllowed_WRITE) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::sl_cwStateAllowed_WRITE

	//	Not any excluded states for sl_cw attribute in read access.
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::sl_cwStateAllowed_READ) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::sl_cwStateAllowed_READ
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_Motor::is_sl_ccw_allowed()
 *	Description : Execution allowed for sl_ccw attribute
 */
//--------------------------------------------------------
bool PowerPMAC_Motor::is_sl_ccw_allowed(TANGO_UNUSED(Tango::AttReqType type))
{
	//	Not any excluded states for sl_ccw attribute in Write access.
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::sl_ccwStateAllowed_WRITE) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::sl_ccwStateAllowed_WRITE

	//	Not any excluded states for sl_ccw attribute in read access.
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::sl_ccwStateAllowed_READ) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::sl_ccwStateAllowed_READ
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_Motor::is_sl_cw_fault_allowed()
 *	Description : Execution allowed for sl_cw_fault attribute
 */
//--------------------------------------------------------
bool PowerPMAC_Motor::is_sl_cw_fault_allowed(TANGO_UNUSED(Tango::AttReqType type))
{

	//	Not any excluded states for sl_cw_fault attribute in read access.
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::sl_cw_faultStateAllowed_READ) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::sl_cw_faultStateAllowed_READ
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_Motor::is_sl_ccw_fault_allowed()
 *	Description : Execution allowed for sl_ccw_fault attribute
 */
//--------------------------------------------------------
bool PowerPMAC_Motor::is_sl_ccw_fault_allowed(TANGO_UNUSED(Tango::AttReqType type))
{

	//	Not any excluded states for sl_ccw_fault attribute in read access.
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::sl_ccw_faultStateAllowed_READ) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::sl_ccw_faultStateAllowed_READ
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_Motor::is_limit_cw_fault_allowed()
 *	Description : Execution allowed for limit_cw_fault attribute
 */
//--------------------------------------------------------
bool PowerPMAC_Motor::is_limit_cw_fault_allowed(TANGO_UNUSED(Tango::AttReqType type))
{

	//	Not any excluded states for limit_cw_fault attribute in read access.
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::limit_cw_faultStateAllowed_READ) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::limit_cw_faultStateAllowed_READ
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_Motor::is_limit_ccw_fault_allowed()
 *	Description : Execution allowed for limit_ccw_fault attribute
 */
//--------------------------------------------------------
bool PowerPMAC_Motor::is_limit_ccw_fault_allowed(TANGO_UNUSED(Tango::AttReqType type))
{

	//	Not any excluded states for limit_ccw_fault attribute in read access.
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::limit_ccw_faultStateAllowed_READ) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::limit_ccw_faultStateAllowed_READ
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_Motor::is_conversion_factor_allowed()
 *	Description : Execution allowed for conversion_factor attribute
 */
//--------------------------------------------------------
bool PowerPMAC_Motor::is_conversion_factor_allowed(TANGO_UNUSED(Tango::AttReqType type))
{
	//	Not any excluded states for conversion_factor attribute in Write access.
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::conversion_factorStateAllowed_WRITE) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::conversion_factorStateAllowed_WRITE

	//	Not any excluded states for conversion_factor attribute in read access.
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::conversion_factorStateAllowed_READ) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::conversion_factorStateAllowed_READ
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_Motor::is_invert_direction_allowed()
 *	Description : Execution allowed for invert_direction attribute
 */
//--------------------------------------------------------
bool PowerPMAC_Motor::is_invert_direction_allowed(TANGO_UNUSED(Tango::AttReqType type))
{
	//	Not any excluded states for invert_direction attribute in Write access.
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::invert_directionStateAllowed_WRITE) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::invert_directionStateAllowed_WRITE

	//	Not any excluded states for invert_direction attribute in read access.
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::invert_directionStateAllowed_READ) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::invert_directionStateAllowed_READ
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_Motor::is_invert_encoder_allowed()
 *	Description : Execution allowed for invert_encoder attribute
 */
//--------------------------------------------------------
bool PowerPMAC_Motor::is_invert_encoder_allowed(TANGO_UNUSED(Tango::AttReqType type))
{
	//	Not any excluded states for invert_encoder attribute in Write access.
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::invert_encoderStateAllowed_WRITE) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::invert_encoderStateAllowed_WRITE

	//	Not any excluded states for invert_encoder attribute in read access.
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::invert_encoderStateAllowed_READ) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::invert_encoderStateAllowed_READ
	return true;
}


//=================================================
//		Commands Allowed Methods
//=================================================

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_Motor::is_PhaseMotor_allowed()
 *	Description : Execution allowed for PhaseMotor attribute
 */
//--------------------------------------------------------
bool PowerPMAC_Motor::is_PhaseMotor_allowed(TANGO_UNUSED(const CORBA::Any &any))
{
	//	Not any excluded states for PhaseMotor command.
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::PhaseMotorStateAllowed) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::PhaseMotorStateAllowed
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_Motor::is_HomeMotor_allowed()
 *	Description : Execution allowed for HomeMotor attribute
 */
//--------------------------------------------------------
bool PowerPMAC_Motor::is_HomeMotor_allowed(TANGO_UNUSED(const CORBA::Any &any))
{
	//	Not any excluded states for HomeMotor command.
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::HomeMotorStateAllowed) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::HomeMotorStateAllowed
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_Motor::is_Calibrate_allowed()
 *	Description : Execution allowed for Calibrate attribute
 */
//--------------------------------------------------------
bool PowerPMAC_Motor::is_Calibrate_allowed(TANGO_UNUSED(const CORBA::Any &any))
{
	//	Not any excluded states for Calibrate command.
	/*----- PROTECTED REGION ID(PowerPMAC_Motor::CalibrateStateAllowed) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::CalibrateStateAllowed
	return true;
}


/*----- PROTECTED REGION ID(PowerPMAC_Motor::PowerPMAC_MotorStateAllowed.AdditionalMethods) ENABLED START -----*/

//	Additional Methods

/*----- PROTECTED REGION END -----*/	//	PowerPMAC_Motor::PowerPMAC_MotorStateAllowed.AdditionalMethods

}	//	End of namespace
