// Copyright (c) 2021 Francesco Vial. All rights reserved.

#pragma once

#include "cinder/gl/gl.h"

#include "entities/enemy.h"
#include "entities/player.h"

#include "items/weapon.h"

#include "map/door.h"
#include "map/room.h"

namespace adventure {

/**
 * Takes in a window width and window height for a Visualizer which displays
 * all the visual elements of an adventure game.
 */
class Visualizer {
 public:
  /**
   * Loads in a window width and window height as integers to initialize the
   * bounds (plus initializes the main and sub-selections as 0, has toggled
   * panels as false, player information as a vector of four empty strings,
   * sub-actions as an empty vector of strings, action information as an
   * empty vector of strings, message as an empty string, and whether it is
   * game over or not as false).
   * @param window_width The width of the app window
   * @param window_height The height of the app window
   */
  Visualizer(int window_width, int window_height);

  const std::vector<std::string> &GetSubActions() const;

  size_t GetMainSelection() const;
  
  void SetMainSelection(size_t main_selection);
  
  size_t GetSubSelection() const;
  
  void SetSubSelection(size_t sub_selection);
  
  bool HasToggledPanels() const;

  bool IsGameOver() const;
  
  void SetHasToggledPanels(bool has_toggled_panels);

  /**
   * Increments the main selection value by one.
   */
  void IncrementMainSelection();

  /**
   * Decrements the main selection value by one.
   */
  void DecrementMainSelection();

  /**
   * Increments the sub-selection value by one.
   */
  void IncrementSubSelection();

  /**
   * Decrements the sub-selection value by one.
   */
  void DecrementSubSelection();

  /**
   * Draws everything that needs to appear in the app window based on a
   * variety of helper methods.
   */
  void Display();

  void UpdateMessage(const std::string& message, bool is_game_over);

  /**
   * Updates the player information text that gets displayed.
   * @param player The Player where the information is found
   */
  void UpdatePlayerInformationText(const Player& player);

  /**
   * Updates the sub-action text that gets displayed.
   * @param enemies The vector of Enemies where the information is found
   */
  void UpdateSubActionText(const std::vector<Enemy>& enemies);

  /**
   * Updates the sub-action text that gets displayed.
   * @param weapons The vector of Weapons where the information is found
   * @param number_of_keys The number of keys where the information is found
   */
  void UpdateSubActionText(const std::vector<Weapon>& weapons,
                           size_t number_of_keys);

  /**
   * Updates the sub-action text that gets displayed.
   * @param doors The vector of Doors where the information is found
   */
  void UpdateSubActionText(const std::vector<Door>& doors);

  /**
   * Updates the sub-action text that gets displayed.
   * @param enemies The vector of Enemies where the information is found
   */
  void UpdateSubInformationText(const std::vector<Enemy>& enemies);

  /**
   * Updates the sub-information text that gets displayed.
   * @param weapons The vector of Weapons where the information is found
   */
  void UpdateSubInformationText(const std::vector<Weapon>& weapons);

  /**
   * Updates the sub-information text that gets displayed.
   * @param doors The vector of Doors where the information is found
   */
  void UpdateSubInformationText(const std::vector<Door>& doors);

private:
  const size_t kMaxBoxes = 4;

  glm::vec2 bounds_;

  std::vector<std::string> player_information_;
  std::vector<std::string> sub_actions_;
  std::vector<std::string> action_information_;
  std::string message_;

  size_t main_selection_;
  size_t sub_selection_;
  bool has_toggled_panels_;

  bool is_game_over_;

  /**
   * Draws the game over display.
   */
  void DrawGameOver();

  /**
   * Draws the panel with the main action buttons.
   */
  void DrawActionPanel();

  /**
   * Draws the panels with the action sub-buttons and relevant information.
   */
  void DrawSubPanels();

  /**
   * Draws the main action buttons.
   */
  void DrawActionButtons(const glm::vec2& panel_center);

  /**
   * Draws the action sub-buttons.
   */
  void DrawSubActionButtons(const glm::vec2& panel_center);

  /**
   * Draws the text label for a button.
   */
  void DrawButtonText(const glm::vec2& button_center,
                      const std::string &text) const;

  /**
   * Draws the bars that border the map portion of the app.
   */
  void DrawBorderBars() const;

  /**
   * Draws a map that backdrops a message display.
   */
  void DrawMap() const;

  /**
   * Draws the bars that show player information.
   */
  void DrawInformationBars() const;

  /**
   * Draws the text label for information bars.
   */
  void DrawPlayerInformationText();

  /**
   * Draws the text label for the information sub-panel.
   */
  void DrawSubInformationText();

  /**
   * Draws the message displayer over the map.
   */
  void DrawMessage();

  /**
   * Draws a solid rectangle based on a width, height, and center.
   */
  static void DrawSolidRectangle(float width, float height,
                                 const glm::vec2& center);
};

}   // namespace adventure