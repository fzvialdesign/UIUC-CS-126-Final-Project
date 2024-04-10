// Copyright (c) 2021 Francesco Vial. All rights reserved.

#include <catch2/catch.hpp>

#include <mechanics/engine.h>

using adventure::Enemy;
using adventure::Player;

using adventure::Weapon;

using adventure::Door;
using adventure::Dungeon;
using adventure::Room;

using adventure::Engine;

TEST_CASE("Engine constructor") {
  std::vector<Weapon> valid_weapons{Weapon("SPELL", "SPELL", 5, 5)};
  Player player("ENTRN", 100, 0, valid_weapons);

  SECTION("Successful") {
    std::string filepath = "C:\\Users\\cesco\\OneDrive\\Documents\\School\\"
                           "UIUC\\2020-2021\\Spring 2021\\CS 126\\Cinder\\"
                           "my-projects\\final-project-fvial2\\resources\\"
                           "test.txt";
    Dungeon dungeon;

    std::ifstream input_file(filepath);
    if (input_file.is_open()) {
      input_file >> dungeon;

      input_file.close();
    }

    REQUIRE_NOTHROW(Engine(player, dungeon));
  }

  SECTION("Dungeon map has no rooms") {
    REQUIRE_THROWS_AS(Engine(player, Dungeon()),std::invalid_argument);
  }
}

TEST_CASE("Engine go") {
  std::vector<Weapon> valid_weapons{Weapon("SPELL", "SPELL", 5, 5)};
  Player player("ENTRN", 100, 0, valid_weapons);
  Dungeon dungeon;

  SECTION("Successful") {
    std::string filepath = "C:\\Users\\cesco\\OneDrive\\Documents\\School\\"
                           "UIUC\\2020-2021\\Spring 2021\\CS 126\\Cinder\\"
                           "my-projects\\final-project-fvial2\\resources\\"
                           "test.txt";

    std::ifstream input_file(filepath);
    if (input_file.is_open()) {
      input_file >> dungeon;

      input_file.close();
    }

    Engine engine(player, dungeon);

    engine.SetQualifier("UP");
    engine.Go();

    REQUIRE(engine.GetPlayer().GetCurrentLocation() == "SWORD");
    REQUIRE(engine.GetMessage() == "YOU WENT UP");
  }

  SECTION("There are no doors in this room") {
    std::string filepath = "C:\\Users\\cesco\\OneDrive\\Documents\\School\\"
                           "UIUC\\2020-2021\\Spring 2021\\CS 126\\Cinder\\"
                           "my-projects\\final-project-fvial2\\resources\\"
                           "doorless.txt";

    std::ifstream input_file(filepath);
    if (input_file.is_open()) {
      input_file >> dungeon;

      input_file.close();
    }

    Engine engine(player, dungeon);

    engine.SetQualifier("UP");
    engine.Go();

    REQUIRE(engine.GetPlayer().GetCurrentLocation() == "ENTRN");
    REQUIRE(engine.GetMessage() == "THERE ARE NO DOORS IN THIS ROOM");
  }
}

