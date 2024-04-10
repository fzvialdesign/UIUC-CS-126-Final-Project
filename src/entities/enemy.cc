// Copyright (c) 2021 Francesco Vial. All rights reserved.

#include "entities/enemy.h"

namespace adventure {

Enemy::Enemy(const std::string& name, const std::string& nickname,
             size_t health, size_t strength, size_t critical_chance)
    : name_(name), nickname_(nickname), health_(health), strength_(strength),
      critical_chance_(critical_chance) {
  size_t max_size = 5;

  if (name.empty() || nickname.empty()) {
    throw std::invalid_argument("NAME AND/OR NICKNAME NOT SPECIFIED");
  } else if (nickname.size() > max_size) {
    throw std::invalid_argument("NICKNAME TOO LONG");
  } else if (health == 0 || strength == 0) {
    throw std::invalid_argument("HEALTH AND/OR STRENGTH EQUAL ZERO");
  }
}

const std::string &Enemy::GetName() const { return name_; }

const std::string &Enemy::GetNickname() const { return nickname_; }

size_t Enemy::GetHealth() const { return health_; }

size_t Enemy::GetStrength() const { return strength_; }

size_t Enemy::GetCriticalChance() const { return critical_chance_; }

size_t Enemy::DealDamage() const {
  return CalculateDamage();
}

void Enemy::TakeDamage(size_t amount) {
  if (amount > health_) {
    health_ = 0;
  } else {
    health_ -= amount;
  }
}

bool Enemy::IsAlive() { return health_ > 0; }

size_t Enemy::CalculateDamage() const {
  if ((size_t)(rand() % 100) <= critical_chance_ && critical_chance_ > 0) {
    return (2 * strength_);
  } else {
    return strength_;
  }
}

}