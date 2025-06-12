#include "ReturnDialog.h"

ReturnDialog::ReturnDialog(wxWindow* parent)
    : wxDialog(parent, wxID_ANY, "Return Book", wxDefaultPosition, wxSize(250, 150)) {
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    sizer->Add(new wxStaticText(this, wxID_ANY, "Book ID:"), 0, wxALL, 5);
    bookIdCtrl = new wxTextCtrl(this, wxID_ANY);
    sizer->Add(bookIdCtrl, 0, wxALL | wxEXPAND, 5);

    sizer->Add(CreateStdDialogButtonSizer(wxOK | wxCANCEL), 0, wxALL | wxALIGN_CENTER, 10);

    SetSizer(sizer);
    Layout();
}

int ReturnDialog::GetBookId() const {
    long val;
    bookIdCtrl->GetValue().ToLong(&val);
    return static_cast<int>(val);
}
int ReturnDialog::GetStudentId() const {
    long val;
    bookIdCtrl->GetValue().ToLong(&val);
    return static_cast<int>(val);
}
