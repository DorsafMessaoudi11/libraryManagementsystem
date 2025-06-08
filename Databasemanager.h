#pragma once
#include "Book.h"
#include "Student.h"
#include "BorrowRecord.h"
#include <wx/msgdlg.h>
#include <sqlite3.h>
#include <vector>
#include <string>

class DatabaseManager {
public:
    explicit DatabaseManager(const std::string& dbName);
    ~DatabaseManager();

    void createTables();
    bool addBook(const Book& book);
    std::vector<Book> getAllBooks();
    bool setBookAvailability(int bookId, bool available);

    bool addStudent(const Student& student);
    std::vector<Student> getAllStudents();

    bool borrowBook(int bookId, int studentId);
    bool returnBook(int bookId, int studentId);
    std::vector<BorrowRecord> getBorrowRecords();

private:
    sqlite3* db;
    bool executeSQL(const std::string& sql);
};

