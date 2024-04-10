// Copyright (c) 2021 Francesco Vial. All rights reserved.

#include <catch2/catch.hpp>

#include <entities/player.h>

using adventure::Player;

using adventure::Weapon;

TEST_CASE("Player constructor") {
  std::vector<Weapon> valid_weapons{Weapon("SWORD", "SWORD", 5, 5)};

  SECTION("Successful") {
     REQUIRE_NOTHROW(Player("ENTRN", 100, 5, valid_weapons));
  }

  SECTION("Current location not specified") {
    REQUIRE_THROWS_AS(Player("", 100, 5, valid_weapons),std::invalid_argument);
  }

  SECTION("Health equals zero") {
    REQUIRE_THROWS_AS(Player("ENTRN", 0, 5, valid_weapons),std::invalid_argument);
  }
}

TEST_CASE("Player regenerate health") {
  std::vector<Weapon> valid_weapons{Weapon("SWORD", "SWORD", 5, 5)};
  Player player("ENTRN", 100, 5, valid_weapons);

  SECTION("No cap") {
    player.TakeDamage(10);
    player.RegenerateHealth();

    REQUIRE(player.GetHealth() == 95);
  }

  SECTION("Cap") {
    player.RegenerateHealth();

    REQUIRE(player.GetHealth() == 100);
  }
}

TEST_CASE("Player take damage") {
  std::vector<Weapon> valid_weapons{Weapon("SWORD", "SWORD", 5, 5)};
  Player player("ENTRN", 100, 5, valid_weapons);

  SECTION("No cap") {
    player.TakeDamage(5);

    REQUIRE(player.GetHealth() == 95);
    REQUIRE(player.IsAlive());
  }

  SECTION("Cap") {
    player.TakeDamage(110);

    REQUIRE(player.GetHealth() == 0);
    REQUIRE_FALSE(player.IsAlive());
  }
}

TEST_CASE("Player deal damage") {
  SECTION("No critical hit") {
    std::vector<Weapon> valid_weapons{Weapon("SWORD", "SWORD", 5, 0)};
    Player player("ENTRN", 100, 5, valid_weapons);

    REQUIRE(player.DealDamage() == valid_weapons.front().GetStrength());
  }

  SECTION("Critical hit") {
    std::vector<Weapon> valid_weapons{Weapon("SWORD", "SWORD", 5, 100)};
    Player player("ENTRN", 100, 5, valid_weapons);

    REQUIRE(player.DealDamage() == (2 * valid_weapons.front().GetStrength()));
  }
}

TEST_CASE("Player change keys") {
  std::vector<Weapon> valid_weapons{Weapon("SWORD", "SWORD", 5, 5)};
  Player player("ENTRN", 100, 0, valid_weapons);

  SECTION("Decrement and increment (no cap)") {
    player.IncrementNumberOfKeys();

    REQUIRE(player.GetNumberOfKeys() == 1);

    player.DecrementNumberOfKeys();

    REQUIRE(player.GetNumberOfKeys() == 0);
  }

  SECTION("Decrement (cap)") {
    player.DecrementNumberOfKeys();

    REQUIRE(player.GetNumberOfKeys() == 0);
  }
}

TEST_CASE("Player add to weapons") {
  std::vector<Weapon> valid_weapons{Weapon("SWORD", "SWORD", 5, 5)};
  Player player("ENTRN", 100, 5, valid_weapons);

  SECTION("Successful") {
    player.AddWeapon(Weapon("BOW", "BOW", 5, 5));

    REQUIRE(player.GetWeapons().size() == 2);
  }

  SECTION("Weapon already exists") {
    REQUIRE_THROWS_AS(player.AddWeapon(Weapon("SWORD", "SWORD", 5, 5)),
                      std::invalid_argument);
    REQUIRE(player.GetWeapons().size() == 1);
  }
}

TEST_CASE("Player remove from weapons") {
  std::vector<Weapon> valid_weapons{Weapon("SWORD", "SWORD", 5, 5)};
  Player player("ENTRN", 100, 5, valid_weapons);

  SECTION("Successful") {
    player.RemoveWeapon(Weapon("SWORD", "SWORD", 5, 5));

    REQUIRE(player.GetWeapons().empty());
  }

  SECTION("Weapons empty") {
    player.RemoveWeapon(Weapon("SWORD", "SWORD", 5, 5));

    REQUIRE_THROWS_AS(player.RemoveWeapon(Weapon("SWORD", "SWORD", 5, 5)),
                      std::invalid_argument);
    REQUIRE(player.GetWeapons().empty());
  }

  SECTION("Weapon not found") {
    REQUIRE_THROWS_AS(player.RemoveWeapon(Weapon("BOW", "BOW", 5, 5)),
                      std::invalid_argument);
    REQUIRE(player.GetWeapons().size() == 1);
  }
}