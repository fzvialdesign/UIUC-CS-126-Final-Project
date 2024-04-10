// Copyright (c) 2021 Francesco Vial. All rights reserved.

#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "mechanics/engine.h"
#include "visualizer.h"

namespace adventure {

/**
 * Holds an Engine, Visualizer, and last button index to display an adventure
 * game as a separate application.
 */
class AdventureApp : public ci::app::App {
 public:
  /**
   * Internally loads an Engine based off its default constructor and a
   * Visualizer based on the window height and width constants. Also sets the
   * app window size and the last button index to three.
   */
  AdventureApp();

  /**
   * Overrides the original draw function to set the app window background to
   * black and prompting the Visualizer to display.
   */
  void draw() override;

  /**
   * Overrides the original keyDown function to respond to inputs from the
   * left arrow, right arrow, return, and escape keys. The arrows call their
   * respective helper methods to change button selection, the return key
   * makes a selection, and the escape key exits either the sub-panels or the
   * app itself as well as resetting the last button index to three.
   * @param event The key event created from pressing a key
   */
  void keyDown(ci::app::KeyEvent event) override;

  /**
   * Overrides the original update function to change the Visualizer's
   * various text variables to reflect updates in the actual game using,
   * helper methods depending on the state.
   */
  void update() override;

 private:
  const int kWindowHeight = 1080;
  const int kWindowWidth = 1440;
  const size_t kFirstButton = 0;
  const size_t kSecondButton = 1;
  const size_t kThirdButton = 2;
  const size_t kFourthButton = 3;

  Engine engine_;
  Visualizer visualizer_;
  size_t last_button_index_;

  void ExecuteCommand();

  /**
   * Moves the current button selection to the left or to the opposite end
   * depending on whether the Visualizer has toggled panels shown or not, the
   * current sub-selection, and the current main selection.
   */
  void MoveSelectionLeft();

  /**
   * Moves the current button selection to the right or to the opposite end
   * depending on whether the Visualizer has toggled panels shown or not, the
   * current sub-selection, and the current main selection.
   */
  void MoveSelectionRight();

  /**
   * Loads in the current Room's Enemies to serve as sub-action buttons and
   * changes the last button index according to the number of Enemies.
   */
  void LoadFightOptions();

  /**
   * Loads in the current Room's Weapons and number of keys to serve as
   * sub-action buttons and changes the last button index according to both the
   * number of Weapons and the number of keys.
   */
  void LoadTakeOptions();

  /**
   * Loads in the Player's Weapons and number of keys to serve as sub-action
   * buttons and changes the last button index according to both the number
   * of Weapons and the number of keys.
   */
  void LoadDropOptions();

  /**
   * Loads in the current Room's Doors to serve as sub-action buttons and
   * changes the last button index according to the number of Doors.
   */
  void LoadGoOptions();
};

}
