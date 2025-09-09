#pragma once
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <initializer_list>
#include <utility>
#include "Inventory.h"  // InventoryManager에 AddItem() 함수가 있어야 함

// ===== 아이템 이름 정의 =====
// 인벤토리에서 사용하는 실제 이름과 맞춰야 함
namespace WIName {
     constexpr const char* GoblinBrokenBone = "고블린의 부러진 뼈";
     constexpr const char* RustyGreatsword = "녹슨 대검";
     constexpr const char* BrokenOrcRing = "부서진 오크의 반지";
     constexpr const char* BrokenOrcGloves = "부서진 오크의 장갑";
     constexpr const char* HealthPotion = "체력 포션";
     constexpr const char* JaksenSword = "작센 소드";
     constexpr const char* OrcRing = "오크의 반지";
     constexpr const char* CeramicGloves = "세라믹 장갑";
}

// ===== 제작 결과 아이템 생성 =====
// Item 생성자가 (이름, 개수, 타입) 순서로 정의돼 있어야 함
inline std::unique_ptr<Item> MakeHealthPotion(int count) {
    return std::make_unique<Item>(WIName::HealthPotion, count, E_Type::Consumable);
}
inline std::unique_ptr<Item> MakeJaksenSword() {
    return std::make_unique<Item>(WIName::JaksenSword, 0,1, E_Type::Equipment);
}
inline std::unique_ptr<Item> MakeOrcRing() {
    return std::make_unique<Item>(WIName::OrcRing, 0, 1, E_Type::Accessory);
}
inline std::unique_ptr<Item> MakeCeramicGloves() {
    return std::make_unique<Item>(WIName::CeramicGloves, 0,1, E_Type::Equipment);
}

// ===== 제작 공방 =====
class Workshop {
public:
    void Open(Inventory& inv);

private:
    void CraftPotion(Inventory& inv);
    void CraftEquipment(Inventory& inv);
    void ShowRecipes() const;

    int AskIntInRange(const std::string& prompt, int minVal, int maxVal) const;

    bool HasAllAndConsume(Inventory& inv,
        const std::initializer_list<std::pair<std::string, int>>& needs) const;
};

/*
주의할 점
1. Item 클래스는 (string name, int count, E_Type type) 형태의 생성자가 필요함.
2. InventoryManager 클래스에는 AddItem(std::unique_ptr<Item>) 함수가 구현돼 있어야 함.
3. 현재 버전은 재료 차감 기능이 없음. → 제작할 때 재료 확인이나 소모 없이 무제한 제작 가능.
4. WIName 네임스페이스의 문자열은 인벤토리 내부에서 쓰는 아이템 이름과 같아야 함.
*/