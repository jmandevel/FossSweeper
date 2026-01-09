// SPDX-FileCopyrightText: 2022 Daniel Valcour <fosssweeper@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

/*
 * Copyright (c) 2022 Daniel Valcour
 *
 * This file is part of FossSweeper.
 *
 * FossSweeper is free software: you can redistribute it and/or modify it under the terms of the GNU
 * General Public License as published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * FossSweeper is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
 * even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with FossSweeper. If not,
 * see <https://www.gnu.org/licenses/>.
 *
 */

#include <cstddef>
#include <fosssweeper/desktop_model.hpp>
#include <fosssweeper/game_model.hpp>
#include <fosssweeper/point.hpp>
#include <fosssweeper/sprite.hpp>
#include <fosssweeper/timer.hpp>
#include <functional>
#include <utility>

fosssweeper::DesktopModel::DesktopModel(fosssweeper::GameModel& game_model) noexcept
    : _gameModel(std::ref(game_model))
{
}

bool fosssweeper::DesktopModel::tryChangePixelScale(int new_pixel_scale)
{
  if (this->_pixelScale == new_pixel_scale) return false;
  this->_pixelScale = new_pixel_scale;
  return true;
}

void fosssweeper::DesktopModel::leftPress() { this->_leftDown = true; }

void fosssweeper::DesktopModel::leftRelease(fosssweeper::Timer& timer)
{
  auto& game_model = this->_gameModel.get();
  if (game_model.getGameState() == fosssweeper::GameState::Playing)
  {
    game_model.updateTime(timer.getGameTime());
  }
  auto initially_playing = game_model.getGameState() == fosssweeper::GameState::Playing;
  if (this->_hoverButtonO.has_value())
  {
    auto& hover_button = this->_hoverButtonO.value();
    if (this->_rightDown)
    {
      game_model.areaClickButton(hover_button.x, hover_button.y);
    }
    else
    {
      game_model.clickButton(hover_button.x, hover_button.y);
    }
    if (game_model.getGameState() == fosssweeper::GameState::Playing && !initially_playing)
    {
      timer.start();
    }
    else if (game_model.getGameState() == fosssweeper::GameState::Dead ||
              game_model.getGameState() == fosssweeper::GameState::Cool && initially_playing)
    {
      timer.stop();
    }
  }
  else if (this->_hoverFace)
  {
    game_model.newGame();
    timer.stop();
  }
  this->_leftDown = false;
}

void fosssweeper::DesktopModel::rightPress(fosssweeper::Timer& timer)
{
  auto& game_model = this->_gameModel.get();
  this->_rightDown = true;
  if (game_model.getGameState() == fosssweeper::GameState::Playing)
  {
    game_model.updateTime(timer.getGameTime());
  }
  if (!this->_leftDown && this->_hoverButtonO.has_value())
  {
    auto& hover_button = this->_hoverButtonO.value();
    game_model.altClickButton(hover_button.x, hover_button.y);
  }
}

void fosssweeper::DesktopModel::rightRelease(fosssweeper::Timer& timer)
{
  auto& game_model = this->_gameModel.get();
  auto initially_playing = game_model.getGameState() == fosssweeper::GameState::Playing;
  if (this->_hoverButtonO.has_value() && this->_leftDown)
  {
    auto& hover_button = this->_hoverButtonO.value();
    game_model.areaClickButton(hover_button.x, hover_button.y);
    if (game_model.getGameState() == fosssweeper::GameState::Dead ||
              game_model.getGameState() == fosssweeper::GameState::Cool)
    {
      timer.stop();
    }
  }
  this->_rightDown = false;
}

void fosssweeper::DesktopModel::mouseLeave() { this->_hoverButtonO = std::nullopt; }

