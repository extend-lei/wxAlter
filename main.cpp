#include <iostream>
#include <wx/wx.h>

#include "MainFrame.h"


class App : public wxApp {
public:
    bool OnInit() override;

    int OnExit() override;
};

bool App::OnInit() {
    if (!wxApp::OnInit()) return false;
    MainFrame *mainFrame = new MainFrame();
    mainFrame->SetClientSize(800, 600);
    mainFrame->Show();
    mainFrame->Center();
    return true;
}

int App::OnExit() {
    return wxApp::OnExit();
}

IMPLEMENT_APP(App)
