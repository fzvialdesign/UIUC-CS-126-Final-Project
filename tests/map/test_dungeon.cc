// Copyright (c) 2021 Francesco Vial. All rights reserved.

#include <catch2/catch.hpp>

#include <map/dungeon.h>
#include <fstream>
#include <iostream>

using adventure::Enemy;

using adventure::Weapon;

using adventure::Door;
using adventure::Dungeon;
using adventure::Room;

TEST_CASE("Dungeon constructor") {
  SECTION("Successful") {
    Dungeon dungeon;

    REQUIRE(dungeon.GetMap().empty());
  }
}

TEST_CASE("Dungeon operator>> overload") {
  std::string filepath = "C:\\Users\\cesco\\OneDrive\\Documents\\School\\UIUC\\"
                         "2020-2021\\Spring 2021\\CS 126\\Cinder\\my-projects\\"
                         "final-project-fvial2\\resources\\test.txt";
  Dungeon dungeon;

  std::ifstream input_file(filepath);
  if (input_file.is_open()) {
    input_file >> dungeon;

    input_file.close();
  } else {
    std::cout << "File not found" << std::endl;
  }

  SECTION("Successful sanity check") {
    REQUIRE_FALSE(dungeon.GetMap().empty());
  }

  Room entrance("ENTRANCE", "ENTRN",
                std::vector<Door>({Door("UP", "SWORD", false),
                                   Door("DOWN", "BOW", false),
                                   Door("LEFT", "BAT", true),
                                   Door("RIGHT", "SKLTN", true)}),
                std::vector<Enemy>(),
                std::vector<Weapon>(),
                0);

  Room sword("SWORD", "SWORD",
              std::vector<Door>({Door("DOWN", "ENTRN", false)}),
              std::vector<Enemy>(),
              std::vector<Weapon>({Weapon("SWORD", "SWORD", 20, 5)}),
              1);

  Room bow("BOW", "BOW",
              std::vector<Door>({Door("UP", "ENTRN", false)}),
              std::vector<Enemy>({Enemy("BLOB", "BLOB", 30, 15, 10)}),
              std::vector<Weapon>({Weapon("BOW", "BOW", 10, 25)}),
              1);

  Room bat("BAT", "BAT",
              std::vector<Door>({Door("RIGHT", "ENTRN", false)}),
              std::vector<Enemy>({Enemy("BAT", "BAT", 5, 5, 65)}),
              std::vector<Weapon>(),
              0);

  Room skeleton("SKELETON", "SKLTN",
              std::vector<Door>({Door("LEFT", "ENTRN", false)}),
              std::vector<Enemy>({Enemy("SKELETON", "SKLTN", 60, 25, 15)}),
              std::vector<Weapon>(),
              0);

  std::vector<Room> expected({entrance, sword, bow, bat, skeleton});

  SECTION("Successful one-to-one") {
    for (size_t room = 0; room < dungeon.GetMap().size(); ++room) {
      Room map_room = dungeon.GetMap()[room];
      Room actual = expected[room];

      REQUIRE(map_room.GetName() == actual.GetName());
      REQUIRE(map_room.GetNickname() == actual.GetNickname());

      REQUIRE(map_room.GetDoors().empty() == actual.GetDoors().empty());
      for (size_t door = 0; door < map_room.GetDoors().size(); ++door) {
        Door room_door = map_room.GetDoors()[door];
        Door actual_door = actual.GetDoors()[door];

        REQUIRE(room_door.GetDirection() == actual_door.GetDirection());
        REQUIRE(room_door.GetAdjacentRoom() == actual_door.GetAdjacentRoom());
        REQUIRE(room_door.IsLocked() == actual_door.IsLocked());
      }

      REQUIRE(map_room.GetEnemies().empty() == actual.GetEnemies().empty());
      for (size_t enemy = 0; enemy < map_room.GetEnemies().size(); ++enemy) {
        Enemy room_enemy = map_room.GetEnemies()[enemy];
        Enemy actual_enemy = actual.GetEnemies()[enemy];

        REQUIRE(room_enemy.GetName() == actual_enemy.GetName());
        REQUIRE(room_enemy.GetNickname() == actual_enemy.GetNickname());
        REQUIRE(room_enemy.GetHealth() == actual_enemy.GetHealth());
        REQUIRE(room_enemy.GetStrength() == actual_enemy.GetStrength());
        REQUIRE(room_enemy.GetCriticalChance() ==
                actual_enemy.GetCriticalChance());
      }

      REQUIRE(map_room.GetWeapons().empty() == actual.GetWeapons().empty());
      for (size_t weapon = 0; weapon < map_room.GetWeapons().size(); ++weapon) {
        Weapon room_weapon = map_room.GetWeapons()[weapon];
        Weapon actual_weapon = actual.GetWeapons()[weapon];

        REQUIRE(room_weapon.GetName() == actual_weapon.GetName());
        REQUIRE(room_weapon.GetNickname() == actual_weapon.GetNickname());
        REQUIRE(room_weapon.GetStrength() == actual_weapon.GetStrength());
        REQUIRE(room_weapon.GetCriticalChance() ==
                actual_weapon.GetCriticalChance());
      }

      REQUIRE(map_room.GetNumberOfKeys() == actual.GetNumberOfKeys());
    }
  }
}