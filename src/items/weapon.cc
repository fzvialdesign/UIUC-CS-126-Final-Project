// Copyright (c) 2021 Francesco Vial. All rights reserved.

#include "items/weapon.h"

namespace adventure {

Weapon::Weapon(const std::string& name, const std::string& nickname,
               size_t strength, size_t critical_chance)
    : name_(name), nickname_(nickname), strength_(strength),
      critical_chance_(critical_chance) {
  size_t max_size = 5;

  if (name.empty() || nickname.empty()) {
    throw std::invalid_argument("NAME AND/OR NICKNAME NOT SPECIFIED");
  } else if (nickname.size() > max_size) {
    throw std::invalid_argument("NICKNAME TOO LONG");
  } else if (strength == 0) {
    throw std::invalid_argument("STRENGTH EQUALS ZERO");
  }
}

const std::string &Weapon::GetName() const { return name_; }

const std::string &Weapon::GetNickname() const { return nickname_; }

size_t Weapon::GetStrength() const { return strength_; }

size_t Weapon::GetCriticalChance() const { return critical_chance_; }

size_t Weapon::CalculateDamage() const {
  if ((size_t)(rand() % 100) <= critical_chance_) {
    return (2 * strength_);
  } else {
    return strength_;
  }
}

}   // namespace adventure