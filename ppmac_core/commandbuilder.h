//
// Created by urbschaj on 23.01.19.
//

#ifndef POWERPMAC_COMMANDBUILDER_H
#define POWERPMAC_COMMANDBUILDER_H

#include <fmt/format.h>

namespace ppmac::cmd {
	// Motor[{}].PosUnit for the type of motor unit

	inline std::string MotorJogToPosition(float pos, MotorID motor)
	{
		return fmt::format("#{}j={}", static_cast<int>(motor), pos);
	}

	inline std::string MotorPhase(MotorID motor)
	{
		return fmt::format("#{}$", static_cast<int>(motor));
	}

	inline std::string MotorAbort(MotorID motor)
	{
		return fmt::format("#{}a", static_cast<int>(motor));
	}

	inline std::string MotorKill(MotorID motor)
	{
		return fmt::format("#{}k", static_cast<int>(motor));
	}

	inline std::string MotorZeroPosition(MotorID motor)
	{
		return fmt::format("#{}hmz", static_cast<int>(motor));
	}

	inline std::string MotorHome(MotorID motor)
	{
		return fmt::format("#{}hm", static_cast<int>(motor));
	}

	inline std::string MotorSetConversion(float value, MotorID motor)
	{
		return fmt::format("Motor[{}].PosSf={}", static_cast<int>(motor), value);
	}

	inline std::string MotorSetHardLimits(std::string value, MotorID motor)
	{
		return fmt::format("Motor[{}].plimits={}", static_cast<int>(motor), value);
	}

	inline std::string MotorGetHardLimitAddr(MotorID motor)
	{
		return fmt::format("Motor[{}].plimits", static_cast<int>(motor));
	}

	inline std::string MotorSetJogAcceleration(float value, MotorID motor)
	{
		return fmt::format("Motor[{}].JogTa={}", static_cast<int>(motor), value);
	}

	inline std::string MotorGetJogAcceleration(MotorID motor)
	{
		return fmt::format("Motor[{}].JogTa", static_cast<int>(motor));
	}

	inline std::string MotorSetJogSpeed(float value, MotorID motor)
	{
		return fmt::format("Motor[{}].JogSpeed={}", static_cast<int>(motor), value);
	}

	inline std::string MotorGetJogSpeed(MotorID motor)
	{
		return fmt::format("Motor[{}].JogSpeed", static_cast<int>(motor));
	}

	inline std::string MotorSetSoftlimitPlus(float value, MotorID motor)
	{
		return fmt::format("Motor[{}].MaxPos={}", static_cast<int>(motor), value);
	}

	inline std::string MotorSetSoftlimitMinus(float value, MotorID motor)
	{
		return fmt::format("Motor[{}].MinPos={}", static_cast<int>(motor), value);
	}

	inline std::string MotorGetSoftlimitPlus(MotorID motor)
	{
		return fmt::format("Motor[{}].MaxPos", static_cast<int>(motor));
	}

	inline std::string MotorGetSoftlimitMinus(MotorID motor)
	{
		return fmt::format("Motor[{}].MinPos", static_cast<int>(motor));
	}

	inline std::string MotorSetMaxVelocity(float value, MotorID motor)
	{
		return fmt::format("Motor[{}].MaxSpeed={}", static_cast<int>(motor), value);
	}

	inline std::string GlobalResetBrickLVAmp()
	{
		return fmt::format("BrickLV.Reset=1");
	}

	inline std::string GlobalReboot()
	{
		return fmt::format("reboot");
	}

	// resets and default initializes all structures
	inline std::string GlobalResetAndReinitialize()
	{
		return fmt::format("$$$***");
	}

	// resets and reloads the configuration
	inline std::string GlobalReset()
	{
		return fmt::format("$$$");
	}

	inline std::string GlobalInfo()
	{
		return fmt::format("type; vers; cpu; Sys.CpuFreq; Sys.CpuTemp");
	}
}

#endif //POWERPMAC_COMMANDBUILDER_H
