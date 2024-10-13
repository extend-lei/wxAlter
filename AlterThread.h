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

class AlterThread : public wxThread {
public:
    AlterThread() : wxThread(wxTHREAD_JOINABLE), stopFlag(false) {
    }

    std::vector<wxString> desc_mods;

    //背包左上角：2680,1200
    //改造：212,552
    //增幅：425,659

#define Move2FirstItem() SetCursorPos(2680,1200)
#define Move2Alt() SetCursorPos(212,552)
#define Move2Augment() SetCursorPos(425,659)


    void UseAlt4Item() {
        Move2Alt();
        wxThread::Sleep(20);
        WinTool::SendRightClick();
        wxThread::Sleep(20);
        Move2FirstItem();
        wxThread::Sleep(20);
        WinTool::SendLeftClick();
        wxThread::Sleep(50);
        Move2Augment();
        wxThread::Sleep(20);
        WinTool::SendRightClick();
        wxThread::Sleep(20);
        Move2FirstItem();
        wxThread::Sleep(20);
        WinTool::SendLeftClick();
        wxThread::Sleep(50);
    }

    void MoveTest() {
        // wxMessageBox(clip_text); //正常工作
        while (!stopFlag) {
            Move2FirstItem();
            wxThread::Sleep(20); // 模拟耗时任务
            WinTool::SendCtrlAltC();
            wxThread::Sleep(20); // 模拟耗时任务

            wxString clip_text = WinTool::GetClipboardText();
            for (const auto &mod: desc_mods) {
                if (clip_text.Contains(mod))
                    return;
            }
            UseAlt4Item();
        }
    }

    // 线程入口
    virtual ExitCode Entry() override {
        MoveTest();
        //     wxThread::Sleep(5000); // 模拟耗时任务

        //    wxLogMessage("Task stopped.");
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
