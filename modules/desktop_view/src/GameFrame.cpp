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

#include "GameFrame.hpp"

#include <fsweep/GameConfiguration.hpp>
#include <fsweep/credits.hpp>
#include <fsweep/license.hpp>
#include <functional>

#include "AboutDialog.hpp"
#include "ConfigDialog.hpp"
#include "DesktopView.hpp"
#include "GamePanel.hpp"
#include "PixelScaleDialog.hpp"
#include "TextDialog.hpp"
#include "icon.hpp"
#include "wx_include.hpp"

BEGIN_EVENT_TABLE(fsweep::GameFrame, wxFrame)
EVT_MENU(wxID_NEW, fsweep::GameFrame::OnNew)
EVT_MENU(wxID_EXIT, fsweep::GameFrame::OnExit)
EVT_MENU(wxID_ABOUT, fsweep::GameFrame::OnAbout)
END_EVENT_TABLE()

void fsweep::GameFrame::resizeGamePanel(int x, int y) {
  wxSize size(x, y);
  this->SetClientSize(size);
  this->game_panel->SetSize(size);
}

fsweep::GameFrame::GameFrame(fsweep::DesktopView &view)
    : view(std::ref(view)),
      wxFrame(NULL, wxID_ANY, "FossSweeper", wxDefaultPosition, wxDefaultSize,
              wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX)) {
  this->SetIcon(wxIcon(fsweep::ICON_XPM_DATA));

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
  beginner_item = new wxMenuItem(game_menu, wxID_ANY, "&Beginner");
  beginner_item->SetCheckable(true);
  intermediate_item = new wxMenuItem(game_menu, wxID_ANY, "&Intermediate");
  intermediate_item->SetCheckable(true);
  expert_item = new wxMenuItem(game_menu, wxID_ANY, "&Expert");
  expert_item->SetCheckable(true);
  auto *const custom_item = new wxMenuItem(game_menu, wxID_ANY, "&Custom...");
  question_marks_item = new wxMenuItem(game_menu, wxID_ANY, "&Question Marks");
  question_marks_item->SetCheckable(true);
  auto *const pixel_scale_item =
      new wxMenuItem(game_menu, wxID_ANY, "&Pixel Scale...");
  auto *const exit_item = new wxMenuItem(game_menu, wxID_EXIT, "&Exit\tAlt+F4");

  // bind game menu items
  Bind(wxEVT_MENU, &fsweep::GameFrame::onNew, this, new_item->GetId());
  Bind(wxEVT_MENU, &fsweep::GameFrame::onBeginner, this,
       beginner_item->GetId());
  Bind(wxEVT_MENU, &fsweep::GameFrame::onIntermediate, this,
       intermediate_item->GetId());
  Bind(wxEVT_MENU, &fsweep::GameFrame::onExpert, this, expert_item->GetId());
  Bind(wxEVT_MENU, &fsweep::GameFrame::onCustom, this, custom_item->GetId());
  Bind(wxEVT_MENU, &fsweep::GameFrame::onQuestionMarks, this,
       question_marks_item->GetId());
  Bind(wxEVT_MENU, &fsweep::GameFrame::onPixelScale, this,
       pixel_scale_item->GetId());
  Bind(wxEVT_MENU, &fsweep::GameFrame::onExit, this, exit_item->GetId());

  // append menu items to game menu
  game_menu->Append(new_item);
  game_menu->AppendSeparator();
  game_menu->Append(beginner_item);
  game_menu->Append(intermediate_item);
  game_menu->Append(expert_item);
  game_menu->Append(custom_item);
  game_menu->AppendSeparator();
  game_menu->Append(question_marks_item);
  game_menu->Append(pixel_scale_item);
  game_menu->AppendSeparator();
  game_menu->Append(exit_item);

  // create help menu items
  auto *const credits_item = new wxMenuItem(help_menu, wxID_ANY, "&Credits...");
  auto *const license_item = new wxMenuItem(help_menu, wxID_ANY, "&License...");
  auto *const about_item = new wxMenuItem(help_menu, wxID_ABOUT, "&About...");

  // bind help menu items
  Bind(wxEVT_MENU, &fsweep::GameFrame::onCredits, this, credits_item->GetId());
  Bind(wxEVT_MENU, &fsweep::GameFrame::onLicense, this, license_item->GetId());
  Bind(wxEVT_MENU, &fsweep::GameFrame::onAbout, this, about_item->GetId());

  // append menu items to help menu
  help_menu->Append(credits_item);
  help_menu->Append(license_item);
  help_menu->Append(about_item);

  // check the beginner difficulty menu item
  beginner_item->Check(true);

  // create the game panel
  auto &desktop_model = view.getDesktopModel();
  const auto size = desktop_model.getSize();
  this->SetClientSize(size.x, size.y);
  this->game_panel = new fsweep::GamePanel(view, this, size.x, size.y);
  this->SetAutoLayout(true);
  this->game_panel->drawAll();
}

