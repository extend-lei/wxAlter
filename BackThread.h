//
// Created by xiaotian on 2024/10/10.
//

#ifndef BACKTHREAD_H
#define BACKTHREAD_H
#include <wx/wx.h>
#include <wx/thread.h>
#include <wx/clipbrd.h>
#include <vector>


class BackThread : public wxThread {
public:
    BackThread() : wxThread(wxTHREAD_JOINABLE), stopFlag(false) {
    }

    std::vector<wxString> desc_mods;

    //背包左上角：2680,1200
    //改造：212,552
    //增幅：425,659

#define Move2FirstItem() SetCursorPos(2680,1200)
#define Move2Alt() SetCursorPos(212,552)
#define Move2Augment() SetCursorPos(425,659)

    static void SendCtrlAltC() {
        INPUT inputs[6] = {};

        // 按下 Ctrl 键
        inputs[0].type = INPUT_KEYBOARD;
        inputs[0].ki.wVk = VK_CONTROL;

        // 按下 Alt 键
        inputs[1].type = INPUT_KEYBOARD;
        inputs[1].ki.wVk = VK_MENU;

        // 按下 C 键
        inputs[2].type = INPUT_KEYBOARD;
        inputs[2].ki.wVk = 'C';

        // 释放 C 键
        inputs[3].type = INPUT_KEYBOARD;
        inputs[3].ki.wVk = 'C';
        inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;

        // 释放 Alt 键
        inputs[4].type = INPUT_KEYBOARD;
        inputs[4].ki.wVk = VK_MENU;
        inputs[4].ki.dwFlags = KEYEVENTF_KEYUP;

        // 释放 Ctrl 键
        inputs[5].type = INPUT_KEYBOARD;
        inputs[5].ki.wVk = VK_CONTROL;
        inputs[5].ki.dwFlags = KEYEVENTF_KEYUP;

        // 只调用一次 SendInput 发送所有按键
        SendInput(6, inputs, sizeof(INPUT));
    }

    static void SendRightClick() {
        // 准备输入事件
        INPUT inputs[2] = {};

        // 鼠标右键按下事件
        inputs[0].type = INPUT_MOUSE;
        inputs[0].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;

        // 鼠标右键抬起事件
        inputs[1].type = INPUT_MOUSE;
        inputs[1].mi.dwFlags = MOUSEEVENTF_RIGHTUP;

        // 调用 SendInput 发送鼠标右键点击
        SendInput(2, inputs, sizeof(INPUT));
    }

    static void SendLeftClick() {
        // 准备输入事件
        INPUT inputs[2] = {};

        // 鼠标右键按下事件
        inputs[0].type = INPUT_MOUSE;
        inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

        // 鼠标右键抬起事件
        inputs[1].type = INPUT_MOUSE;
        inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;

        // 调用 SendInput 发送鼠标右键点击
        SendInput(2, inputs, sizeof(INPUT));
    }

    static wxString GetClipText() {
        wxString d("Fail to read");
        if (wxTheClipboard->Open()) {
            // 打开剪切板
            if (wxTheClipboard->IsSupported(wxDF_TEXT)) {
                // 检查是否有文本数据
                wxTextDataObject data;
                if (wxTheClipboard->GetData(data)) {
                    // 获取剪切板数据
                    d = data.GetText();
                }
            } else {
                d = "No text data available in the clipboard.";
            }
            wxTheClipboard->Close(); // 关闭剪切板
        } else {
            d = "Unable to open the clipboard.";
        }
        return d;
    }

    void UseAlt4Item() {
        Move2Alt();
        wxThread::Sleep(20);
        SendRightClick();
        wxThread::Sleep(20);
        Move2FirstItem();
        wxThread::Sleep(20);
        SendLeftClick();
        wxThread::Sleep(50);
    }

    void MoveTest() {
        // wxMessageBox(clip_text); //正常工作
        while (!stopFlag) {
            Move2FirstItem();
            wxThread::Sleep(20); // 模拟耗时任务
            SendCtrlAltC();
            wxThread::Sleep(20); // 模拟耗时任务
            wxString clip_text = GetClipText();
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
