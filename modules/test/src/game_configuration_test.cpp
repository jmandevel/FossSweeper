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

#include <catch2/catch_all.hpp>
#include <fosssweeper/game_configuration.hpp>
#include <fosssweeper/game_difficulty.hpp>

SCENARIO("GameConfiguration object is created with a default constructor") {
  GIVEN("A GameConfiguration object created with a default constructor") {
    const fosssweeper::GameConfiguration game_configuration;

    THEN("The properties are correct for beginner difficulty") {
      CHECK(game_configuration.getButtonsWide() ==
            fosssweeper::GameConfiguration::BEGINNER_BUTTONS_WIDE);
      CHECK(game_configuration.getButtonsTall() ==
            fosssweeper::GameConfiguration::BEGINNER_BUTTONS_TALL);
      CHECK(game_configuration.getBombCount() ==
            fosssweeper::GameConfiguration::BEGINNER_BOMB_COUNT);
      CHECK(game_configuration.getGameDifficulty() ==
            fosssweeper::GameDifficulty::Beginner);
    }
  }
}

SCENARIO("GameConfiguration objects are created from a GameDifficulty") {
  GIVEN("A GameConfiguration created with GameDifficulty::Beginner") {
    const fosssweeper::GameConfiguration game_configuration(
        fosssweeper::GameDifficulty::Beginner);

    THEN("The properties are correct for beginner difficulty") {
      CHECK(game_configuration.getButtonsWide() ==
            fosssweeper::GameConfiguration::BEGINNER_BUTTONS_WIDE);
      CHECK(game_configuration.getButtonsTall() ==
            fosssweeper::GameConfiguration::BEGINNER_BUTTONS_TALL);
      CHECK(game_configuration.getBombCount() ==
            fosssweeper::GameConfiguration::BEGINNER_BOMB_COUNT);
      CHECK(game_configuration.getGameDifficulty() ==
            fosssweeper::GameDifficulty::Beginner);
    }
  }

  GIVEN("A GameConfiguration created with GameDifficulty::Intermediate") {
    const fosssweeper::GameConfiguration game_configuration(
        fosssweeper::GameDifficulty::Intermediate);

    THEN("The properties are correct for intermediate difficulty") {
      CHECK(game_configuration.getButtonsWide() ==
            fosssweeper::GameConfiguration::INTERMEDIATE_BUTTONS_WIDE);
      CHECK(game_configuration.getButtonsTall() ==
            fosssweeper::GameConfiguration::INTERMEDIATE_BUTTONS_TALL);
      CHECK(game_configuration.getBombCount() ==
            fosssweeper::GameConfiguration::INTERMEDIATE_BOMB_COUNT);
      CHECK(game_configuration.getGameDifficulty() ==
            fosssweeper::GameDifficulty::Intermediate);
    }
  }

  GIVEN("A GameConfiguration created with GameDifficulty::Expert") {
    const fosssweeper::GameConfiguration game_configuration(
        fosssweeper::GameDifficulty::Expert);

    THEN("The properties are correct for expert difficulty") {
      CHECK(game_configuration.getButtonsWide() ==
            fosssweeper::GameConfiguration::EXPERT_BUTTONS_WIDE);
      CHECK(game_configuration.getButtonsTall() ==
            fosssweeper::GameConfiguration::EXPERT_BUTTONS_TALL);
      CHECK(game_configuration.getBombCount() ==
            fosssweeper::GameConfiguration::EXPERT_BOMB_COUNT);
      CHECK(game_configuration.getGameDifficulty() ==
            fosssweeper::GameDifficulty::Expert);
    }
  }

  GIVEN("A GameConfiguration created with GameDifficulty::Custom") {
    const fosssweeper::GameConfiguration game_configuration(
        fosssweeper::GameDifficulty::Custom);

    THEN("The properties are correct for beginner difficulty") {
      CHECK(game_configuration.getButtonsWide() ==
            fosssweeper::GameConfiguration::BEGINNER_BUTTONS_WIDE);
      CHECK(game_configuration.getButtonsTall() ==
            fosssweeper::GameConfiguration::BEGINNER_BUTTONS_TALL);
      CHECK(game_configuration.getBombCount() ==
            fosssweeper::GameConfiguration::BEGINNER_BOMB_COUNT);
      CHECK(game_configuration.getGameDifficulty() ==
            fosssweeper::GameDifficulty::Beginner);
    }
  }
}

