// SPDX-FileCopyrightText: 2022 Daniel Valcour <fosssweeper@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

/*
 * Copyright (c) 2022 Daniel Valcour
 *
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

#ifndef FOSSSWEEPER_GAME_MODEL_HPP
#define FOSSSWEEPER_GAME_MODEL_HPP

#include <fosssweeper/button.hpp>
#include <fosssweeper/button_position.hpp>
#include <fosssweeper/game_configuration.hpp>
#include <fosssweeper/game_state.hpp>
#include <functional>
#include <random>
#include <stack>
#include <string>
#include <vector>

namespace fosssweeper {
struct GameModel {
  std::vector<fosssweeper::Button> _buttons = std::vector<fosssweeper::Button>(
      fosssweeper::GameConfiguration::BEGINNER_BUTTONS_WIDE *
      fosssweeper::GameConfiguration::BEGINNER_BUTTONS_TALL);
  fosssweeper::GameConfiguration _gameConfiguration = fosssweeper::GameConfiguration();
  fosssweeper::GameState _gameState = fosssweeper::GameState::Default;
  bool _questionsEnabled = false;
  int _flagCount = 0;
  int _buttonsLeft = (fosssweeper::GameConfiguration::BEGINNER_BUTTONS_WIDE *
                      fosssweeper::GameConfiguration::BEGINNER_BUTTONS_TALL) -
                     fosssweeper::GameConfiguration::BEGINNER_BOMB_COUNT;
  unsigned long _gameTime = 0;
  std::random_device _rnd = std::random_device();
  std::mt19937 _rng = std::mt19937(_rnd());
  std::vector<fosssweeper::ButtonPosition> _floodFillStack =
      std::vector<fosssweeper::ButtonPosition>();

  fosssweeper::Button &getButton(int x, int y);
  void pressButton(int x, int y);
  void floodFillClick(int x, int y);
  bool choordingPossible(int x, int y);
  void
  surroundingButtonAction(const fosssweeper::ButtonPosition &center_position,
                          std::function<void(const fosssweeper::Button &,
                                             const fosssweeper::ButtonPosition &)>
                              action);
  void placeBombs(int initial_x, int initial_y);
  void calculateSurroundingBombs();
  void tryWin() noexcept;

  GameModel() noexcept = default;
  GameModel(fosssweeper::GameConfiguration game_configuration,
            bool questions_enabled, fosssweeper::GameState game_state, int game_time,
            std::string_view button_string);

  void newGame();
  void newGame(fosssweeper::GameConfiguration game_configuration);
  void clickButton(int x, int y);
  void altClickButton(int x, int y);
  void areaClickButton(int x, int y);
  void setQuestionsEnabled(bool questions_enabled);
  bool getQuestionsEnabled() const noexcept;
  int getFlagCount() const noexcept;
  int getBombsLeft() const noexcept;
  int getButtonsLeft() const noexcept;
  void updateTime(unsigned int game_time);
  fosssweeper::GameState getGameState() const noexcept;
  fosssweeper::GameConfiguration getGameConfiguration() const noexcept;
  unsigned long getGameTime() const noexcept;
  unsigned long getTimerSeconds() const noexcept;
  const fosssweeper::Button &getButton(int x, int y) const;
  const std::vector<fosssweeper::Button> &getButtons() const noexcept;
};
} // namespace fosssweeper

#endif
