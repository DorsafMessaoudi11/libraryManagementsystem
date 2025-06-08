#include < wx/wx.h >
#include<string>
#include "LibraryFrame.h"

class LibraryApp : public wxApp {
public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(LibraryApp);

bool LibraryApp::OnInit() {
    LibraryFrame* frame = new LibraryFrame("Library Management System");
    frame->Show(true);
    return true;
}