SCENARIO(
    "A GameConfiguration created with specific dimensions and bomb count") {
  GIVEN("A GameConfiguration created with beginner difficulty properties") {
    const fosssweeper::GameConfiguration game_configuration(
        fosssweeper::GameConfiguration::BEGINNER_BUTTONS_WIDE,
        fosssweeper::GameConfiguration::BEGINNER_BUTTONS_TALL,
        fosssweeper::GameConfiguration::BEGINNER_BOMB_COUNT);

    THEN("The properties are correct for beginner difficulty") {
      CHECK(game_configuration.getButtonsWide() ==
            fosssweeper::GameConfiguration::BEGINNER_BUTTONS_WIDE);
      CHECK(game_configuration.getButtonsTall() ==
            fosssweeper::GameConfiguration::BEGINNER_BUTTONS_TALL);
      CHECK(game_configuration.getBombCount() ==
            fosssweeper::GameConfiguration::BEGINNER_BOMB_COUNT);
      CHECK(game_configuration.getGameDifficulty() ==
            fosssweeper::GameDifficulty::Beginner);
    }
  }

  GIVEN("A GameConfiguration created with intermediate difficulty properties") {
    const fosssweeper::GameConfiguration game_configuration(
        fosssweeper::GameConfiguration::INTERMEDIATE_BUTTONS_WIDE,
        fosssweeper::GameConfiguration::INTERMEDIATE_BUTTONS_TALL,
        fosssweeper::GameConfiguration::INTERMEDIATE_BOMB_COUNT);

    THEN("The properties are correct for intermediate difficulty") {
      CHECK(game_configuration.getButtonsWide() ==
            fosssweeper::GameConfiguration::INTERMEDIATE_BUTTONS_WIDE);
      CHECK(game_configuration.getButtonsTall() ==
            fosssweeper::GameConfiguration::INTERMEDIATE_BUTTONS_TALL);
      CHECK(game_configuration.getBombCount() ==
            fosssweeper::GameConfiguration::INTERMEDIATE_BOMB_COUNT);
      CHECK(game_configuration.getGameDifficulty() ==
            fosssweeper::GameDifficulty::Intermediate);
    }
  }

  GIVEN("A GameConfiguration created with expert difficulty properties") {
    const fosssweeper::GameConfiguration game_configuration(
        fosssweeper::GameConfiguration::EXPERT_BUTTONS_WIDE,
        fosssweeper::GameConfiguration::EXPERT_BUTTONS_TALL,
        fosssweeper::GameConfiguration::EXPERT_BOMB_COUNT);

    THEN("The properties are correct for expert difficulty") {
      CHECK(game_configuration.getButtonsWide() ==
            fosssweeper::GameConfiguration::EXPERT_BUTTONS_WIDE);
      CHECK(game_configuration.getButtonsTall() ==
            fosssweeper::GameConfiguration::EXPERT_BUTTONS_TALL);
      CHECK(game_configuration.getBombCount() ==
            fosssweeper::GameConfiguration::EXPERT_BOMB_COUNT);
      CHECK(game_configuration.getGameDifficulty() ==
            fosssweeper::GameDifficulty::Expert);
    }
  }

  GIVEN("A GameConfiguration created with 64x32 dimensions and 110 bombs") {
    const fosssweeper::GameConfiguration game_configuration(64, 32, 110);

    THEN("The properties are correct") {
      CHECK(game_configuration.getButtonsWide() == 64);
      CHECK(game_configuration.getButtonsTall() == 32);
      CHECK(game_configuration.getBombCount() == 110);
      CHECK(game_configuration.getGameDifficulty() ==
            fosssweeper::GameDifficulty::Custom);
    }
  }

  GIVEN("A GameConfiguration created with 8x8 dimensions and 100 bombs") {
    const fosssweeper::GameConfiguration game_configuration(8, 8, 110);

    THEN("The dimensions are the same, but bomb count is clamped to the button "
         "count") {
      CHECK(game_configuration.getButtonsWide() == 8);
      CHECK(game_configuration.getButtonsTall() == 8);
      CHECK(game_configuration.getBombCount() == 64);
      CHECK(game_configuration.getGameDifficulty() ==
            fosssweeper::GameDifficulty::Custom);
    }
  }

  GIVEN("A GameConfiguration created with properties that are bellow the "
        "minimum") {
    const fosssweeper::GameConfiguration game_configuration(-50, -99, -5);

    THEN("The properties are clamped to the minimum") {
      CHECK(game_configuration.getButtonsWide() ==
            fosssweeper::GameConfiguration::MIN_BUTTONS_WIDE);
      CHECK(game_configuration.getButtonsTall() ==
            fosssweeper::GameConfiguration::MIN_BUTTONS_TALL);
      CHECK(game_configuration.getBombCount() ==
            fosssweeper::GameConfiguration::MIN_BOMB_COUNT);
      CHECK(game_configuration.getGameDifficulty() ==
            fosssweeper::GameDifficulty::Custom);
    }
  }
}

