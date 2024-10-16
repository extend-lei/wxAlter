//
// Created by xiaotian on 2024/10/10.
//

#include "TujinThread.h"

void TujinThread::MoveTest() {
    for (int i = 0; i < tujinRowCount; ++i) {
        for (int j = 0; j < tujinColCount; ++j) {
            SetCursorPos((tujinLastItemX - tujinFirstItemX) * i / (tujinRowCount - 1) + tujinFirstItemX,
                         (tujinLastItemY - tujinFirstItemY) * j / (tujinColCount - 1) + tujinFirstItemY);
            Sleep(20);
            // WinTool::SendCtrlAltC();
            // wxThread::Sleep(20); // 模拟耗时任务
            //
            // wxString item =  WinTool::GetClipboardText();
            wxString item = PoeWork::SendCopyAndGetThisItemDescription();
            if (!IsNeedItem(item)) //只处理通货
                continue;
            WinTool::SendLeftClick();
            Sleep(200);
            int price1 = GetNowPrice();
            if (price1 == -1) //如果读取价格失败，跳过
                continue;
            int enterPrice1 = static_cast<int>(price1 * 0.6); // 直接将结果向下取整
            WinTool::SendIntAsKeystrokes(enterPrice1);
            Sleep(100);
            WinTool::ClickPos(tujinEnterKeyX, tujinEnterKeyY);
            Sleep(100);
            int price2 = GetNowPrice();
            if (price2 == -1) //如果读取价格失败，说明已经购买成功，跳过
                continue;
            int enterPrice2 = (enterPrice1 + price2) / 2; // 直接将结果向下取整
            WinTool::SendIntAsKeystrokes(enterPrice2);
            Sleep(100);
            WinTool::ClickPos(tujinEnterKeyX, tujinEnterKeyY);
            Sleep(50);
            WinTool::ClickPos(tujinEnterKeyX, tujinEnterKeyY);
            Sleep(50);
        }
    }

    //
    // for (int i = 0; i < 11; ++i) {
    //     for (int j = 0; j < 5; ++j) {
    //         SetCursorPos(x_start + i * (x_end - x_start) / 11, y_start + j * (y_end - y_start) / 4);
    //         wxThread::Sleep(20);
    //         WinTool::SendCtrlAltC();
    //         wxThread::Sleep(40); // 模拟耗时任务
    //         // wxString clip_text = WinTool::GetClipText();
    //         wxString clip_text3 = WinTool::GetClipboardText();
    //         int page = ItemFliter::GetPages(clip_text3);
    //         if (page >= 0) {
    //             PoeWork::StashMove2Page(page);
    //             wxThread::Sleep(50);
    //             WinTool::SendCtrlLeftClick();
    //             wxThread::Sleep(50);
    //         }
    //     }
    // }

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

/**
 *
 * @return -1=获取失败
 */
int TujinThread::GetNowPrice() {
    SetCursorPos(tujinPriceBoxX, tujinPriceBoxY);
    Sleep(100);
    WinTool::SendLeftClick();
    Sleep(100);
    WinTool::SendCtrlPlusChar('A');
    Sleep(100);
    WinTool::SendCtrlPlusChar('C');
    Sleep(100);
    return WinTool::wxStringToInt(WinTool::GetClipboardText());
}

bool TujinThread::IsNeedItem(const wxString &item) {
    std::vector<wxString> list{
        "Alteration",
        "Binding",
        "Fusing",
        "Chaos Orb",
        "Scouring",
        "Alchemy",
        "Regret",
        "Chromatic Orb",
        "Augmentation",
        "Vaal Orb",
        "Blessed Orb",
        "Splinter of Esh",
        "Jeweller's Orb",
        "Annulment",
        "Dense Fossil",
        "Divine Orb",
    };
    for (const wxString &ci: list) {
        if (item.Contains(ci))
            return true;
    }



    return false;
}
