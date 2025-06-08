#pragma once


#include <wx/wx.h>
#include "Student.h"  // Make sure you have a struct Student defined somewhere

class StudentDialog : public wxDialog {
public:
    StudentDialog(wxWindow* parent)
        : wxDialog(parent, wxID_ANY, "👤 Add New Student", wxDefaultPosition, wxSize(350, 250))
    {
        wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

        mainSizer->Add(CreateLabeledTextCtrl("Student Name", nameCtrl), 0, wxEXPAND | wxALL, 10);
        mainSizer->Add(CreateLabeledTextCtrl("Student Email", emailCtrl), 0, wxEXPAND | wxALL, 10);

        wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);
        btnSizer->AddStretchSpacer();
        btnSizer->Add(new wxButton(this, wxID_OK, "Add"), 0, wxRIGHT, 10);
        btnSizer->Add(new wxButton(this, wxID_CANCEL, "Cancel"));
        mainSizer->Add(btnSizer, 0, wxEXPAND | wxALL, 10);

        SetSizer(mainSizer);
    }

    bool ValidateAndGetStudent(Student& student) {
        if (nameCtrl->GetValue().IsEmpty() || emailCtrl->GetValue().IsEmpty()) {
            wxMessageBox("All fields must be filled.", "Validation Error", wxICON_ERROR);
            return false;
        }

        student.name = std::string(nameCtrl->GetValue().mb_str());
        student.email = std::string(emailCtrl->GetValue().mb_str());
        return true;
    }

private:
    wxTextCtrl* nameCtrl;
    wxTextCtrl* emailCtrl;

    wxSizer* CreateLabeledTextCtrl(const wxString& label, wxTextCtrl*& ctrl) {
        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
        sizer->Add(new wxStaticText(this, wxID_ANY, label), 0, wxBOTTOM, 2);
        ctrl = new wxTextCtrl(this, wxID_ANY);
        sizer->Add(ctrl, 0, wxEXPAND);
        return sizer;
    }
};