SCENARIO("Two GameConfiguration objects are compared") {
  GIVEN("A GameConfiguration object named a created with beginner difficulty") {
    const fosssweeper::GameConfiguration a(fosssweeper::GameDifficulty::Beginner);

    GIVEN(
        "A GameConfiguration object named b created with beginner difficulty") {
      const fosssweeper::GameConfiguration b(fosssweeper::GameDifficulty::Beginner);

      THEN("The objects are equal") { CHECK(a == b); }
      THEN("a is not equal to b is false") { CHECK(!(a != b)); }
    }

    GIVEN("A GameConfiguration object named b created with intermediate "
          "difficulty") {
      const fosssweeper::GameConfiguration b(fosssweeper::GameDifficulty::Intermediate);

      THEN("a is less than b") { CHECK(a < b); }
      THEN("a equals b is false") { CHECK(!(a == b)); }
      THEN("a is not equal to b") { CHECK(a != b); }
    }

    GIVEN("A GameConfiguration object named b created with expert difficulty") {
      const fosssweeper::GameConfiguration b(fosssweeper::GameDifficulty::Expert);

      THEN("a is less than b") { CHECK(a < b); }
      THEN("a equals b is false") { CHECK(!(a == b)); }
      THEN("a is not equal to b") { CHECK(a != b); }
    }

    GIVEN("A GameConfiguration object named b created with a min sized custom "
          "difficulty") {
      const fosssweeper::GameConfiguration b(
          fosssweeper::GameConfiguration::MIN_BUTTONS_WIDE,
          fosssweeper::GameConfiguration::MIN_BUTTONS_TALL,
          fosssweeper::GameConfiguration::MIN_BOMB_COUNT);

      THEN("a is less than b") { CHECK(a < b); }
      THEN("a equals b is false") { CHECK(!(a == b)); }
      THEN("a is not equal to b") { CHECK(a != b); }
    }
  }

  GIVEN("A GameConfiguration object named a created with intermediate "
        "difficulty") {
    const fosssweeper::GameConfiguration a(fosssweeper::GameDifficulty::Intermediate);

    GIVEN(
        "A GameConfiguration object named b crated with beginner difficulty") {
      const fosssweeper::GameConfiguration b(fosssweeper::GameDifficulty::Beginner);

      THEN("a is greater than b") { CHECK(a > b); }
      THEN("a equals b is false") { CHECK(!(a == b)); }
      THEN("a is not equal to b") { CHECK(a != b); }
    }

    GIVEN("A GameConfiguration object named b created with intermediate "
          "difficulty") {
      const fosssweeper::GameConfiguration b(fosssweeper::GameDifficulty::Intermediate);

      THEN("a equals b") { CHECK(a == b); }
      THEN("a is not equal to b is false") { CHECK(!(a != b)); }
    }

    GIVEN("A GameConfiguration object named b created with expert difficulty") {
      const fosssweeper::GameConfiguration b(fosssweeper::GameDifficulty::Expert);

      THEN("a is less than b") { CHECK(a < b); }
      THEN("a equals b is false") { CHECK(!(a == b)); }
      THEN("a is not equal to b") { CHECK(a != b); }
    }

    GIVEN("A GameConfiguration object named b created with a min sized custom "
          "difficulty") {
      const fosssweeper::GameConfiguration b(
          fosssweeper::GameConfiguration::MIN_BUTTONS_WIDE,
          fosssweeper::GameConfiguration::MIN_BUTTONS_TALL,
          fosssweeper::GameConfiguration::MIN_BOMB_COUNT);

      THEN("a is less than b") { CHECK(a < b); }
      THEN("a equals b is false") { CHECK(!(a == b)); }
      THEN("a is not equal to b") { CHECK(a != b); }
    }
  }

  GIVEN("A GameConfiguration object named a created with expert difficulty") {
    const fosssweeper::GameConfiguration a(fosssweeper::GameDifficulty::Expert);

    GIVEN(
        "A GameConfiguration object named b crated with beginner difficulty") {
      const fosssweeper::GameConfiguration b(fosssweeper::GameDifficulty::Beginner);

      THEN("a is greater than b") { CHECK(a > b); }
      THEN("a equals b is false") { CHECK(!(a == b)); }
      THEN("a is not equal to b") { CHECK(a != b); }
    }

    GIVEN("A GameConfiguration object named b created with intermediate "
          "difficulty") {
      const fosssweeper::GameConfiguration b(fosssweeper::GameDifficulty::Intermediate);

      THEN("a is greater than b") { CHECK(a > b); }
      THEN("a equals b is false") { CHECK(!(a == b)); }
      THEN("a is not equal to b") { CHECK(a != b); }
    }

    GIVEN("A GameConfiguration object named b created with expert difficulty") {
      const fosssweeper::GameConfiguration b(fosssweeper::GameDifficulty::Expert);

      THEN("a equals b") { CHECK(a == b); }
      THEN("a is not equal to b is false") { CHECK(!(a != b)); }
    }

    GIVEN("A GameConfiguration object named b created with a min sized custom "
          "difficulty") {
      const fosssweeper::GameConfiguration b(
          fosssweeper::GameConfiguration::MIN_BUTTONS_WIDE,
          fosssweeper::GameConfiguration::MIN_BUTTONS_TALL,
          fosssweeper::GameConfiguration::MIN_BOMB_COUNT);

      THEN("a is less than b") { CHECK(a < b); }
      THEN("a equals b is false") { CHECK(!(a == b)); }
      THEN("a is not equal to b") { CHECK(a != b); }
    }
  }

  GIVEN("A GameConfiguration object named a created with a min sized custom "
        "difficulty") {
    const fosssweeper::GameConfiguration a(
        fosssweeper::GameConfiguration::MIN_BUTTONS_WIDE,
        fosssweeper::GameConfiguration::MIN_BUTTONS_TALL,
        fosssweeper::GameConfiguration::MIN_BOMB_COUNT);

    GIVEN(
        "A GameConfiguration object named b crated with beginner difficulty") {
      const fosssweeper::GameConfiguration b(fosssweeper::GameDifficulty::Beginner);

      THEN("a is greater than b") { CHECK(a > b); }
      THEN("a equals b is false") { CHECK(!(a == b)); }
      THEN("a is not equal to b") { CHECK(a != b); }
    }

    GIVEN("A GameConfiguration object named b created with intermediate "
          "difficulty") {
      const fosssweeper::GameConfiguration b(fosssweeper::GameDifficulty::Intermediate);

      THEN("a is greater than b") { CHECK(a > b); }
      THEN("a equals b is false") { CHECK(!(a == b)); }
      THEN("a is not equal to b") { CHECK(a != b); }
    }

    GIVEN("A GameConfiguration object named b created with expert difficulty") {
      const fosssweeper::GameConfiguration b(fosssweeper::GameDifficulty::Expert);

      THEN("a is greater than b") { CHECK(a > b); }
      THEN("a equals b is false") { CHECK(!(a == b)); }
      THEN("a is not equal to b") { CHECK(a != b); }
    }

    GIVEN("A GameConfiguration object named b created with a min sized custom "
          "difficulty") {
      const fosssweeper::GameConfiguration b(
          fosssweeper::GameConfiguration::MIN_BUTTONS_WIDE,
          fosssweeper::GameConfiguration::MIN_BUTTONS_TALL,
          fosssweeper::GameConfiguration::MIN_BOMB_COUNT);

      THEN("a equals b") { CHECK(a == b); }
      THEN("a is not equal to b is false") { CHECK(!(a != b)); }
    }

    GIVEN("A GameConfigruation object named b created with 100x100 dimensions "
          "and 50 bombs") {
      const fosssweeper::GameConfiguration b(100, 100, 50);

      THEN("a is less than b") { CHECK(a < b); }
      THEN("a equals b is false") { CHECK(!(a == b)); }
      THEN("a is not equal to b") { CHECK(a != b); }
    }
  }
}