// Copyright (c) 2021 Francesco Vial. All rights reserved.

#include "entities/player.h"

namespace adventure {

Player::Player() : current_location_("ENTRN"), max_health_(1000),
      health_(1000), number_of_keys_(0) {
  std::vector<Weapon> start_weapons{Weapon("SWORD", "SWORD", 15, 15)};
  weapons_ = start_weapons;
}

Player::Player(const std::string& current_location, size_t health,
               size_t number_of_keys, const std::vector<Weapon>& weapons)
    : current_location_(current_location), max_health_(health),
      health_(health), number_of_keys_(number_of_keys), weapons_(weapons) {
  size_t max_size = 5;

  if (current_location.empty()) {
    throw std::invalid_argument("CURRENT LOCATION NOT SPECIFIED");
  } else if (current_location.size() > max_size) {
    throw std::invalid_argument("CURRENT LOCATION TOO LONG");
  } else if (health == 0) {
    throw std::invalid_argument("HEALTH EQUALS ZERO");
  }
}

const std::string &Player::GetCurrentLocation() const {
  return current_location_;
}

size_t Player::GetHealth() const { return health_; }

size_t Player::GetMaxHealth() const { return max_health_; }

size_t Player::GetNumberOfKeys() const { return number_of_keys_; }

const std::vector<Weapon> &Player::GetWeapons() const { return weapons_; }

void Player::SetCurrentLocation(const std::string& new_location) {
  current_location_ = new_location;
}

void Player::RegenerateHealth() {
  health_ += max_health_ / 20;

  if (health_ > max_health_) {
    health_ = max_health_;
  }
}

size_t Player::DealDamage() const {
  return RetrieveStrongestWeapon().CalculateDamage();
}

void Player::TakeDamage(size_t amount) {
  if (amount > health_) {
    health_ = 0;
  } else {
    health_ -= amount;
  }
}

bool Player::IsAlive() const { return health_ > 0; }

void Player::IncrementNumberOfKeys() {
  ++number_of_keys_;
}

void Player::DecrementNumberOfKeys() {
  if (number_of_keys_ > 0) {
    --number_of_keys_;
  }
}

void Player::AddWeapon(const Weapon& weapon) {
  for (Weapon& player_weapon : weapons_) {
    if (player_weapon.GetName() == weapon.GetName()) {
      throw std::invalid_argument("WEAPON ALREADY ON PERSON");
    }
  }

  weapons_.push_back(weapon);
}

void Player::RemoveWeapon(const Weapon& weapon) {
  if (weapons_.empty()) {
    throw std::invalid_argument("WEAPONS EMPTY");
  }

  for (size_t index = 0; index < weapons_.size(); ++index) {
    if (weapons_[index].GetName() == weapon.GetName()) {
      weapons_.erase(weapons_.begin() + (int)index);
      return;
    }
  }

  throw std::invalid_argument("WEAPON NOT FOUND");
}

Weapon &Player::RetrieveWeapon(const std::string& name) {
  if (name.empty()) {
    throw std::invalid_argument("WEAPON NAME NOT SPECIFIED");
  }

  for (Weapon& weapon : weapons_) {
    if (weapon.GetNickname() == name) {
      return weapon;
    }
  }

  throw std::invalid_argument("WEAPON NOT FOUND");
}

const Weapon &Player::RetrieveStrongestWeapon() const {
  size_t max_strength = 0;
  size_t index = 0;

  for (size_t weapon = 0; weapon < weapons_.size(); ++weapon) {
    size_t strength = weapons_[weapon].GetStrength();

    if (strength > max_strength) {
      max_strength = strength;
      index = weapon;
    }
  }

  return weapons_.at(index);
}


}   // namespace adventure