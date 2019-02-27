//
// Created by urbschaj on 23.01.19.
//

#ifndef POWERPMAC_COMMANDBUILDER_H
#define POWERPMAC_COMMANDBUILDER_H

#include "pmac/defines.h"
#include <vector>
#include <string>

// Motor[{}].PosUnit for the type of motor unit

namespace ppmac::cmd {

	///////////////////////////////////////////////////////////////
	// motor commands

	std::string MotorJogToPosition(MotorID motor, double pos);
	std::string MotorPhase(MotorID motor);
	std::string MotorAbort(MotorID motor);
	std::string MotorKill(MotorID motor);
	std::string MotorZeroPosition(MotorID motor);
	std::string MotorHome(MotorID motor);
	std::string MotorReset(MotorID motor);
	std::string MotorSetConversion(MotorID motor, double value);
	std::string MotorSetHardLimits(MotorID motor, std::string value);
	std::string MotorGetHardLimitAddr(MotorID motor);
	std::string MotorSetJogAcceleration(MotorID motor, double value);
	std::string MotorGetJogAcceleration(MotorID motor);
	std::string MotorSetJogSpeed(MotorID motor, double value);
	std::string MotorGetJogSpeed(MotorID motor) ;
	std::string MotorSetJogAndMaxSpeed(MotorID motor, double value);
	std::string MotorSetSoftlimitPlus(MotorID motor, double value);
	std::string MotorSetSoftlimitMinus(MotorID motor, double value);
	std::string MotorGetSoftlimitPlus(MotorID motor);
	std::string MotorGetSoftlimitMinus(MotorID motor);
	std::string MotorSetHomeOffset(MotorID motor, double value) ;
	std::string MotorGetHomeOffset(MotorID motor);
	std::string MotorSetMaxVelocity(MotorID motor, double value);
	std::string MotorSetServoControl(MotorID motor, bool enable);
	std::string MotorGetServoControl(MotorID motor);

	///////////////////////////////////////////////////////////////
	// port commands

	// addresses are predefined on the power pmac in the tango.pch file. this allows easy
	// access to the register values as the actual value resides in the upper 16 bit
	std::string WritePortAddress(const std::string& address, int32_t value);
	std::string ReadPortAddress(const std::string& address);
	// access by name is more complicated and should only be used if no address name exists.
	// to set the actual gate value we neet to write the upper 16 bits, this means the number must be
	// shifted. same is true for port reading by name but we need to shift down.
	std::string WritePortByName(const std::string& name, int32_t value);
	std::string ReadPortByName(const std::string& name);


	///////////////////////////////////////////////////////////////
	// global commands

	std::string GlobalResetBrickLVAmp();
	std::string GlobalReboot();
	// resets and default initializes all structures
	std::string GlobalResetAndReinitialize();
	// resets and reloads the configuration
	std::string GlobalReset();
	std::string GlobalSetAbortAll(bool abort);

	///////////////////////////////////////////////////////////////
	// plc commands

	std::string GetPlcActive(int32_t plcIndex);
	std::string GetPlcRunning(int32_t plcIndex);
	std::string SetPLCActice(int32_t plcIndex);
	std::string SetPLCDeactive(int32_t plcIndex);
	std::string SetPlcRunning(int32_t plcIndex);
	std::string SetPlcPause(int32_t plcIndex);

	///////////////////////////////////////////////////////////////
	// coord commands

	std::string CoordMoveAxis(CoordID coord, const std::string& axis, double pos);
	std::string CoordMoveAxisLinear(CoordID coord, const std::string& axis, double pos, int32_t ta, int32_t ts, int32_t f);
	std::string CoordGetPositions(CoordID  coord, const std::string& axis);
	std::string CoordAbortMove(CoordID  coord);
	std::string CoordRunProgram(CoordID  coord, const std::string& prg);
	std::string CoordGetAxisCount(CoordID  coord);
	std::string SetAxisTransformMatrice(CoordID  coord, int32_t transformMatrice);

	///////////////////////////////////////////////////////////////
	// compensation table setup

	std::string SetCompensationTable(CompensationTableID table, MotorID source, MotorID target, double from, double to, const std::vector<double>& values);
}

#endif //POWERPMAC_COMMANDBUILDER_H
