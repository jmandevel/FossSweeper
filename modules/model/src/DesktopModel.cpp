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
#include <fsweep/DesktopModel.hpp>
#include <fsweep/GameModel.hpp>
#include <fsweep/Point.hpp>
#include <fsweep/Sprite.hpp>
#include <fsweep/Timer.hpp>
#include <functional>
#include <utility>

fsweep::DesktopModel::DesktopModel(fsweep::GameModel& game_model) noexcept
    : game_model(std::ref(game_model))
{
}

bool fsweep::DesktopModel::tryChangePixelScale(int new_pixel_scale)
{
  if (this->pixel_scale == new_pixel_scale) return false;
  this->pixel_scale = new_pixel_scale;
  return true;
}

void fsweep::DesktopModel::leftPress() { this->left_down = true; }

void fsweep::DesktopModel::leftRelease(fsweep::Timer& timer)
{
  auto& game_model = this->game_model.get();
  if (game_model.getGameState() == fsweep::GameState::Playing)
  {
    game_model.updateTime(timer.getGameTime());
  }
  auto initially_playing = game_model.getGameState() == fsweep::GameState::Playing;
  if (this->hover_button_o.has_value())
  {
    auto& hover_button = this->hover_button_o.value();
    if (this->right_down)
    {
      game_model.areaClickButton(hover_button.x, hover_button.y);
    }
    else
    {
      game_model.clickButton(hover_button.x, hover_button.y);
    }
    if (game_model.getGameState() == fsweep::GameState::Playing && !initially_playing)
    {
      timer.start();
    }
    else if (game_model.getGameState() == fsweep::GameState::Dead ||
              game_model.getGameState() == fsweep::GameState::Cool && initially_playing)
    {
      timer.stop();
    }
  }
  else if (this->hover_face)
  {
    game_model.newGame();
    timer.stop();
  }
  this->left_down = false;
}

void fsweep::DesktopModel::rightPress(fsweep::Timer& timer)
{
  auto& game_model = this->game_model.get();
  this->right_down = true;
  if (game_model.getGameState() == fsweep::GameState::Playing)
  {
    game_model.updateTime(timer.getGameTime());
  }
  if (!this->left_down && this->hover_button_o.has_value())
  {
    auto& hover_button = this->hover_button_o.value();
    game_model.altClickButton(hover_button.x, hover_button.y);
  }
}

void fsweep::DesktopModel::rightRelease(fsweep::Timer& timer)
{
  auto& game_model = this->game_model.get();
  auto initially_playing = game_model.getGameState() == fsweep::GameState::Playing;
  if (this->hover_button_o.has_value() && this->left_down)
  {
    auto& hover_button = this->hover_button_o.value();
    game_model.areaClickButton(hover_button.x, hover_button.y);
    if (game_model.getGameState() == fsweep::GameState::Dead ||
              game_model.getGameState() == fsweep::GameState::Cool)
    {
      timer.stop();
    }
  }
  this->right_down = false;
}

void fsweep::DesktopModel::mouseLeave() { this->hover_button_o = std::nullopt; }

void fsweep::DesktopModel::mouseMove(int x, int y)
{
  this->hover_button_o = std::nullopt;
  if (x >= this->getBorderSize() && x < this->getSize().x - this->getBorderSize() &&
      y >= this->getHeaderHeight() && y < this->getSize().y - this->getBorderSize())
  {
    this->hover_button_o =
        fsweep::ButtonPosition((x - this->getBorderSize()) / this->getButtonDimension(),
                               (y - this->getHeaderHeight()) / this->getButtonDimension());
  }
  const auto face_point = this->getFacePoint();
  this->hover_face = x >= face_point.x && x < face_point.x + this->getFaceDimension() &&
                     y >= face_point.y && y < face_point.y + this->getFaceDimension();
}

const int FACE_BUTTON_DIMENSION = 24;
const int BORDER_SIZE = 8;
const int BUTTON_DIMENSION = 16;
const int LCD_DIGIT_WIDTH = 16;
const int HEADER_HEIGHT = BORDER_SIZE * 2 + FACE_BUTTON_DIMENSION;

int fsweep::DesktopModel::getPixelScale() const noexcept { return this->pixel_scale; }

int fsweep::DesktopModel::getFaceDimension() const noexcept
{
  return this->pixel_scale * FACE_BUTTON_DIMENSION;
}

int fsweep::DesktopModel::getBorderSize() const noexcept { return this->pixel_scale * BORDER_SIZE; }

int fsweep::DesktopModel::getButtonDimension() const noexcept
{
  return this->pixel_scale * BUTTON_DIMENSION;
}

int fsweep::DesktopModel::getLcdDigitWidth() const noexcept
{
  return this->pixel_scale * LCD_DIGIT_WIDTH;
}

int fsweep::DesktopModel::getHeaderHeight() const noexcept
{
  return this->pixel_scale * HEADER_HEIGHT;
}

