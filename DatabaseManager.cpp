#include "DatabaseManager.h"
#include <iostream>
#include <ctime>
#include <wx/msgdlg.h>
DatabaseManager::DatabaseManager(const std::string& dbName) {
    if (sqlite3_open(dbName.c_str(), &db)) {
        std::cerr << "Can't open DB: " << sqlite3_errmsg(db) << std::endl;
        db = nullptr;
    }
}

DatabaseManager::~DatabaseManager() {
    if (db) sqlite3_close(db);
}

bool DatabaseManager::executeSQL(const std::string& sql) {
    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}

void DatabaseManager::createTables() {
    const char* sql_books =
        "CREATE TABLE IF NOT EXISTS books ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "title TEXT,"
        "author TEXT,"
        "publisher TEXT,"
        "year INTEGER,"
        "available INTEGER);";

    const char* sql_students =
        "CREATE TABLE IF NOT EXISTS students ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "name TEXT,"
        "email TEXT);";

    const char* sql_borrow =
        "CREATE TABLE IF NOT EXISTS borrow ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "book_id INTEGER,"
        "student_id INTEGER,"
        "borrow_date TEXT,"
        "return_date TEXT);";

    executeSQL(sql_books);
    executeSQL(sql_students);
    executeSQL(sql_borrow);
}

bool DatabaseManager::addBook(const Book& book) {
    std::string sql = "INSERT INTO books (title, author, publisher, year, available) VALUES ('" +
        book.title + "', '" + book.author + "', '" + book.publisher + "', " +
        std::to_string(book.year) + ", 1);";
    return executeSQL(sql);
}

std::vector<Book> DatabaseManager::getAllBooks() {
    std::vector<Book> books;
    std::string sql = "SELECT * FROM books;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            Book book;
            book.id = sqlite3_column_int(stmt, 0);
            book.title = (const char*)sqlite3_column_text(stmt, 1);
            book.author = (const char*)sqlite3_column_text(stmt, 2);
            book.publisher = (const char*)sqlite3_column_text(stmt, 3);
            book.year = sqlite3_column_int(stmt, 4);
            book.available = sqlite3_column_int(stmt, 5);
            books.push_back(book);
        }
    }
    sqlite3_finalize(stmt);
    return books;
}

bool DatabaseManager::setBookAvailability(int bookId, bool available) {
    std::string sql = "UPDATE books SET available = " + std::to_string(available ? 1 : 0) +
        " WHERE id = " + std::to_string(bookId) + ";";
    return executeSQL(sql);
}

bool DatabaseManager::addStudent(const Student& student) {
    std::string sql = "INSERT INTO students (name, email) VALUES ('" +
        student.name + "', '" + student.email + "');";
    return executeSQL(sql);
}

std::vector<Student> DatabaseManager::getAllStudents() {
    std::vector<Student> students;
    std::string sql = "SELECT * FROM students;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            Student student;
            student.id = sqlite3_column_int(stmt, 0);
            student.name = (const char*)sqlite3_column_text(stmt, 1);
            student.email = (const char*)sqlite3_column_text(stmt, 2);
            students.push_back(student);
        }
    }
    sqlite3_finalize(stmt);
    return students;
}

bool DatabaseManager::borrowBook(int bookId, int studentId) {
    time_t now = time(0);
    char dt[26];
    ctime_s(dt, sizeof(dt), &now);
    std::string borrowDate(dt);

    std::string sql = "INSERT INTO borrow (book_id, student_id, borrow_date, return_date) VALUES (" +
        std::to_string(bookId) + ", " + std::to_string(studentId) + ", '" + borrowDate + "', '');";
    if (!executeSQL(sql)) return false;
    return setBookAvailability(bookId, false);
}

bool DatabaseManager::returnBook(int bookId, int studentId) {
    time_t now = time(0);
    char dt[26];  
    ctime_s(dt, sizeof(dt), &now);
    std::string returnDate(dt);

    std::string sql = "UPDATE borrow SET return_date = '" + returnDate + "' WHERE book_id = " +
        std::to_string(bookId) + " AND student_id = " + std::to_string(studentId) +
        " AND return_date = '';";
    if (!executeSQL(sql)) return false;
    return setBookAvailability(bookId, true);
}

std::vector<BorrowRecord> DatabaseManager::getBorrowRecords() {
    std::vector<BorrowRecord> records;
    std::string sql = "SELECT * FROM borrow;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            BorrowRecord record;
            record.id = sqlite3_column_int(stmt, 0);
            record.book_id = sqlite3_column_int(stmt, 1);
            record.student_id = sqlite3_column_int(stmt, 2);
            record.borrow_date = (const char*)sqlite3_column_text(stmt, 3);
            record.return_date = (const char*)sqlite3_column_text(stmt, 4);
            records.push_back(record);
        }
    }
    sqlite3_finalize(stmt);
    return records;
}