void fsweep::GameFrame::onNew(wxCommandEvent &WXUNUSED(e)) {
  this->view.get().getGameModel().newGame();
  this->game_panel->drawAll();
}

void fsweep::GameFrame::onBeginner(wxCommandEvent &WXUNUSED(e)) {
  auto &game_model = this->view.get().getGameModel();
  auto &desktop_model = this->view.get().getDesktopModel();
  this->beginner_item->Check(true);
  this->intermediate_item->Check(false);
  this->expert_item->Check(false);
  const fsweep::GameConfiguration game_configuration(
      fsweep::GameDifficulty::Beginner);
  game_model.newGame(game_configuration);
  auto size = desktop_model.getSize();
  this->resizeGamePanel(size.x, size.y);
  this->game_panel->drawAll();
}

void fsweep::GameFrame::onIntermediate(wxCommandEvent &WXUNUSED(e)) {
  auto &game_model = this->view.get().getGameModel();
  auto &desktop_model = this->view.get().getDesktopModel();
  this->beginner_item->Check(false);
  this->intermediate_item->Check(true);
  this->expert_item->Check(false);
  const fsweep::GameConfiguration game_configuration(
      fsweep::GameDifficulty::Intermediate);
  game_model.newGame(game_configuration);
  auto size = desktop_model.getSize();
  this->resizeGamePanel(size.x, size.y);
  this->game_panel->drawAll();
}

void fsweep::GameFrame::onExpert(wxCommandEvent &WXUNUSED(e)) {
  auto &game_model = this->view.get().getGameModel();
  auto &desktop_model = this->view.get().getDesktopModel();
  this->beginner_item->Check(false);
  this->intermediate_item->Check(false);
  this->expert_item->Check(true);
  const fsweep::GameConfiguration game_configuration(
      fsweep::GameDifficulty::Expert);
  game_model.newGame(game_configuration);
  auto size = desktop_model.getSize();
  this->resizeGamePanel(size.x, size.y);
  this->game_panel->drawAll();
}

void fsweep::GameFrame::onCustom(wxCommandEvent &WXUNUSED(e)) {
  fsweep::ConfigDialog config_dialog(this);
  const auto dialog_result = config_dialog.ShowModal();
  if (dialog_result == wxOK) {
    auto &game_model = this->view.get().getGameModel();
    auto &desktop_model = this->view.get().getDesktopModel();
    const fsweep::GameConfiguration game_configuration(
        config_dialog.getButtonsWide(), config_dialog.getButtonsTall(),
        config_dialog.getBombCount());
    game_model.newGame(game_configuration);
    auto size = desktop_model.getSize();
    this->resizeGamePanel(size.x, size.y);
    this->game_panel->drawAll();
  }
}

void fsweep::GameFrame::onQuestionMarks(wxCommandEvent &WXUNUSED(e)) {
  const auto questions_enabled = question_marks_item->IsChecked();
  this->view.get().getGameModel().setQuestionsEnabled(questions_enabled);
  this->game_panel->drawChanged();
}

void fsweep::GameFrame::onPixelScale(wxCommandEvent &e) {
  const auto &desktop_model = this->view.get().getDesktopModel();
  fsweep::PixelScaleDialog pixel_scale_dialog(
      this, this->game_panel->getPixelScale());
  const auto dialog_result = pixel_scale_dialog.ShowModal();
  if (dialog_result == wxOK) {
    if (this->game_panel->tryChangePixelScale(
            pixel_scale_dialog.getPixelScale())) {
      const auto size = desktop_model.getSize();
      this->resizeGamePanel(size.x, size.y);
      this->game_panel->drawAll();
    }
  }
}

void fsweep::GameFrame::onExit(wxCommandEvent &WXUNUSED(e)) { this->Close(); }

void fsweep::GameFrame::onCredits(wxCommandEvent &e) {
  auto credits_dialog = fsweep::createCreditsDialog(this);
  credits_dialog.ShowModal();
}

void fsweep::GameFrame::onLicense(wxCommandEvent &WXUNUSED(e)) {
  auto license_dialog = fsweep::createLicenseDialog(this);
  license_dialog.ShowModal();
}

void fsweep::GameFrame::onAbout(wxCommandEvent &WXUNUSED(e)) {
  fsweep::AboutDialog about_dialog(this);
  about_dialog.ShowModal();
}
