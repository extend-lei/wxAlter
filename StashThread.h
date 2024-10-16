//
// Created by xiaotian on 2024/10/10.
//

#pragma once

#include <wx/wx.h>
#include <wx/thread.h>
#include <wx/clipbrd.h>
#include <vector>

#include "WinTool.h"
#include "ItemFliter.h"
#include "PoeWork.h"

class StashThread : public wxThread {
public:
    StashThread() : wxThread(wxTHREAD_JOINABLE), stopFlag(false) {
    }

    void MoveTest() {
        // wxMessageBox(clip_text); //正常工作
        const int x_start = 2680;
        const int y_start = 1200;
        const int x_end = 3760;
        const int y_end = 1580;
        for (int i = 0; i < 11; ++i) {
            for (int j = 0; j < 5; ++j) {
                SetCursorPos(x_start + i * (x_end - x_start) / 11, y_start + j * (y_end - y_start) / 4);
                wxThread::Sleep(20);
                WinTool::SendCtrlAltC();
                wxThread::Sleep(40); // 模拟耗时任务
                // wxString clip_text = WinTool::GetClipText();
                wxString clip_text3 = WinTool::GetClipboardText();
                int page = ItemFliter::GetPages(clip_text3);
                if (page >= 0) {
                    PoeWork::StashMove2Page(page);
                    wxThread::Sleep(50);
                    WinTool::SendCtrlLeftClick();
                    wxThread::Sleep(50);
                }
            }
        }

        // while (!stopFlag) {
        //     Move2FirstItem();
        //     wxThread::Sleep(20); // 模拟耗时任务
        //     WinTool::SendCtrlAltC();
        //     wxThread::Sleep(20); // 模拟耗时任务
        //     wxString clip_text = WinTool::GetClipText();
        //     for (const auto &mod: desc_mods) {
        //         if (clip_text.Contains(mod))
        //             return;
        //     }
        //     UseAlt4Item();
        // }
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
