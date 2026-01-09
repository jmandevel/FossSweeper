// SPDX-FileCopyrightText: 2022 Daniel Valcour <fosssweeper@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

/*
 * Copyright (c) 2022 Daniel Valcour
 *
 * This file is part of FossSweeper.
 *
 * FossSweeper is free software: you can redistribute it and/or modify it under the terms of the GNU
 * General Public License as published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * FossSweeper is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
 * even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with FossSweeper. If not,
 * see <https://www.gnu.org/licenses/>.
 *
 */

#include <algorithm>
#include <fosssweeper/game_configuration.hpp>

const int fosssweeper::GameConfiguration::BEGINNER_BUTTONS_WIDE = 8;
const int fosssweeper::GameConfiguration::BEGINNER_BUTTONS_TALL = 8;
const int fosssweeper::GameConfiguration::BEGINNER_BOMB_COUNT = 10;
const int fosssweeper::GameConfiguration::INTERMEDIATE_BUTTONS_WIDE = 16;
const int fosssweeper::GameConfiguration::INTERMEDIATE_BUTTONS_TALL = 16;
const int fosssweeper::GameConfiguration::INTERMEDIATE_BOMB_COUNT = 40;
const int fosssweeper::GameConfiguration::EXPERT_BUTTONS_WIDE = 30;
const int fosssweeper::GameConfiguration::EXPERT_BUTTONS_TALL = 16;
const int fosssweeper::GameConfiguration::EXPERT_BOMB_COUNT = 99;
const int fosssweeper::GameConfiguration::MIN_BUTTONS_WIDE = 8;
const int fosssweeper::GameConfiguration::MIN_BUTTONS_TALL = 1;
const int fosssweeper::GameConfiguration::MIN_BOMB_COUNT = 0;

fosssweeper::GameConfiguration::GameConfiguration(fosssweeper::GameDifficulty game_difficulty) noexcept
{
  switch (game_difficulty)
  {
  case fosssweeper::GameDifficulty::Intermediate:
    this->_buttonsWide = fosssweeper::GameConfiguration::INTERMEDIATE_BUTTONS_WIDE;
    this->_buttonsTall = fosssweeper::GameConfiguration::INTERMEDIATE_BUTTONS_TALL;
    this->_bombCount = fosssweeper::GameConfiguration::INTERMEDIATE_BOMB_COUNT;
    this->_gameDifficulty = game_difficulty;
    break;
  case fosssweeper::GameDifficulty::Expert:
    this->_buttonsWide = fosssweeper::GameConfiguration::EXPERT_BUTTONS_WIDE;
    this->_buttonsTall = fosssweeper::GameConfiguration::EXPERT_BUTTONS_TALL;
    this->_bombCount = fosssweeper::GameConfiguration::EXPERT_BOMB_COUNT;
    this->_gameDifficulty = game_difficulty;
    break;
  case fosssweeper::GameDifficulty::Beginner:
  default:
    this->_buttonsWide = fosssweeper::GameConfiguration::BEGINNER_BUTTONS_WIDE;
    this->_buttonsTall = fosssweeper::GameConfiguration::BEGINNER_BUTTONS_TALL;
    this->_bombCount = fosssweeper::GameConfiguration::BEGINNER_BOMB_COUNT;
    this->_gameDifficulty = fosssweeper::GameDifficulty::Beginner;
    break;
  }
}

fosssweeper::GameConfiguration::GameConfiguration(int buttons_wide, int buttons_tall,
                                             int bomb_count) noexcept
{
  if (buttons_wide == fosssweeper::GameConfiguration::BEGINNER_BUTTONS_WIDE &&
      buttons_tall == fosssweeper::GameConfiguration::BEGINNER_BUTTONS_TALL &&
      bomb_count == fosssweeper::GameConfiguration::BEGINNER_BOMB_COUNT)
  {
    this->_gameDifficulty = fosssweeper::GameDifficulty::Beginner;
  }
  else if (buttons_wide == fosssweeper::GameConfiguration::INTERMEDIATE_BUTTONS_WIDE &&
           buttons_tall == fosssweeper::GameConfiguration::INTERMEDIATE_BUTTONS_TALL &&
           bomb_count == fosssweeper::GameConfiguration::INTERMEDIATE_BOMB_COUNT)
  {
    this->_gameDifficulty = fosssweeper::GameDifficulty::Intermediate;
  }
  else if (buttons_wide == fosssweeper::GameConfiguration::EXPERT_BUTTONS_WIDE &&
           buttons_tall == fosssweeper::GameConfiguration::EXPERT_BUTTONS_TALL &&
           bomb_count == fosssweeper::GameConfiguration::EXPERT_BOMB_COUNT)
  {
    this->_gameDifficulty = fosssweeper::GameDifficulty::Expert;
  }
  else
  {
    this->_gameDifficulty = fosssweeper::GameDifficulty::Custom;
  }
  this->_buttonsWide = std::max(buttons_wide, fosssweeper::GameConfiguration::MIN_BUTTONS_WIDE);
  this->_buttonsTall = std::max(buttons_tall, fosssweeper::GameConfiguration::MIN_BUTTONS_TALL);
  const int button_count = this->_buttonsWide * this->_buttonsTall;
  this->_bombCount =
      std::clamp(bomb_count, fosssweeper::GameConfiguration::MIN_BOMB_COUNT, button_count);
}

bool fosssweeper::GameConfiguration::operator==(const fosssweeper::GameConfiguration& other) const noexcept
{
  if (this->_gameDifficulty != fosssweeper::GameDifficulty::Custom &&
      other._gameDifficulty != fosssweeper::GameDifficulty::Custom)
  {
    return this->_gameDifficulty == other._gameDifficulty;
  }
  return this->_buttonsWide == other._buttonsWide && this->_buttonsTall == other._buttonsTall &&
         this->_bombCount == other._bombCount;
}

bool fosssweeper::GameConfiguration::operator!=(const fosssweeper::GameConfiguration& other) const noexcept
{
  return !this->operator==(other);
}

std::strong_ordering fosssweeper::GameConfiguration::operator<=>(
    const fosssweeper::GameConfiguration& other) const noexcept
{
  if (this->_gameDifficulty == other._gameDifficulty)
  {
    return this->_buttonsWide * this->_buttonsTall <=> other._buttonsWide * other._buttonsTall;
  }
  return static_cast<int>(this->_gameDifficulty) <=> static_cast<int>(other._gameDifficulty);
}

fosssweeper::GameDifficulty fosssweeper::GameConfiguration::getGameDifficulty() const noexcept
{
  return this->_gameDifficulty;
}

int fosssweeper::GameConfiguration::getButtonsWide() const noexcept { return this->_buttonsWide; }

int fosssweeper::GameConfiguration::getButtonsTall() const noexcept { return this->_buttonsTall; }

int fosssweeper::GameConfiguration::getBombCount() const noexcept { return this->_bombCount; }

int fosssweeper::GameConfiguration::getButtonCount() const noexcept
{
  return static_cast<std::size_t>(this->_buttonsWide * this->_buttonsTall);
}
