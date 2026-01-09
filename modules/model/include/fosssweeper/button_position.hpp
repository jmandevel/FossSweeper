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

#ifndef FOSSSWEEPER_BUTTON_POSITION_H
#define FOSSSWEEPER_BUTTON_POSITION_H

#include <cmath>
#include <cstddef>

namespace fosssweeper {
struct ButtonPosition {
  int x, y;

  constexpr ButtonPosition() noexcept : x(-1), y(-1) {}

  constexpr ButtonPosition(const int x, const int y) noexcept : x(x), y(y) {}

  constexpr bool hasLeft() const noexcept { return this->x > 0; }

  constexpr bool hasRight(const int buttons_wide) const noexcept {
    return this->x < buttons_wide - 1;
  }

  constexpr bool hasUp() const noexcept { return this->y > 0; }

  constexpr bool hasDown(const int buttons_tall) const noexcept {
    return this->y < buttons_tall - 1;
  }

  constexpr bool hasLeftUp() const noexcept {
    return this->x > 0 && this->y > 0;
  }

  constexpr bool hasLeftDown(const int buttons_tall) const noexcept {
    return this->x > 0 && this->y < buttons_tall - 1;
  }

  constexpr bool hasRightUp(const int buttons_wide) const noexcept {
    return this->x < buttons_wide - 1 && this->y > 0;
  }

  constexpr bool hasRightDown(const int buttons_wide,
                              const int buttons_tall) const noexcept {
    return this->x < buttons_wide - 1 && this->y < buttons_tall - 1;
  }

  constexpr fosssweeper::ButtonPosition getLeft() const noexcept {
    return fosssweeper::ButtonPosition(this->x - 1, this->y);
  }

  constexpr fosssweeper::ButtonPosition getRight() const noexcept {
    return fosssweeper::ButtonPosition(this->x + 1, this->y);
  }

  constexpr fosssweeper::ButtonPosition getUp() const noexcept {
    return fosssweeper::ButtonPosition(this->x, this->y - 1);
  }

  constexpr fosssweeper::ButtonPosition getDown() const noexcept {
    return fosssweeper::ButtonPosition(this->x, this->y + 1);
  }

  constexpr fosssweeper::ButtonPosition getLeftUp() const noexcept {
    return fosssweeper::ButtonPosition(this->x - 1, this->y - 1);
  }

  constexpr fosssweeper::ButtonPosition getLeftDown() const noexcept {
    return fosssweeper::ButtonPosition(this->x - 1, this->y + 1);
  }

  constexpr fosssweeper::ButtonPosition getRightUp() const noexcept {
    return fosssweeper::ButtonPosition(this->x + 1, this->y - 1);
  }

  constexpr fosssweeper::ButtonPosition getRightDown() const noexcept {
    return fosssweeper::ButtonPosition(this->x + 1, this->y + 1);
  }

  constexpr std::size_t getIndex(const int buttons_wide) const noexcept {
    return static_cast<std::size_t>((buttons_wide * this->y) + this->x);
  }

  constexpr bool operator==(const ButtonPosition &other) const noexcept {
    return (this->x == other.x) && (this->y == other.y);
  }

  constexpr bool operator!=(const ButtonPosition &other) const noexcept {
    return (this->x != other.x) || (this->y != other.y);
  }

  bool isNear(const fosssweeper::ButtonPosition &other) const noexcept {
    return (std::abs(this->x - other.x) <= 1) &&
           (std::abs(this->y - other.y) <= 1);
  }
};
} // namespace fosssweeper

#endif
