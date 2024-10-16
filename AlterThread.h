//
// Created by xiaotian on 2024/10/10.
//

#ifndef BACKTHREAD_H
#define BACKTHREAD_H
#include <wx/wx.h>
#include <wx/thread.h>
#include <wx/clipbrd.h>
#include <vector>
#include "WinTool.h"

#include "PoeWork.h"

class AlterThread : public wxThread {
public:
    AlterThread() : wxThread(wxTHREAD_JOINABLE), stopFlag(false) {
    }

    std::vector<wxString> desc_mods;


    void MoveTest() {
        while (!stopFlag) {
            PoeWork::Move2StashFirstItem();
            wxThread::Sleep(20); // 模拟耗时任务
            WinTool::SendCtrlAltC();
            wxThread::Sleep(20); // 模拟耗时任务

            wxString clip_text = WinTool::GetClipboardText();
            for (const auto &mod: desc_mods) {
                if (clip_text.Contains(mod))
                    return;
            }
            PoeWork::UseAlt4StashFIrstItem();
        }
    }

    // 线程入口
    virtual ExitCode Entry() override {
        MoveTest();
        return nullptr;
    }

    // 终止任务
    void Stop() {
        stopFlag = true;
    }

private:
    bool stopFlag;
};


#endif //BACKTHREAD_H
