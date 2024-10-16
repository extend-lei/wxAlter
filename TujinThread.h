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

class TujinThread : public wxThread {
public:
    TujinThread() : wxThread(wxTHREAD_JOINABLE), stopFlag(false) {
    }

    const static int tujinFirstItemX = 756;
    const static int tujinFirstItemY = 580;
    const static int tujinLastItemX = 858;
    const static int tujinLastItemY = 1580;
    const static int tujinColCount = 11;
    const static int tujinRowCount = 2;
    const static int tujinPriceBoxX = 1395;
    const static int tujinPriceBoxY = 1472;
    const static int tujinEnterKeyX = 1240;
    const static int tujinEnterKeyY = 1675;

    void MoveTest();

    static int GetNowPrice();
    static  bool IsNeedItem(const wxString& item);

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
