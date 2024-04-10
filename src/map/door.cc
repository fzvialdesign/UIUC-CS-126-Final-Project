// Copyright (c) 2021 Francesco Vial. All rights reserved.

#include "map/door.h"

namespace adventure {

Door::Door(const std::string& direction, const std::string& adjacent_room,
           bool is_locked)
    : direction_(direction), adjacent_room_(adjacent_room),
      is_locked_(is_locked) {
  size_t max_size = 5;

  if (direction.empty() || adjacent_room.empty()) {
    throw std::invalid_argument("DIRECTION AND/OR ADJACENT ROOM NOT SPECIFIED");
  } else if (adjacent_room.size() > max_size) {
    throw std::invalid_argument("ADJACENT ROOM TOO LONG");
  }
}

const std::string &Door::GetDirection() const { return direction_; }

const std::string &Door::GetAdjacentRoom() const { return adjacent_room_; }

bool Door::IsLocked() const { return is_locked_; }

void Door::SwitchLock() { is_locked_ = !is_locked_; }

}   // namespace adventure