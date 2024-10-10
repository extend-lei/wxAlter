//
// Created by xiaotian on 2024/10/10.
//

#ifndef MAINFRAME_H
#define MAINFRAME_H
#include <wx/wx.h>
#include "BackThread.h"

class MainFrame:public wxFrame{
public:
    MainFrame();
    void OnHotKey(wxKeyEvent& evt);
    void OnChoiceSelected(wxCommandEvent& evt);

    wxPanel *panel ;
    wxStaticText *titleText;
    wxTextCtrl* modInput;
    wxChoice* m_choice1;

private:
    BackThread* workerThread = nullptr;
};




#endif //MAINFRAME_H
