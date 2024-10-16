//
// Created by xiaotian on 2024/10/11.
//

#include "WinTool.h"

void WinTool::SendCtrlPlusChar(char c) {
    // 转换为虚拟键码
    SHORT vkChar = VkKeyScanA(c); // 将字符转换为虚拟键码
    if (vkChar == -1) {
        return; // 无法识别字符
    }

    INPUT inputs[4] = {};

    // 按下 Ctrl 键
    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = VK_CONTROL; // Ctrl 键

    // 按下字符键
    inputs[1].type = INPUT_KEYBOARD;
    inputs[1].ki.wVk = LOBYTE(vkChar); // 字符的虚拟键码

    // 释放字符键
    inputs[2].type = INPUT_KEYBOARD;
    inputs[2].ki.wVk = LOBYTE(vkChar); // 字符的虚拟键码
    inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;

    // 释放 Ctrl 键
    inputs[3].type = INPUT_KEYBOARD;
    inputs[3].ki.wVk = VK_CONTROL;
    inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;

    // 发送输入事件
    SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
}


/**
 * 安全的转换wxString为Int
 * @param str
 * @return 如果失败返回-1，否则都是成功
 */
int WinTool::wxStringToInt(const wxString &str) {
    long result;
    if (str.ToLong(&result)) {
        return static_cast<int>(result);
    }
    return -1; // 默认值
}

void WinTool::SendIntAsKeystrokes(int num) {
    // 将数字转换为字符串，便于逐位处理
    std::string numStr = std::to_string(num);

    // 创建一个输入数组，包含按下和释放的所有按键事件


    for (char ch: numStr) {
        std::vector<INPUT> inputs;
        // 获取字符对应的虚拟键码，假设输入的数字是0-9
        SHORT vkCode = VkKeyScanA(ch) & 0xFF;

        // 按下字符键
        INPUT inputDown = {};
        inputDown.type = INPUT_KEYBOARD;
        inputDown.ki.wVk = vkCode;

        // 释放字符键
        INPUT inputUp = {};
        inputUp.type = INPUT_KEYBOARD;
        inputUp.ki.wVk = vkCode;
        inputUp.ki.dwFlags = KEYEVENTF_KEYUP;

        // 将按下和释放的事件加入输入数组
        inputs.push_back(inputDown);
        inputs.push_back(inputUp);
        SendInput(static_cast<UINT>(inputs.size()), inputs.data(), sizeof(INPUT));
    }

    // 调用一次 SendInput 发送所有按键事件
}

/**
 * 点击一个坐标
 */
void WinTool::ClickPos(int x, int y) {
    SetCursorPos(x, y);
    Sleep(20);
    SendLeftClick();
}

void WinTool::SendBackspace() {
    INPUT input[2] = {};

    // 按下 Backspace 键
    input[0].type = INPUT_KEYBOARD;
    input[0].ki.wVk = VK_BACK;

    // 释放 Backspace 键
    input[1].type = INPUT_KEYBOARD;
    input[1].ki.wVk = VK_BACK;
    input[1].ki.dwFlags = KEYEVENTF_KEYUP;

    // 发送输入
    SendInput(2, input, sizeof(INPUT));
}
