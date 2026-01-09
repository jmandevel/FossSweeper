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

#ifndef FOSSSWEEPER_BUTTON_HPP
#define FOSSSWEEPER_BUTTON_HPP

#include <fosssweeper/button_state.hpp>

namespace fosssweeper {
struct Button {
  fosssweeper::ButtonState _buttonState = fosssweeper::ButtonState::Default;
  bool _hasBomb = false;
  int _surroundingBombs = 0;

  constexpr Button() noexcept = default;
  Button(char c) noexcept;

  void unpress() noexcept;
  void press() noexcept;
  void altPress(bool questions_enabled) noexcept;
  void removeQuestion() noexcept;
  void setHasBomb(bool has_bomb) noexcept;
  void setSurroundingBombs(int surrounding_bombs) noexcept;
  void addSurroundingBomb() noexcept;
  bool getIsPressable() const noexcept;
  bool getHasBomb() const noexcept;
  int getSurroundingBombs() const noexcept;
  fosssweeper::ButtonState getButtonState() const noexcept;
};
} // namespace fosssweeper

#endif
