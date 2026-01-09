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

#include "desktop_timer.hpp"

#include "wx_include.hpp"

const unsigned long TIMER_INTERVAL = 1000 / 15;

fosssweeper::DesktopTimer::DesktopTimer(wxEvtHandler *handler) noexcept
    : _timer(handler) {}

unsigned long fosssweeper::DesktopTimer::getGameTime() {
  return this->_stopwatch.Time();
}

void fosssweeper::DesktopTimer::start() {
  this->_stopwatch.Start(0);
  this->_timer.Start(TIMER_INTERVAL);
}

void fosssweeper::DesktopTimer::stop() {
  this->_timer.Stop();
  this->_stopwatch.Pause();
}

wxTimer &fosssweeper::DesktopTimer::getTimer() noexcept { return this->_timer; }