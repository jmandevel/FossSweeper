# SPDX-FileCopyrightText: 2022 Daniel Valcour <fosssweeper@gmail.com>
#
# SPDX-License-Identifier: GPL-3.0-or-later

#
# Copyright (c) 2022 Daniel Valcour
#
# This file is part of FossSweeper.
# 
# FossSweeper is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
# 
# FossSweeper is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License along with FossSweeper. If not, see <https://www.gnu.org/licenses/>.
# 

target_sources(fosssweeper_desktop_view
    PRIVATE
        "about_dialog.cpp"
        "config_dialog.cpp"
        "desktop_app.cpp"
        "desktop_timer.cpp"
        "desktop_view.cpp"
        "game_frame.cpp"
        "game_panel.cpp"
        "icon.cpp"
        "main.cpp"
        "pixel_scale_dialog.cpp"
        "spritesheet.cpp"
        "text_dialog.cpp"
        "about_dialog.hpp"
        "desktop_app.hpp"
        "desktop_timer.hpp"
        "desktop_view.hpp"
        "game_frame.hpp"
        "game_panel.hpp"
        "game_panel_state.hpp"
        "icon.hpp"
        "pixel_scale_dialog.hpp"
        "spritesheet.hpp"
        "text_dialog.hpp"
        "wx_include.hpp"
)