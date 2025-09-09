//#pragma once
//
//#if defined(_MSC_VER)
//#  pragma execution_character_set("utf-8")
//#endif
//
//#include <string>
//#include <vector>
//#include <unordered_map>
//#include <limits>
//#include <iostream>
//#include <memory>
//
//#include "Item.h"
//#include "Inventory.h"
//#include "ItemDB.h"   // ← DB 연동
//
//class Workshop {
//public:
//    // DB를 함께 전달받는다.
//    void Open(Inventory& inv, const ItemDB& db);
//
//private:
//    // 카테고리별 메뉴
//    void CraftPotion(Inventory& inv, const ItemDB& db);     // "alchemy"
//    void CraftEquipment(Inventory& inv, const ItemDB& db);  // "blacksmith"
//    void CraftAccessory(Inventory& inv, const ItemDB& db);  // "accessory" (DB에 없으면 자동 스킵)
//    void ShowRecipes(const ItemDB& db) const;
//
//    // 공통 I/O
//    int  AskIntInRange(const std::string& prompt, int minVal, int maxVal) const;
//    bool AskYesNo(const std::string& prompt) const;
//
//    // 리스트(중복=개수)에 대해 이름별 개수로 압축
//    static std::unordered_map<std::string, int>
//        CountByName(const std::vector<Item>& items);
//
//    // 현재 인벤토리 보유량 조회 (없으면 0)
//    static int GetOwnedCount(const Inventory& inv, const std::string& name);
//
//    // 입력(재료) 충족 여부 체크
//    static bool HasAllInputs(const Inventory& inv,
//        const std::unordered_map<std::string, int>& req);
//
//    // 재료 차감 (충분하다고 가정하고 차감; 0이면 remove)
//    static void ConsumeInputs(Inventory& inv,
//        const std::unordered_map<std::string, int>& req);
//
//    // 산출 지급 (중복 합산해서 한 번에 add)
//    static void GiveOutputs(Inventory& inv,
//        const std::vector<Item>& outputs,
//        int times);
//};
