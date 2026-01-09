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

#ifndef FOSSSWEEPER_GAME_PANEL_HPP
#define FOSSSWEEPER_GAME_PANEL_HPP

#include <array>
#include <fosssweeper/button_position.hpp>
#include <functional>
#include <optional>

#include "desktop_timer.hpp"
#include "game_panel_state.hpp"
#include "spritesheet.hpp"
#include "wx_include.hpp"

namespace fosssweeper {
class DesktopView;

class GamePanel : public wxPanel {
public:
  std::reference_wrapper<fosssweeper::DesktopView> _desktopView;
  fosssweeper::DesktopTimer _timer;
  std::array<wxBitmap, static_cast<std::size_t>(fosssweeper::Sprite::Count)>
      _baseBitmaps;
  std::array<wxBitmap, static_cast<std::size_t>(fosssweeper::Sprite::Count)>
      _scaledBitmaps;
  fosssweeper::GamePanelState _gamePanelState;
  bool _needsRedraw = true;
  bool _timerOnly = false;
  wxBitmap &getBitmap(fosssweeper::Sprite sprite);

  GamePanel(fosssweeper::DesktopView &desktop_view, wxFrame *parent, int width,
            int height);
  virtual ~GamePanel();

  void onRender(wxPaintEvent &evt);
  void onMouseMove(wxMouseEvent &evt);
  void onLeftPress(wxMouseEvent &evt);
  void onLeftRelease(wxMouseEvent &evt);
  void onRightPress(wxMouseEvent &evt);
  void onRightRelease(wxMouseEvent &evt);
  void onMouseLeave(wxMouseEvent &evt);
  void onTimer(wxTimerEvent &evt);

  bool tryChangePixelScale(int new_pixel_scale);
  int getPixelScale() const noexcept;

  DECLARE_EVENT_TABLE();
};
} // namespace fosssweeper

#endif
