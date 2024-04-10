// Copyright (c) 2021 Francesco Vial. All rights reserved.

#include "mechanics/engine.h"

namespace adventure {

Engine::Engine() {
  std::string kFilepath = "C:\\Users\\cesco\\OneDrive\\Documents\\"
                                 "School\\UIUC\\2020-2021\\Spring 2021\\"
                                 "CS 126\\Cinder\\my-projects\\"
                                 "final-project-fvial2\\resources\\"
                                 "dungeon.txt";
  Dungeon dungeon;

  std::ifstream input_file(kFilepath);
  if (input_file.is_open()) {
    input_file >> dungeon;

    input_file.close();
  } else {
    std::invalid_argument("FILE NOT FOUND");
  }

  map_ = dungeon.GetMap();
}

Engine::Engine(const Player& player, const Dungeon& dungeon)
    : player_(player), map_(dungeon.GetMap()), qualifier_(), message_()  {
  if (dungeon.GetMap().empty()) {
    throw std::invalid_argument("DUNGEON MAP HAS NO ROOMS");
  }
}

const Player &Engine::GetPlayer() const { return player_; }

const std::vector<Room> &Engine::GetMap() const { return map_; }

const std::string &Engine::GetMessage() const { return message_; }

void Engine::SetQualifier(const std::string& qualifier) {
  qualifier_ = qualifier;
}

void Engine::SetMessage(const std::string& message) { message_ = message; }

void Engine::Go() {
  Room& player_room = RetrieveRoom(player_.GetCurrentLocation());

  if (player_room.GetDoors().empty()) {
    message_ = "THERE ARE NO DOORS IN THIS ROOM";
  } else {
    Door& target_door = player_room.RetrieveDoor(qualifier_);

    if (target_door.IsLocked()) {
      if (player_.GetNumberOfKeys() > 0) {
        Room& adjacent_room = RetrieveRoom(target_door.GetAdjacentRoom());

        target_door.SwitchLock();

        player_.DecrementNumberOfKeys();
        message_ = "YOU UNLOCKED THE DOOR";

        player_.RegenerateHealth();
      } else {
        message_ = "YOU DO NOT HAVE A KEY";
      }
    } else {
      player_.SetCurrentLocation(target_door.GetAdjacentRoom());

      message_ = "YOU WENT ";
      message_.append(qualifier_);

      player_.RegenerateHealth();
    }
  }
}

void Engine::Take() {
  Room& player_room = RetrieveRoom(player_.GetCurrentLocation());

  if (player_room.GetNumberOfKeys() == 0 && player_room.GetWeapons().empty()) {
    message_ = "THERE ARE NO ITEMS IN THIS ROOM";
  } else if (player_.GetWeapons().size() == kMaxPlayerWeapons) {
    message_ = "YOU ARE CARRYING TOO MANY WEAPONS";
  } else {
    if (qualifier_ == "KEY") {
      player_.IncrementNumberOfKeys();
      player_room.DecrementNumberOfKeys();

      message_ = "YOU TOOK A KEY";
    } else {
      Weapon& weapon = player_room.RetrieveWeapon(qualifier_);

      player_.AddWeapon(weapon);
      player_room.RemoveWeapon(weapon);

      message_ = "YOU TOOK THE ";
      message_.append(qualifier_);
    }

    player_.RegenerateHealth();
  }
}

void Engine::Drop() {
  Room& player_room = RetrieveRoom(player_.GetCurrentLocation());

  if (player_.GetNumberOfKeys() == 0 && player_.GetWeapons().empty()) {
    message_ = "THERE ARE NO ITEMS ON YOUR PERSON";
  } else {
    if (qualifier_ == "KEY") {
      player_.DecrementNumberOfKeys();
      player_room.IncrementNumberOfKeys();

      message_ = "YOU DROPPED A KEY";
    } else {
      Weapon& weapon = player_.RetrieveWeapon(qualifier_);

      player_room.AddWeapon(weapon);
      player_.RemoveWeapon(weapon);

      message_ = "YOU DROPPED THE ";
      message_.append(qualifier_);
    }

    player_.RegenerateHealth();
  }
}

void Engine::Fight() {
  Room& player_room = RetrieveRoom(player_.GetCurrentLocation());

  if (player_room.GetEnemies().empty()) {
    message_ = "THERE ARE NO ENEMIES IN THIS ROOM";
  } else {
    Enemy& room_enemy = player_room.RetrieveEnemy(qualifier_);

    while (room_enemy.IsAlive() && player_.IsAlive()) {
      room_enemy.TakeDamage(player_.DealDamage());
      player_.TakeDamage(room_enemy.DealDamage());
    }

    if (!player_.IsAlive()) {
      message_ = "YOU LOSE";
    } else {
      if (player_.GetCurrentLocation() == map_.back().GetNickname()) {
        message_ = "YOU WIN";
      } else {
        player_room.RemoveEnemy(room_enemy);

        message_ = "YOU FOUGHT THE ";
        message_.append(qualifier_);
      }
    }
  }
}

Room &Engine::RetrieveRoom(const std::string& name) {
  if (name.empty()) {
    throw std::invalid_argument("ROOM NAME NOT SPECIFIED");
  }

  for (Room& room : map_) {
    if (room.GetNickname() == name) {
      return room;
    }
  }

  throw std::invalid_argument("ROOM NOT FOUND");
}

}   // namespace adventure