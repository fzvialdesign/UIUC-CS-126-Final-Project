// Copyright (c) 2021 Francesco Vial. All rights reserved.

#include "adventure_app.h"

namespace adventure {

AdventureApp::AdventureApp() : engine_(),
                               visualizer_(kWindowWidth, kWindowHeight),
                               last_button_index_(3) {
  ci::app::setWindowSize(kWindowWidth, kWindowHeight);

  engine_.SetMessage("WHAT WILL YOU DO?");
}

void AdventureApp::draw() {
  ci::gl::clear(ci::Color("black"));

  visualizer_.Display();
}

void AdventureApp::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_RIGHT:
      if (!visualizer_.IsGameOver()) {
        MoveSelectionRight();
        break;
      }

    case ci::app::KeyEvent::KEY_LEFT:
      if (!visualizer_.IsGameOver()) {
        MoveSelectionLeft();
        break;
      }

    case ci::app::KeyEvent::KEY_RETURN:
      if (!visualizer_.IsGameOver()) {
        if (visualizer_.HasToggledPanels()) {
          ExecuteCommand();

          visualizer_.SetSubSelection(kFirstButton);
          visualizer_.SetHasToggledPanels(false);

          last_button_index_ = 3;
        } else {
          visualizer_.SetHasToggledPanels(true);
        }
        break;
      }

    case ci::app::KeyEvent::KEY_ESCAPE:
      if (visualizer_.HasToggledPanels()) {
        visualizer_.SetSubSelection(kFirstButton);
        visualizer_.SetHasToggledPanels(false);

        last_button_index_ = 3;
        break;
      } else {
        ci::app::App::quit();
        break;
      }
  }
}

void AdventureApp::update() {
  visualizer_.UpdatePlayerInformationText(engine_.GetPlayer());

  if (engine_.GetMessage() == "YOU WIN" || engine_.GetMessage() == "YOU LOSE") {
    visualizer_.UpdateMessage(engine_.GetMessage(), true);
  } else {
    visualizer_.UpdateMessage(engine_.GetMessage(), false);
  }


  if (visualizer_.HasToggledPanels()) {
    if (visualizer_.GetMainSelection() == kFirstButton) {
      LoadFightOptions();
    } else if (visualizer_.GetMainSelection() == kSecondButton) {
      LoadTakeOptions();
    } else if (visualizer_.GetMainSelection() == kThirdButton) {
      LoadDropOptions();
    } else if (visualizer_.GetMainSelection() == kFourthButton) {
      LoadGoOptions();
    }
  }
}

void AdventureApp::ExecuteCommand() {
  engine_.SetQualifier(visualizer_.GetSubActions()
                           .at(visualizer_.GetSubSelection()));

  if (visualizer_.GetMainSelection() == kFirstButton) {
    engine_.Fight();
  } else if (visualizer_.GetMainSelection() == kSecondButton) {
    engine_.Take();
  } else if (visualizer_.GetMainSelection() == kThirdButton) {
    engine_.Drop();
  } else if (visualizer_.GetMainSelection() == kFourthButton) {
    engine_.Go();
  }
}

void AdventureApp::MoveSelectionLeft() {
  if (visualizer_.HasToggledPanels()) {
    if (visualizer_.GetSubSelection() == kFirstButton) {
      visualizer_.SetSubSelection(last_button_index_);
    } else {
      visualizer_.DecrementSubSelection();
    }
  } else {
    if (visualizer_.GetMainSelection() == kFirstButton) {
      visualizer_.SetMainSelection(last_button_index_);
    } else {
      visualizer_.DecrementMainSelection();
    }
  }
}

void AdventureApp::MoveSelectionRight() {
  if (visualizer_.HasToggledPanels()) {
    if (visualizer_.GetSubSelection() == last_button_index_) {
      visualizer_.SetSubSelection(kFirstButton);
    } else {
      visualizer_.IncrementSubSelection();
    }
  } else {
    if (visualizer_.GetMainSelection() == last_button_index_) {
      visualizer_.SetMainSelection(kFirstButton);
    } else {
      visualizer_.IncrementMainSelection();
    }
  }
}
void AdventureApp::LoadFightOptions() {
  Room current_room = engine_.RetrieveRoom(engine_.GetPlayer()
                                               .GetCurrentLocation());

  if (current_room.GetEnemies().empty()) {
    visualizer_.SetHasToggledPanels(false);

    // Attempts to execute a command because the failure will produce the
    // desired visual output message
    engine_.Fight();
  } else {
    engine_.SetMessage("WHAT WILL YOU DO?");
    last_button_index_ = current_room.GetEnemies().size() - 1;

    visualizer_.UpdateSubActionText(current_room.GetEnemies());
    visualizer_.UpdateSubInformationText(current_room.GetEnemies());
  }


}

void AdventureApp::LoadTakeOptions() {
  Room current_room = engine_.RetrieveRoom(engine_.GetPlayer()
                                               .GetCurrentLocation());

  if (current_room.GetWeapons().empty() &&
      current_room.GetNumberOfKeys() == 0) {
    visualizer_.SetHasToggledPanels(false);

    // Attempts to execute a command because the failure will produce the
    // desired visual output message
    engine_.Take();
  } else {
    engine_.SetMessage("WHAT WILL YOU DO?");
    last_button_index_ = (current_room.GetWeapons().size() +
                          current_room.GetNumberOfKeys()) - 1;

    visualizer_.UpdateSubActionText(current_room.GetWeapons(),
                                    current_room.GetNumberOfKeys());

    if (!current_room.GetWeapons().empty()) {
      visualizer_.UpdateSubInformationText(current_room.GetWeapons());
    }
  }
}

void AdventureApp::LoadDropOptions() {
  Player player = engine_.GetPlayer();

  if (player.GetWeapons().empty() && player.GetNumberOfKeys() == 0) {
    visualizer_.SetHasToggledPanels(false);

    // Attempts to execute a command because the failure will produce the
    // desired visual output message
    engine_.Drop();
  } else {
    engine_.SetMessage("WHAT WILL YOU DO?");
    last_button_index_ = (player.GetWeapons().size() +
                          player.GetNumberOfKeys()) - 1;

    visualizer_.UpdateSubActionText(player.GetWeapons(),
                                    player.GetNumberOfKeys());

    if (!player.GetWeapons().empty()) {
      visualizer_.UpdateSubInformationText(player.GetWeapons());
    }
  }
}

void AdventureApp::LoadGoOptions() {
  Room current_room = engine_.RetrieveRoom(engine_.GetPlayer()
                                               .GetCurrentLocation());

  if (current_room.GetDoors().empty()) {
    visualizer_.SetHasToggledPanels(false);

    // Attempts to execute a command because the failure will produce the
    // desired visual output message
    engine_.Go();
  } else {
    engine_.SetMessage("WHAT WILL YOU DO?");
    last_button_index_ = current_room.GetDoors().size() - 1;

    visualizer_.UpdateSubActionText(current_room.GetDoors());
    visualizer_.UpdateSubInformationText(current_room.GetDoors());
  }
}

}
