//
// Created by xiaotian on 2024/10/16.
//

#ifndef POEWORK_H
#define POEWORK_H
#include "WinTool.h"
#include <wx/wx.h>
//背包左上角：2680,1200
//改造：212,552
//增幅：425,659


/**
 * 提供poe里坐标级别的抽象，有固定的坐标操作
 */
class PoeWork {
public:
    static void Move2StashFirstItem();

    static void Move2Alt();

    static void Move2Augment();


    static void UseAlt4StashFIrstItem();

    static void StashMove2Page(int page);

    static wxString SendCopyAndGetThisItemDescription();
};


#endif //POEWORK_H
