// StudentDialog.h
#pragma once

#ifndef STUDENTDIALOG_H
#define STUDENTDIALOG_H

#include <wx/wx.h>
#include "students.h"

class StudentDialog : public wxDialog {
public:
    StudentDialog(wxWindow* parent)
        : wxDialog(parent, wxID_ANY, "Add New Student", wxDefaultPosition, wxSize(380, 220)) {

        SetBackgroundColour(wxColour(250, 250, 250));
        wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

        mainSizer->Add(CreateLabeledTextCtrl("Student Name", nameCtrl), 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 15);
        mainSizer->Add(CreateLabeledTextCtrl("Student Email", emailCtrl), 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);

        wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);
        btnSizer->AddStretchSpacer(1);
        btnSizer->Add(new wxButton(this, wxID_OK, "Add"), 0, wxRIGHT, 10);
        btnSizer->Add(new wxButton(this, wxID_CANCEL, "Cancel"), 0);

        mainSizer->Add(btnSizer, 0, wxEXPAND | wxALL, 15);

        SetSizer(mainSizer);
        CentreOnParent();
    }

    Student GetStudent() const {
        Student student;
        student.name = std::string(nameCtrl->GetValue().mb_str());
        student.email = std::string(emailCtrl->GetValue().mb_str());
        return student;
    }

private:
    wxTextCtrl* nameCtrl = nullptr;
    wxTextCtrl* emailCtrl = nullptr;

    wxSizer* CreateLabeledTextCtrl(const wxString& label, wxTextCtrl*& ctrl) {
        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
        auto* labelText = new wxStaticText(this, wxID_ANY, label);
        labelText->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
        sizer->Add(labelText, 0, wxBOTTOM, 2);

        ctrl = new wxTextCtrl(this, wxID_ANY);
        sizer->Add(ctrl, 1, wxEXPAND);
        return sizer;
    }
};

#endif // STUDENTDIALOG_H
