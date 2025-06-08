#pragma once
#include <string>

class BorrowRecord {
public:
    int id;
    int book_id;
    int student_id;
    std::string borrow_date;
    std::string return_date;
};