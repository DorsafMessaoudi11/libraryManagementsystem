#include "BorrowDialog.h"
#include "Database.h"
BorrowDialog::BorrowDialog(wxWindow* parent)
    : wxDialog(parent, wxID_ANY, "Borrow Book", wxDefaultPosition, wxSize(400, 250)) {

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    // Load data
    DatabaseManager db;
    books = db.getAllBooks();
    students = db.getAllStudents();

    // Book dropdown
    sizer->Add(new wxStaticText(this, wxID_ANY, "Select Book:"), 0, wxALL, 5);
    bookChoice = new wxChoice(this, wxID_ANY);
    for (const auto& b : books) {
        bookChoice->Append(wxString::Format("%d - %s", b.id, b.title), (void*)(intptr_t)b.id);
    }
    sizer->Add(bookChoice, 0, wxALL | wxEXPAND, 5);

    // Student dropdown
    sizer->Add(new wxStaticText(this, wxID_ANY, "Select Student:"), 0, wxALL, 5);
    studentChoice = new wxChoice(this, wxID_ANY);
    for (const auto& s : students) {
        studentChoice->Append(wxString::Format("%d - %s", s.id, s.name), (void*)(intptr_t)s.id);
    }
    sizer->Add(studentChoice, 0, wxALL | wxEXPAND, 5);

    // Buttons
    sizer->Add(CreateSeparatedButtonSizer(wxOK | wxCANCEL), 0, wxALL | wxALIGN_CENTER, 10);

    SetSizerAndFit(sizer);
}

int BorrowDialog::GetBookId() const {
    int sel = bookChoice->GetSelection();
    return (sel != wxNOT_FOUND) ? (int)(intptr_t)bookChoice->GetClientData(sel) : -1;
}

int BorrowDialog::GetStudentId() const {
    int sel = studentChoice->GetSelection();
    return (sel != wxNOT_FOUND) ? (int)(intptr_t)studentChoice->GetClientData(sel) : -1;
}
