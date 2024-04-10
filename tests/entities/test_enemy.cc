// Copyright (c) 2021 Francesco Vial. All rights reserved.

#include <catch2/catch.hpp>

#include <entities/enemy.h>

using adventure::Enemy;

TEST_CASE("Enemy constructor") {
  SECTION("Successful") {
    REQUIRE_NOTHROW(Enemy("SKELETON", "SKLTN", 5, 5, 5));
  }

  SECTION("Name not specified") {
    REQUIRE_THROWS_AS(Enemy("", "SKLTN", 5, 5, 5),std::invalid_argument);
  }

  SECTION("Nickname not specified") {
    REQUIRE_THROWS_AS(Enemy("SKELETON", "", 5, 5, 5),std::invalid_argument);
  }

  SECTION("Nickname longer than five characters") {
    REQUIRE_THROWS_AS(Enemy("SKELETON", "SKLTON", 5, 5, 5),
                      std::invalid_argument);
  }

  SECTION("Health equals zero") {
    REQUIRE_THROWS_AS(Enemy("SKELETON", "SKLTN", 0, 5, 5),
                      std::invalid_argument);
  }

  SECTION("Strength equals zero") {
    REQUIRE_THROWS_AS(Enemy("SKELETON", "SKLTN", 5, 0, 5),
                      std::invalid_argument);
  }
}

TEST_CASE("Enemy take damage") {
  Enemy enemy("SKELETON", "SKLTN", 5, 5, 5);

  SECTION("No cap") {
    enemy.TakeDamage(4);

    REQUIRE(enemy.GetHealth() == 1);
    REQUIRE(enemy.IsAlive());
  }

  SECTION("Cap") {
    enemy.TakeDamage(6);

    REQUIRE(enemy.GetHealth() == 0);
    REQUIRE_FALSE(enemy.IsAlive());
  }
}

TEST_CASE("Enemy deal damage") {
  SECTION("No critical hit") {
    Enemy enemy("SKELETON", "SKLTN", 5, 5, 0);

    REQUIRE(enemy.DealDamage() == enemy.GetStrength());
  }

  SECTION("Critical hit") {
    Enemy enemy("SKELETON", "SKLTN", 5, 5, 100);

    REQUIRE(enemy.DealDamage() == (2 * enemy.GetStrength()));
  }
}