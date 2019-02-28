//
// Created by urbschaj on 22.02.19.
//
#include "commandbuilder.h"
#include <fmt/format.h>
#include <fmt/ranges.h>

namespace ppmac::cmd {

	std::string MotorJogToPosition(MotorID motor, double pos) {
		return fmt::format("#{}j={}", static_cast<int>(motor), pos);
	}

	std::string MotorPhase(MotorID motor) {
		return fmt::format("#{}$", static_cast<int>(motor));
	}

	std::string MotorAbort(MotorID motor) {
		return fmt::format("#{}a", static_cast<int>(motor));
	}

	std::string MotorKill(MotorID motor) {
		return fmt::format("#{}k", static_cast<int>(motor));
	}

	std::string MotorZeroPosition(MotorID motor) {
		return fmt::format("#{}hmz", static_cast<int>(motor));
	}

	std::string MotorHome(MotorID motor) {
		return fmt::format("#{}hm", static_cast<int>(motor));
	}

	std::string MotorReset(MotorID motor) {
		return fmt::format("#{}j/", static_cast<int>(motor));
	}

	std::string MotorSetConversion(MotorID motor, double value) {
		return fmt::format("Motor[{}].PosSf={}", static_cast<int>(motor), value);
	}

	std::string MotorSetHardLimits(MotorID motor, std::string value) {
		return fmt::format("Motor[{}].plimits={}", static_cast<int>(motor), value);
	}

	std::string MotorGetHardLimitAddr(MotorID motor) {
		return fmt::format("Motor[{}].plimits", static_cast<int>(motor));
	}

	std::string MotorSetJogAcceleration(MotorID motor, double value) {
		return fmt::format("Motor[{}].JogTa={}", static_cast<int>(motor), value);
	}

	std::string MotorGetJogAcceleration(MotorID motor) {
		return fmt::format("Motor[{}].JogTa", static_cast<int>(motor));
	}

	std::string MotorSetJogSpeed(MotorID motor, double value) {
		return fmt::format("Motor[{}].JogSpeed={}", static_cast<int>(motor), value);
	}

	std::string MotorGetJogSpeed(MotorID motor) {
		return fmt::format("Motor[{}].JogSpeed", static_cast<int>(motor));
	}

	std::string MotorSetJogAndMaxSpeed(MotorID motor, double value) {
		return fmt::format("Motor[{0}].JogSpeed={1};Motor[{0}].MaxSpeed={1}", static_cast<int>(motor), value);
	}

	std::string MotorSetSoftlimitPlus(MotorID motor, double value) {
		return fmt::format("Motor[{}].MaxPos={}", static_cast<int>(motor), value);
	}

	std::string MotorSetSoftlimitMinus(MotorID motor, double value) {
		return fmt::format("Motor[{}].MinPos={}", static_cast<int>(motor), value);
	}

	std::string MotorGetSoftlimitPlus(MotorID motor) {
		return fmt::format("Motor[{}].MaxPos", static_cast<int>(motor));
	}

	std::string MotorGetSoftlimitMinus(MotorID motor) {
		return fmt::format("Motor[{}].MinPos", static_cast<int>(motor));
	}

	std::string MotorSetHomeOffset(MotorID motor, double value) {
		return fmt::format("Motor[{}].HomeOffset={}", static_cast<int>(motor), value);
	}

	std::string MotorGetHomeOffset(MotorID motor) {
		return fmt::format("Motor[{}].HomeOffset", static_cast<int>(motor));
	}

	std::string MotorSetMaxVelocity(MotorID motor, double value) {
		return fmt::format("Motor[{}].MaxSpeed={}", static_cast<int>(motor), value);
	}

	std::string MotorSetServoControl(MotorID motor, bool enable) {
		return fmt::format("Motor[{}].ServoCtrl={}", static_cast<int>(motor), static_cast<int>(enable));
	}
	std::string MotorGetServoControl(MotorID motor) {
		return fmt::format("Motor[{}].ServoCtrl", static_cast<int>(motor));
	}

	namespace detail {
		std::string MotorGetCoordAxisDefinition(int32_t motorIndex) {
			return fmt::format("&0#{}->", motorIndex);
		}
	}

	///////////////////////////////////////////////////////////////
	// port commands

	// addresses are predefined on the power pmac in the tango.pch file. this allows easy
	// access to the register values as the actual value resides in the upper 16 bit
	std::string WritePortAddress(const std::string& address, int32_t value) {
		return fmt::format("{}={}", address, value);
	}

	std::string ReadPortAddress(const std::string& address) {
		return fmt::format("{}", address);
	}

	// access by name is more complicated and should only be used if no address name exists.
	// to set the actual gate value we neet to write the upper 16 bits, this means the number must be
	// shifted. same is true for port reading by name but we need to shift down.
	std::string WritePortByName(const std::string& name, int32_t value) {
		return fmt::format("{}={}", name, value);
	}

