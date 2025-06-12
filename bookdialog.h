
#include "books.h"
#include <wx/wx.h>


class bookDialog : public wxDialog {
public:
    bookDialog(wxWindow* parent);

    Book GetBook() const;

private:
    wxTextCtrl* titleCtrl, * authorCtrl, * publisherCtrl, * yearCtrl;
};



