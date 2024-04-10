// Copyright (c) 2021 Francesco Vial. All rights reserved.

#pragma once

#include "door.h"
#include "entities/enemy.h"
#include "items/weapon.h"

#include <string>
#include <vector>

namespace adventure {

/**
 * Takes in a Room name, nickname, set of Doors, set of Enemies, set of Weapons,
 * and number of keys to represent a door in a room.
 */
class Room {
 public:
  /**
     * Loads a Room name, nickname set of Doors, set of Enemies, set of Weapons,
     * and number of keys as two strings, vector of Doors, vector of Enemies,
     * vector of Weapons, and size_t, respectively. Throws an error if the name
     * string and/or nickname string are empty and/or if the nickname is
     * greater than five characters.
     * @param name The Room's name
     * @param nickname The Room's shortened name
     * @param doors The Room's vector of Doors
     * @param enemies The Room's vector of Enemies
     * @param weapons The Room's vector of Weapons
     * @param number_of_keys The Room's number of keys
     */
  Room(const std::string& name, const std::string& nickname,
       const std::vector<Door>& doors, const std::vector<Enemy>& enemies,
       const std::vector<Weapon>& weapons, size_t number_of_keys);

  const std::string &GetName() const;

  const std::string &GetNickname() const;

  const std::vector<Door> &GetDoors() const;

  const std::vector<Enemy> &GetEnemies() const;

  const std::vector<Weapon> &GetWeapons() const;

  size_t GetNumberOfKeys() const;

  /**
   * Increments the number of keys the Player currently has by one.
   */
  void IncrementNumberOfKeys();

  /**
   * Decrements the number of keys the Player currently has by one. If the
   * Player will end up with a number below 0, nothing happens.
   */
  void DecrementNumberOfKeys();

  /**
   * Adds the specified Weapon to the back of the vector of Weapons. Throws an
   * error if the Weapon is already in the vector.
   * @param weapon The specified Weapon to add to the vector
   */
  void AddWeapon(const Weapon& weapon);

  /**
   * Removes the specified Weapon by iterating through the vector until it
   * finds the specified Weapon. Throws an error if the vector is empty or
   * the Weapon is not in the vector.
   * @param weapon The specified Weapon to remove from the vector
   */
  void RemoveWeapon(const Weapon& weapon);

  /**
   * Removes the specified Enemy by iterating through the vector until it
   * finds the specified Enemy. Throws an error if the vector is empty or
   * the Enemy is not in the vector.
   * @param enemy The specified Enemy to remove from the vector
   */
  void RemoveEnemy(const Enemy& enemy);

  /**
   * Iterates through the vector of Weapons and returns the specified Weapon
   * based on a name string. Throws an error if the name string is empty or
   * the Weapon is not in the vector.
   * @param name The name of the Weapon being searched for
   * @return The Weapon being searched for
   */
  Weapon &RetrieveWeapon(const std::string& name);

  /**
   * Iterates through the vector of Doors and returns the specified Door
   * based on a direction string. Throws an error if the Door is not in the
   * vector.
   * @param name The direction of the Door being searched for
   * @return The Door being searched for
   */
  Door &RetrieveDoor(const std::string& direction);

  /**
   * Iterates through the vector of Enemies and returns the specified Enemy
   * based on a name string. Throws an error if the name string is empty or
   * the Enemy is not in the vector.
   * @param name The name of the Enemy being searched for
   * @return The Enemy being searched for
   */
  Enemy &RetrieveEnemy(const std::string& name);

 private:
  std::string name_;
  std::string nickname_;
  std::vector<Door> doors_;
  std::vector<Enemy> enemies_;
  std::vector<Weapon> weapons_;
  size_t number_of_keys_;
};

}   // namespace adventure
