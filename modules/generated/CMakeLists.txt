# SPDX-FileCopyrightText: 2025 Free Software Foundation <licensing@fsf.org>
#
# SPDX-License-Identifier: GPL-3.0-or-later

#
# Copyright (c) 2025 Free Software Foundation <licensing@fsf.org>
#
# This file is part of FossSweeper.
# 
# FossSweeper is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
# 
# FossSweeper is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License along with FossSweeper. If not, see <https://www.gnu.org/licenses/>.
# 

# configure version file
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/src/version.hpp.in" "${CMAKE_CURRENT_SOURCE_DIR}/include/fosssweeper/version.hpp")
# configure short hash file
include("${FOSSSWEEPER_CMAKE_SCRIPT_DIR}/get_short_hash.CMake")
get_short_hash("${FOSSSWEEPER_CMAKE_SOURCE_DIR}" "FOSSSWEEPER_SHORT_HASH")
set(FOSSSWEEPER_HASH_INPUT_FILE "${CMAKE_CURRENT_SOURCE_DIR}/src/short_hash.hpp.in")
set(FOSSSWEEPER_HASH_OUTPUT_FILE "${CMAKE_CURRENT_SOURCE_DIR}/include/fosssweeper/short_hash.hpp")
configure_file("${FOSSSWEEPER_HASH_INPUT_FILE}" "${FOSSSWEEPER_HASH_OUTPUT_FILE}")
# save short hash cache
file(WRITE "${CMAKE_BINARY_DIR}/short_hash.cache" "${FOSSSWEEPER_SHORT_HASH}")
# create target to update short hash if it changes
add_custom_target(fosssweeper_short_hash_check 
    COMMAND ${CMAKE_COMMAND}
    -D HASH_INPUT_FILE="${FOSSSWEEPER_HASH_INPUT_FILE}"
    -D HASH_OUTPUT_FILE="${FOSSSWEEPER_HASH_OUTPUT_FILE}"
    -D CMAKE_SCRIPT_DIR="${FOSSSWEEPER_CMAKE_SCRIPT_DIR}"
    -D CACHE_DIR="${CMAKE_BINARY_DIR}"
    -D GIT_SOURCE_DIR="${FOSSSWEEPER_CMAKE_SOURCE_DIR}"
    -P "${FOSSSWEEPER_CMAKE_SCRIPT_DIR}/hash_check.CMake"
    BYPRODUCTS "${CMAKE_BINARY_DIR}/short_hash.cache"
)
# embed license and credits text
include("${FOSSSWEEPER_CMAKE_SCRIPT_DIR}/embed_string.CMake")
embed_string("FOSSSWEEPER_LICENSE_TEXT" "${FOSSSWEEPER_CMAKE_SOURCE_DIR}/COPYING" "${CMAKE_CURRENT_SOURCE_DIR}/src/license.cpp.in" "${CMAKE_CURRENT_SOURCE_DIR}/src/license.cpp")
embed_string("FOSSSWEEPER_CREDITS_TEXT" "${FOSSSWEEPER_CMAKE_SOURCE_DIR}/CREDITS" "${CMAKE_CURRENT_SOURCE_DIR}/src/credits.cpp.in" "${CMAKE_CURRENT_SOURCE_DIR}/src/credits.cpp")

# setup library target
add_library(fosssweeper_generated STATIC "")
add_library(fosssweeper::generated ALIAS fosssweeper_generated)
target_include_directories(fosssweeper_generated
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src/"
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include/"
)
add_subdirectory(src)
add_dependencies(fosssweeper_generated fosssweeper_short_hash_check)
set_target_properties(fosssweeper_generated
    PROPERTIES
    OUTPUT_NAME "fosssweepergenerated"
    CXX_STANDARD ${FOSSSWEEPER_CXX_STANDARD}
    CXX_STANDARD_REQUIRED TRUE
)
