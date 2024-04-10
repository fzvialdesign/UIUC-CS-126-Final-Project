// Copyright (c) 2021 Francesco Vial. All rights reserved.

#include "map/room.h"

namespace adventure {

Room::Room(const std::string& name, const std::string& nickname,
           const std::vector<Door>& doors, const std::vector<Enemy>& enemies,
           const std::vector<Weapon>& weapons, size_t number_of_keys)
    : name_(name), nickname_(nickname), doors_(doors), enemies_(enemies),
      weapons_(weapons), number_of_keys_(number_of_keys) {
  size_t max_size = 5;

  if (name.empty() || nickname.empty()) {
    throw std::invalid_argument("NAME AND/OR NICKNAME NOT SPECIFIED");
  } else if (nickname.size() > max_size) {
    throw std::invalid_argument("NICKNAME TOO LONG");
  }
}

const std::string &Room::GetName() const { return name_; }

const std::string &Room::GetNickname() const { return nickname_; }

const std::vector<Door> &Room::GetDoors() const { return doors_; }

const std::vector<Enemy> &Room::GetEnemies() const { return enemies_; }

const std::vector<Weapon> &Room::GetWeapons() const { return weapons_; }

size_t Room::GetNumberOfKeys() const { return number_of_keys_; }

void Room::IncrementNumberOfKeys() {
  ++number_of_keys_;
}

void Room::DecrementNumberOfKeys() {
  if (number_of_keys_ > 0) {
    --number_of_keys_;
  }
}

void Room::AddWeapon(const Weapon& weapon) {
  for (Weapon& room_weapon : weapons_) {
    if (room_weapon.GetName() == weapon.GetName()) {
      throw std::invalid_argument("WEAPON ALREADY IN ROOM");
    }
  }

  weapons_.push_back(weapon);
}

void Room::RemoveWeapon(const Weapon& weapon) {
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

void Room::RemoveEnemy(const Enemy& enemy) {
  if (enemies_.empty()) {
    throw std::invalid_argument("ENEMIES EMPTY");
  }

  for (size_t index = 0; index < enemies_.size(); ++index) {
    if (enemies_[index].GetName() == enemy.GetName()) {
      enemies_.erase(enemies_.begin() + (int)index);
      return;
    }
  }

  throw std::invalid_argument("ENEMY NOT FOUND");
}

Weapon &Room::RetrieveWeapon(const std::string& name) {
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

Door &Room::RetrieveDoor(const std::string &direction) {
  if (direction.empty()) {
    throw std::invalid_argument("DOOR DIRECTION NOT SPECIFIED");
  }

  for (Door& door : doors_) {
    if (door.GetDirection() == direction) {
      return door;
    }
  }

  throw std::invalid_argument("DOOR NOT FOUND");
}

Enemy &Room::RetrieveEnemy(const std::string &name) {
  if (name.empty()) {
    throw std::invalid_argument("ENEMY NAME NOT SPECIFIED");
  }

  for (Enemy& enemy : enemies_) {
    if (enemy.GetNickname() == name) {
      return enemy;
    }
  }

  throw std::invalid_argument("ENEMY NOT FOUND");
}

}   // namespace adventure