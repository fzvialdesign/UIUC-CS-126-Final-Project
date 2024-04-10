// Copyright (c) 2021 Francesco Vial. All rights reserved.

#include <catch2/catch.hpp>

#include <map/room.h>

using adventure::Enemy;

using adventure::Weapon;

using adventure::Door;
using adventure::Room;

TEST_CASE("Room constructor") {
  std::vector<Door> doors = {Door("RIGHT", "SKLKE", false)};
  std::vector<Enemy> enemies = {Enemy("SKELETON", "SKLTN", 5, 5, 5)};
  std::vector<Weapon> weapons = {Weapon("SWORD", "SWORD", 5, 5)};

  SECTION("Successful") {
    REQUIRE_NOTHROW(Room("ENTRANCE", "ENTRN", doors, enemies, weapons, 5));
  }

  SECTION("No doors edge case") {
    REQUIRE_NOTHROW(Room("ENTRANCE", "ENTRN", std::vector<Door>(), enemies,
                         weapons, 5));
  }

  SECTION("No enemies edge case") {
    REQUIRE_NOTHROW(Room("ENTRANCE", "ENTRN", doors, std::vector<Enemy>(),
                         weapons, 5));
  }

  SECTION("No weapons edge case") {
    REQUIRE_NOTHROW(Room("ENTRANCE", "ENTRN", doors, enemies,
                         std::vector<Weapon>(), 5));
  }

  SECTION("No keys edge case") {
    REQUIRE_NOTHROW(Room("ENTRANCE", "ENTRN", doors, enemies, weapons, 0));
  }

  SECTION("Name not specified") {
    REQUIRE_THROWS_AS(Room("", "ENTRN", doors, enemies, weapons, 5),
                      std::invalid_argument);
  }

  SECTION("Nickname not specified") {
    REQUIRE_THROWS_AS(Room("ENTRANCE", "", doors, enemies, weapons, 5),
                      std::invalid_argument);
  }

  SECTION("Nickname too long") {
    REQUIRE_THROWS_AS(Room("ENTRANCE", "ENTRNC", doors, enemies, weapons, 5),
                      std::invalid_argument);
  }
}

TEST_CASE("Room change keys") {
  std::vector<Door> doors = {Door("RIGHT", "SKLKE", false)};
  std::vector<Enemy> enemies = {Enemy("SKELETON", "SKLTN", 5, 5, 5)};
  std::vector<Weapon> weapons = {Weapon("SWORD", "SWORD", 5, 5)};

  Room room("ENTRANCE", "ENTRN", doors, enemies, weapons, 0);

  SECTION("Decrement and increment (no cap)") {
    room.IncrementNumberOfKeys();

    REQUIRE(room.GetNumberOfKeys() == 1);

    room.DecrementNumberOfKeys();

    REQUIRE(room.GetNumberOfKeys() == 0);
  }

  SECTION("Decrement (cap)") {
    room.DecrementNumberOfKeys();

    REQUIRE(room.GetNumberOfKeys() == 0);
  }
}

TEST_CASE("Room add to weapons") {
  std::vector<Door> doors = {Door("RIGHT", "SKLKE", false)};
  std::vector<Enemy> enemies = {Enemy("SKELETON", "SKLTN", 5, 5, 5)};
  std::vector<Weapon> weapons = {Weapon("SWORD", "SWORD", 5, 5)};


  Room room("ENTRANCE", "ENTRN", doors, enemies, weapons, 5);

  SECTION("Successful") {
    room.AddWeapon(Weapon("BOW", "BOW", 5, 5));
    
    REQUIRE(room.GetWeapons().size() == 2);
  }

  SECTION("Weapon already in room") {
    REQUIRE_THROWS_AS(room.AddWeapon(Weapon("SWORD", "SWORD", 5, 5)),
                      std::invalid_argument);
    REQUIRE(room.GetWeapons().size() == 1);
  }
}

TEST_CASE("Room remove from weapons") {
  std::vector<Door> doors = {Door("RIGHT", "SKLKE", false)};
  std::vector<Enemy> enemies = {Enemy("SKELETON", "SKLTN", 5, 5, 5)};
  std::vector<Weapon> weapons = {Weapon("SWORD", "SWORD", 5, 5)};


  Room room("ENTRANCE", "ENTRN", doors, enemies, weapons, 5);

  SECTION("Successful") {
    room.RemoveWeapon(Weapon("SWORD", "SWORD", 5, 5));
    
    REQUIRE(room.GetWeapons().empty());
  }

  SECTION("Weapons empty") {
    room.RemoveWeapon(Weapon("SWORD", "SWORD", 5, 5));
    
    REQUIRE_THROWS_AS(room.RemoveWeapon(Weapon("SWORD", "SWORD", 5, 5)),
                      std::invalid_argument);
    REQUIRE(room.GetWeapons().empty());
  }

  SECTION("Weapons not found") {
    REQUIRE_THROWS_AS(room.RemoveWeapon(Weapon("BOW", "BOW", 5, 5)),
                      std::invalid_argument);
    REQUIRE(room.GetWeapons().size() == 1);
  }
}

