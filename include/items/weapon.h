// Copyright (c) 2021 Francesco Vial. All rights reserved.

#pragma once

#include <string>

namespace adventure {

/**
 * Takes in a name, nickname, strength, and critical hit chance for a Weapon.
 */
class Weapon {
 public:
  /**
   * Loads in a name, nickname, strength value, and critical hit chance value
   * as two strings and two size_ts, respectively. Throws an error if the
   * name string and/or nickname string is empty, if the nickname string is
   * greater than five characters, and/or if the strength equals zero.
   * @param name The Weapon's name
   * @param nickname The Weapon's shortened name
   * @param strength The Weapon's strength
   * @param critical_chance The Weapon's critical hit chance
   */
  Weapon(const std::string& name, const std::string& nickname, size_t strength,
         size_t critical_chance);

  const std::string &GetName() const;

  const std::string &GetNickname() const;

  size_t GetStrength() const;

  size_t GetCriticalChance() const;

  /**
   * Calculates damage to deal based on the current strength and critical hit
   * chance (based on random number generation between 0 and 99). If the
   * number is less than or equal to the critical hit chance, it returns
   * double the strength. Otherwise, it returns just the strength.
   * @return The calculated damage
   */
  size_t CalculateDamage() const;

 private:
  std::string name_;
  std::string nickname_;
  size_t strength_;
  size_t critical_chance_;
};

}   // namespace adventure