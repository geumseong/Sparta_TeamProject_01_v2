#pragma once
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <initializer_list>
#include <utility>
#include "Inventory.h"  // InventoryManager�� AddItem() �Լ��� �־�� ��

// ===== ������ �̸� ���� =====
// �κ��丮���� ����ϴ� ���� �̸��� ����� ��
namespace WIName {
     constexpr const char* GoblinBrokenBone = "����� �η��� ��";
     constexpr const char* RustyGreatsword = "�콼 ���";
     constexpr const char* BrokenOrcRing = "�μ��� ��ũ�� ����";
     constexpr const char* BrokenOrcGloves = "�μ��� ��ũ�� �尩";
     constexpr const char* HealthPotion = "ü�� ����";
     constexpr const char* JaksenSword = "�ۼ� �ҵ�";
     constexpr const char* OrcRing = "��ũ�� ����";
     constexpr const char* CeramicGloves = "����� �尩";
}

// ===== ���� ��� ������ ���� =====
// Item �����ڰ� (�̸�, ����, Ÿ��) ������ ���ǵ� �־�� ��
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

// ===== ���� ���� =====
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
������ ��
1. Item Ŭ������ (string name, int count, E_Type type) ������ �����ڰ� �ʿ���.
2. InventoryManager Ŭ�������� AddItem(std::unique_ptr<Item>) �Լ��� ������ �־�� ��.
3. ���� ������ ��� ���� ����� ����. �� ������ �� ��� Ȯ���̳� �Ҹ� ���� ������ ���� ����.
4. WIName ���ӽ����̽��� ���ڿ��� �κ��丮 ���ο��� ���� ������ �̸��� ���ƾ� ��.
*/