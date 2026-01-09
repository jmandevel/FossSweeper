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

#include <fosssweeper/button.hpp>
#include <fosssweeper/button_state.hpp>

fosssweeper::Button::Button(char c) noexcept
{
  switch (c)
  {
  case 'd':
    this->_buttonState = fosssweeper::ButtonState::Down;
    break;
  case 'b':
    this->_hasBomb = true;
    break;
  case 'x':
    this->_buttonState = fosssweeper::ButtonState::Down;
    this->_hasBomb = true;
    break;
  case 'f':
    this->_buttonState = fosssweeper::ButtonState::Flagged;
    break;
  case 'c':
    this->_buttonState = fosssweeper::ButtonState::Flagged;
    this->_hasBomb = true;
    break;
  case 'q':
    this->_buttonState = fosssweeper::ButtonState::Questioned;
    break;
  case 'r':
    this->_buttonState = fosssweeper::ButtonState::Questioned;
    this->_hasBomb = true;
    break;
  }
}

void fosssweeper::Button::unpress() noexcept
{
  if (this->_buttonState == fosssweeper::ButtonState::Down)
  {
    this->_buttonState = fosssweeper::ButtonState::None;
  }
}

void fosssweeper::Button::press() noexcept
{
  if (this->_buttonState != fosssweeper::ButtonState::Flagged)
  {
    this->_buttonState = fosssweeper::ButtonState::Down;
  }
}

void fosssweeper::Button::altPress(bool questions_enabled) noexcept
{
  if (this->_buttonState == fosssweeper::ButtonState::None)
  {
    this->_buttonState = fosssweeper::ButtonState::Flagged;
  }
  else if (this->_buttonState == fosssweeper::ButtonState::Flagged)
  {
    if (questions_enabled)
    {
      this->_buttonState = fosssweeper::ButtonState::Questioned;
    }
    else
    {
      this->_buttonState = fosssweeper::ButtonState::None;
    }
  }
  else if (this->_buttonState == fosssweeper::ButtonState::Questioned)
  {
    this->_buttonState = fosssweeper::ButtonState::None;
  }
}

void fosssweeper::Button::removeQuestion() noexcept
{
  if (this->_buttonState == fosssweeper::ButtonState::Questioned)
  {
    this->_buttonState = fosssweeper::ButtonState::None;
  }
}

void fosssweeper::Button::setHasBomb(bool has_bomb) noexcept { this->_hasBomb = has_bomb; }

void fosssweeper::Button::setSurroundingBombs(int surrounding_bombs) noexcept
{
  this->_surroundingBombs = surrounding_bombs;
}

void fosssweeper::Button::addSurroundingBomb() noexcept { this->_surroundingBombs++; }

bool fosssweeper::Button::getIsPressable() const noexcept
{
  return this->_buttonState != fosssweeper::ButtonState::Down &&
         this->_buttonState != fosssweeper::ButtonState::Flagged;
}

bool fosssweeper::Button::getHasBomb() const noexcept { return this->_hasBomb; }

int fosssweeper::Button::getSurroundingBombs() const noexcept { return this->_surroundingBombs; }

fosssweeper::ButtonState fosssweeper::Button::getButtonState() const noexcept { return this->_buttonState; }