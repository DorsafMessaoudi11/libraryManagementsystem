#pragma once
#include <wx/wx.h>
#include <wx/msgdlg.h>
#include "DatabaseManager.h"

class LibraryFrame : public wxFrame {
public:
    LibraryFrame(const wxString& title);
private:

    DatabaseManager db;

    void OnAddBook(wxCommandEvent& event);
    void OnViewBooks(wxCommandEvent& event);
    void OnAddStudent(wxCommandEvent& event);
    void OnBorrowBook(wxCommandEvent& event);
    void OnReturnBook(wxCommandEvent& event);
    void OnSearchBooks(wxCommandEvent& event);
};
