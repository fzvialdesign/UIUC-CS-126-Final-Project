// Copyright (c) 2021 Francesco Vial. All rights reserved.

#pragma once

#include <string>

namespace adventure {

/**
 * Takes in a name, nickname, health, strength, and critical hit chance for an
 * enemy in a dungeon room.
 */
class Enemy {
 public:
  /**
   * Loads in a name, nickname, health value, strength value, and critical hit
   * chance value as two strings and three size_ts, respectively. Throws an
   * error if the name string and/or nickname string are empty, if the nickname
   * string is greater than five characters, and/or if the health and/or
   * strength equal zero.
   * @param name The Enemy's name
   * @param nickname The Enemy's shortened name
   * @param health The Enemy's health
   * @param attack The Enemy's strength
   * @param critical_chance The Enemy's critical hit chance
   */
  Enemy(const std::string& name, const std::string& nickname, size_t health,
         size_t strength, size_t critical_chance);

  const std::string &GetName() const;

  const std::string &GetNickname() const;

  size_t GetHealth() const;

  size_t GetStrength() const;

  size_t GetCriticalChance() const;

  /**
   * Generates and returns attack damage based on a helper method that
   * calculates the value.
   * @return The generated attack damage
   */
  size_t DealDamage() const;

  /**
   * Diminishes the health by the specified amount. If the Enemy would end up
   * with health below 0, the health will be set to 0.
   * @param amount The amount to diminish by
   */
  void TakeDamage(size_t amount);

  /**
   * Returns whether the Enemy is alive or not (i.e. whether the health is
   * above zero or not).
   * @return Whether the health is above zero or not
   */
  bool IsAlive();

 private:
  std::string name_;
  std::string nickname_;
  size_t health_;
  size_t strength_;
  size_t critical_chance_;

  /**
   * Calculates damage to deal based on the current strength and critical hit
   * chance (based on random number generation between 0 and 99). If the
   * number is less than or equal to the critical hit chance, it returns
   * double the strength. Otherwise, it returns just the strength.
   * @return The calculated damage
   */
  size_t CalculateDamage() const;
};

}   // namespace adventure