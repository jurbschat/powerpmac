//
// Created by urbschaj on 23.01.19.
//

#ifndef POWERPMAC_COMMANDBUILDER_H
#define POWERPMAC_COMMANDBUILDER_H

#include "pmac/defines.h"
#include "pmac/datastructures.h"
#include <vector>
#include <string>

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
	namespace detail {
		std::string MotorGetCoordAxisDefinition(int32_t motorIndex);
		std::string MotorGetUnit(int32_t motorIndex);
	}
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
	std::string GlobalGetAmpChannelOverCurrent(int32_t channel);
	std::string GlobalGetAmpChannelOverLoad(int32_t channel);
	std::string GlobalReboot();
	// resets and default initializes all structures
	std::string GlobalResetAndReinitialize();
	// resets and reloads the configuration
	std::string GlobalReset();
	std::string GlobalSetAbortAll(bool abort);
	std::string GlobalSetBrickLVMonitoring(bool mode);  // these commands can return multiple non delemited/multi delemited lines and should be used via consume
	std::string GlobalGetBrickLVMonitoring();
	std::string GlobalGetActiveCompensationTableCount();
	std::string GlobalSetActiveCompensationTableCount(int32_t activeTables);

	///////////////////////////////////////////////////////////////
	// plc commands

	std::string GetPlcActive(PlcID plcIndex);
	std::string GetPlcRunning(PlcID plcIndex);
	std::string SetPLCActice(PlcID plcIndex);
	std::string SetPLCDeactive(PlcID plcIndex);
	std::string SetPlcRunning(PlcID plcIndex);
	std::string SetPlcPause(PlcID plcIndex);

	///////////////////////////////////////////////////////////////
	// coord commands

	std::string CoordMoveAxis(CoordID coord, const std::string& axis, double pos);
	std::string CoordMoveAxisLinear(CoordID coord, const std::string& axis, double pos, int32_t ta, int32_t ts, int32_t f);
	std::string CoordGetPositions(CoordID  coord, const std::string& axis);
	std::string CoordAbortMove(CoordID  coord);
	std::string CoordRunProgram(CoordID  coord, const std::string& prg);
	std::string CoordGetAxisCount(CoordID  coord);
	std::string CoordSetAxisTransformMatrix(CoordID coord, int32_t transformMatrice);
	std::string CoordMultiAxisMove(CoordID coord, const std::vector<MultiAxisMoveInfo>& info);

	///////////////////////////////////////////////////////////////
	// compensation table setup

	std::string CompensationTableGetSource(CompensationTableID table);
	std::string CompensationTableSetSource(CompensationTableID table, int32_t source);
	std::string CompensationTableGetTarget(CompensationTableID table);
	std::string CompensationTableSetTarget(CompensationTableID table, int32_t target);
	std::string CompensationTableResetTarget(CompensationTableID table);
	std::string CompensationTableGetStartX(CompensationTableID table);
	std::string CompensationTableSetStartX(CompensationTableID table, int32_t startx);
	std::string CompensationTableGetDeltaX(CompensationTableID table);
	std::string CompensationTableSetDeltaX(CompensationTableID table, int32_t deltax);
	std::string CompensationTableGetDataEntry(CompensationTableID table, int32_t idx);
	std::string CompensationTableSetDataEntry(CompensationTableID table, int32_t idx, double val);
	std::string CompensationTableSetAll(CompensationTableID table, MotorID source, MotorID target, double from, double to, const std::vector<double>& values);
	std::string CompensationTableSetData(CompensationTableID table, const std::vector<double>& values);
}

#endif //POWERPMAC_COMMANDBUILDER_H
