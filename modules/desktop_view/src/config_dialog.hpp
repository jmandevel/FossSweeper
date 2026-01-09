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

#ifndef FOSSSWEEPER_CONFIG_DIALOG_HPP
#define FOSSSWEEPER_CONFIG_DIALOG_HPP

#include <wx/spinctrl.h>

#include <fosssweeper/game_configuration.hpp>

#include "wx_include.hpp"

namespace fosssweeper {
class ConfigDialog : public wxDialog {
public:
  int _buttonsWide = fosssweeper::GameConfiguration::BEGINNER_BUTTONS_WIDE;
  int _buttonsTall = fosssweeper::GameConfiguration::BEGINNER_BUTTONS_TALL;
  int _bombCount = fosssweeper::GameConfiguration::BEGINNER_BOMB_COUNT;

  wxSpinCtrl *_buttonsWideCtrl = nullptr;
  wxSpinCtrl *_buttonsTallCtrl = nullptr;
  wxSpinCtrl *_bombsCtrl = nullptr;
  wxStaticText *_invalidValueText = nullptr;

  ConfigDialog(wxWindow *parent);

  void onConfirm(wxCommandEvent &e);
  void onCancel(wxCommandEvent &e);

  int getButtonsWide() const noexcept;
  int getButtonsTall() const noexcept;
  int getBombCount() const noexcept;
};
} // namespace fosssweeper

#endif
