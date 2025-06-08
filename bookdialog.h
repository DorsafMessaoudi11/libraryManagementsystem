#pragma once


#include <wx/wx.h>
#include "Book.h"  // Make sure you have a struct Book defined somewhere

class bookDialog : public wxDialog {
public:
    bookDialog(wxWindow* parent)
        : wxDialog(parent, wxID_ANY, "➕ Add New Book", wxDefaultPosition, wxSize(400, 350))
    {
        wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

        // Title
        mainSizer->Add(CreateLabeledTextCtrl("Title", titleCtrl), 0, wxEXPAND | wxALL, 10);

        // Author
        mainSizer->Add(CreateLabeledTextCtrl("Author", authorCtrl), 0, wxEXPAND | wxALL, 10);

        // Publisher
        mainSizer->Add(CreateLabeledTextCtrl("Publisher", publisherCtrl), 0, wxEXPAND | wxALL, 10);

        // Year
        mainSizer->Add(CreateLabeledTextCtrl("Year", yearCtrl), 0, wxEXPAND | wxALL, 10);

        // Buttons
        wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);
        btnSizer->AddStretchSpacer();
        btnSizer->Add(new wxButton(this, wxID_OK, "Add"), 0, wxRIGHT, 10);
        btnSizer->Add(new wxButton(this, wxID_CANCEL, "Cancel"));
        mainSizer->Add(btnSizer, 0, wxEXPAND | wxALL, 10);

        SetSizer(mainSizer);
    }

    bool ValidateAndGetBook(Book& book) {
        if (titleCtrl->GetValue().IsEmpty() ||
            authorCtrl->GetValue().IsEmpty() ||
            publisherCtrl->GetValue().IsEmpty() ||
            yearCtrl->GetValue().IsEmpty())
        {
            wxMessageBox("All fields must be filled.", "Validation Error", wxICON_ERROR);
            return false;
        }

        long year;
        if (!yearCtrl->GetValue().ToLong(&year) || year < 0 || year > 2100) {
            wxMessageBox("Please enter a valid year (0–2100).", "Validation Error", wxICON_ERROR);
            return false;
        }

        book.title = std::string(titleCtrl->GetValue().mb_str());
        book.author = std::string(authorCtrl->GetValue().mb_str());
        book.publisher = std::string(publisherCtrl->GetValue().mb_str());
        book.year = static_cast<int>(year);
        book.available = true;

        return true;
    }

private:
    wxTextCtrl* titleCtrl;
    wxTextCtrl* authorCtrl;
    wxTextCtrl* publisherCtrl;
    wxTextCtrl* yearCtrl;

    wxSizer* CreateLabeledTextCtrl(const wxString& label, wxTextCtrl*& ctrl) {
        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
        sizer->Add(new wxStaticText(this, wxID_ANY, label), 0, wxBOTTOM, 2);
        ctrl = new wxTextCtrl(this, wxID_ANY);
        sizer->Add(ctrl, 0, wxEXPAND);
        return sizer;
    }
};