TEST_CASE("Room remove from enemies") {
  std::vector<Door> doors = {Door("RIGHT", "SKLKE", false)};
  std::vector<Enemy> enemies = {Enemy("SKELETON", "SKLTN", 5, 5, 5)};
  std::vector<Weapon> weapons = {Weapon("SWORD", "SWORD", 5, 5)};


  Room room("ENTRANCE", "ENTRN", doors, enemies, weapons, 5);

  SECTION("Successful") {
    room.RemoveEnemy(Enemy("SKELETON", "SKLTN", 5, 5, 5));

    REQUIRE(room.GetEnemies().empty());
  }

  SECTION("Enemies empty") {
    room.RemoveEnemy(Enemy("SKELETON", "SKLTN", 5, 5, 5));

    REQUIRE_THROWS_AS(room.RemoveEnemy(Enemy("SKELETON", "SKLTN", 5, 5, 5)),
                      std::invalid_argument);
    REQUIRE(room.GetEnemies().empty());
  }

  SECTION("Enemy not found") {
    REQUIRE_THROWS_AS(room.RemoveEnemy(Enemy("BAT", "BAT", 5, 5, 5)),
                      std::invalid_argument);
    REQUIRE(room.GetEnemies().size() == 1);
  }
}

TEST_CASE("Room retrieve weapon") {
  std::vector<Door> doors = {Door("RIGHT", "SKLKE", false)};
  std::vector<Enemy> enemies = {Enemy("SKELETON", "SKLTN", 5, 5, 5)};
  std::vector<Weapon> weapons = {Weapon("SWORD", "SWORD", 5, 5)};


  Room room("ENTRANCE", "ENTRN", doors, enemies, weapons, 5);

  SECTION("Successful") {
    REQUIRE(room.RetrieveWeapon("SWORD").GetName() == weapons.front().GetName());
  }

  SECTION("Weapon name not specified") {
    REQUIRE_THROWS_AS(room.RetrieveWeapon(""), std::invalid_argument);
  }

  SECTION("Weapon not found") {
    REQUIRE_THROWS_AS(room.RetrieveWeapon("BOW"), std::invalid_argument);
  }
}

TEST_CASE("Room retrieve door") {
  std::vector<Door> doors = {Door("RIGHT", "SKLKE", false)};
  std::vector<Enemy> enemies = {Enemy("SKELETON", "SKLTN", 5, 5, 5)};
  std::vector<Weapon> weapons = {Weapon("SWORD", "SWORD", 5, 5)};


  Room room("ENTRANCE", "ENTRN", doors, enemies, weapons, 5);

  SECTION("Successful") {
    REQUIRE(room.RetrieveDoor("RIGHT").GetAdjacentRoom() ==
            doors.front().GetAdjacentRoom());
  }

  SECTION("Direction direction not specified") {
    REQUIRE_THROWS_AS(room.RetrieveDoor(""), std::invalid_argument);
  }

  SECTION("Door not found") {
    REQUIRE_THROWS_AS(room.RetrieveDoor("LEFT"), std::invalid_argument);
  }
}

TEST_CASE("Room retrieve enemy") {
  std::vector<Door> doors = {Door("RIGHT", "SKLKE", false)};
  std::vector<Enemy> enemies = {Enemy("SKELETON", "SKLTN", 5, 5, 5)};
  std::vector<Weapon> weapons = {Weapon("SWORD", "SWORD", 5, 5)};


  Room room("ENTRANCE", "ENTRN", doors, enemies, weapons, 5);

  SECTION("Successful") {
    REQUIRE(room.RetrieveWeapon("SWORD").GetName() == weapons.front().GetName());
  }

  SECTION("Enemy name not specified") {
    REQUIRE_THROWS_AS(room.RetrieveWeapon(""), std::invalid_argument);
  }

  SECTION("Enemy not found") {
    REQUIRE_THROWS_AS(room.RetrieveWeapon("BOW"), std::invalid_argument);
  }
}