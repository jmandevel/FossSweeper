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

#include <fsweep/Button.hpp>
#include <fsweep/ButtonState.hpp>

fsweep::Button::Button(char c) noexcept
{
  switch (c)
  {
  case 'd':
    this->button_state = fsweep::ButtonState::Down;
    break;
  case 'b':
    this->has_bomb = true;
    break;
  case 'x':
    this->button_state = fsweep::ButtonState::Down;
    this->has_bomb = true;
    break;
  case 'f':
    this->button_state = fsweep::ButtonState::Flagged;
    break;
  case 'c':
    this->button_state = fsweep::ButtonState::Flagged;
    this->has_bomb = true;
    break;
  case 'q':
    this->button_state = fsweep::ButtonState::Questioned;
    break;
  case 'r':
    this->button_state = fsweep::ButtonState::Questioned;
    this->has_bomb = true;
    break;
  }
}

void fsweep::Button::unpress() noexcept
{
  if (this->button_state == fsweep::ButtonState::Down)
  {
    this->button_state = fsweep::ButtonState::None;
  }
}

void fsweep::Button::press() noexcept
{
  if (this->button_state != fsweep::ButtonState::Flagged)
  {
    this->button_state = fsweep::ButtonState::Down;
  }
}

void fsweep::Button::altPress(bool questions_enabled) noexcept
{
  if (this->button_state == fsweep::ButtonState::None)
  {
    this->button_state = fsweep::ButtonState::Flagged;
  }
  else if (this->button_state == fsweep::ButtonState::Flagged)
  {
    if (questions_enabled)
    {
      this->button_state = fsweep::ButtonState::Questioned;
    }
    else
    {
      this->button_state = fsweep::ButtonState::None;
    }
  }
  else if (this->button_state == fsweep::ButtonState::Questioned)
  {
    this->button_state = fsweep::ButtonState::None;
  }
}

void fsweep::Button::removeQuestion() noexcept
{
  if (this->button_state == fsweep::ButtonState::Questioned)
  {
    this->button_state = fsweep::ButtonState::None;
  }
}

void fsweep::Button::setHasBomb(bool has_bomb) noexcept { this->has_bomb = has_bomb; }

void fsweep::Button::setSurroundingBombs(int surrounding_bombs) noexcept
{
  this->surrounding_bombs = surrounding_bombs;
}

void fsweep::Button::addSurroundingBomb() noexcept { this->surrounding_bombs++; }

bool fsweep::Button::getIsPressable() const noexcept
{
  return this->button_state != fsweep::ButtonState::Down &&
         this->button_state != fsweep::ButtonState::Flagged;
}

bool fsweep::Button::getHasBomb() const noexcept { return this->has_bomb; }

int fsweep::Button::getSurroundingBombs() const noexcept { return this->surrounding_bombs; }

fsweep::ButtonState fsweep::Button::getButtonState() const noexcept { return this->button_state; }