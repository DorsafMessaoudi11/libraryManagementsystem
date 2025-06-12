#include "BookDialog.h"

bookDialog::bookDialog(wxWindow* parent)
    : wxDialog(parent, wxID_ANY, "Add Book", wxDefaultPosition, wxSize(300, 300)) {

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    sizer->Add(new wxStaticText(this, wxID_ANY, "Title"), 0, wxALL, 5);
    titleCtrl = new wxTextCtrl(this, wxID_ANY);
    sizer->Add(titleCtrl, 0, wxALL | wxEXPAND, 5);

    sizer->Add(new wxStaticText(this, wxID_ANY, "Author"), 0, wxALL, 5);
    authorCtrl = new wxTextCtrl(this, wxID_ANY);
    sizer->Add(authorCtrl, 0, wxALL | wxEXPAND, 5);

    sizer->Add(new wxStaticText(this, wxID_ANY, "Publisher"), 0, wxALL, 5);
    publisherCtrl = new wxTextCtrl(this, wxID_ANY);
    sizer->Add(publisherCtrl, 0, wxALL | wxEXPAND, 5);

    sizer->Add(new wxStaticText(this, wxID_ANY, "Year"), 0, wxALL, 5);
    yearCtrl = new wxTextCtrl(this, wxID_ANY);
    sizer->Add(yearCtrl, 0, wxALL | wxEXPAND, 5);

    wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);
    btnSizer->Add(new wxButton(this, wxID_OK), 0, wxALL, 5);
    btnSizer->Add(new wxButton(this, wxID_CANCEL), 0, wxALL, 5);
    sizer->Add(btnSizer, 0, wxALIGN_CENTER);

    SetSizerAndFit(sizer);
}

Book bookDialog::GetBook() const {
    Book b;
    b.title = titleCtrl->GetValue().ToStdString();
    b.author = authorCtrl->GetValue().ToStdString();
    b.publisher = publisherCtrl->GetValue().ToStdString();
    yearCtrl->GetValue().ToLong((long*)&b.year);
    return b;
}
