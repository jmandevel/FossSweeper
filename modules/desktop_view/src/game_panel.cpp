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

const int MILLISECONDS_PER_SECOND = 1000;
const int TIMER_INTERVAL = MILLISECONDS_PER_SECOND / 15;

#include "game_panel.hpp"
#include "desktop_view.hpp"

#include <cstddef>
#include <fosssweeper/desktop_model.hpp>
#include <fosssweeper/sprite.hpp>
#include <functional>
#include <optional>

#include "spritesheet.hpp"
#include "wx_include.hpp"

BEGIN_EVENT_TABLE(fosssweeper::GamePanel, wxPanel)
EVT_PAINT(fosssweeper::GamePanel::onRender)
EVT_MOTION(fosssweeper::GamePanel::onMouseMove)
EVT_LEFT_DOWN(fosssweeper::GamePanel::onLeftPress)
EVT_LEFT_UP(fosssweeper::GamePanel::onLeftRelease)
EVT_RIGHT_DOWN(fosssweeper::GamePanel::onRightPress)
EVT_RIGHT_UP(fosssweeper::GamePanel::onRightRelease)
EVT_LEAVE_WINDOW(fosssweeper::GamePanel::onMouseLeave)
END_EVENT_TABLE()

wxBitmap &fosssweeper::GamePanel::getBitmap(fosssweeper::Sprite sprite) {
  return this->_scaledBitmaps[static_cast<std::size_t>(sprite)];
}

fosssweeper::GamePanel::GamePanel(fosssweeper::DesktopView &desktop_view, wxFrame *parent,
                             int width, int height)
    : wxPanel(parent, wxID_ANY), _desktopView(std::ref(desktop_view)),
      _timer(this) {
  Bind(wxEVT_TIMER, &GamePanel::onTimer, this, this->_timer.getTimer().GetId());
  for (std::size_t bitmap_i = 0;
       bitmap_i < static_cast<std::size_t>(fosssweeper::Sprite::Count); bitmap_i++) {
    this->_baseBitmaps[bitmap_i] =
        wxBitmap(fosssweeper::SPRITESHEET_XPM_DATA[bitmap_i]);
    this->_scaledBitmaps[bitmap_i] = wxBitmap(this->_baseBitmaps[bitmap_i]);
  }
  this->SetSize(wxSize(width, height));
}

fosssweeper::GamePanel::~GamePanel() {}

void fosssweeper::GamePanel::onRender(wxPaintEvent &WXUNUSED(e)) { this->drawAll(); }

void fosssweeper::GamePanel::onMouseMove(wxMouseEvent &e) {
  auto &desktop_model = this->_desktopView.get().getDesktopModel();
  wxPoint mouse_position = e.GetPosition();
  desktop_model.mouseMove(mouse_position.x, mouse_position.y);
  this->drawChanged();
}

void fosssweeper::GamePanel::onLeftPress(wxMouseEvent &WXUNUSED(e)) {
  auto &desktop_model = this->_desktopView.get().getDesktopModel();
  desktop_model.leftPress();
  if (!this->HasCapture()) {
    this->CaptureMouse(); // prevents issues when mouse leaves the window on
                          // Windows platform
  }
  this->drawChanged();
}

void fosssweeper::GamePanel::onLeftRelease(wxMouseEvent &WXUNUSED(e)) {
  auto &desktop_model = this->_desktopView.get().getDesktopModel();
  desktop_model.leftRelease(this->_timer);
  if (this->HasCapture()) {
    this->ReleaseMouse(); // undo the CaptureMouse() from the press event
  }
  this->drawChanged();
}

void fosssweeper::GamePanel::onRightPress(wxMouseEvent &WXUNUSED(e)) {
  auto &desktop_model = this->_desktopView.get().getDesktopModel();
  desktop_model.rightPress(this->_timer);
  if (!this->HasCapture()) {
    this->CaptureMouse();
  }
  this->drawChanged();
}

void fosssweeper::GamePanel::onRightRelease(wxMouseEvent &WXUNUSED(e)) {
  auto &desktop_model = this->_desktopView.get().getDesktopModel();
  desktop_model.rightRelease(this->_timer);
  if (this->HasCapture()) {
    this->ReleaseMouse();
  }
  this->drawChanged();
}

void fosssweeper::GamePanel::onMouseLeave(wxMouseEvent &WXUNUSED(e)) {
  auto &desktop_model = this->_desktopView.get().getDesktopModel();
  desktop_model.mouseLeave();
  this->drawChanged();
}

void fosssweeper::GamePanel::onTimer(wxTimerEvent &WXUNUSED(e)) {
  auto &game_model = this->_desktopView.get().getGameModel();
  game_model.updateTime(this->_timer.getGameTime());
  this->drawChanged(true);
}

