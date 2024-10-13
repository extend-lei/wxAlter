//
// Created by xiaotian on 2024/10/13.
//

#include "ItemFliter.h"

///
/// @param item 物品信息
/// @return 正常返回页码，0=直接存不改变页码，-1=不存
int ItemFliter::GetPages(const wxString &item) {
    if (item.Contains("孕育石"))
        return 15;
    if (item.Contains("可以在君锋镇铁匠处使用"))
        return 15;
    if (item.Contains("每位玩家在每个战斗区域只能消耗一个预兆"))
        return 13;
    if (item.Contains("堆叠数量"))
        return 0;
    if (item.Contains("地图碎片"))
        return 0;


    return -1;
}
