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

#include "about_dialog.hpp"

#include <wx/clipbrd.h>
#include <wx/hyperlink.h>

#include <fosssweeper/credits.hpp>
#include <fosssweeper/license.hpp>
#include <fosssweeper/short_hash.hpp>
#include <fosssweeper/version.hpp>
#include <sstream>

#include "text_dialog.hpp"
#include "wx_include.hpp"

fosssweeper::AboutDialog::AboutDialog(wxWindow *parent)
    : wxDialog(parent, wxID_ANY, wxT("About FossSweeper")) {
  auto *const sizer = new wxBoxSizer(wxVERTICAL);

  auto *const header = new wxStaticText(this, wxID_ANY, wxT("FossSweeper"));
  auto header_font = header->GetFont();
  header_font.SetPointSize(24);
  header_font.SetWeight(wxFONTWEIGHT_BOLD);
  header->SetFont(header_font);
  sizer->Add(header, 0, wxALIGN_CENTER | wxUP | wxLEFT | wxRIGHT, 20);

  std::stringstream version_ss("");
  version_ss << "v" << FOSSSWEEPER_VERSION << " " << FOSSSWEEPER_SHORT_HASH;
  auto *const version =
      new wxStaticText(this, wxID_ANY, version_ss.str().data());
  auto version_font = version->GetFont();
  version_font.SetPointSize(18);
  version_font.SetWeight(wxFONTWEIGHT_LIGHT);
  version_font.SetStyle(wxFONTSTYLE_ITALIC);
  version->SetFont(version_font);
  sizer->Add(version, 0, wxALIGN_CENTER | wxDOWN | wxLEFT | wxRIGHT, 20);

  auto *const subtext = new wxStaticText(
      this, wxID_ANY, wxT("An open source mine avoidance game."));
  auto subtext_font = subtext->GetFont();
  subtext_font.SetStyle(wxFONTSTYLE_ITALIC);
  sizer->Add(subtext, 0, wxALIGN_CENTER | wxALL, 20);
  auto *const info_sizer = new wxBoxSizer(wxHORIZONTAL);
  info_sizer->AddSpacer(20);
  auto *const info_text =
      new wxStaticText(this, wxID_ANY,
                       wxT("FossSweeper is released under the GNU General Public "
                           "License version 3. It was created "
                           "using the wxWidgets library, which is released under "
                           "the GNU General Public License "
                           "version 2 and is covered by FossSweeper's license."));
  info_text->Wrap(540);
  info_sizer->AddSpacer(20);
  info_sizer->Add(info_text, 0, wxALIGN_CENTER, 20);
  info_sizer->AddSpacer(20);
  sizer->Add(info_sizer);

  sizer->AddSpacer(20);

  auto *const itch_sizer = new wxBoxSizer(wxHORIZONTAL);
  itch_sizer->Add(new wxStaticText(this, wxID_ANY, wxT("Download Page: ")));
  itch_sizer->Add(new wxHyperlinkCtrl(
      this, wxID_ANY, "https://jmandevel.itch.io/FossSweeper",
      "https://jmandevel.itch.io/FossSweeper"));
  sizer->Add(itch_sizer, 0, wxALIGN_CENTER | wxALL, 5);

  auto *const source_sizer = new wxBoxSizer(wxHORIZONTAL);
  source_sizer->Add(new wxStaticText(this, wxID_ANY, wxT("Source Code: ")));
  source_sizer->Add(new wxHyperlinkCtrl(
      this, wxID_ANY, "https://github.com/jmandevel/FossSweeper",
      "https://github.com/jmandevel/FossSweeper"));
  sizer->Add(source_sizer, 0, wxALIGN_CENTER | wxALL, 5);

  auto *const wxwidgets_sizer = new wxBoxSizer(wxHORIZONTAL);
  wxwidgets_sizer->Add(new wxStaticText(this, wxID_ANY, wxT("wxWidgets: ")));
  wxwidgets_sizer->Add(new wxHyperlinkCtrl(this, wxID_ANY,
                                           "https://www.wxwidgets.org/",
                                           "https://www.wxwidgets.org/"));
  sizer->Add(wxwidgets_sizer, 0, wxALIGN_CENTER | wxALL, 5);

  auto *const gnu_sizer = new wxBoxSizer(wxHORIZONTAL);
  gnu_sizer->Add(new wxStaticText(this, wxID_ANY, wxT("License Info: ")));
  gnu_sizer->Add(new wxHyperlinkCtrl(
      this, wxID_ANY, "https://www.gnu.org/licenses/gpl-3.0.en.html",
      "https://www.gnu.org/licenses/gpl-3.0.en.html"));
  sizer->Add(gnu_sizer, 0, wxALIGN_CENTER | wxALL, 5);

  auto *const button_sizer = new wxBoxSizer(wxHORIZONTAL);
  auto *const copy_version_button =
      new wxButton(this, wxID_ANY, wxT("Copy Version"));
  Bind(wxEVT_BUTTON, &fosssweeper::AboutDialog::onCopyVersion, this,
       copy_version_button->GetId());
  button_sizer->Add(copy_version_button, 0, wxALIGN_CENTER | wxALL, 10);
  auto *const copy_hash_button = new wxButton(this, wxID_ANY, wxT("Copy Hash"));
  Bind(wxEVT_BUTTON, &fosssweeper::AboutDialog::onCopyHash, this,
       copy_hash_button->GetId());
  button_sizer->Add(copy_hash_button, 0, wxALIGN_CENTER | wxALL, 10);
  auto *const license_button = new wxButton(this, wxID_ANY, wxT("License"));
  Bind(wxEVT_BUTTON, &fosssweeper::AboutDialog::onLicense, this,
       license_button->GetId());
  button_sizer->Add(license_button, 0, wxALIGN_CENTER | wxALL, 10);
  auto *const credits_button = new wxButton(this, wxID_ANY, wxT("Credits"));
  Bind(wxEVT_BUTTON, &fosssweeper::AboutDialog::onCredits, this,
       credits_button->GetId());
  button_sizer->Add(credits_button, 0, wxALIGN_CENTER | wxALL, 10);
  auto *const close_button = new wxButton(this, wxID_OK, "Close");
  close_button->SetDefault();
  button_sizer->Add(close_button, 0, wxALIGN_CENTER | wxALL, 10);
  sizer->Add(button_sizer, 0, wxALIGN_CENTER | wxALL, 0);

  this->SetSizerAndFit(sizer);
  sizer->Layout();
}

void fosssweeper::AboutDialog::onCredits(wxCommandEvent &WXUNUSED(e)) {
  auto credits_dialog = fosssweeper::createCreditsDialog(this);
  credits_dialog.ShowModal();
}

void fosssweeper::AboutDialog::onLicense(wxCommandEvent &WXUNUSED(e)) {
  auto license_dialog = fosssweeper::createLicenseDialog(this);
  license_dialog.ShowModal();
}

void fosssweeper::AboutDialog::onCopyVersion(wxCommandEvent &e) {
  if (wxTheClipboard->Open()) {
    wxTheClipboard->SetData(new wxTextDataObject(FOSSSWEEPER_VERSION));
    wxTheClipboard->Close();
  }
}

void fosssweeper::AboutDialog::onCopyHash(wxCommandEvent &e) {
  if (wxTheClipboard->Open()) {
    wxTheClipboard->SetData(new wxTextDataObject(FOSSSWEEPER_SHORT_HASH));
    wxTheClipboard->Close();
  }
}