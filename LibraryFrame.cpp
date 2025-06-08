#include "LibraryFrame.h"
#include <wx/textdlg.h>
#include <wx/msgdlg.h>
#include<wx/wx.h>
#include<string>
LibraryFrame::LibraryFrame(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(600, 400)),
    db("library.db")
{
    db.createTables();

    // Menu bar setup
    wxMenuBar* menuBar = new wxMenuBar;

    wxMenu* bookMenu = new wxMenu;
    bookMenu->Append(101, "Add Book");
    bookMenu->Append(102, "View Books");
    bookMenu->Append(103, "Search Books");
    menuBar->Append(bookMenu, "Books");

    wxMenu* studentMenu = new wxMenu;
    studentMenu->Append(201, "Add Student");
    menuBar->Append(studentMenu, "Students");

    wxMenu* borrowMenu = new wxMenu;
    borrowMenu->Append(301, "Borrow Book");
    borrowMenu->Append(302, "Return Book");
    menuBar->Append(borrowMenu, "Borrow/Return");

    SetMenuBar(menuBar);

    // Event bindings
    Bind(wxEVT_MENU, &LibraryFrame::OnAddBook, this, 101);
    Bind(wxEVT_MENU, &LibraryFrame::OnViewBooks, this, 102);
    Bind(wxEVT_MENU, &LibraryFrame::OnSearchBooks, this, 103);
    Bind(wxEVT_MENU, &LibraryFrame::OnAddStudent, this, 201);
    Bind(wxEVT_MENU, &LibraryFrame::OnBorrowBook, this, 301);
    Bind(wxEVT_MENU, &LibraryFrame::OnReturnBook, this, 302);
}

void LibraryFrame::OnAddBook(wxCommandEvent&) {
    wxTextEntryDialog titleDlg(this, "Enter book title:");
    if (titleDlg.ShowModal() != wxID_OK) return;
    wxString title = titleDlg.GetValue();

    wxTextEntryDialog authorDlg(this, "Enter author:");
    if (authorDlg.ShowModal() != wxID_OK) return;
    wxString author = authorDlg.GetValue();

    wxTextEntryDialog pubDlg(this, "Enter publisher:");
    if (pubDlg.ShowModal() != wxID_OK) return;
    wxString publisher = pubDlg.GetValue();

    wxTextEntryDialog yearDlg(this, "Enter publication year:");
    if (yearDlg.ShowModal() != wxID_OK) return;
    int year = wxAtoi(yearDlg.GetValue());

    Book book{
    0,
    std::string(title.mb_str()),      // Converts wxString to std::string safely
    std::string(author.mb_str()),
    std::string(publisher.mb_str()),
    year,
    true
};

    if (db.addBook(book))
        wxMessageBox("Book added successfully.");
    else
        wxMessageBox("Failed to add book.", "Error", wxICON_ERROR);
}

void LibraryFrame::OnViewBooks(wxCommandEvent&) {
    std::vector<Book> books = db.getAllBooks();
    wxString result;

    for (const auto& book : books) {
        result += wxString::Format(
            "ID: %d\nTitle: %s\nAuthor: %s\nPublisher: %s\nYear: %d\nAvailable: %s\n\n",
            book.id, book.title, book.author, book.publisher, book.year,
            book.available ? "Yes" : "No"
        );
    }

    wxMessageBox(result.IsEmpty() ? "No books found." : result);
}

void LibraryFrame::OnAddStudent(wxCommandEvent&) {
    wxTextEntryDialog nameDlg(this, "Enter student name:");
    if (nameDlg.ShowModal() != wxID_OK) return;
    wxString name = nameDlg.GetValue();

    wxTextEntryDialog emailDlg(this, "Enter student email:");
    if (emailDlg.ShowModal() != wxID_OK) return;
    wxString email = emailDlg.GetValue();
    Student student{ 0, std::string(name.mb_str()), std::string(email.mb_str()) };

    if (db.addStudent(student))
        wxMessageBox("Student added successfully.");
    else
        wxMessageBox("Failed to add student.", "Error", wxICON_ERROR);
}

void LibraryFrame::OnBorrowBook(wxCommandEvent&) {
    wxTextEntryDialog bookIdDlg(this, "Enter book ID to borrow:");
    if (bookIdDlg.ShowModal() != wxID_OK) return;
    int bookId = wxAtoi(bookIdDlg.GetValue());

    wxTextEntryDialog studentIdDlg(this, "Enter student ID:");
    if (studentIdDlg.ShowModal() != wxID_OK) return;
    int studentId = wxAtoi(studentIdDlg.GetValue());

    if (db.borrowBook(bookId, studentId))
        wxMessageBox("Book borrowed successfully.");
    else
        wxMessageBox("Failed to borrow book.", "Error", wxICON_ERROR);
}

void LibraryFrame::OnReturnBook(wxCommandEvent&) {
    wxTextEntryDialog bookIdDlg(this, "Enter book ID to return:");
    if (bookIdDlg.ShowModal() != wxID_OK) return;
    int bookId = wxAtoi(bookIdDlg.GetValue());

    wxTextEntryDialog studentIdDlg(this, "Enter student ID:");
    if (studentIdDlg.ShowModal() != wxID_OK) return;
    int studentId = wxAtoi(studentIdDlg.GetValue());

    if (db.returnBook(bookId, studentId))
        wxMessageBox("Book returned successfully.");
    else
        wxMessageBox("Failed to return book.", "Error", wxICON_ERROR);
}

void LibraryFrame::OnSearchBooks(wxCommandEvent&) {
    wxTextEntryDialog searchDlg(this, "Enter keyword to search (title or author):");
    if (searchDlg.ShowModal() != wxID_OK) return;
    std::string keyword = std::string(searchDlg.GetValue().mb_str());

    std::vector<Book> books = db.getAllBooks();
    wxString result;

    for (const auto& book : books) {
        if (book.title.find(keyword) != std::string::npos ||
            book.author.find(keyword) != std::string::npos) {
            result += wxString::Format(
                "ID: %d\nTitle: %s\nAuthor: %s\nPublisher: %s\nYear: %d\nAvailable: %s\n\n",
                book.id, book.title, book.author, book.publisher, book.year,
                book.available ? "Yes" : "No"
            );
        }
    }

    wxMessageBox(result.IsEmpty() ? "No matching books found." : result);
}
