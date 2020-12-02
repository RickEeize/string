#define CATCH_CONFIG_MAIN
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "String.h"
#include "str_exception.h"
#include "catch.hpp"
TEST_CASE("exceptions") {
	string s = "12345";
	REQUIRE_THROWS_AS(s.substr(4, 12), str_exception);
	REQUIRE_THROWS_AS(s.find("abc"), str_exception);
	REQUIRE_THROWS_AS(s.insert(15, "abc"), str_exception);
}