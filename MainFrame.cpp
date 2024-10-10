//
// Created by xiaotian on 2024/10/10.
//

#include "MainFrame.h"
#include <wx/tokenzr.h>

MainFrame::MainFrame(): wxFrame(nullptr, wxID_ANY, "wxAlter") {
    panel = new wxPanel(this);
    panel->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("微软雅黑")));
    wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);
    titleText = new wxStaticText(panel, wxID_ANY, "改造工具:Alt+Q启动");
    mainSizer->Add(titleText, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);


    wxBoxSizer *bSizer2 = new wxBoxSizer(wxHORIZONTAL);


    bSizer2->Add(0, 0, 1, wxEXPAND, 5);

    wxStaticText *m_staticText2 = new wxStaticText(panel, wxID_ANY, _("预设词条"), wxDefaultPosition, wxDefaultSize, 0);
    m_staticText2->Wrap(-1);
    bSizer2->Add(m_staticText2, 0, wxALL, 5);

    wxArrayString m_choice1Choices{"幽魂之甲", "巨人魔盾", "巫妖之冠", "咒士手套", "咒士之靴", "玛瑙护身符"};
    m_choice1 = new wxChoice(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice1Choices, 0);
    m_choice1->SetSelection(0);
    m_choice1->Bind(wxEVT_CHOICE, &MainFrame::OnChoiceSelected, this);
    bSizer2->Add(m_choice1, 0, wxALL, 5);
    bSizer2->Add(0, 0, 1, wxEXPAND, 5);

    mainSizer->Add(bSizer2, 1, wxALIGN_CENTER_HORIZONTAL, 5);

    modInput = new wxTextCtrl(panel, wxID_ANY,
                              "请输入词条",
                              wxDefaultPosition, wxSize(600, 300),
                              wxTE_MULTILINE);
    mainSizer->Add(modInput, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);
    mainSizer->Add(0, 0, 1, wxEXPAND, 5);

    panel->SetSizer(mainSizer);
    panel->Layout();

    wxWindow::RegisterHotKey(1001, wxMOD_ALT, 'Q');
    Bind(wxEVT_HOTKEY, &MainFrame::OnHotKey, this);
}

void SimulateKeyPress(char key) {
    // 准备输入结构体
    INPUT input;
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = VkKeyScan(key); // 获取虚拟键码
    input.ki.wScan = 0; // 确保是虚拟键码而不是扫描码
    input.ki.dwFlags = 0; // 0 表示按下键
    input.ki.time = 0;
    input.ki.dwExtraInfo = 0;

    // 发送按键按下事件
    SendInput(1, &input, sizeof(INPUT));

    // 模拟按键抬起事件
    input.ki.dwFlags = KEYEVENTF_KEYUP; // 表示抬起键
    SendInput(1, &input, sizeof(INPUT));
}

void MainFrame::OnHotKey(wxKeyEvent &evt) {
    if (workerThread && workerThread->IsRunning()) {
        //    wxLogMessage("Stopping task...");
        workerThread->Stop();
        workerThread->Wait();
        delete workerThread;
        workerThread = nullptr;
    } else {
        //   wxLogMessage("Starting task...");
        workerThread = new BackThread();
        wxString text = modInput->GetValue();
        wxStringTokenizer tokenizer(text, "\n");
        while (tokenizer.HasMoreTokens()) {
            workerThread->desc_mods.push_back(tokenizer.GetNextToken());
        }
        if (workerThread->Run() != wxTHREAD_NO_ERROR) {
            wxLogError("Failed to start thread!");
            delete workerThread;
            workerThread = nullptr;
        }
    }
}

void MainFrame::OnChoiceSelected(wxCommandEvent &evt) {
    //{"幽魂之甲", "巨人魔盾", "巫妖之冠", "咒士手套", "咒士之靴", "玛瑙护身符"};
    wxString choice_str = evt.GetString();
    if (choice_str == "幽魂之甲") {
        modInput->SetValue("幻觉的\n无形的\n幻象的\n蜂鸟的");
    }
    if (choice_str == "巨人魔盾") {
        modInput->SetValue("炽焰的\n坚不可摧的\n稳步坚决的\n六翼天使的");
    }
    if (choice_str == "巫妖之冠") {
        modInput->SetValue("炽烈的\n坚不可摧的\n六翼天使的");
    }
    if (choice_str == "咒士手套") {
        modInput->SetValue("沸腾的\n坚不可摧的\n六翼天使的");
    }
    if (choice_str == "咒士之靴") {
        modInput->SetValue("沸腾的\n坚不可摧的\n六翼天使的");
    }
    if (choice_str == "玛瑙护身符") {
        modInput->SetValue("眩目的\n坚不可摧的\n天才之");
    }
}
