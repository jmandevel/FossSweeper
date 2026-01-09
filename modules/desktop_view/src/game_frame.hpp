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

#ifndef FOSSSWEEPER_GAME_FRAME_HPP
#define FOSSSWEEPER_GAME_FRAME_HPP

#include <fosssweeper/desktop_model.hpp>
#include <functional>

#include "wx_include.hpp"

namespace fosssweeper {
class DesktopView;
class GamePanel;

class GameFrame : public wxFrame {
public:
  std::reference_wrapper<fosssweeper::DesktopView> _view;
  wxMenuItem *_beginnerItem;
  wxMenuItem *_intermediateItem;
  wxMenuItem *_expertItem;
  wxMenuItem *_questionMarksItem;
  fosssweeper::GamePanel *_gamePanel;

  void resizeGamePanel(int x, int y);

  GameFrame(fosssweeper::DesktopView &view);

  void onNew(wxCommandEvent &e);
  void onBeginner(wxCommandEvent &e);
  void onIntermediate(wxCommandEvent &e);
  void onExpert(wxCommandEvent &e);
  void onCustom(wxCommandEvent &e);
  void onPixelScale(wxCommandEvent &e);
  void onQuestionMarks(wxCommandEvent &e);
  void onExit(wxCommandEvent &e);
  void onCredits(wxCommandEvent &e);
  void onLicense(wxCommandEvent &e);
  void onAbout(wxCommandEvent &e);

  DECLARE_EVENT_TABLE()
};
} // namespace fosssweeper

#endif