fsweep::Sprite fsweep::DesktopModel::getFaceSprite() const noexcept
{
  const auto& game_model = this->game_model.get();
  if (game_model.getGameState() == fsweep::GameState::None ||
      game_model.getGameState() == fsweep::GameState::Playing)
  {
    if (this->left_down && this->hover_face)
    {
      return fsweep::Sprite::ButtonSmileDown;
    }
    else if (this->left_down && this->hover_button_o.has_value())
    {
      const auto& hover_button = this->hover_button_o.value();
      const auto& button = game_model.getButton(hover_button.x, hover_button.y);
      if (button.getButtonState() != fsweep::ButtonState::Down &&
          button.getButtonState() != fsweep::ButtonState::Flagged)
      {
        return fsweep::Sprite::ButtonShocked;
      }
    }
  }
  else if (game_model.getGameState() == fsweep::GameState::Cool)
  {
    if (this->left_down && this->hover_face)
    {
      return fsweep::Sprite::ButtonSmileDown;
    }
    else
    {
      return fsweep::Sprite::ButtonCool;
    }
  }
  else  // if (model.getGameState() == fsweep::GameState::Dead)
  {
    if (this->left_down && this->hover_face)
    {
      return fsweep::Sprite::ButtonSmileDown;
    }
    else
    {
      return fsweep::Sprite::ButtonDead;
    }
  }
  return fsweep::Sprite::ButtonSmile;
}

fsweep::Sprite fsweep::DesktopModel::getButtonSprite(int x, int y) const noexcept
{
  const auto& game_model = this->game_model.get();
  if (x >= game_model.getGameConfiguration().getButtonsWide() ||
      y >= game_model.getGameConfiguration().getButtonsTall())
  {
    return fsweep::Sprite::ButtonNone;
  }
  const auto& button = game_model.getButton(x, y);
  auto button_position = fsweep::ButtonPosition(x, y);
  if (game_model.getGameState() == fsweep::GameState::None ||
      game_model.getGameState() == fsweep::GameState::Playing)
  {
    if (button.getButtonState() != fsweep::ButtonState::Flagged &&
        button.getButtonState() != fsweep::ButtonState::Down && this->left_down &&
        this->hover_button_o.has_value())
    {
      const auto& hover_button = this->hover_button_o.value();
      if ((hover_button == button_position) ||
          (this->right_down && hover_button.isNear(button_position)))
      {
        if (fsweep::ButtonState() == fsweep::ButtonState::Questioned)
        {
          return fsweep::Sprite::ButtonQuestionDown;
        }
        return fsweep::Sprite::ButtonDown;
      }
    }
    else if (button.getButtonState() == fsweep::ButtonState::Flagged)
    {
      return fsweep::Sprite::ButtonFlag;
    }
    else if (button.getButtonState() == fsweep::ButtonState::Questioned)
    {
      return fsweep::Sprite::ButtonQuestion;
    }
    else if (button.getButtonState() == fsweep::ButtonState::Down)
    {
      return fsweep::getDownButtonSprite(button.getSurroundingBombs());
    }
    else
    {
      return fsweep::Sprite::ButtonNone;
    }
  }
  else  // if (model.getGameState() == fsweep::GameState::Cool || model.getGameState() ==
        // fsweep::GameState::Dead)
  {
    if (button.getButtonState() == fsweep::ButtonState::None ||
        button.getButtonState() == fsweep::ButtonState::Questioned)
    {
      if (button.getHasBomb())
      {
        return fsweep::Sprite::ButtonBomb;
      }
      else
      {
        return fsweep::Sprite::ButtonNone;
      }
    }
    else if (button.getButtonState() == fsweep::ButtonState::Flagged)
    {
      if (button.getHasBomb())
      {
        return fsweep::Sprite::ButtonFlagHit;
      }
      else
      {
        return fsweep::Sprite::ButtonFlagMiss;
      }
    }
    else if (button.getButtonState() == fsweep::ButtonState::Down)
    {
      if (button.getHasBomb())
      {
        return fsweep::Sprite::ButtonBombExplode;
      }
      else
      {
        return fsweep::getDownButtonSprite(button.getSurroundingBombs());
      }
    }
  }
  return fsweep::Sprite::ButtonNone;
}

fsweep::Point fsweep::DesktopModel::getFacePoint() const noexcept
{
  return fsweep::Point((this->getSize().x / 2) - (this->getFaceDimension() / 2),
                       this->getBorderSize());
}

fsweep::Point fsweep::DesktopModel::getButtonPoint(int x, int y) const noexcept
{
  return fsweep::Point(this->getBorderSize() + (x * this->getButtonDimension()),
                       this->getHeaderHeight() + (y * this->getButtonDimension()));
}

fsweep::Point fsweep::DesktopModel::getScorePoint(std::size_t digit) const noexcept
{
  return fsweep::Point(this->getBorderSize() + (this->getLcdDigitWidth() * digit),
                       this->getBorderSize());
}

fsweep::Point fsweep::DesktopModel::getTimerPoint(std::size_t digit) const noexcept
{
  return fsweep::Point(
      this->getSize().x - (this->getBorderSize() + (this->getLcdDigitWidth() * (3 - digit))),
      this->getBorderSize());
}

fsweep::Point fsweep::DesktopModel::getSize() const noexcept
{
  const auto& game_model = this->game_model.get();
  return fsweep::Point(
      (game_model.getGameConfiguration().getButtonsWide() *
       (this->pixel_scale * BUTTON_DIMENSION)) +
          ((this->pixel_scale * BORDER_SIZE) * 2),
      (game_model.getGameConfiguration().getButtonsTall() *
       (this->pixel_scale * BUTTON_DIMENSION)) +
          ((this->pixel_scale * BORDER_SIZE) + (this->pixel_scale * HEADER_HEIGHT)));
}
