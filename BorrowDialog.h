#pragma once
#include <wx/wx.h>
#include "Database.h"

class BorrowDialog : public wxDialog {
public:
    BorrowDialog(wxWindow* parent);

    int GetBookId() const;
    int GetStudentId() const;

private:
    wxChoice* bookChoice;
    wxChoice* studentChoice;
    std::vector<Book> books;
    std::vector<Student> students;

    void PopulateChoices();
};

