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
#include <fosssweeper/desktop_model.hpp>
#include <fosssweeper/game_model.hpp>
#include <fosssweeper/point.hpp>
#include <fosssweeper/sprite.hpp>

#include "TestTimer.hpp"

TEST_CASE("A DesktopModel is constructed") {
  GIVEN("A default constructed GameModel") {
    fosssweeper::GameModel game_model;

    GIVEN("A DesktopModel constructed with the GameModel") {
      fosssweeper::DesktopModel desktop_model(game_model);

      THEN("The getters of the DesktopModel return expected values") {
        CHECK(desktop_model.getPixelScale() == 2);
        CHECK(desktop_model.getFaceDimension() == 48);
        CHECK(desktop_model.getBorderSize() == 16);
        CHECK(desktop_model.getButtonDimension() == 32);
        CHECK(desktop_model.getLcdDigitWidth() == 32);
        CHECK(desktop_model.getHeaderHeight() == 80);
        CHECK(desktop_model.getFacePoint() == fosssweeper::Point(120, 16));
        CHECK(desktop_model.getButtonPoint(0, 0) == fosssweeper::Point(16, 80));
        CHECK(desktop_model.getScorePoint(0) == fosssweeper::Point(16, 16));
        CHECK(desktop_model.getScorePoint(1) == fosssweeper::Point(48, 16));
        CHECK(desktop_model.getTimerPoint(0) == fosssweeper::Point(176, 16));
        CHECK(desktop_model.getTimerPoint(1) == fosssweeper::Point(208, 16));
        CHECK(desktop_model.getSize() == fosssweeper::Point(288, 352));
      }
    }
  }
}

TEST_CASE("The pixel scale of a DesktopModel is changed") {
  GIVEN("A default constructed GameModel") {
    fosssweeper::GameModel game_model;

    GIVEN("A DesktopModel constructed with the GameModel") {
      fosssweeper::DesktopModel desktop_model(game_model);

      WHEN("The pixel scale is changed to 2") {
        bool changed = desktop_model.tryChangePixelScale(2);

        THEN("Nothing changed") { CHECK(!changed); }
      }

      WHEN("The pixel scale is changed to 1") {
        bool changed = desktop_model.tryChangePixelScale(1);

        THEN("It changed") { CHECK(changed); }

        THEN("The returned values from all position and size getters are "
             "halved") {
          CHECK(desktop_model.getPixelScale() == 1);
          CHECK(desktop_model.getFaceDimension() == 24);
          CHECK(desktop_model.getBorderSize() == 8);
          CHECK(desktop_model.getButtonDimension() == 16);
          CHECK(desktop_model.getLcdDigitWidth() == 16);
          CHECK(desktop_model.getHeaderHeight() == 40);
          CHECK(desktop_model.getFaceSprite() ==
                fosssweeper::Sprite::ButtonSmile);
          CHECK(desktop_model.getButtonSprite(0, 0) ==
                fosssweeper::Sprite::ButtonNone);
          CHECK(desktop_model.getFacePoint() == fosssweeper::Point(60, 8));
          CHECK(desktop_model.getButtonPoint(0, 0) ==
                fosssweeper::Point(8, 40));
          CHECK(desktop_model.getScorePoint(0) == fosssweeper::Point(8, 8));
          CHECK(desktop_model.getScorePoint(1) == fosssweeper::Point(24, 8));
          CHECK(desktop_model.getTimerPoint(0) == fosssweeper::Point(88, 8));
          CHECK(desktop_model.getTimerPoint(1) == fosssweeper::Point(104, 8));
          CHECK(desktop_model.getSize() == fosssweeper::Point(144, 176));
        }

        WHEN("The pixel scale is changed to 1") {
          changed = desktop_model.tryChangePixelScale(1);

          THEN("Nothing changed") { CHECK(!changed); }
        }
      }
    }
  }
}

TEST_CASE("Buttons are clicked in through a DesktopModel") {
  GIVEN("A default constructed TestTimer that is running") {
    fosssweeper::TestTimer timer;
    timer.start();

    GIVEN("A GameModel with a Playing GameState") {
      fosssweeper::GameModel game_model(
          fosssweeper::GameConfiguration(fosssweeper::GameDifficulty::Beginner),
          true, fosssweeper::GameState::Playing, 30,
          ".bdddddd"
          "bdbddddd"
          "bbdddddd"
          "dddddddd"
          "dddddddd"
          "ddddddbb"
          "dddddb.b"
          "dddddb..");

      GIVEN("A DesktopModel constructed with the GameModel") {
        fosssweeper::DesktopModel desktop_model(game_model);

        WHEN("The Button at (0, 0) is left pressed") {
          desktop_model.mouseMove(18, 82);
          desktop_model.leftPress();

          WHEN("The left mouse button is released") {
            desktop_model.leftRelease(timer);

            THEN("The Button at (0, 0) has ButtonState::Down") {
              CHECK(game_model.getButton(0, 0).getButtonState() ==
                    fosssweeper::ButtonState::Down);
            }

            THEN("The timer is running") { CHECK(timer.getIsRunning()); }
          }

          WHEN("The mouse is moved to the Button at (7, 7) and the left mouse "
               "button is released") {
            desktop_model.mouseMove(240, 306);
            desktop_model.leftRelease(timer);

            THEN("The Button at (0, 0) has ButtonState::None") {
              CHECK(game_model.getButton(0, 0).getButtonState() ==
                    fosssweeper::ButtonState::None);
            }

            THEN("The Button at (7, 7) has ButtonState::Down") {
              CHECK(game_model.getButton(7, 7).getButtonState() ==
                    fosssweeper::ButtonState::Down);
            }

            THEN("The timer is running") { CHECK(timer.getIsRunning()); }
          }
        }
      }
    }

    GIVEN("A GameModel with a Playing GameState") {
      fosssweeper::GameModel game_model(
          fosssweeper::GameConfiguration(fosssweeper::GameDifficulty::Beginner),
          true, fosssweeper::GameState::Playing, 30,
          ".bdddddd"
          "bdbddddd"
          "bbdddddd"
          "dddddddd"
          "dddddddd"
          "ddddddbb"
          "dddddbdb"
          "dddddbdd");

      GIVEN("A DesktopModel constructed with the GameModel") {
        fosssweeper::DesktopModel desktop_model(game_model);

        WHEN("The final unbombed Button not pressed at (0, 0) is left pressed "
             "and released") {
          desktop_model.mouseMove(18, 82);
          desktop_model.leftPress();
          desktop_model.leftRelease(timer);

          THEN("The timer is not running") { CHECK(!timer.getIsRunning()); }
        }
      }
    }
  }
}

