//
// Created by urbschaj on 28.01.19.
//

#include <catch2/catch.hpp>

#include "commandbuilder.h"



TEST_CASE( "Basic Commandbuilder", "command" )
{
	auto range_0_8 = ppmac::cmd::detail::MakePrefixPostfixRangeCommand("#", "p", ppmac::MotorID::Motor0, ppmac::MotorID::Motor8);
	auto range_0_1 = ppmac::cmd::detail::MakePrefixPostfixRangeCommand("#", "p", ppmac::MotorID::Motor0, ppmac::MotorID::Motor1);
	auto range_0_0 = ppmac::cmd::detail::MakePrefixPostfixRangeCommand("#", "p", ppmac::MotorID::Motor0, ppmac::MotorID::Motor0); // valid, one element

	REQUIRE( fmt::to_string(range_0_8) == "#0,1,2,3,4,5,6,7,8p");
	REQUIRE( fmt::to_string(range_0_1) == "#0,1p");
	REQUIRE( fmt::to_string(range_0_0) == "#0p");

	CHECK_THROWS(ppmac::cmd::detail::MakePrefixPostfixRangeCommand("#", "p", ppmac::MotorID::Motor3, ppmac::MotorID::Motor1) );

	auto list_0_3_4 = ppmac::cmd::detail::MakePrefixPostfixCommand("#", "vp", ppmac::MotorID::Motor0, ppmac::MotorID::Motor3, ppmac::MotorID::Motor4);
	REQUIRE( fmt::to_string(list_0_3_4) == "#0,3,4vp");

	CHECK_THROWS(ppmac::cmd::detail::MakePrefixPostfixCommand("#", "vp", ppmac::MotorID::Motor3, ppmac::MotorID::Motor1) );
}
