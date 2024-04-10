// Copyright (c) 2021 Francesco Vial. All rights reserved.

#pragma once

#include "items/weapon.h"

#include <string>
#include <vector>

namespace adventure {

/**
 * Takes in a current location, starting health, starting number of keys, and
 * a set of Weapons for a Player in a dungeon.
 */
class Player {
 public:

  /**
   * Internally loads a name, current location, starting health, starting number
   * of keys, and Weapons based on preset values. This is recommended for use
   * with the Engine default constructor and, by extent, the AdventureApp code.
   */
  Player();

  /**
   * Loads in a current location, starting health, starting number of keys
   * and Weapons as two strings, two size_ts, and a vector of Weapons,
   * respectively (plus a size_t for max health). Throws an error if the
   * current location string is empty, if the current location is greater than
   * five characters, and/or if the health equals zero.
   * @param currentLocation The player's current location
   * @param health The player's starting health
   * @param keys The starting number of keys
   * @param weapons The vector of Weapons
   */
  Player(const std::string& current_location, size_t health,
         size_t number_of_keys, const std::vector<Weapon>& weapons);

  const std::string &GetCurrentLocation() const;

  size_t GetHealth() const;

  size_t GetMaxHealth() const;

  size_t GetNumberOfKeys() const;

  const std::vector<Weapon> &GetWeapons() const;

  void SetCurrentLocation(const std::string& new_location);

  /**
   * Augments the health by 5% of the max health. If the health ends up
   * exceeding the max health, it gets set to the max health.
   */
  void RegenerateHealth();

  /**
   * Generates and returns attack damage based on a helper method that
   * retrieves the strongest Weapon.
   * @return The generated attack damage
   */
  size_t DealDamage() const;

  /**
   * Diminishes the health by the specified amount. If the Player would end up
   * with health below 0, the health will be set to 0.
   * @param amount The amount to diminish by
   */
  void TakeDamage(size_t amount);

  /**
   * Returns whether the Player is alive or not (i.e. whether the health is
   * above zero or not).
   * @return Whether the health is above zero or not
   */
  bool IsAlive() const;

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
   * Iterates through the vector of Weapons and returns the specified Weapon
   * based on a name string. Throws an error if the name string is empty or
   * the Weapon is not in the vector.
   * @param name The name of the Weapon being searched for
   * @return The Weapon being searched for
   */
  Weapon &RetrieveWeapon(const std::string& name);

 private:
  std::string current_location_;
  size_t max_health_;
  size_t health_;
  size_t number_of_keys_;
  std::vector<Weapon> weapons_;

  /**
   * Iterates through the vector of Weapons and returns the strongest Weapon.
   * @return The strongest Weapon being searched for
   */
  const Weapon &RetrieveStrongestWeapon() const;
};

}   // namespace adventure