#include <catch2/catch.hpp>

#include <map/door.h>

using adventure::Door;

TEST_CASE("Door constructor") {
  SECTION("Successful") {
    REQUIRE_NOTHROW(Door("RIGHT", "SKLKE", false));
  }

  SECTION("Direction not specified") {
    REQUIRE_THROWS_AS(Door("", "SKLKE", false), std::invalid_argument);
  }

  SECTION("Adjacent room specified") {
    REQUIRE_THROWS_AS(Door("RIGHT", "", false), std::invalid_argument);
  }

  SECTION("Adjacent room too long") {
    REQUIRE_THROWS_AS(Door("RIGHT", "SKLTKE", false), std::invalid_argument);
  }
}