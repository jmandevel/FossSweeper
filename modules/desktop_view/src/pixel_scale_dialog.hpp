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

#ifndef FOSSSWEEPER_PIXEL_SCALE_DIALOG_HPP
#define FOSSSWEEPER_PIXEL_SCALE_DIALOG_HPP

#include <wx/spinctrl.h>

#include "wx_include.hpp"

namespace fosssweeper {
struct PixelScaleDialog : public wxDialog {
  int _pixelScale = 1;

  wxSpinCtrl *_pixelScaleCtrl = nullptr;

  PixelScaleDialog(wxWindow *parent, int pixel_scale);

  void onConfirm(wxCommandEvent &e);
  void onCancel(wxCommandEvent &e);

  int getPixelScale() const noexcept;
};
} // namespace fosssweeper

#endif