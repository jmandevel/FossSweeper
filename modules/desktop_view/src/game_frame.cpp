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

#include "game_frame.hpp"

#include <fosssweeper/game_configuration.hpp>
#include <fosssweeper/credits.hpp>
#include <fosssweeper/license.hpp>
#include <functional>

#include "about_dialog.hpp"
#include "config_dialog.hpp"
#include "desktop_view.hpp"
#include "game_panel.hpp"
#include "pixel_scale_dialog.hpp"
#include "text_dialog.hpp"
#include "icon.hpp"
#include "wx_include.hpp"

BEGIN_EVENT_TABLE(fosssweeper::GameFrame, wxFrame)
EVT_MENU(wxID_NEW, fosssweeper::GameFrame::onNew)
EVT_MENU(wxID_EXIT, fosssweeper::GameFrame::onExit)
EVT_MENU(wxID_ABOUT, fosssweeper::GameFrame::onAbout)
END_EVENT_TABLE()

void fosssweeper::GameFrame::resizeGamePanel(int x, int y) {
  wxSize size(x, y);
  this->SetClientSize(size);
  this->_gamePanel->SetSize(size);
}

fosssweeper::GameFrame::GameFrame(fosssweeper::DesktopView &view)
    : _view(std::ref(view)),
      wxFrame(NULL, wxID_ANY, "FossSweeper", wxDefaultPosition, wxDefaultSize,
              wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX)) {
  this->SetIcon(wxIcon(fosssweeper::ICON_XPM_DATA));

  // create top menu bar
  auto menu_bar = new wxMenuBar;
  this->SetMenuBar(menu_bar);

  // create top menu bar menus
  auto *const game_menu = new wxMenu;
  auto *const help_menu = new wxMenu;

  // add menus to top menu bar
  menu_bar->Append(game_menu, _("&Game"));
  menu_bar->Append(help_menu, _("&Help"));

  // create game menu items
  auto *const new_item = new wxMenuItem(game_menu, wxID_NEW, "&New\tF2");
  this->_beginnerItem = new wxMenuItem(game_menu, wxID_ANY, "&Beginner");
  this->_beginnerItem->SetCheckable(true);
  this->_intermediateItem = new wxMenuItem(game_menu, wxID_ANY, "&Intermediate");
  this->_intermediateItem->SetCheckable(true);
  this->_expertItem = new wxMenuItem(game_menu, wxID_ANY, "&Expert");
  this->_expertItem->SetCheckable(true);
  auto *const custom_item = new wxMenuItem(game_menu, wxID_ANY, "&Custom...");
  this->_questionMarksItem = new wxMenuItem(game_menu, wxID_ANY, "&Question Marks");
  this->_questionMarksItem->SetCheckable(true);
  auto *const pixel_scale_item =
      new wxMenuItem(game_menu, wxID_ANY, "&Pixel Scale...");
  auto *const exit_item = new wxMenuItem(game_menu, wxID_EXIT, "&Exit\tAlt+F4");

  // bind game menu items
  Bind(wxEVT_MENU, &fosssweeper::GameFrame::onNew, this, new_item->GetId());
  Bind(wxEVT_MENU, &fosssweeper::GameFrame::onBeginner, this,
       this->_beginnerItem->GetId());
  Bind(wxEVT_MENU, &fosssweeper::GameFrame::onIntermediate, this,
       this->_intermediateItem->GetId());
  Bind(wxEVT_MENU, &fosssweeper::GameFrame::onExpert, this, this->_expertItem->GetId());
  Bind(wxEVT_MENU, &fosssweeper::GameFrame::onCustom, this, custom_item->GetId());
  Bind(wxEVT_MENU, &fosssweeper::GameFrame::onQuestionMarks, this,
       this->_questionMarksItem->GetId());
  Bind(wxEVT_MENU, &fosssweeper::GameFrame::onPixelScale, this,
       pixel_scale_item->GetId());
  Bind(wxEVT_MENU, &fosssweeper::GameFrame::onExit, this, exit_item->GetId());

  // append menu items to game menu
  game_menu->Append(new_item);
  game_menu->AppendSeparator();
  game_menu->Append(this->_beginnerItem);
  game_menu->Append(this->_intermediateItem);
  game_menu->Append(this->_expertItem);
  game_menu->Append(custom_item);
  game_menu->AppendSeparator();
  game_menu->Append(this->_questionMarksItem);
  game_menu->Append(pixel_scale_item);
  game_menu->AppendSeparator();
  game_menu->Append(exit_item);

  // create help menu items
  auto *const credits_item = new wxMenuItem(help_menu, wxID_ANY, "&Credits...");
  auto *const license_item = new wxMenuItem(help_menu, wxID_ANY, "&License...");
  auto *const about_item = new wxMenuItem(help_menu, wxID_ABOUT, "&About...");

  // bind help menu items
  Bind(wxEVT_MENU, &fosssweeper::GameFrame::onCredits, this, credits_item->GetId());
  Bind(wxEVT_MENU, &fosssweeper::GameFrame::onLicense, this, license_item->GetId());
  Bind(wxEVT_MENU, &fosssweeper::GameFrame::onAbout, this, about_item->GetId());

  // append menu items to help menu
  help_menu->Append(credits_item);
  help_menu->Append(license_item);
  help_menu->Append(about_item);

  // check the beginner difficulty menu item
  this->_beginnerItem->Check(true);

  // create the game panel
  auto &desktop_model = _view.get().getDesktopModel();
  const auto size = desktop_model.getSize();
  this->SetClientSize(size.x, size.y);
  this->_gamePanel = new fosssweeper::GamePanel(view, this, size.x, size.y);
  this->SetAutoLayout(true);
  this->_gamePanel->drawAll();
}

