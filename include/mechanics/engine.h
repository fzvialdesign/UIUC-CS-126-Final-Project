// Copyright (c) 2021 Francesco Vial. All rights reserved.

#pragma once

#include "entities/player.h"
#include "map/dungeon.h"
#include "map/room.h"

#include <string>
#include <vector>

namespace adventure {

/**
 * Takes in a Player and a Dungeon for a game Engine, or initializes the
 * Engine based on the default constructor, which provides all the mechanics
 * of an adventure game.
 */
class Engine {
 public:

  /**
   * Internally loads a Player based on its default constructor and a
   * Dungeon using its operator overloads. This is recommended for use with
   * the AdventureApp code.
   */
  Engine();

  /**
   * Loads in a Player and a Dungeon to work with the Engine. Throws an error
   * if the Dungeon's vector of Rooms is empty.
   * @param player The Player playing through the game
   * @param dungeon The Dungeon the Player will be playing through
   */
  Engine(const Player& player, const Dungeon& dungeon);

  const Player &GetPlayer() const;

  const std::vector<Room> &GetMap() const;

  const std::string &GetMessage() const;

  void SetQualifier(const std::string& qualifier);

  void SetMessage(const std::string& message);

  /**
   * Attempts to move to an adjacent room based on the current qualifier from
   * a whole command input.
   */
  void Go();

  /**
   * Attempts to take the current Room's key or Weapon and place it in the
   * Player's hand based on the current qualifier from a whole command
   * input.
   */
  void Take();

  /**
   * Attempts to drop a Player's key or Weapon into its current Room
   * based on the current qualifier from a whole command input.
   */
  void Drop();

  /**
   * Attempts to fight an Enemy in the Player's current Room based on the
   * current qualifier from a whole command input.
   */
  void Fight();

  /**
   * Iterates through the vector of Rooms and returns the specified Room
   * based on a name string. Throws an error if the name string is empty or
   * the Room is not in the vector.
   * @param name The name of the Room being searched for
   * @return The Room being searched for
   */
  Room &RetrieveRoom(const std::string& name);

 private:
  const int kMaxPlayerWeapons = 4;

  Player player_;
  std::vector<Room> map_;
  std::string qualifier_;
  std::string message_;
};

}   // namespace adventure