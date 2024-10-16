//
// Created by xiaotian on 2024/10/11.
//

#ifndef WINTOOL_H
#define WINTOOL_H

#include <wx/wx.h>
#include <wx/clipbrd.h>
#include <comdef.h>
#include <string>

/**
 * 提供winapi级别的抽象，主要是发送按键，移动鼠标等操作，不写死poe里的坐标
 */
class WinTool {
public:
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

    static void SendCtrlLeftClick() {
        // 创建INPUT数组
        INPUT inputs[4] = {};

        // Step 1: 模拟按下 Ctrl 键
        inputs[0].type = INPUT_KEYBOARD;
        inputs[0].ki.wVk = VK_CONTROL; // Ctrl 键的虚拟键码

        // Step 2: 模拟按下鼠标左键
        inputs[1].type = INPUT_MOUSE;
        inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

        // Step 3: 模拟释放鼠标左键
        inputs[2].type = INPUT_MOUSE;
        inputs[2].mi.dwFlags = MOUSEEVENTF_LEFTUP;

        // Step 4: 模拟释放 Ctrl 键
        inputs[3].type = INPUT_KEYBOARD;
        inputs[3].ki.wVk = VK_CONTROL; // Ctrl 键的虚拟键码
        inputs[3].ki.dwFlags = KEYEVENTF_KEYUP; // 表示释放按键

        // 一次性发送所有输入
        SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
    }


    static wxString GetClipboardText() {
        if (!OpenClipboard(nullptr)) {
            return "";
        }

        wxString wxStr;

        // 检查是否为Unicode文本
        if (IsClipboardFormatAvailable(CF_UNICODETEXT)) {
            HANDLE hData = GetClipboardData(CF_UNICODETEXT);
            if (hData) {
                wchar_t *pText = static_cast<wchar_t *>(GlobalLock(hData));
                if (pText) {
                    wxStr = wxString(pText, wxMBConvUTF8());
                    GlobalUnlock(hData);
                }
            }
        }
        // 清空剪切板
        EmptyClipboard();
        CloseClipboard();
        return wxStr;
    }


    static void SendCtrlPlusChar(char c);

    static int wxStringToInt(const wxString &str);

    static void SendIntAsKeystrokes(int num);

    static void ClickPos(int x, int y);

    static void SendBackspace();
};


#endif //WINTOOL_H
