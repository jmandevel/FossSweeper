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

#include <fosssweeper/lcd_digit.hpp>
#include <fosssweeper/sprite.hpp>

fosssweeper::Sprite fosssweeper::getSpriteFromDigit(fosssweeper::LcdDigit digit) noexcept
{
  switch (digit)
  {
  case fosssweeper::LcdDigit::One:
    return fosssweeper::Sprite::LcdOne;
  case fosssweeper::LcdDigit::Two:
    return fosssweeper::Sprite::LcdTwo;
  case fosssweeper::LcdDigit::Three:
    return fosssweeper::Sprite::LcdThree;
  case fosssweeper::LcdDigit::Four:
    return fosssweeper::Sprite::LcdFour;
  case fosssweeper::LcdDigit::Five:
    return fosssweeper::Sprite::LcdFive;
  case fosssweeper::LcdDigit::Six:
    return fosssweeper::Sprite::LcdSix;
  case fosssweeper::LcdDigit::Seven:
    return fosssweeper::Sprite::LcdSeven;
  case fosssweeper::LcdDigit::Eight:
    return fosssweeper::Sprite::LcdEight;
  case fosssweeper::LcdDigit::Nine:
    return fosssweeper::Sprite::LcdNine;
  case fosssweeper::LcdDigit::Zero:
    return fosssweeper::Sprite::LcdZero;
  case fosssweeper::LcdDigit::Minus:
    return fosssweeper::Sprite::LcdHythen;
  default:
    return fosssweeper::Sprite::LcdNone;
  }
}

fosssweeper::Sprite fosssweeper::getDownButtonSprite(int surrounding_bombs) noexcept
{
  switch (surrounding_bombs)
  {
  case 1:
    return fosssweeper::Sprite::ButtonDownOne;
  case 2:
    return fosssweeper::Sprite::ButtonDownTwo;
  case 3:
    return fosssweeper::Sprite::ButtonDownThree;
  case 4:
    return fosssweeper::Sprite::ButtonDownFour;
  case 5:
    return fosssweeper::Sprite::ButtonDownFive;
  case 6:
    return fosssweeper::Sprite::ButtonDownSix;
  case 7:
    return fosssweeper::Sprite::ButtonDownSeven;
  case 8:
    return fosssweeper::Sprite::ButtonDownEight;
  default:
    return fosssweeper::Sprite::ButtonDown;
  }
}