void fosssweeper::DesktopModel::mouseMove(int x, int y)
{
  this->_hoverButtonO = std::nullopt;
  if (x >= this->getBorderSize() && x < this->getSize().x - this->getBorderSize() &&
      y >= this->getHeaderHeight() && y < this->getSize().y - this->getBorderSize())
  {
    this->_hoverButtonO =
        fosssweeper::ButtonPosition((x - this->getBorderSize()) / this->getButtonDimension(),
                               (y - this->getHeaderHeight()) / this->getButtonDimension());
  }
  const auto face_point = this->getFacePoint();
  this->_hoverFace = x >= face_point.x && x < face_point.x + this->getFaceDimension() &&
                     y >= face_point.y && y < face_point.y + this->getFaceDimension();
}

const int FACE_BUTTON_DIMENSION = 24;
const int BORDER_SIZE = 8;
const int BUTTON_DIMENSION = 16;
const int LCD_DIGIT_WIDTH = 16;
const int HEADER_HEIGHT = BORDER_SIZE * 2 + FACE_BUTTON_DIMENSION;

int fosssweeper::DesktopModel::getPixelScale() const noexcept { return this->_pixelScale; }

int fosssweeper::DesktopModel::getFaceDimension() const noexcept
{
  return this->_pixelScale * FACE_BUTTON_DIMENSION;
}

int fosssweeper::DesktopModel::getBorderSize() const noexcept { return this->_pixelScale * BORDER_SIZE; }

int fosssweeper::DesktopModel::getButtonDimension() const noexcept
{
  return this->_pixelScale * BUTTON_DIMENSION;
}

int fosssweeper::DesktopModel::getLcdDigitWidth() const noexcept
{
  return this->_pixelScale * LCD_DIGIT_WIDTH;
}

int fosssweeper::DesktopModel::getHeaderHeight() const noexcept
{
  return this->_pixelScale * HEADER_HEIGHT;
}

fosssweeper::Sprite fosssweeper::DesktopModel::getFaceSprite() const noexcept
{
  const auto& game_model = this->_gameModel.get();
  if (game_model.getGameState() == fosssweeper::GameState::None ||
      game_model.getGameState() == fosssweeper::GameState::Playing)
  {
    if (this->_leftDown && this->_hoverFace)
    {
      return fosssweeper::Sprite::ButtonSmileDown;
    }
    else if (this->_leftDown && this->_hoverButtonO.has_value())
    {
      const auto& hover_button = this->_hoverButtonO.value();
      const auto& button = game_model.getButton(hover_button.x, hover_button.y);
      if (button.getButtonState() != fosssweeper::ButtonState::Down &&
          button.getButtonState() != fosssweeper::ButtonState::Flagged)
      {
        return fosssweeper::Sprite::ButtonShocked;
      }
    }
  }
  else if (game_model.getGameState() == fosssweeper::GameState::Cool)
  {
    if (this->_leftDown && this->_hoverFace)
    {
      return fosssweeper::Sprite::ButtonSmileDown;
    }
    else
    {
      return fosssweeper::Sprite::ButtonCool;
    }
  }
  else  // if (model.getGameState() == fosssweeper::GameState::Dead)
  {
    if (this->_leftDown && this->_hoverFace)
    {
      return fosssweeper::Sprite::ButtonSmileDown;
    }
    else
    {
      return fosssweeper::Sprite::ButtonDead;
    }
  }
  return fosssweeper::Sprite::ButtonSmile;
}

