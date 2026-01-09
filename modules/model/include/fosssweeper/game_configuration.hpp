// SPDX-FileCopyrightText: 2025 Free Software Foundation <licensing@fsf.org>
//
// SPDX-License-Identifier: GPL-3.0-or-later

/*
 * Copyright (c) 2025 Free Software Foundation <licensing@fsf.org>
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

#ifndef FOSSSWEEPER_GAME_CONFIGURATION_HPP
#define FOSSSWEEPER_GAME_CONFIGURATION_HPP

#include <compare>
#include <fosssweeper/game_difficulty.hpp>

namespace fosssweeper {
struct GameConfiguration {
  static const int BEGINNER_BUTTONS_WIDE;
  static const int BEGINNER_BUTTONS_TALL;
  static const int BEGINNER_BOMB_COUNT;
  static const int INTERMEDIATE_BUTTONS_WIDE;
  static const int INTERMEDIATE_BUTTONS_TALL;
  static const int INTERMEDIATE_BOMB_COUNT;
  static const int EXPERT_BUTTONS_WIDE;
  static const int EXPERT_BUTTONS_TALL;
  static const int EXPERT_BOMB_COUNT;
  static const int MIN_BUTTONS_WIDE;
  static const int MIN_BUTTONS_TALL;
  static const int MIN_BOMB_COUNT;

  fosssweeper::GameDifficulty _gameDifficulty = fosssweeper::GameDifficulty::Default;
  int _buttonsWide = fosssweeper::GameConfiguration::BEGINNER_BUTTONS_WIDE;
  int _buttonsTall = fosssweeper::GameConfiguration::BEGINNER_BUTTONS_TALL;
  int _bombCount = fosssweeper::GameConfiguration::BEGINNER_BOMB_COUNT;

  constexpr GameConfiguration() noexcept = default;
  GameConfiguration(fosssweeper::GameDifficulty game_difficulty) noexcept;
  GameConfiguration(int buttons_wide, int buttons_tall,
                    int bomb_count) noexcept;

  bool operator==(const fosssweeper::GameConfiguration &other) const noexcept;
  bool operator!=(const fosssweeper::GameConfiguration &other) const noexcept;
  std::strong_ordering
  operator<=>(const fosssweeper::GameConfiguration &other) const noexcept;

  fosssweeper::GameDifficulty getGameDifficulty() const noexcept;
  int getButtonsWide() const noexcept;
  int getButtonsTall() const noexcept;
  int getBombCount() const noexcept;
  int getButtonCount() const noexcept;
};
} // namespace fosssweeper

#endif
