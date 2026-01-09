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

#ifndef FOSSSWEEPER_DESKTOP_MODEL_HPP
#define FOSSSWEEPER_DESKTOP_MODEL_HPP

#include <cstddef>
#include <fosssweeper/button_position.hpp>
#include <fosssweeper/game_model.hpp>
#include <fosssweeper/point.hpp>
#include <fosssweeper/sprite.hpp>
#include <functional>
#include <optional>

namespace fosssweeper {
class Timer;

struct DesktopModel {
  std::reference_wrapper<fosssweeper::GameModel> _gameModel;
  std::optional<fosssweeper::ButtonPosition> _hoverButtonO = std::nullopt;
  bool _leftDown = false;
  bool _rightDown = false;
  bool _hoverFace = false;
  int _pixelScale = 2;

  DesktopModel(fosssweeper::GameModel &game_model) noexcept;

  bool tryChangePixelScale(int new_pixel_scale);
  void leftPress();
  void leftRelease(fosssweeper::Timer &timer);
  void rightPress(fosssweeper::Timer &timer);
  void rightRelease(fosssweeper::Timer &timer);
  void mouseLeave();
  void mouseMove(int x, int y);
  int getPixelScale() const noexcept;
  int getFaceDimension() const noexcept;
  int getBorderSize() const noexcept;
  int getButtonDimension() const noexcept;
  int getLcdDigitWidth() const noexcept;
  int getHeaderHeight() const noexcept;
  fosssweeper::Sprite getFaceSprite() const noexcept;
  fosssweeper::Sprite getButtonSprite(int x, int y) const noexcept;
  fosssweeper::Point getFacePoint() const noexcept;
  fosssweeper::Point getButtonPoint(int x, int y) const noexcept;
  fosssweeper::Point getScorePoint(std::size_t digit) const noexcept;
  fosssweeper::Point getTimerPoint(std::size_t digit) const noexcept;
  fosssweeper::Point getSize() const noexcept;
};
} // namespace fosssweeper

#endif