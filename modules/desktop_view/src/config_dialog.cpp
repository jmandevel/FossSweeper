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

#include "config_dialog.hpp"

#include "wx_include.hpp"

fosssweeper::ConfigDialog::ConfigDialog(wxWindow *parent)
    : wxDialog(parent, wxID_ANY, wxT("FossSweeper Custom Configuration")) {
  auto *const sizer = new wxBoxSizer(wxVERTICAL);

  auto *const buttons_wide_sizer = new wxBoxSizer(wxHORIZONTAL);
  buttons_wide_sizer->Add(new wxStaticText(this, wxID_ANY, wxT("Buttons Wide: ")));
  this->_buttonsWideCtrl = new wxSpinCtrl(this, wxID_ANY);
  this->_buttonsWideCtrl->SetRange(fosssweeper::GameConfiguration::MIN_BUTTONS_WIDE,
                                    64);
  buttons_wide_sizer->Add(this->_buttonsWideCtrl);
  sizer->Add(buttons_wide_sizer, 0, wxALIGN_CENTER | wxALL, 5);

  auto *const buttons_tall_sizer = new wxBoxSizer(wxHORIZONTAL);
  buttons_tall_sizer->Add(new wxStaticText(this, wxID_ANY, wxT("Buttons Tall: ")));
  this->_buttonsTallCtrl = new wxSpinCtrl(this, wxID_ANY);
  this->_buttonsTallCtrl->SetRange(fosssweeper::GameConfiguration::MIN_BUTTONS_TALL,
                                    64);
  buttons_tall_sizer->Add(this->_buttonsTallCtrl);
  sizer->Add(buttons_tall_sizer, 0, wxALIGN_CENTER | wxALL, 5);

  auto *const bomb_count_sizer = new wxBoxSizer(wxHORIZONTAL);
  bomb_count_sizer->Add(new wxStaticText(this, wxID_ANY, wxT("Snake Count: ")));
  this->_bombsCtrl = new wxSpinCtrl(this, wxID_ANY);
  bomb_count_sizer->Add(this->_bombsCtrl);
  sizer->Add(bomb_count_sizer, 0, wxALIGN_CENTER | wxALL, 5);

  auto *const button_sizer = new wxBoxSizer(wxHORIZONTAL);
  auto *const cancel_button = new wxButton(this, wxID_CANCEL, wxT("Cancel"));
  button_sizer->Add(cancel_button, 0, wxALIGN_CENTER | wxALL, 10);
  Bind(wxEVT_BUTTON, &fosssweeper::ConfigDialog::onCancel, this,
       cancel_button->GetId());
  auto *const confirm_button = new wxButton(this, wxID_OK, wxT("Confirm"));
  confirm_button->SetDefault();
  Bind(wxEVT_BUTTON, &fosssweeper::ConfigDialog::onConfirm, this,
       confirm_button->GetId());
  button_sizer->Add(confirm_button, 0, wxALIGN_CENTER | wxALL, 10);
  sizer->Add(button_sizer, 0, wxALIGN_CENTER | wxALL, 5);

  this->SetSizerAndFit(sizer);
  sizer->Layout();
}

void fosssweeper::ConfigDialog::onConfirm(wxCommandEvent &WXUNUSED(e)) {
  this->_buttonsWide = this->_buttonsWideCtrl->GetValue();
  this->_buttonsTall = this->_buttonsTallCtrl->GetValue();
  this->_bombCount = this->_bombsCtrl->GetValue();
  this->EndModal(wxOK);
}

void fosssweeper::ConfigDialog::onCancel(wxCommandEvent &WXUNUSED(e)) {
  this->EndModal(wxCANCEL);
}

int fosssweeper::ConfigDialog::getButtonsWide() const noexcept {
  return this->_buttonsWide;
}

int fosssweeper::ConfigDialog::getButtonsTall() const noexcept {
  return this->_buttonsTall;
}

int fosssweeper::ConfigDialog::getBombCount() const noexcept {
  return this->_bombCount;
}