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

#ifndef FOSSSWEEPER_DESKTOP_APP_HPP
#define FOSSSWEEPER_DESKTOP_APP_HPP

#include <fosssweeper/desktop_model.hpp>
#include <fosssweeper/game_model.hpp>

#include "desktop_timer.hpp"
#include "desktop_view.hpp"
#include "wx_include.hpp"

namespace fosssweeper {
class DesktopApp : public wxApp {
public:
  fosssweeper::GameModel _gameModel = fosssweeper::GameModel();
  fosssweeper::DesktopModel _desktopModel = fosssweeper::DesktopModel(this->_gameModel);
  fosssweeper::DesktopView _view =
      fosssweeper::DesktopView(this->_desktopModel, this->_gameModel);

  DesktopApp() noexcept = default;
  bool OnInit() override;
};
} // namespace fosssweeper

#endif
