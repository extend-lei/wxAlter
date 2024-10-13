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

class StashThread : public wxThread {
public:
    StashThread() : wxThread(wxTHREAD_JOINABLE), stopFlag(false) {
    }

    std::vector<wxString> desc_mods;

    //背包左上角：2680,1200
    //改造：212,552
    //增幅：425,659
    //最后一个位置 3760,1580

#define Move2FirstItem() SetCursorPos(2680,1200)
#define Move2Alt() SetCursorPos(212,552)
#define Move2Augment() SetCursorPos(425,659)


    int lastPage = 0;

    void Move2Page(int page) {
        if (page < 1) {
            lastPage=page;
            return;
        }
        if (page == lastPage)
            return;
        // 构建50个左箭头键和10个右箭头键
        const int leftKeyCount = 50;
        int rightKeyCount = page - 1;

        std::vector<INPUT> inputs;

        // 构建左箭头键输入
        for (int i = 0; i < leftKeyCount; ++i) {
            INPUT input = {0};
            input.type = INPUT_KEYBOARD;
            input.ki.wVk = VK_LEFT; // 左箭头键
            inputs.push_back(input);

            // 对应的键释放
            input.ki.dwFlags = KEYEVENTF_KEYUP;
            inputs.push_back(input);
        }

        // 构建右箭头键输入
        for (int i = 0; i < rightKeyCount; ++i) {
            INPUT input = {0};
            input.type = INPUT_KEYBOARD;
            input.ki.wVk = VK_RIGHT; // 右箭头键
            inputs.push_back(input);

            // 对应的键释放
            input.ki.dwFlags = KEYEVENTF_KEYUP;
            inputs.push_back(input);
        }

        // 发送所有的键输入
        SendInput(static_cast<UINT>(inputs.size()), inputs.data(), sizeof(INPUT));
        lastPage = page;
    }


    void UseAlt4Item() {
        Move2Alt();
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
                wxString clip_text3= WinTool::GetClipboardText();
                int page = ItemFliter::GetPages(clip_text3);
                if (page >= 0) {
                    Move2Page(page);
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
