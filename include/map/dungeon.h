// Copyright (c) 2021 Francesco Vial. All rights reserved.

#pragma once

#include "map/room.h"

#include <vector>
#include <fstream>
#include <iostream>

namespace adventure {

/**
 * Initializes a Dungeon which holds a dungeon map that can be filled using an
 * operator overload.
 */
class Dungeon {
 public:
  /**
   * Internally loads a map as an empty vector of Rooms
   */
  Dungeon();

  const std::vector<Room> &GetMap() const;

  /**
   * Loads an in-stream and parses through a dungeon file, loading in all of
   * its information into a vector of Rooms using various helper methods.
   * Throws an error if the specified file is invalid.
   * @param is The in-stream that holds the file
   * @param dungeon The Dungeon the file is being loaded into
   * @return The in-stream that went into the operator
   */
  friend std::istream &operator>>(std::istream& is, Dungeon& dungeon);

 private:
  std::vector<Room> map_;

  /**
   * Generates a Room by parsing through a following portion of the dungeon
   * file's text lines.
   * @param is The in-stream that holds the file
   * @param line The current line being examined by the operator
   * @return The generated Room
   */
  static Room GenerateRoom(std::istream& is, std::string& line);

  /**
   * Generates a Door by parsing through a following portion of the dungeon
   * file's text lines.
   * @param is The in-stream that holds the file
   * @param line The current line being examined by the operator
   * @return The generated Door
   */
  static Door GenerateDoor(std::istream& is, std::string& line);

  /**
   * Generates an Enemy by parsing through a following portion of the dungeon
   * file's text lines.
   * @param is The in-stream that holds the file
   * @param line The current line being examined by the operator
   * @return The generated Enemy
   */
  static Enemy GenerateEnemy(std::istream& is, std::string& line);

  /**
   * Generates a Weapon by parsing through a following portion of the dungeon
   * file's text lines.
   * @param is The in-stream that holds the file
   * @param line The current line being examined by the operator
   * @return The generated Weapon
   */
  static Weapon GenerateWeapon(std::istream& is, std::string& line);
};

}   // namespace adventure