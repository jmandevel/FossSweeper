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

#ifndef FSWEEP_DESKTOP_MODEL_HPP
#define FSWEEP_DESKTOP_MODEL_HPP

#include <cstddef>
#include <fsweep/ButtonPosition.hpp>
#include <fsweep/GameModel.hpp>
#include <fsweep/Point.hpp>
#include <fsweep/Sprite.hpp>
#include <functional>
#include <optional>

namespace fsweep {
class Timer;

class DesktopModel {
private:
  std::reference_wrapper<fsweep::GameModel> game_model;
  std::optional<fsweep::ButtonPosition> hover_button_o = std::nullopt;
  bool left_down = false;
  bool right_down = false;
  bool hover_face = false;
  int pixel_scale = 1;

public:
  DesktopModel(fsweep::GameModel &game_model) noexcept;

  bool tryChangePixelScale(int new_pixel_scale);
  void leftPress();
  void leftRelease(fsweep::Timer &timer);
  void rightPress(fsweep::Timer &timer);
  void rightRelease(fsweep::Timer &timer);
  void mouseLeave();
  void mouseMove(int x, int y);
  int getPixelScale() const noexcept;
  int getFaceDimension() const noexcept;
  int getBorderSize() const noexcept;
  int getButtonDimension() const noexcept;
  int getLcdDigitWidth() const noexcept;
  int getHeaderHeight() const noexcept;
  fsweep::Sprite getFaceSprite() const noexcept;
  fsweep::Sprite getButtonSprite(int x, int y) const noexcept;
  fsweep::Point getFacePoint() const noexcept;
  fsweep::Point getButtonPoint(int x, int y) const noexcept;
  fsweep::Point getScorePoint(std::size_t digit) const noexcept;
  fsweep::Point getTimerPoint(std::size_t digit) const noexcept;
  fsweep::Point getSize() const noexcept;
};
} // namespace fsweep

#endif