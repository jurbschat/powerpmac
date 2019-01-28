#include <catch2/catch.hpp>

#define CATCH_CONFIG_MAIN

int theAnswer() { return 6*9; }

TEST_CASE( "Life, the universe and everything", "[42][theAnswer]" ) {
	REQUIRE( theAnswer() == 42 );
}