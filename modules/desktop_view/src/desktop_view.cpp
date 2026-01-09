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

#include "desktop_view.hpp"

#include <fosssweeper/desktop_model.hpp>
#include <fosssweeper/game_model.hpp>
#include <functional>
#include <sstream>
#include <stdexcept>

#include "game_frame.hpp"
#include "wx_include.hpp"

fosssweeper::DesktopView::DesktopView(fosssweeper::DesktopModel &desktop_model,
                                 fosssweeper::GameModel &game_model) noexcept
    : _desktopModel(std::ref(desktop_model)), _gameModel(std::ref(game_model)) {
}

bool fosssweeper::DesktopView::run() noexcept {
  try {
    auto *const game_frame = new fosssweeper::GameFrame(*this);
    game_frame->Show();
  } catch (const std::exception &e) {
    std::stringstream ss("");
    ss << "FossSweeper crashed due to unhandled exception:\n\n\"" << e.what()
       << "\"";
    wxMessageBox(wxString::FromUTF8(ss.str()), _("FossSweeper"), wxICON_ERROR);
    return false;
  }

  return true;
}

fosssweeper::DesktopModel &fosssweeper::DesktopView::getDesktopModel() noexcept {
  return this->_desktopModel.get();
}

fosssweeper::GameModel &fosssweeper::DesktopView::getGameModel() noexcept {
  return this->_gameModel.get();
}