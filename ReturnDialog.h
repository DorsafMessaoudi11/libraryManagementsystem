#pragma once
#ifndef RETURNDIALOG_H
#define RETURNDIALOG_H

#include <wx/wx.h>

class ReturnDialog : public wxDialog {
public:
    ReturnDialog(wxWindow* parent);

    int GetBookId() const;
    int GetStudentId() const;
private:
    wxTextCtrl* bookIdCtrl;
};

#endif
