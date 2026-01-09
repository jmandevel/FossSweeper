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

#include <cstddef>
#include <fosssweeper/lcd_number.hpp>
#include <stdexcept>

fosssweeper::LcdNumber::LcdNumber(const int number) : _number(number)
{
  if (number >= 999)
  {
    this->_digits[0] = fosssweeper::LcdDigit::Nine;
    this->_digits[1] = fosssweeper::LcdDigit::Nine;
    this->_digits[2] = fosssweeper::LcdDigit::Nine;
  }
  else if (number <= -99)
  {
    this->_digits[0] = fosssweeper::LcdDigit::Minus;
    this->_digits[1] = fosssweeper::LcdDigit::Nine;
    this->_digits[2] = fosssweeper::LcdDigit::Nine;
  }
  else if (number < -9)
  {
    this->_digits[0] = fosssweeper::LcdDigit::Minus;
    const int tens = (number / -10);
    this->_digits[1] = static_cast<fosssweeper::LcdDigit>(tens);
    const int ones = -(number % 10);
    this->_digits[2] = static_cast<fosssweeper::LcdDigit>(ones);
  }
  else if (number < 0)
  {
    this->_digits[0] = fosssweeper::LcdDigit::None;
    this->_digits[1] = fosssweeper::LcdDigit::Minus;
    const int ones = -number;
    this->_digits[2] = static_cast<fosssweeper::LcdDigit>(ones);
  }
  else if (number < 10)
  {
    this->_digits[0] = fosssweeper::LcdDigit::None;
    this->_digits[1] = fosssweeper::LcdDigit::None;
    const int ones = number;
    this->_digits[2] = static_cast<fosssweeper::LcdDigit>(number);
  }
  else if (number < 100)
  {
    this->_digits[0] = fosssweeper::LcdDigit::None;
    const int tens = number / 10;
    this->_digits[1] = static_cast<fosssweeper::LcdDigit>(tens);
    const int ones = number - (tens * 10);
    this->_digits[2] = static_cast<fosssweeper::LcdDigit>(ones);
  }
  else  // if (number < 999)
  {
    const int hundreds = number / 100;
    this->_digits[0] = static_cast<fosssweeper::LcdDigit>(hundreds);
    const int tens = (number % 100) / 10;
    this->_digits[1] = static_cast<fosssweeper::LcdDigit>(tens);
    const int ones = (number % 10);
    this->_digits[2] = static_cast<fosssweeper::LcdDigit>(ones);
  }
}

fosssweeper::LcdDigit fosssweeper::LcdNumber::operator[](std::size_t digit_i) const
{
  if (digit_i > 3)
  {
    throw std::out_of_range("number index out of range");
  }
  return this->_digits[digit_i];
}

int fosssweeper::LcdNumber::getNumber() const noexcept { return this->_number; }