void fosssweeper::GameFrame::onNew(wxCommandEvent &WXUNUSED(e)) {
  this->_view.get().getGameModel().newGame();
  this->_gamePanel->drawAll();
}

void fosssweeper::GameFrame::onBeginner(wxCommandEvent &WXUNUSED(e)) {
  auto &game_model = this->_view.get().getGameModel();
  auto &desktop_model = this->_view.get().getDesktopModel();
  this->_beginnerItem->Check(true);
  this->_intermediateItem->Check(false);
  this->_expertItem->Check(false);
  const fosssweeper::GameConfiguration game_configuration(
      fosssweeper::GameDifficulty::Beginner);
  game_model.newGame(game_configuration);
  auto size = desktop_model.getSize();
  this->resizeGamePanel(size.x, size.y);
  this->_gamePanel->drawAll();
}

void fosssweeper::GameFrame::onIntermediate(wxCommandEvent &WXUNUSED(e)) {
  auto &game_model = this->_view.get().getGameModel();
  auto &desktop_model = this->_view.get().getDesktopModel();
  this->_beginnerItem->Check(false);
  this->_intermediateItem->Check(true);
  this->_expertItem->Check(false);
  const fosssweeper::GameConfiguration game_configuration(
      fosssweeper::GameDifficulty::Intermediate);
  game_model.newGame(game_configuration);
  auto size = desktop_model.getSize();
  this->resizeGamePanel(size.x, size.y);
  this->_gamePanel->drawAll();
}

void fosssweeper::GameFrame::onExpert(wxCommandEvent &WXUNUSED(e)) {
  auto &game_model = this->_view.get().getGameModel();
  auto &desktop_model = this->_view.get().getDesktopModel();
  this->_beginnerItem->Check(false);
  this->_intermediateItem->Check(false);
  this->_expertItem->Check(true);
  const fosssweeper::GameConfiguration game_configuration(
      fosssweeper::GameDifficulty::Expert);
  game_model.newGame(game_configuration);
  auto size = desktop_model.getSize();
  this->resizeGamePanel(size.x, size.y);
  this->_gamePanel->drawAll();
}

void fosssweeper::GameFrame::onCustom(wxCommandEvent &WXUNUSED(e)) {
  fosssweeper::ConfigDialog config_dialog(this);
  const auto dialog_result = config_dialog.ShowModal();
  if (dialog_result == wxOK) {
    auto &game_model = this->_view.get().getGameModel();
    auto &desktop_model = this->_view.get().getDesktopModel();
    const fosssweeper::GameConfiguration game_configuration(
        config_dialog.getButtonsWide(), config_dialog.getButtonsTall(),
        config_dialog.getBombCount());
    game_model.newGame(game_configuration);
    auto size = desktop_model.getSize();
    this->resizeGamePanel(size.x, size.y);
    this->_gamePanel->drawAll();
  }
}

void fosssweeper::GameFrame::onQuestionMarks(wxCommandEvent &WXUNUSED(e)) {
  const auto questions_enabled = this->_questionMarksItem->IsChecked();
  this->_view.get().getGameModel().setQuestionsEnabled(questions_enabled);
  this->_gamePanel->drawChanged();
}

void fosssweeper::GameFrame::onPixelScale(wxCommandEvent &e) {
  const auto &desktop_model = this->_view.get().getDesktopModel();
  fosssweeper::PixelScaleDialog pixel_scale_dialog(
      this, this->_gamePanel->getPixelScale());
  const auto dialog_result = pixel_scale_dialog.ShowModal();
  if (dialog_result == wxOK) {
    if (this->_gamePanel->tryChangePixelScale(
            pixel_scale_dialog.getPixelScale())) {
      const auto size = desktop_model.getSize();
      this->resizeGamePanel(size.x, size.y);
      this->_gamePanel->drawAll();
    }
  }
}

void fosssweeper::GameFrame::onExit(wxCommandEvent &WXUNUSED(e)) { this->Close(); }

void fosssweeper::GameFrame::onCredits(wxCommandEvent &e) {
  auto credits_dialog = fosssweeper::createCreditsDialog(this);
  credits_dialog.ShowModal();
}

void fosssweeper::GameFrame::onLicense(wxCommandEvent &WXUNUSED(e)) {
  auto license_dialog = fosssweeper::createLicenseDialog(this);
  license_dialog.ShowModal();
}

void fosssweeper::GameFrame::onAbout(wxCommandEvent &WXUNUSED(e)) {
  fosssweeper::AboutDialog about_dialog(this);
  about_dialog.ShowModal();
}
