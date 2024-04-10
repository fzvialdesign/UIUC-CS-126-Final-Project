// Copyright (c) 2021 Francesco Vial. All rights reserved.

#include "map/dungeon.h"

#include <algorithm>
#include <string>

namespace adventure {

Dungeon::Dungeon() : map_() {}

const std::vector<Room> &Dungeon::GetMap() const { return map_; }

std::istream &operator>>(std::istream &is, Dungeon &dungeon) {
  std::string line;
  std::getline(is , line);

  if (line == "DUNGEON_LOAD_FINAL_PROJECT") {
    while (is.good()) {
      std::getline(is , line);

      if (line == "    {") {
        dungeon.map_.push_back(dungeon.GenerateRoom(is, line));
      }
    }
  } else {
    throw std::invalid_argument("INVALID FILE");
  }

  return is;
}

Room Dungeon::GenerateRoom(std::istream &is, std::string &line) {
  std::getline(is , line);
  line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
  std::string name = line;

  std::getline(is , line);
  line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
  std::string nickname = line;

  std::vector<Door> doors;
  std::getline(is , line);
  if (line == "      [") {
    while (line != "      ]") {
      std::getline(is , line);

      if (line == "        {") {
        doors.push_back(GenerateDoor(is, line));
      }
    }
  }

  std::vector<Enemy> enemies;
  std::getline(is , line);
  if (line == "      [") {
    while (line != "      ]") {
      std::getline(is, line);

      if (line == "        {") {
        enemies.push_back(GenerateEnemy(is, line));
      }
    }
  }

  std::vector<Weapon> weapons;
  std::getline(is , line);
  if (line == "      [") {
    while (line != "      ]") {
      std::getline(is, line);

      if (line == "        {") {
        weapons.push_back(GenerateWeapon(is, line));
      }
    }
  }

  std::getline(is , line);
  line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
  size_t number_of_keys = (size_t)std::stoi(line);

  return Room(name, nickname, doors, enemies, weapons, number_of_keys);
}

Door Dungeon::GenerateDoor(std::istream &is, std::string &line) {
  std::getline(is , line);
  line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
  std::string direction = line;

  std::getline(is , line);
  line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
  std::string adjacent_room = line;

  std::getline(is , line);
  line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
  bool is_locked;

  if (line == "TRUE") {
    is_locked = true;
  } else {
    is_locked = false;
  }

  std::getline(is, line);

  return Door(direction, adjacent_room, is_locked);
}

Enemy Dungeon::GenerateEnemy(std::istream &is, std::string &line) {
  std::getline(is , line);
  line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
  std::string name = line;

  std::getline(is , line);
  line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
  std::string nickname = line;

  std::getline(is , line);
  line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
  size_t health = (size_t)std::stoi(line);

  std::getline(is , line);
  line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
  size_t strength = (size_t)std::stoi(line);

  std::getline(is , line);
  line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
  size_t critical_chance = (size_t)std::stoi(line);

  std::getline(is, line);

  return Enemy(name, nickname, health, strength, critical_chance);
}

Weapon Dungeon::GenerateWeapon(std::istream &is, std::string &line) {
  std::getline(is , line);
  line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
  std::string name = line;

  std::getline(is , line);
  line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
  std::string nickname = line;

  std::getline(is , line);
  line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
  size_t strength = (size_t)std::stoi(line);

  std::getline(is , line);
  line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
  size_t critical_chance = (size_t)std::stoi(line);

  std::getline(is, line);

  return Weapon(name, nickname, strength, critical_chance);
}

}
