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

#include "TestTimer.hpp"

unsigned long fosssweeper::TestTimer::getGameTime() { return 0; }

void fosssweeper::TestTimer::start() { this->is_running = true; }

void fosssweeper::TestTimer::stop() { this->is_running = false; }

bool fosssweeper::TestTimer::getIsRunning() const noexcept {
  return this->is_running;
}