	std::string ReadPortByName(const std::string& name) {
		return fmt::format("{}", name);
	}


	///////////////////////////////////////////////////////////////
	// global commands

	std::string GlobalResetBrickLVAmp() {
		return fmt::format("BrickLV.Reset=1");
	}

	std::string GlobalGetAmpChannelState(int32_t channel) {
		return fmt::format("BrickLV.Chan[{}].OverCurrent", channel);
	}

	std::string GlobalReboot() {
		return fmt::format("reboot");
	}

	// resets and default initializes all structures
	std::string GlobalResetAndReinitialize() {
		return fmt::format("$$$***");
	}

	// resets and reloads the configuration
	std::string GlobalReset() {
		return fmt::format("$$$");
	}

	std::string GlobalSetAbortAll(bool abort) {
		return fmt::format("Sys.AbortAll={}", static_cast<int>(abort));
	}

	///////////////////////////////////////////////////////////////
	// plc commands

	std::string GetPlcActive(int32_t plcIndex) {
		return fmt::format("Plc[{}].Active", (plcIndex));
	}

	std::string GetPlcRunning(int32_t plcIndex) {
		return fmt::format("Plc[{}].Running", (plcIndex));
	}

	std::string SetPLCActice(int32_t plcIndex) {
		return fmt::format("enable plc {}", (plcIndex));
	}

	std::string SetPLCDeactive(int32_t plcIndex) {
		return fmt::format("disable plc {}", (plcIndex));
	}

	std::string SetPlcRunning(int32_t plcIndex) {
		return fmt::format("resume plc {}", (plcIndex));
	}

	std::string SetPlcPause(int32_t plcIndex) {
		return fmt::format("pause plc {}", (plcIndex));
	}

	///////////////////////////////////////////////////////////////
	// coord commands

	std::string CoordMoveAxis(CoordID coord, const std::string& axis, double pos) {
		return fmt::format("&{} pcx {}{}", static_cast<int>(coord), axis, pos);
	}

	std::string CoordMoveAxisLinear(CoordID coord, const std::string& axis, double pos, int32_t ta, int32_t ts, int32_t f) {
		return fmt::format("&{} pcx linear ta{} ts{} f{} {}{}", static_cast<int>(coord), ta, ts, f, axis, pos);
	}

	std::string CoordGetPositions(CoordID  coord, const std::string& axis) {
		return fmt::format("&{}p", static_cast<int>(coord), axis);
	}

	std::string CoordAbortMove(CoordID  coord) {
		return fmt::format("&{}a", static_cast<int>(coord));
	}

	std::string CoordRunProgram(CoordID  coord, const std::string& prg) {
		return fmt::format("&{}; start {}", static_cast<int>(coord), prg);
	}

	std::string CoordGetAxisCount(CoordID  coord) {
		return fmt::format("Coord[{}].NumMotors", static_cast<int>(coord));
	}

	std::string SetAxisTransformMatrice(CoordID  coord, int32_t transformMatrice) {
		return fmt::format("&{} tsel {}", static_cast<int>(coord), transformMatrice);
	}

	///////////////////////////////////////////////////////////////
	// compensation table setup

	std::string SetCompensationTable(CompensationTableID table,
	                                        MotorID source,
	                                        MotorID target,
	                                        double from,
	                                        double to,
	                                        const std::vector<double>& values) {
		const char* templ = R"(CompTable[{table}].Source[0] = {source};
CompTable[{table}].Nx[0] = {valueCount};
CompTable[{table}].Nx[1] = 0 ;
CompTable[{table}].Nx[2] = 0;
CompTable[{table}].X0[0] = {from};
CompTable[{table}].Dx[0] = {dist};
CompTable[{table}].Target[0] = Motor[{target}].CompPos.a;
CompTable[{table}].Target[1] = Motor[{target}].CompPos2.a;
CompTable[{table}].Sf[0] = 1;
CompTable[{table}].Sf[0] = 1;
CompTable[{table}].Ctrl = 7 ;
CompTable[{table}].OutCtrl = 0;
CompTable[{table}].Data[0] = {values};)";
		fmt::memory_buffer valStrBuff;
		for(size_t i = 0; i < values.size(); i++) {
			fmt::format_to(valStrBuff, "{}{}", (i != 0 ? "," : ""), values[i]);
		}
		return fmt::format(templ,
				fmt::arg("valueCount", values.size()),
				fmt::arg("table", static_cast<int>(table)),
				fmt::arg("source", static_cast<int>(source)),
				fmt::arg("target", static_cast<int>(target)),
				fmt::arg("from", from),
				fmt::arg("dist", to - from),
				fmt::arg("values", fmt::to_string(valStrBuff))
		);
	}

}

