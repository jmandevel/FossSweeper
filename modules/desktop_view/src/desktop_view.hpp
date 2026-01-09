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

#ifndef FOSSSWEEPER_DESKTOP_VIEW_HPP
#define FOSSSWEEPER_DESKTOP_VIEW_HPP

#include <functional>

namespace fosssweeper {
class DesktopModel;
class GameModel;

struct DesktopView {
  std::reference_wrapper<fosssweeper::DesktopModel> _desktopModel;
  std::reference_wrapper<fosssweeper::GameModel> _gameModel;

  DesktopView(fosssweeper::DesktopModel &desktop_model,
              fosssweeper::GameModel &game_model) noexcept;

  bool run() noexcept;
  fosssweeper::DesktopModel &getDesktopModel() noexcept;
  fosssweeper::GameModel &getGameModel() noexcept;
};
} // namespace fosssweeper

#endif
