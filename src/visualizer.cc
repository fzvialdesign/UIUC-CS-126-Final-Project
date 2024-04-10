// Copyright (c) 2021 Francesco Vial. All rights reserved.

#include "visualizer.h"

namespace adventure {

Visualizer::Visualizer(int window_width, int window_height) 
    : bounds_(glm::vec2(window_width, window_height)),
      player_information_(std::vector<std::string>(4, "")),
      sub_actions_(), action_information_(), message_(), main_selection_(0),
      sub_selection_(0), has_toggled_panels_(false), is_game_over_(false) {}

const std::vector<std::string> &Visualizer::GetSubActions() const {
  return sub_actions_;
}

size_t Visualizer::GetMainSelection() const { return main_selection_; }

void Visualizer::SetMainSelection(size_t main_selection) {
  main_selection_ = main_selection;
}

size_t Visualizer::GetSubSelection() const { return sub_selection_; }

void Visualizer::SetSubSelection(size_t sub_selection) {
  sub_selection_ = sub_selection;
}

bool Visualizer::HasToggledPanels() const { return has_toggled_panels_; }

bool Visualizer::IsGameOver() const { return is_game_over_; }

void Visualizer::SetHasToggledPanels(bool has_toggled_panels) {
  has_toggled_panels_ = has_toggled_panels;
}

void Visualizer::IncrementMainSelection() { ++main_selection_; }

void Visualizer::DecrementMainSelection() { --main_selection_; }

void Visualizer::IncrementSubSelection() { ++sub_selection_; }

void Visualizer::DecrementSubSelection() { --sub_selection_; }

void Visualizer::Display() {
  if (is_game_over_) {
    DrawGameOver();
  } else {
    DrawActionPanel();
    DrawBorderBars();

    if (has_toggled_panels_) {
      DrawSubPanels();
      DrawSubInformationText();
    } else {
      DrawMap();
      DrawInformationBars();
      DrawPlayerInformationText();
      DrawMessage();
    }
  }
}

void Visualizer::UpdateMessage(const std::string& message, bool is_game_over) {
  message_ = message;
  is_game_over_ = is_game_over;
}

void Visualizer::UpdatePlayerInformationText(const Player& player) {
  size_t index = 0;
  player_information_.at(index) = "ROOM: ";
  player_information_.at(index).append(player.GetCurrentLocation());

  ++index;
  player_information_.at(index) = "HP: ";
  player_information_.at(index).append(std::to_string(player.GetHealth()));
  player_information_.at(index).append("/");
  player_information_.at(index).append(std::to_string(player.GetMaxHealth()));


  ++index;
  player_information_.at(index) = "KEYS: ";
  player_information_.at(index).append(std::to_string(player
                                                          .GetNumberOfKeys()));

  ++index;
  player_information_.at(index) = "WEAPONS: ";
  player_information_.at(index).append(std::to_string(player.GetWeapons()
                                                          .size()));
  player_information_.at(index).append("/");
  player_information_.at(index).append(std::to_string(kMaxBoxes));
}

void Visualizer::UpdateSubActionText(const std::vector<Enemy>& enemies) {
  sub_actions_.clear();

  for (const Enemy& enemy : enemies) {
    sub_actions_.push_back(enemy.GetNickname());
  }
}

void Visualizer::UpdateSubActionText(const std::vector<Weapon>& weapons,
                         size_t number_of_keys) {
  sub_actions_.clear();

  for (const Weapon& weapon : weapons) {
    sub_actions_.push_back(weapon.GetNickname());
  }

  if (number_of_keys == 1) {
    sub_actions_.emplace_back("KEY");
  }
}

void Visualizer::UpdateSubActionText(const std::vector<Door>& doors) {
  sub_actions_.clear();

  for (const Door& door : doors) {
    sub_actions_.push_back(door.GetDirection());
  }
}

void Visualizer::UpdateSubInformationText(const std::vector<Enemy>& enemies) {
  action_information_.clear();
  Enemy enemy = enemies.at(sub_selection_);

  std::string text = "NAME: ";
  text.append(enemy.GetName());
  action_information_.push_back(text);

  text = "HP: ";
  text.append(std::to_string(enemy.GetHealth()));
  action_information_.push_back(text);

  text = "STR: ";
  text.append(std::to_string(enemy.GetStrength()));
  action_information_.push_back(text);

  text = "CRIT: ";
  text.append(std::to_string(enemy.GetCriticalChance()));
  action_information_.push_back(text);
}

void Visualizer::UpdateSubInformationText(const std::vector<Weapon>& weapons) {
  action_information_.clear();
  Weapon weapon = weapons.at(sub_selection_);

  std::string text = "NAME: ";
  text.append(weapon.GetName());
  action_information_.push_back(text);

  text = "STR: ";
  text.append(std::to_string(weapon.GetStrength()));
  action_information_.push_back(text);

  text = "CRIT: ";
  text.append(std::to_string(weapon.GetCriticalChance()));
  action_information_.push_back(text);
}

void Visualizer::UpdateSubInformationText(const std::vector<Door>& doors) {
  action_information_.clear();
  Door door = doors.at(sub_selection_);

  std::string text = "ROOM: ";
  text.append(door.GetAdjacentRoom());
  action_information_.push_back(text);

  text = "LOCKED: ";
  if (door.IsLocked()) {
    text.append("TRUE");
  } else {
    text.append("FALSE");
  }
  action_information_.push_back(text);
}

void Visualizer::DrawGameOver() {
  float size = (3.0f * (float)bounds_.y) / 10.0f;
  float center_x = (1.0f * (float)bounds_.x) / 2.0f;
  float center_y = (29.0f * (float)bounds_.y) / 80.0f;

  glm::vec2 center(center_x, center_y);
  const ci::Font font("Impact", size);

  ci::gl::drawStringCentered(message_, center, ci::Color("white"), font);
}

void Visualizer::DrawActionPanel() {
  float width = (float)bounds_.x;
  float height = (7.0f * (float)bounds_.y) / 20.0f;
  float center_x = (1.0f * (float)bounds_.x) / 2.0f;
  float center_y = (33.0f * (float)bounds_.y) / 40.0f;

  ci::gl::color(ci::Color::gray(0.0625));
  DrawSolidRectangle(width, height, glm::vec2(center_x, center_y));

  DrawActionButtons(glm::vec2(center_x, center_y));
}

void Visualizer::DrawSubPanels() {
  float width = (7.0f * (float)bounds_.x) / 15.0f;
  float height = (1.0f * (float)bounds_.y) / 2.0f;
  float center_x = (1.0f * (float)bounds_.x) / 4.0f;
  float center_y = (13.0f * (float)bounds_.y) / 40.0f;

  ci::gl::color(ci::Color::gray(0.0625));
  DrawSolidRectangle(width, height, glm::vec2(center_x, center_y));

  DrawSubActionButtons(glm::vec2(center_x, center_y));

  center_x = (3.0f * (float)bounds_.x) / 4.0f;

  ci::gl::color(ci::Color::gray(0.0625));
  DrawSolidRectangle(width, height, glm::vec2(center_x, center_y));
}

void Visualizer::DrawActionButtons(const glm::vec2& panel_center) {
  std::vector<std::string> command_actions{"FIGHT", "TAKE", "DROP", "GO"};

  float width = (7.0f * (float)bounds_.x) / 40.0f;
  float height = (3.0f * (float)bounds_.y) / 20.0f;
  float center_x = panel_center.x - ((7.0f * (float)bounds_.x) / 20.0f);
  float center_y = panel_center.y;

  for (size_t button = 0; button < kMaxBoxes; ++button) {
    if (button == main_selection_) {
      ci::gl::color(ci::Color::gray(0.25));
    } else {
      ci::gl::color(ci::Color::gray(0.125));
    }

    DrawSolidRectangle(width, height, glm::vec2(center_x, center_y));
    DrawButtonText(glm::vec2(center_x, center_y), command_actions[button]);

    center_x += (7.0f * (float)bounds_.x) / 30.0f;
  }
}

void Visualizer::DrawSubActionButtons(const glm::vec2& panel_center) {
  float width = (11.0f * (float)bounds_.x) / 60.0f;
  float height = (3.0f * (float)bounds_.y) / 20.0f;
  float center_x = (17.0f * (float)bounds_.x) / 120.0f;
  float center_y = (9.0f * (float)bounds_.y) / 40.0f;

  for (size_t button = 0; button < sub_actions_.size(); ++button) {
    if (button == kMaxBoxes / 2) {
      center_x -= (13.0f * (float)bounds_.x) / 30.0f;
      center_y += (1.0f * (float)bounds_.y) / 5.0f;
    }

    if (button == sub_selection_) {
      ci::gl::color(ci::Color::gray(0.25));
    } else {
      ci::gl::color(ci::Color::gray(0.125));
    }

    DrawSolidRectangle(width, height, glm::vec2(center_x, center_y));
    DrawButtonText(glm::vec2(center_x, center_y), sub_actions_[button]);

    center_x += (13.0f * (float)bounds_.x) / 60.0f;
  }
}

void Visualizer::DrawButtonText(const glm::vec2& button_center,
                                const std::string& text) const {
  float size = (1.0f * (float)bounds_.y) / 10.0f;
  float text_adjust_y = button_center.y - ((1.0f * (float)bounds_.x) / 30.0f);

  glm::vec2 new_center(button_center.x, text_adjust_y);
  const ci::Font font("Impact", size);

  ci::gl::drawStringCentered(text, new_center, ci::Color("white"), font);
}

void Visualizer::DrawBorderBars() const {
  float width = (float)bounds_.x;
  float height = (float)bounds_.y / 20.0f;
  float center_x = (1.0f * (float)bounds_.x) / 2.0f;
  float center_y = (1.0f * (float)bounds_.y) / 40.0f;

  ci::gl::color(ci::Color::gray(0.125));
  DrawSolidRectangle(width, height, glm::vec2(center_x, center_y));

  center_y = (5.0f * (float)bounds_.y) / 8.0f;

  DrawSolidRectangle(width, height, glm::vec2(center_x, center_y));
}

void Visualizer::DrawMap() const {
  float width = (19.0f * (float)bounds_.x) / 30.0f;
  float height = (37.0f * (float)bounds_.y) / 80.0f;
  float center_x = (1.0f * (float)bounds_.x) / 2.0f;
  float center_y = (47.0f * (float)bounds_.y) / 160.0f;

  ci::gl::color(ci::Color::gray(0.0625));
  DrawSolidRectangle(width, height, glm::vec2(center_x, center_y));
}

void Visualizer::DrawInformationBars() const {
  float width = (1.0f * (float)bounds_.x) / 8.0f;
  float height = (1.0f * (float)bounds_.y) / 20.0f;
  float center_x = (1.0f * (float)bounds_.x) / 2.0f;
  float center_y = (5.0f * (float)bounds_.y) / 40.0f;

  ci::gl::color(ci::Color::gray(0.125));
  DrawSolidRectangle(width, height, glm::vec2(center_x, center_y));

  width = (1.0f * (float)bounds_.x) / 2.0f;
  height = (1.0f * (float)bounds_.y) / 20.0f;
  center_x = (1.0f * (float)bounds_.x) / 2.0f;
  center_y = (9.0f * (float)bounds_.y) / 16.0f;

  DrawSolidRectangle(width, height, glm::vec2(center_x, center_y));
}

void Visualizer::DrawPlayerInformationText() {
  float size = (49.0f * (float)bounds_.y) / 1890.0f;
  float top_x = (1.0f * (float)bounds_.x) / 2.0f;
  float top_y = (9.0f * (float)bounds_.y) / 80.0f;

  const ci::Font font("Impact", size);
  glm::vec2 top(top_x, top_y);

  size_t index = 0;

  ci::gl::drawStringCentered(player_information_.at(index), top,
                             ci::Color("white"), font);

  top.x = (22.0f * (float)bounds_.x) / 80.0f;
  top.y = (44.0f * (float)bounds_.y) / 80.0f;

  ++index;
  ci::gl::drawString(player_information_.at(index), top,
                     ci::Color("white"), font);

  top.x = (1.0f * (float)bounds_.x) / 2.0f;

  ++index;
  ci::gl::drawStringCentered(player_information_.at(index), top,
                     ci::Color("white"), font);

  top.x = (58.0f * (float)bounds_.x) / 80.0f;

  ++index;
  ci::gl::drawStringRight(player_information_.at(index), top,
                             ci::Color("white"), font);
}

void Visualizer::DrawSubInformationText() {
  float size = (1.0f * (float)bounds_.y) / 18.0f;
  float center_x = (3.0f * (float)bounds_.x) / 4.0f;
  float center_y = (7.0f * (float)bounds_.y) / 20.0f;

  center_y -= ((float)action_information_.size() * (float)bounds_.y) / 20.0f;
  glm::vec2 center(center_x, center_y);
  const ci::Font font("Impact", size);

  for (const std::string& line : action_information_) {
    ci::gl::drawStringCentered(line, center, ci::Color("white"), font);
    center.y += (1.0f * (float)bounds_.y) / 10.0f;
  }
}

void Visualizer::DrawMessage() {
  float size = (1.0f * (float)bounds_.y) / 15.0f;
  float center_x = (1.0f * (float)bounds_.x) / 2.0f;
  float center_y = (21.0f * (float)bounds_.y) / 80.0f;

  glm::vec2 center(center_x, center_y);
  const ci::Font font("Impact", size);

  ci::gl::drawStringCentered(message_, center, ci::Color("white"), font);
}

void Visualizer::DrawSolidRectangle(float width, float height,
                                    const glm::vec2& center) {
  glm::vec2 top(center.x - (width / 2.0f), center.y - (height / 2.0f));
  glm::vec2 bottom(center.x + (width / 2.0f), center.y + (height / 2.0f));

  ci::gl::drawSolidRect(ci::Rectf(top, bottom));
}

}   // namespace adventure