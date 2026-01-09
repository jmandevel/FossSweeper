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
#include <fosssweeper/button.hpp>

SCENARIO("A Button is constructed with its default constructor") {
  GIVEN("A default constructed Button") {
    const fosssweeper::Button button;

    THEN("The ButtonState is None") {
      CHECK(button.getButtonState() == fosssweeper::ButtonState::None);
    }

    THEN("The Button has no bomb") { CHECK(button.getHasBomb() == false); }

    THEN("The Button has 0 surrounding bombs") {
      CHECK(button.getSurroundingBombs() == 0);
    }
  }
}

SCENARIO("A Button is constructed with its char constructor") {
  GIVEN("A Button constructed with 'd'") {
    const fosssweeper::Button button('d');

    THEN("The Button is down but has no bomb.") {
      CHECK(button.getButtonState() == fosssweeper::ButtonState::Down);
      CHECK(button.getHasBomb() == false);
    }
  }

  GIVEN("A Button constructed with 'b'") {
    const fosssweeper::Button button('b');

    THEN("The Button is up with a bomb") {
      CHECK(button.getButtonState() == fosssweeper::ButtonState::None);
      CHECK(button.getHasBomb() == true);
    }
  }

  GIVEN("A Button is constructed with 'x'") {
    const fosssweeper::Button button('x');

    THEN("The Button is down with a bomb") {
      CHECK(button.getButtonState() == fosssweeper::ButtonState::Down);
      CHECK(button.getHasBomb() == true);
    }
  }

  GIVEN("A Button is constructed with 'f'") {
    const fosssweeper::Button button('f');

    THEN("The Button has a flag and has no bomb") {
      CHECK(button.getButtonState() == fosssweeper::ButtonState::Flagged);
      CHECK(button.getHasBomb() == false);
    }
  }

  GIVEN("A Button is constructed with 'c'") {
    const fosssweeper::Button button('c');

    THEN("The Button has a flag and has a bomb") {
      CHECK(button.getButtonState() == fosssweeper::ButtonState::Flagged);
      CHECK(button.getHasBomb() == true);
    }
  }

  GIVEN("A Button is constructed with 'q'") {
    const fosssweeper::Button button('q');

    THEN("The Button is questioned and has no bomb") {
      CHECK(button.getButtonState() == fosssweeper::ButtonState::Questioned);
      CHECK(button.getHasBomb() == false);
    }
  }

  GIVEN("A Button is constructed with 'r'") {
    const fosssweeper::Button button('r');

    THEN("The Button is questioned and has a bomb") {
      CHECK(button.getButtonState() == fosssweeper::ButtonState::Questioned);
      CHECK(button.getHasBomb() == true);
    }
  }
}

SCENARIO("A Button is pressed and unpressed") {
  GIVEN("A Button") {
    fosssweeper::Button button;

    THEN("The ButtonState is None") {
      CHECK(button.getButtonState() == fosssweeper::ButtonState::None);
    }

    WHEN("The Button is pressed") {
      button.press();

      THEN("The ButtonState is Down") {
        CHECK(button.getButtonState() == fosssweeper::ButtonState::Down);
      }

      WHEN("The button is unpressed") {
        button.unpress();

        THEN("The ButtonState is None") {
          CHECK(button.getButtonState() == fosssweeper::ButtonState::None);
        }
      }
    }
  }
}

SCENARIO("A Button is alt pressed") {
  GIVEN("A Button") {
    fosssweeper::Button button;

    WHEN("The Button is alt pressed without questions enabled") {
      button.altPress(false);

      THEN("The ButtonState is Flagged") {
        CHECK(button.getButtonState() == fosssweeper::ButtonState::Flagged);
      }

      WHEN("The Button is alt pressed without questions enabled") {
        button.altPress(false);

        THEN("The ButtonState is None") {
          CHECK(button.getButtonState() == fosssweeper::ButtonState::None);
        }
      }
    }

    WHEN("The Button is alt pressed with questions enabled") {
      button.altPress(true);

      THEN("The ButtonState is Flagged") {
        CHECK(button.getButtonState() == fosssweeper::ButtonState::Flagged);
      }

      WHEN("The Button is alt pressed with questions enabled") {
        button.altPress(true);

        THEN("The ButtonState is Questioned") {
          CHECK(button.getButtonState() == fosssweeper::ButtonState::Questioned);
        }

        WHEN("The Button is alt pressed with questions enabled") {
          button.altPress(true);

          THEN("The ButtonState is None") {
            CHECK(button.getButtonState() == fosssweeper::ButtonState::None);
          }
        }
      }
    }
  }
}

SCENARIO("The Questioned state of a Button is removed") {
  GIVEN("A Button with ButtonState::Questioned") {
    fosssweeper::Button button;
    button.altPress(true);
    button.altPress(true);

    WHEN("The question is removed") {
      button.removeQuestion();

      THEN("The ButtonState is None") {
        CHECK(button.getButtonState() == fosssweeper::ButtonState::None);
      }
    }
  }

  GIVEN("A Button with ButtonState::Flagged") {
    fosssweeper::Button button;
    button.altPress(true);

    WHEN("The question is removed") {
      button.removeQuestion();

      THEN("The ButtonState is Flagged") {
        CHECK(button.getButtonState() == fosssweeper::ButtonState::Flagged);
      }
    }
  }
}

SCENARIO("A Button is set having a bomb") {
  GIVEN("A Button") {
    fosssweeper::Button button;

    WHEN("The Button is set having a bomb") {
      button.setHasBomb(true);

      THEN("The Button has a bomb") { CHECK(button.getHasBomb() == true); }
    }

    WHEN("The Button is set not having a bomb") {
      button.setHasBomb(false);

      THEN("The Button does not have a bomb") {
        CHECK(button.getHasBomb() == false);
      }
    }
  }
}

SCENARIO("The surrounding bombs of a button are set") {
  GIVEN("A Button") {
    fosssweeper::Button button;

    WHEN("The surrounding bombs of the Button are set to 2") {
      button.setSurroundingBombs(2);

      THEN("The surrounding bombs of the Button are 2") {
        CHECK(button.getSurroundingBombs() == 2);
      }
    }
  }
}

SCENARIO("A surrounding bombs are added to a Button") {
  GIVEN("A Button") {
    fosssweeper::Button button;

    WHEN("A surrounding bomb is added to the Button") {
      button.addSurroundingBomb();

      THEN("The Button has 1 surrounding bombs") {
        CHECK(button.getSurroundingBombs() == 1);
      }

      WHEN("A surrounding bomb is added to the Button") {
        button.addSurroundingBomb();

        THEN("The button has 2 surrounding bombs") {
          CHECK(button.getSurroundingBombs() == 2);
        }
      }
    }
  }
}

SCENARIO("It is determined if a Button is pressable") {
  GIVEN("A Button") {
    fosssweeper::Button button;

    THEN("The Button is pressable") { CHECK(button.getIsPressable() == true); }

    WHEN("The Button is Down") {
      button.press();

      THEN("The Button is not pressable") {
        CHECK(button.getIsPressable() == false);
      }
    }

    WHEN("The Button is Flagged") {
      button.altPress(false);

      THEN("The Button is not pressable") {
        CHECK(button.getIsPressable() == false);
      }
    }

    WHEN("The Button is Questioned") {
      button.altPress(true);
      button.altPress(true);

      THEN("The Button is pressable") {
        CHECK(button.getIsPressable() == true);
      }
    }
  }
}