TEST_CASE("Buttons are chorded (area clicked) through the DesktopModel") {
  GIVEN("A default constructed TestTimer that is running") {
    fosssweeper::TestTimer timer;
    timer.start();

    GIVEN("A GameModel with some chordable Buttons") {
      fosssweeper::GameModel game_model(
          fosssweeper::GameConfiguration(fosssweeper::GameDifficulty::Beginner),
          true, fosssweeper::GameState::Playing, 30,
          "df..dc.."
          "b....c.."
          "........"
          "b....c.."
          "b...cdc."
          "...c...."
          "...db..."
          "........");

      GIVEN("A DesktopModel constructed with the GameModel") {
        fosssweeper::DesktopModel desktop_model(game_model);

        WHEN("An up Button is chorded") {
          desktop_model.mouseMove(96, 258);
          desktop_model.leftPress();
          desktop_model.rightPress(timer);
          desktop_model.leftRelease(timer);
          desktop_model.rightRelease(timer);

          THEN("The amount of Buttons left is correct") {
            CHECK(game_model.getButtonsLeft() == 50);
          }
        }

        WHEN("A non-chordable down Button is chorded") {
          desktop_model.mouseMove(146, 306);
          desktop_model.leftPress();
          desktop_model.rightPress(timer);
          desktop_model.leftRelease(timer);
          desktop_model.rightRelease(timer);

          THEN("The amount of Buttons left is correct") {
            CHECK(game_model.getButtonsLeft() == 50);
          }
        }

        WHEN("A chordable down Button is chorded") {
          desktop_model.mouseMove(162, 82);
          desktop_model.leftPress();
          desktop_model.rightPress(timer);
          desktop_model.leftRelease(timer);
          desktop_model.rightRelease(timer);

          THEN("The amount of Buttons left is correct") {
            CHECK(game_model.getButtonsLeft() == 33);
          }
        }

        WHEN("Two Buttons were chorded with left release without releasing the "
             "right mouse button") {
          desktop_model.mouseMove(162, 82);
          desktop_model.leftPress();
          desktop_model.rightPress(timer);
          desktop_model.leftRelease(timer);
          desktop_model.mouseMove(178, 226);
          desktop_model.leftPress();
          desktop_model.leftRelease(timer);
          desktop_model.rightRelease(timer);

          THEN("The amount of Buttons left is correct") {
            CHECK(game_model.getButtonsLeft() == 29);
          }
        }

        WHEN("Two Buttons were chorded with right release without releasing "
             "the left mouse button") {
          desktop_model.mouseMove(162, 82);
          desktop_model.leftPress();
          desktop_model.rightPress(timer);
          desktop_model.rightRelease(timer);
          desktop_model.mouseMove(178, 226);
          desktop_model.leftPress();
          desktop_model.rightRelease(timer);
          desktop_model.leftRelease(timer);

          THEN("The amount of Buttons left is correct") {
            CHECK(game_model.getButtonsLeft() == 29);
          }
        }
      }
    }
  }
}

TEST_CASE("The mouse leaves the game area of a DesktopModel") {
  GIVEN("A default constructed GameModel") {
    fosssweeper::GameModel game_model;

    GIVEN("A default constructed TestTimer") {
      fosssweeper::TestTimer timer;

      GIVEN("A DesktopModel constructed with the GameModel") {
        fosssweeper::DesktopModel desktop_model(game_model);

        WHEN("The Button at (0, 0) is held down with the left mouse button") {
          desktop_model.mouseMove(9, 41);
          desktop_model.leftPress();

          WHEN("The mouse is moved out of the game area") {
            desktop_model.mouseLeave();

            THEN("The Sprite of the Button at (0, 0) is ButtonNone") {
              CHECK(desktop_model.getButtonSprite(0, 0) ==
                    fosssweeper::Sprite::ButtonNone);
            }

            WHEN("The left mouse button is released") {
              desktop_model.leftRelease(timer);

              THEN("The GameState is None") {
                CHECK(game_model.getGameState() ==
                      fosssweeper::GameState::None);
              }
            }
          }
        }
      }
    }
  }
}