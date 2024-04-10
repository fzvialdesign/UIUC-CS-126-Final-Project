// Copyright (c) 2021 Francesco Vial. All rights reserved.

#include <catch2/catch.hpp>

#include <items/weapon.h>

using adventure::Weapon;

TEST_CASE("Weapon constructor") {
  SECTION("Successful") {
    REQUIRE_NOTHROW(Weapon("SWORD", "SWORD", 5, 5));
  }

  SECTION("Name not specified") {
    REQUIRE_THROWS_AS(Weapon("", "SWORD", 5, 5), std::invalid_argument);
  }

  SECTION("Nickname not specified") {
    REQUIRE_THROWS_AS(Weapon("SWORD", "", 5, 5), std::invalid_argument);
  }

  SECTION("Nickname longer than five characters") {
    REQUIRE_THROWS_AS(Weapon("SWORD", "SWORDS", 5, 5), std::invalid_argument);
  }

  SECTION("Strength equals zero") {
    REQUIRE_THROWS_AS(Weapon("SWORD", "SWORD", 0, 5), std::invalid_argument);
  }
}

TEST_CASE("Weapon calculate damage") {
  SECTION("No critical hit") {
    Weapon weapon("SWORD", "SWORD", 5, 0);

    REQUIRE(weapon.CalculateDamage() == weapon.GetStrength());
  }

  SECTION("Critical hit") {
    Weapon weapon("SWORD", "SWORD", 5, 100);

    REQUIRE(weapon.CalculateDamage() == (2 * weapon.GetStrength()));
  }
}