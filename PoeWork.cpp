//
// Created by xiaotian on 2024/10/16.
//

#include "PoeWork.h"

#include <Windows.h>

void PoeWork::Move2StashFirstItem() {
    SetCursorPos(2680, 1200);
}

void PoeWork::Move2Alt() {
    SetCursorPos(212, 552);
}

void PoeWork::Move2Augment() {
    SetCursorPos(425, 659);
}

void PoeWork::UseAlt4StashFIrstItem() {
    {
        PoeWork::Move2Alt();
        wxThread::Sleep(20);
        WinTool::SendRightClick();
        wxThread::Sleep(20);
        PoeWork::Move2StashFirstItem();
        wxThread::Sleep(20);
        WinTool::SendLeftClick();
        wxThread::Sleep(50);
        PoeWork::Move2Augment();
        wxThread::Sleep(20);
        WinTool::SendRightClick();
        wxThread::Sleep(20);
        PoeWork::Move2StashFirstItem();
        wxThread::Sleep(20);
        WinTool::SendLeftClick();
        wxThread::Sleep(50);
    }
}

void PoeWork::StashMove2Page(int page) {
    static int lastPage = 0;
    if (page < 1) {
        lastPage = page;
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

wxString PoeWork::SendCopyAndGetThisItemDescription() {
    WinTool::SendCtrlAltC();
    wxThread::Sleep(20); // 模拟耗时任务

    return WinTool::GetClipboardText();
}
