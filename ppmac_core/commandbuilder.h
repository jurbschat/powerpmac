//
// Created by urbschaj on 23.01.19.
//

#ifndef POWERPMAC_COMMANDBUILDER_H
#define POWERPMAC_COMMANDBUILDER_H

#include <fmt/format.h>

namespace ppmac::cmd {
	// Motor[{}].PosUnit for the type of motor unit

	inline std::string MotorJogToPosition(float pos, MotorID::TYPE motor)
	{
		return fmt::format("#{}j={}", static_cast<int>(motor), pos);
	}

	inline std::string MotorPhase(MotorID::TYPE motor)
	{
		return fmt::format("#{}$", static_cast<int>(motor));
	}

	inline std::string MotorSetConversion(float value, MotorID::TYPE motor)
	{
		return fmt::format("Motor[{}].PosSf={}", static_cast<int>(motor), value);
	}

	inline std::string MotorSetHardLimits(float value, MotorID::TYPE motor)
	{
		return fmt::format("Motor[{}].plimits={}", static_cast<int>(motor), value);
	}

	inline std::string MotorSetJogAcceleration(float value, MotorID::TYPE motor)
	{
		return fmt::format("Motor[{}].JogTa={}", static_cast<int>(motor), value);
	}

	inline std::string MotorSetJogSpeed(float value, MotorID::TYPE motor)
	{
		return fmt::format("Motor[{}].JogSpeed={}", static_cast<int>(motor), value);
	}

	inline std::string MotorSetSoftlimitPlus(float value, MotorID::TYPE motor)
	{
		return fmt::format("Motor[{}].SoftPlusLimit={}", static_cast<int>(motor), value);
	}

	inline std::string MotorSetSoftlimitMinus(float value, MotorID::TYPE motor)
	{
		return fmt::format("Motor[{}].SoftMinusLimit={}", static_cast<int>(motor), value);
	}

	inline std::string MotorGetSoftlimitPlus(MotorID::TYPE motor)
	{
		return fmt::format("Motor[{}].SoftPlusLimit", static_cast<int>(motor));
	}

	inline std::string MotorGetSoftlimitMinus(MotorID::TYPE motor)
	{
		return fmt::format("Motor[{}].MotorSetSoftlimitMinus", static_cast<int>(motor));
	}

	inline std::string MotorSetMaxVelocity(float value, MotorID::TYPE motor)
	{
		return fmt::format("Motor[{}].MaxSpeed={}", static_cast<int>(motor), value);
	}

	inline std::string MotorZeroPosition(MotorID::TYPE motor)
	{
		return fmt::format("#{}hmz", static_cast<int>(motor));
	}

	inline std::string MotorHome(MotorID::TYPE motor)
	{
		return fmt::format("#{}hm", static_cast<int>(motor));
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