bool fosssweeper::GamePanel::tryChangePixelScale(int new_pixel_scale) {
  auto &desktop_model = this->_desktopView.get().getDesktopModel();
  if (desktop_model.tryChangePixelScale(new_pixel_scale)) {
    for (std::size_t bitmap_i = 0;
         bitmap_i < static_cast<std::size_t>(fosssweeper::Sprite::Count);
         bitmap_i++) {
      const auto &base_bitmap = this->_baseBitmaps[bitmap_i];
      auto image = base_bitmap.ConvertToImage();
      image.Rescale(base_bitmap.GetWidth() * new_pixel_scale,
                    base_bitmap.GetHeight() * new_pixel_scale);
      this->_scaledBitmaps[bitmap_i] = wxBitmap(image);
    }
    return true;
  } else
    return false;
}

int fosssweeper::GamePanel::getPixelScale() const noexcept {
  auto &desktop_model = this->_desktopView.get().getDesktopModel();
  return desktop_model.getPixelScale();
}

void fosssweeper::GamePanel::drawAll() {
  const auto &desktop_model = this->_desktopView.get().getDesktopModel();
  const auto &game_model = this->_desktopView.get().getGameModel();
  fosssweeper::Point point;
  wxPoint wx_point;
  wxClientDC dc(this);
  dc.SetBrush(wxBrush(wxColour(142, 142, 142)));
  point = desktop_model.getSize();
  wx_point = wxPoint(point.x, point.y);
  dc.DrawRectangle(wxRect(wxPoint(0, 0), wx_point));
  dc.DrawBitmap(this->getBitmap(fosssweeper::Sprite::BorderLeftTop), wxPoint(0, 0),
                false);
  dc.DrawBitmap(
      this->getBitmap(fosssweeper::Sprite::BorderRightTop),
      wxPoint(desktop_model.getSize().x - desktop_model.getBorderSize(), 0),
      false);
  dc.DrawBitmap(
      this->getBitmap(fosssweeper::Sprite::BorderLeftBottom),
      wxPoint(0, desktop_model.getSize().y - desktop_model.getBorderSize()),
      false);
  dc.DrawBitmap(
      this->getBitmap(fosssweeper::Sprite::BorderRightBottom),
      wxPoint(desktop_model.getSize().x - desktop_model.getBorderSize(),
              desktop_model.getSize().y - desktop_model.getBorderSize()),
      false);
  for (std::size_t i = 0;
       i < (desktop_model.getSize().x / desktop_model.getBorderSize()) - 2;
       i++) {
    dc.DrawBitmap(this->getBitmap(fosssweeper::Sprite::BorderTop),
                  wxPoint(desktop_model.getBorderSize() +
                              (i * desktop_model.getBorderSize()),
                          0),
                  false);
  }
  for (std::size_t i = 0;
       i < (this->GetSize().x / desktop_model.getBorderSize()) - 2; i++) {
    dc.DrawBitmap(
        this->getBitmap(fosssweeper::Sprite::BorderBottom),
        wxPoint(desktop_model.getBorderSize() +
                    (i * desktop_model.getBorderSize()),
                desktop_model.getSize().y - desktop_model.getBorderSize()),
        false);
  }
  dc.DrawBitmap(this->getBitmap(fosssweeper::Sprite::BorderLeftIntersection),
                wxPoint(0, desktop_model.getBorderSize() * 4), false);
  dc.DrawBitmap(
      this->getBitmap(fosssweeper::Sprite::BorderRightIntersection),
      wxPoint(desktop_model.getSize().x - desktop_model.getBorderSize(),
              desktop_model.getBorderSize() * 4),
      false);
  for (std::size_t i = 0;
       i < (desktop_model.getSize().x / desktop_model.getBorderSize()) - 2;
       i++) {
    dc.DrawBitmap(this->getBitmap(fosssweeper::Sprite::BorderTop),
                  wxPoint(desktop_model.getBorderSize() +
                              (i * desktop_model.getBorderSize()),
                          desktop_model.getBorderSize() * 4),
                  false);
  }
  for (std::size_t i = 1; i < 4; i++) {
    dc.DrawBitmap(this->getBitmap(fosssweeper::Sprite::BorderLeft),
                  wxPoint(0, i * desktop_model.getBorderSize()), false);
  }
  for (std::size_t i = 1; i < 4; i++) {
    dc.DrawBitmap(
        this->getBitmap(fosssweeper::Sprite::BorderRight),
        wxPoint(desktop_model.getSize().x - desktop_model.getBorderSize(),
                i * desktop_model.getBorderSize()),
        false);
  }
  for (std::size_t i = 5;
       i < (desktop_model.getSize().y / desktop_model.getBorderSize()) - 1;
       i++) {
    dc.DrawBitmap(this->getBitmap(fosssweeper::Sprite::BorderLeft),
                  wxPoint(0, i * desktop_model.getBorderSize()), false);
  }
  for (std::size_t i = 5;
       i < (desktop_model.getSize().y / desktop_model.getBorderSize()) - 1;
       i++) {
    dc.DrawBitmap(
        this->getBitmap(fosssweeper::Sprite::BorderRight),
        wxPoint(desktop_model.getSize().x - desktop_model.getBorderSize(),
                i * desktop_model.getBorderSize()),
        false);
  }
  const auto score_lcd = fosssweeper::LcdNumber(game_model.getBombsLeft());
  for (std::size_t digit_i = 0; digit_i < 3; digit_i++) {
    const auto lcd_sprite = fosssweeper::getSpriteFromDigit(score_lcd[digit_i]);
    point = desktop_model.getScorePoint(digit_i);
    wx_point = wxPoint(point.x, point.y);
    dc.DrawBitmap(this->getBitmap(lcd_sprite), wx_point, false);
    this->_gamePanelState.score_lcd[digit_i] = lcd_sprite;
  }
  const auto time_lcd = fosssweeper::LcdNumber(game_model.getTimerSeconds());
  for (std::size_t digit_i = 0; digit_i < 3; digit_i++) {
    const auto lcd_sprite = fosssweeper::getSpriteFromDigit(time_lcd[digit_i]);
    point = desktop_model.getTimerPoint(digit_i);
    wx_point = wxPoint(point.x, point.y);
    dc.DrawBitmap(this->getBitmap(lcd_sprite), wx_point, false);
    this->_gamePanelState.time_lcd[digit_i] = lcd_sprite;
  }
  const auto face_sprite = desktop_model.getFaceSprite();
  point = desktop_model.getFacePoint();
  wx_point = wxPoint(point.x, point.y);
  dc.DrawBitmap(this->getBitmap(face_sprite), wx_point, false);
  this->_gamePanelState.face_sprite = face_sprite;
  this->_gamePanelState.button_sprites.clear();
  this->_gamePanelState.button_sprites.reserve(
      game_model.getGameConfiguration().getButtonCount());
  for (int x = 0; x < game_model.getGameConfiguration().getButtonsWide(); x++) {
    for (int y = 0; y < game_model.getGameConfiguration().getButtonsTall();
         y++) {
      const auto button_sprite = desktop_model.getButtonSprite(x, y);
      point = desktop_model.getButtonPoint(x, y);
      wx_point = wxPoint(point.x, point.y);
      dc.DrawBitmap(this->getBitmap(desktop_model.getButtonSprite(x, y)),
                    wx_point, false);
      this->_gamePanelState.button_sprites.push_back(button_sprite);
    }
  }
}

