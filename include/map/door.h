// Copyright (c) 2021 Francesco Vial. All rights reserved.

#pragma once

#include <string>

namespace adventure {

/**
 * Takes in a direction, room that it leads into, and its lock status to
 * represent a door in a room.
 */
class Door {
 public:
  /**
     * Loads a direction, room that it leads into, and its lock status as two
     * strings and a boolean, respectively. Throws an error if the direction
     * and/or adjacent room strings are empty and/or if the adjacent room string
     * is greater than five characters.
     * @param direction The direction of the Door with respect to its Room
     * @param adjacent_room The Room the Door leads into
     * @param is_locked Whether the given Door is locked or not
     */
  Door(const std::string& direction, const std::string& adjacent_room,
       bool is_locked);

  const std::string &GetDirection() const;

  const std::string &GetAdjacentRoom() const;

  bool IsLocked() const;

  /**
   * Switches the lock status of the door (i.e. true to false or false to true).
   */
  void SwitchLock();

 private:
  std::string direction_;
  std::string adjacent_room_;
  bool is_locked_;
};

}   // namespace adventure