TEST_CASE("Engine take") {
  std::vector<Weapon> valid_weapons{Weapon("SPELL", "SPELL", 5, 5),
                                    Weapon("TRINKET", "TRNKT", 5, 5),
                                    Weapon("DAGGER", "DGR", 5, 5)};
  Player player("ENTRN", 100, 0, valid_weapons);
  Dungeon dungeon;

  std::string filepath = "C:\\Users\\cesco\\OneDrive\\Documents\\School\\"
                         "UIUC\\2020-2021\\Spring 2021\\CS 126\\Cinder\\"
                         "my-projects\\final-project-fvial2\\resources\\"
                         "test.txt";

  std::ifstream input_file(filepath);
  if (input_file.is_open()) {
    input_file >> dungeon;

    input_file.close();
  }

  Engine engine(player, dungeon);

  SECTION("Successful key") {
    engine.SetQualifier("DOWN");
    engine.Go();

    engine.SetQualifier("KEY");
    engine.Take();

    REQUIRE(engine.GetPlayer().GetNumberOfKeys() == 1);
    REQUIRE(engine.GetMap().at(2).GetNumberOfKeys() == 0);
    REQUIRE(engine.GetMessage() == "YOU TOOK A KEY");
  }

  SECTION("Successful weapon") {
    engine.SetQualifier("DOWN");
    engine.Go();

    engine.SetQualifier("BOW");
    engine.Take();

    REQUIRE(engine.GetPlayer().GetWeapons().size() == 4);
    REQUIRE(engine.GetMap().at(2).GetWeapons().empty());
    REQUIRE(engine.GetMessage() == "YOU TOOK THE BOW");
  }

  SECTION("There are no items in this room") {
    engine.SetQualifier("KEY");
    engine.Take();

    REQUIRE(engine.GetPlayer().GetNumberOfKeys() == 0);
    REQUIRE(engine.GetMap().front().GetNumberOfKeys() == 0);
    REQUIRE(engine.GetMessage() == "THERE ARE NO ITEMS IN THIS ROOM");

    engine.SetQualifier("BOW");
    engine.Take();

    REQUIRE(engine.GetPlayer().GetWeapons().size() == 3);
    REQUIRE(engine.GetMap().front().GetWeapons().empty());
    REQUIRE(engine.GetMessage() == "THERE ARE NO ITEMS IN THIS ROOM");
  }

  SECTION("You are carrying too many weapons") {
    engine.SetQualifier("UP");
    engine.Go();

    engine.SetQualifier("SWORD");
    engine.Take();

    engine.SetQualifier("DOWN");
    engine.Go();
    engine.Go();

    engine.SetQualifier("BOW");
    engine.Take();

    REQUIRE(engine.GetPlayer().GetWeapons().size() == 4);
    REQUIRE(engine.GetMap().at(2).GetWeapons().size() == 1);
    REQUIRE(engine.GetMessage() == "YOU ARE CARRYING TOO MANY WEAPONS");
  }
}

TEST_CASE("Engine drop") {
  std::vector<Weapon> valid_weapons{Weapon("SPELL", "SPELL", 5, 5)};
  Player player("ENTRN", 100, 1, valid_weapons);
  Dungeon dungeon;

  std::string filepath = "C:\\Users\\cesco\\OneDrive\\Documents\\School\\"
                         "UIUC\\2020-2021\\Spring 2021\\CS 126\\Cinder\\"
                         "my-projects\\final-project-fvial2\\resources\\"
                         "test.txt";

  std::ifstream input_file(filepath);
  if (input_file.is_open()) {
    input_file >> dungeon;

    input_file.close();
  }

  Engine engine(player, dungeon);

  SECTION("Successful key") {
    engine.SetQualifier("KEY");
    engine.Drop();

    REQUIRE(engine.GetPlayer().GetNumberOfKeys() == 0);
    REQUIRE(engine.GetMap().front().GetNumberOfKeys() == 1);
    REQUIRE(engine.GetMessage() == "YOU DROPPED A KEY");
  }

  SECTION("Successful weapon") {
    engine.SetQualifier("SPELL");
    engine.Drop();

    REQUIRE(engine.GetPlayer().GetWeapons().empty());
    REQUIRE(engine.GetMap().front().GetWeapons().size() == 1);
    REQUIRE(engine.GetMessage() == "YOU DROPPED THE SPELL");
  }

  SECTION("There are no items on your person") {
    engine.SetQualifier("KEY");
    engine.Drop();

    engine.SetQualifier("SPELL");
    engine.Drop();

    engine.Drop();

    REQUIRE(engine.GetPlayer().GetNumberOfKeys() == 0);
    REQUIRE(engine.GetMap().front().GetNumberOfKeys() == 1);
    REQUIRE(engine.GetPlayer().GetWeapons().empty());
    REQUIRE(engine.GetMap().front().GetWeapons().size() == 1);
    REQUIRE(engine.GetMessage() == "THERE ARE NO ITEMS ON YOUR PERSON");
  }
}