fosssweeper::Sprite fosssweeper::DesktopModel::getButtonSprite(int x, int y) const noexcept
{
  const auto& game_model = this->_gameModel.get();
  if (x >= game_model.getGameConfiguration().getButtonsWide() ||
      y >= game_model.getGameConfiguration().getButtonsTall())
  {
    return fosssweeper::Sprite::ButtonNone;
  }
  const auto& button = game_model.getButton(x, y);
  auto button_position = fosssweeper::ButtonPosition(x, y);
  if (game_model.getGameState() == fosssweeper::GameState::None ||
      game_model.getGameState() == fosssweeper::GameState::Playing)
  {
    if (button.getButtonState() != fosssweeper::ButtonState::Flagged &&
        button.getButtonState() != fosssweeper::ButtonState::Down && this->_leftDown &&
        this->_hoverButtonO.has_value())
    {
      const auto& hover_button = this->_hoverButtonO.value();
      if ((hover_button == button_position) ||
          (this->_rightDown && hover_button.isNear(button_position)))
      {
        if (fosssweeper::ButtonState() == fosssweeper::ButtonState::Questioned)
        {
          return fosssweeper::Sprite::ButtonQuestionDown;
        }
        return fosssweeper::Sprite::ButtonDown;
      }
    }
    else if (button.getButtonState() == fosssweeper::ButtonState::Flagged)
    {
      return fosssweeper::Sprite::ButtonFlag;
    }
    else if (button.getButtonState() == fosssweeper::ButtonState::Questioned)
    {
      return fosssweeper::Sprite::ButtonQuestion;
    }
    else if (button.getButtonState() == fosssweeper::ButtonState::Down)
    {
      return fosssweeper::getDownButtonSprite(button.getSurroundingBombs());
    }
    else
    {
      return fosssweeper::Sprite::ButtonNone;
    }
  }
  else  // if (model.getGameState() == fosssweeper::GameState::Cool || model.getGameState() ==
        // fosssweeper::GameState::Dead)
  {
    if (button.getButtonState() == fosssweeper::ButtonState::None ||
        button.getButtonState() == fosssweeper::ButtonState::Questioned)
    {
      if (button.getHasBomb())
      {
        return fosssweeper::Sprite::ButtonBomb;
      }
      else
      {
        return fosssweeper::Sprite::ButtonNone;
      }
    }
    else if (button.getButtonState() == fosssweeper::ButtonState::Flagged)
    {
      if (button.getHasBomb())
      {
        return fosssweeper::Sprite::ButtonFlagHit;
      }
      else
      {
        return fosssweeper::Sprite::ButtonFlagMiss;
      }
    }
    else if (button.getButtonState() == fosssweeper::ButtonState::Down)
    {
      if (button.getHasBomb())
      {
        return fosssweeper::Sprite::ButtonBombExplode;
      }
      else
      {
        return fosssweeper::getDownButtonSprite(button.getSurroundingBombs());
      }
    }
  }
  return fosssweeper::Sprite::ButtonNone;
}

fosssweeper::Point fosssweeper::DesktopModel::getFacePoint() const noexcept
{
  return fosssweeper::Point((this->getSize().x / 2) - (this->getFaceDimension() / 2),
                       this->getBorderSize());
}

fosssweeper::Point fosssweeper::DesktopModel::getButtonPoint(int x, int y) const noexcept
{
  return fosssweeper::Point(this->getBorderSize() + (x * this->getButtonDimension()),
                       this->getHeaderHeight() + (y * this->getButtonDimension()));
}

fosssweeper::Point fosssweeper::DesktopModel::getScorePoint(std::size_t digit) const noexcept
{
  return fosssweeper::Point(this->getBorderSize() + (this->getLcdDigitWidth() * digit),
                       this->getBorderSize());
}

fosssweeper::Point fosssweeper::DesktopModel::getTimerPoint(std::size_t digit) const noexcept
{
  return fosssweeper::Point(
      this->getSize().x - (this->getBorderSize() + (this->getLcdDigitWidth() * (3 - digit))),
      this->getBorderSize());
}

fosssweeper::Point fosssweeper::DesktopModel::getSize() const noexcept
{
  const auto& game_model = this->_gameModel.get();
  return fosssweeper::Point(
      (game_model.getGameConfiguration().getButtonsWide() *
       (this->_pixelScale * BUTTON_DIMENSION)) +
          ((this->_pixelScale * BORDER_SIZE) * 2),
      (game_model.getGameConfiguration().getButtonsTall() *
       (this->_pixelScale * BUTTON_DIMENSION)) +
          ((this->_pixelScale * BORDER_SIZE) + (this->_pixelScale * HEADER_HEIGHT)));
}
