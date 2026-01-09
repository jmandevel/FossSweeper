// SPDX-FileCopyrightText: 2022 Daniel Valcour <fosssweeper@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

/*
 * Copyright (c) 2022 Daniel Valcour
 *model
 * This file is part of FossSweeper.
 *
 * FossSweeper is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * FossSweeper is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * FossSweeper. If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include <algorithm>
#include <cstddef>
#include <fosssweeper/button_position.hpp>
#include <fosssweeper/game_model.hpp>
#include <fosssweeper/timer.hpp>
#include <stdexcept>
#include <string>

fosssweeper::GameModel::GameModel(
    fosssweeper::GameConfiguration game_configuration, bool questions_enabled,
    fosssweeper::GameState game_state, int game_time,
    std::string_view button_string)
    : _gameConfiguration(game_configuration), _flagCount(0),
      _gameTime(game_time), _buttonsLeft(game_configuration.getButtonCount() -
                                         game_configuration.getBombCount()),
      _questionsEnabled(questions_enabled), _buttons(), _gameState(game_state) {
  if (button_string.length() != game_configuration.getButtonCount()) {
    throw std::runtime_error("invalid button string length");
  }
  this->_buttons.reserve(game_configuration.getButtonCount());
  for (std::size_t button_i = 0; button_i < game_configuration.getButtonCount();
       button_i++) {
    this->_buttons.emplace_back(button_string[button_i]);
    const auto &button = this->_buttons.back();
    if (button.getButtonState() == fosssweeper::ButtonState::Flagged) {
      this->_flagCount++;
    }
    if (button.getButtonState() == fosssweeper::ButtonState::Down) {
      this->_buttonsLeft--;
    }
  }
  this->calculateSurroundingBombs();
}

fosssweeper::Button &fosssweeper::GameModel::getButton(int x, int y) {
  const fosssweeper::ButtonPosition position(x, y);
  return this
      ->_buttons[position.getIndex(this->_gameConfiguration.getButtonsWide())];
}

void fosssweeper::GameModel::pressButton(int x, int y) {
  auto &button = this->getButton(x, y);
  if (button.getIsPressable()) {
    if (button.getHasBomb()) {
      button.press();
      this->_gameState = fosssweeper::GameState::Dead;
    } else {
      this->floodFillClick(x, y);
    }
  }
}

void fosssweeper::GameModel::floodFillClick(int x, int y) {
  const fosssweeper::ButtonPosition start_position(x, y);
  const auto buttons_wide = this->_gameConfiguration.getButtonsWide();
  const auto buttons_tall = this->_gameConfiguration.getButtonsTall();
  this->_floodFillStack.clear();
  this->_floodFillStack.push_back(start_position);
  do {
    const auto cur_position = this->_floodFillStack.back();
    this->_floodFillStack.pop_back();
    auto &cur_button = this->getButton(cur_position.x, cur_position.y);
    cur_button.press();
    this->_buttonsLeft--;
    if (cur_button.getSurroundingBombs() == 0) {
      this->surroundingButtonAction(
          cur_position, [&](const fosssweeper::Button &button,
                            const fosssweeper::ButtonPosition &position) {
            if (button.getIsPressable() &&
                std::find(this->_floodFillStack.begin(),
                          this->_floodFillStack.end(),
                          position) == this->_floodFillStack.end()) {
              this->_floodFillStack.push_back(position);
            }
          });
    }
  } while (!this->_floodFillStack.empty());
}

bool fosssweeper::GameModel::choordingPossible(int x, int y) {
  const auto &button = this->getButton(x, y);
  if (button.getButtonState() != fosssweeper::ButtonState::Down)
    return false;
  auto surrounding_flags = 0;
  this->surroundingButtonAction(
      fosssweeper::ButtonPosition(x, y),
      [&](const fosssweeper::Button &button,
          const fosssweeper::ButtonPosition position) {
        if (button.getButtonState() == fosssweeper::ButtonState::Flagged) {
          surrounding_flags++;
        }
      });
  return surrounding_flags == button.getSurroundingBombs();
}

void fosssweeper::GameModel::surroundingButtonAction(
    const fosssweeper::ButtonPosition &center_position,
    std::function<void(const fosssweeper::Button &,
                       const fosssweeper::ButtonPosition &)>
        action) {
  const auto buttons_wide = this->_gameConfiguration.getButtonsWide();
  const auto buttons_tall = this->_gameConfiguration.getButtonsTall();
  if (center_position.hasLeftUp()) {
    const auto left_up_position = center_position.getLeftUp();
    auto &left_up_button =
        this->getButton(left_up_position.x, left_up_position.y);
    action(left_up_button, left_up_position);
  }
  if (center_position.hasUp()) {
    const auto up_position = center_position.getUp();
    auto &up_button = this->getButton(up_position.x, up_position.y);
    action(up_button, up_position);
  }
  if (center_position.hasRightUp(buttons_wide)) {
    const auto right_up_position = center_position.getRightUp();
    auto &right_up_button =
        this->getButton(right_up_position.x, right_up_position.y);
    action(right_up_button, right_up_position);
  }
  if (center_position.hasLeft()) {
    const auto left_position = center_position.getLeft();
    auto &left_button = this->getButton(left_position.x, left_position.y);
    action(left_button, left_position);
  }
  if (center_position.hasRight(buttons_wide)) {
    const auto right_position = center_position.getRight();
    auto &right_button = this->getButton(right_position.x, right_position.y);
    action(right_button, right_position);
  }
  if (center_position.hasLeftDown(buttons_tall)) {
    const auto left_down_position = center_position.getLeftDown();
    auto &left_down_button =
        this->getButton(left_down_position.x, left_down_position.y);
    action(left_down_button, left_down_position);
  }
  if (center_position.hasDown(buttons_tall)) {
    const auto down_position = center_position.getDown();
    auto &down_button = this->getButton(down_position.x, down_position.y);
    action(down_button, down_position);
  }
  if (center_position.hasRightDown(buttons_wide, buttons_tall)) {
    const auto right_down_position = center_position.getRightDown();
    auto &right_down_button =
        this->getButton(right_down_position.x, right_down_position.y);
    action(right_down_button, right_down_position);
  }
}

void fosssweeper::GameModel::placeBombs(int initial_x, int initial_y) {
  const auto bomb_count = this->_gameConfiguration.getBombCount();
  for (auto &button : this->_buttons) {
    button.setHasBomb(false);
    button.unpress();
  }
  std::vector<bool> bombs(this->_gameConfiguration.getButtonCount());
  for (std::size_t button_i = 0; button_i < bomb_count; button_i++) {
    bombs[button_i] = true;
  }
  if (bomb_count == this->_buttons.size()) {
    for (auto &cur_button : this->_buttons) {
      cur_button.setSurroundingBombs(8);
    }
    return;
  }
  const auto last_minable_button_i = this->_buttons.size() - 2;
  std::uniform_int_distribution<std::mt19937::result_type> distributor(
      0, last_minable_button_i);
  for (std::size_t button_i = 0; button_i <= last_minable_button_i;
       button_i++) {
    const std::size_t swap_i = static_cast<std::size_t>(distributor(this->_rng));
    // vector of bool are weird, std::swap doesn't work.
    bool temp = bombs[button_i];
    bombs[button_i] = bombs[swap_i];
    bombs[swap_i] = temp;
  }
  const fosssweeper::ButtonPosition initial_position(initial_x, initial_y);
  const std::size_t initial_i =
      initial_position.getIndex(this->_gameConfiguration.getButtonsWide());
  const std::size_t swap_i = bombs.size() - 1;
  bool temp = bombs[initial_i];
  bombs[initial_i] = bombs[swap_i];
  bombs[swap_i] = temp;
  for (std::size_t button_i = 0; button_i < this->_buttons.size(); button_i++) {
    if (bombs[button_i]) {
      this->_buttons[button_i].setHasBomb(true);
    }
  }
  this->calculateSurroundingBombs();
}

void fosssweeper::GameModel::calculateSurroundingBombs() {
  const auto buttons_wide = this->_gameConfiguration.getButtonsWide();
  const auto buttons_tall = this->_gameConfiguration.getButtonsTall();
  for (int x = 0; x < buttons_wide; x++) {
    for (int y = 0; y < buttons_tall; y++) {
      const fosssweeper::ButtonPosition cur_button_position(x, y);
      auto &cur_button = this->getButton(x, y);
      this->surroundingButtonAction(
          cur_button_position,
          [&](const fosssweeper::Button &button,
              const fosssweeper::ButtonPosition &position) {
            if (button.getHasBomb()) {
              cur_button.addSurroundingBomb();
            }
          });
    }
  }
}

void fosssweeper::GameModel::tryWin() noexcept {
  if (this->_buttonsLeft <= 0) {
    this->_gameState = fosssweeper::GameState::Cool;
  }
}

void fosssweeper::GameModel::newGame() {
  if (this->_gameState != fosssweeper::GameState::None) {
    std::fill(this->_buttons.begin(), this->_buttons.end(),
              fosssweeper::Button());
  }
  this->_gameTime = 0;
  this->_gameState = fosssweeper::GameState::None;
  this->_flagCount = 0;
  this->_buttonsLeft = this->_gameConfiguration.getButtonCount() -
                       this->_gameConfiguration.getBombCount();
}

void fosssweeper::GameModel::newGame(
    fosssweeper::GameConfiguration game_configuration) {
  if (this->_gameConfiguration != game_configuration) {
    const std::size_t button_count = game_configuration.getButtonCount();
    this->_gameConfiguration = game_configuration;
    this->_buttons.clear();
    this->_buttons.resize(button_count);
    this->_floodFillStack.reserve(button_count);
    this->_gameTime = 0;
    this->_gameState = fosssweeper::GameState::None;
    this->_flagCount = 0;
    this->_buttonsLeft = this->_gameConfiguration.getButtonCount() -
                         this->_gameConfiguration.getBombCount();
  } else {
    this->newGame();
  }
}

void fosssweeper::GameModel::clickButton(int x, int y) {
  if (this->_gameState != fosssweeper::GameState::Playing &&
      this->_gameState != fosssweeper::GameState::None)
    return;
  const auto &button = this->getButton(x, y);
  if (button.getButtonState() == fosssweeper::ButtonState::Flagged)
    return;
  if (this->_gameState == fosssweeper::GameState::None) {
    this->placeBombs(x, y);
    this->_gameState = fosssweeper::GameState::Playing;
  }
  this->pressButton(x, y);
  if (this->_gameConfiguration.getBombCount() ==
      this->_gameConfiguration.getButtonCount()) {
    this->_gameState = fosssweeper::GameState::Dead;
  }
  this->tryWin();
}

void fosssweeper::GameModel::altClickButton(int x, int y) {
  if (this->_gameState == fosssweeper::GameState::Dead ||
      this->_gameState == fosssweeper::GameState::Cool)
    return;
  auto &button = this->getButton(x, y);
  if (button.getButtonState() == fosssweeper::ButtonState::Flagged) {
    this->_flagCount--;
  }
  button.altPress(this->_questionsEnabled);
  if (button.getButtonState() == fosssweeper::ButtonState::Flagged) {
    this->_flagCount++;
  }
}

void fosssweeper::GameModel::areaClickButton(int x, int y) {
  if (this->_gameState == fosssweeper::GameState::Dead ||
      this->_gameState == fosssweeper::GameState::Cool)
    return;
  if (!this->choordingPossible(x, y))
    return;
  const auto buttons_wide = this->_gameConfiguration.getButtonsWide();
  const auto buttons_tall = this->_gameConfiguration.getButtonsTall();
  const fosssweeper::ButtonPosition center_position(x, y);
  auto &center_button = this->getButton(center_position.x, center_position.y);
  if (center_button.getIsPressable()) {
    this->pressButton(center_position.x, center_position.y);
  }
  this->surroundingButtonAction(
      center_position, [&](const fosssweeper::Button &button,
                           const fosssweeper::ButtonPosition &position) {
        if (button.getIsPressable()) {
          this->pressButton(position.x, position.y);
        }
      });
  this->tryWin();
}

void fosssweeper::GameModel::setQuestionsEnabled(bool questions_enabled) {
  if (this->_questionsEnabled == questions_enabled)
    return;
  if (!questions_enabled) {
    for (auto &button : this->_buttons) {
      button.removeQuestion();
    }
  }
  this->_questionsEnabled = questions_enabled;
}

bool fosssweeper::GameModel::getQuestionsEnabled() const noexcept {
  return this->_questionsEnabled;
}

int fosssweeper::GameModel::getFlagCount() const noexcept {
  return this->_flagCount;
}

int fosssweeper::GameModel::getBombsLeft() const noexcept {
  return this->_gameConfiguration.getBombCount() - this->_flagCount;
}

int fosssweeper::GameModel::getButtonsLeft() const noexcept {
  return this->_buttonsLeft;
}

fosssweeper::GameState fosssweeper::GameModel::getGameState() const noexcept {
  return this->_gameState;
}

fosssweeper::GameConfiguration
fosssweeper::GameModel::getGameConfiguration() const noexcept {
  return this->_gameConfiguration;
}

void fosssweeper::GameModel::updateTime(unsigned int game_time) {
  if (this->_gameState == fosssweeper::GameState::Playing) {
    this->_gameTime = game_time;
  }
}

unsigned long fosssweeper::GameModel::getGameTime() const noexcept {
  return this->_gameTime;
}

const unsigned long MILLISECONDS_PER_SECOND = 1000;

unsigned long fosssweeper::GameModel::getTimerSeconds() const noexcept {
  return this->_gameTime / MILLISECONDS_PER_SECOND;
}

const fosssweeper::Button &fosssweeper::GameModel::getButton(int x,
                                                             int y) const {
  const fosssweeper::ButtonPosition position(x, y);
  return this->_buttons.at(
      position.getIndex(this->_gameConfiguration.getButtonsWide()));
}

const std::vector<fosssweeper::Button> &
fosssweeper::GameModel::getButtons() const noexcept {
  return this->_buttons;
}