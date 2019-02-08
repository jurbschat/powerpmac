//
// Created by urbschaj on 23.01.19.
//

#ifndef POWERPMAC_COMMANDBUILDER_H
#define POWERPMAC_COMMANDBUILDER_H

#include <fmt/format.h>

// Motor[{}].PosUnit for the type of motor unit

namespace ppmac::cmd {

	///////////////////////////////////////////////////////////////
	// motor commands

	inline std::string MotorJogToPosition(MotorID motor, double pos)
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

	inline std::string MotorSetConversion(MotorID motor, double value)
	{
		return fmt::format("Motor[{}].PosSf={}", static_cast<int>(motor), value);
	}

	inline std::string MotorSetHardLimits(MotorID motor, std::string value)
	{
		return fmt::format("Motor[{}].plimits={}", static_cast<int>(motor), value);
	}

	inline std::string MotorGetHardLimitAddr(MotorID motor)
	{
		return fmt::format("Motor[{}].plimits", static_cast<int>(motor));
	}

	inline std::string MotorSetJogAcceleration(MotorID motor, double value)
	{
		return fmt::format("Motor[{}].JogTa={}", static_cast<int>(motor), value);
	}

	inline std::string MotorGetJogAcceleration(MotorID motor)
	{
		return fmt::format("Motor[{}].JogTa", static_cast<int>(motor));
	}

	inline std::string MotorSetJogSpeed(MotorID motor, double value)
	{
		return fmt::format("Motor[{}].JogSpeed={}", static_cast<int>(motor), value);
	}

	inline std::string MotorGetJogSpeed(MotorID motor)
	{
		return fmt::format("Motor[{}].JogSpeed", static_cast<int>(motor));
	}

	inline std::string MotorSetJogAndMaxSpeed(MotorID motor, double value)
	{
		return fmt::format("Motor[{0}].JogSpeed={1};Motor[{0}].MaxSpeed={1}", static_cast<int>(motor), value);
	}

	inline std::string MotorSetSoftlimitPlus(MotorID motor, double value)
	{
		return fmt::format("Motor[{}].MaxPos={}", static_cast<int>(motor), value);
	}

	inline std::string MotorSetSoftlimitMinus(MotorID motor, double value)
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

	inline std::string MotorSetHomeOffset(MotorID motor, double value)
	{
		return fmt::format("Motor[{}].HomeOffset={}", static_cast<int>(motor), value);
	}

	inline std::string MotorGetHomeOffset(MotorID motor)
	{
		return fmt::format("Motor[{}].HomeOffset", static_cast<int>(motor));
	}

	inline std::string MotorSetMaxVelocity(MotorID motor, double value)
	{
		return fmt::format("Motor[{}].MaxSpeed={}", static_cast<int>(motor), value);
	}

	///////////////////////////////////////////////////////////////
	// port commands

	// addresses are predefined on the power pmac in the tango.pch file. this allows easy
	// access to the register values as the actual value resides in the upper 16 bit
	inline std::string WritePortAddress(const std::string& address, int32_t value)
	{
		return fmt::format("{}={}", address, value);
	}

	inline std::string ReadPortAddress(const std::string& address)
	{
		return fmt::format("{}", address);
	}

	// access by name is more complicated and should only be used if no address name exists.
	// to set the actual gate value we neet to write the upper 16 bits, this means the number must be
	// shifted. same is true for port reading by name but we need to shift down.
	inline std::string WritePortByName(const std::string& name, int32_t value)
	{
		return fmt::format("{}={}", name, value);
	}

	inline std::string ReadPortByName(const std::string& name)
	{
		return fmt::format("{}", name);
	}


	///////////////////////////////////////////////////////////////
	// global commands

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

	inline std::string GlobalSetAbortAll(bool abort)
	{
		return fmt::format("Sys.AbortAll={}", static_cast<int>(abort));
	}
}

#endif //POWERPMAC_COMMANDBUILDER_H