void fosssweeper::GamePanel::drawChanged(bool timer_only) {
  fosssweeper::Point point;
  wxPoint wx_point;
  const auto &game_model = this->_desktopView.get().getGameModel();
  const auto &desktop_model = this->_desktopView.get().getDesktopModel();
  const auto buttons_wide = game_model.getGameConfiguration().getButtonsWide();
  [[maybe_unused]] wxClientDC dc(this);
  const auto time_lcd = fosssweeper::LcdNumber(game_model.getTimerSeconds());
  for (std::size_t digit_i = 0; digit_i < 3; digit_i++) {
    const auto lcd_sprite = fosssweeper::getSpriteFromDigit(time_lcd[digit_i]);
    if (this->_gamePanelState.time_lcd[digit_i] != lcd_sprite) {
      point = desktop_model.getTimerPoint(digit_i);
      wx_point = wxPoint(point.x, point.y);
      dc.DrawBitmap(this->getBitmap(lcd_sprite), wx_point, false);
      this->_gamePanelState.time_lcd[digit_i] = lcd_sprite;
    }
  }
  if (timer_only)
    return;
  auto score_lcd = fosssweeper::LcdNumber(game_model.getBombsLeft());
  for (std::size_t digit_i = 0; digit_i < 3; digit_i++) {
    const auto lcd_sprite = fosssweeper::getSpriteFromDigit(score_lcd[digit_i]);
    if (this->_gamePanelState.score_lcd[digit_i] != lcd_sprite) {
      point = desktop_model.getScorePoint(digit_i);
      wx_point = wxPoint(point.x, point.y);
      dc.DrawBitmap(this->getBitmap(lcd_sprite), wx_point, false);
      this->_gamePanelState.score_lcd[digit_i] = lcd_sprite;
    }
  }
  const auto face_sprite = desktop_model.getFaceSprite();
  if (face_sprite != this->_gamePanelState.face_sprite) {
    point = desktop_model.getFacePoint();
    wx_point = wxPoint(point.x, point.y);
    dc.DrawBitmap(this->getBitmap(face_sprite), wx_point, false);
    this->_gamePanelState.face_sprite = face_sprite;
  }
  for (int x = 0; x < game_model.getGameConfiguration().getButtonsWide(); x++) {
    for (int y = 0; y < game_model.getGameConfiguration().getButtonsTall();
         y++) {
      const fosssweeper::ButtonPosition button_position(x, y);
      const auto button_sprite = desktop_model.getButtonSprite(x, y);
      if (button_sprite !=
          this->_gamePanelState
              .button_sprites[button_position.getIndex(buttons_wide)]) {
        point = desktop_model.getButtonPoint(x, y);
        wx_point = wxPoint(point.x, point.y);
        dc.DrawBitmap(this->getBitmap(button_sprite), wx_point, false);
        this->_gamePanelState
            .button_sprites[button_position.getIndex(buttons_wide)] =
            button_sprite;
      }
    }
  }
}