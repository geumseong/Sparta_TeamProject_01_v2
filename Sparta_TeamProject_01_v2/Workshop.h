#pragma once

#if defined(_MSC_VER)
#  pragma execution_character_set("utf-8")
#endif

#include <string>
#include <vector>
#include <unordered_map>
#include <limits>
#include <iostream>
#include <memory>

#include "Item.h"
#include "Inventory.h"
#include "ItemDB.h"   // �� DB ����

class Workshop {
public:
    // DB�� �Բ� ���޹޴´�.
    void Open(Inventory& inv, const ItemDB& db);

private:
    // ī�װ��� �޴�
    void CraftPotion(Inventory& inv, const ItemDB& db);     // "alchemy"
    void CraftEquipment(Inventory& inv, const ItemDB& db);  // "blacksmith"
    void CraftAccessory(Inventory& inv, const ItemDB& db);  // "accessory" (DB�� ������ �ڵ� ��ŵ)
    void ShowRecipes(const ItemDB& db) const;

    // ���� I/O
    int  AskIntInRange(const std::string& prompt, int minVal, int maxVal) const;
    bool AskYesNo(const std::string& prompt) const;

    // ����Ʈ(�ߺ�=����)�� ���� �̸��� ������ ����
    static std::unordered_map<std::string, int>
        CountByName(const std::vector<Item>& items);

    // ���� �κ��丮 ������ ��ȸ (������ 0)
    static int GetOwnedCount(const Inventory& inv, const std::string& name);

    // �Է�(���) ���� ���� üũ
    static bool HasAllInputs(const Inventory& inv,
        const std::unordered_map<std::string, int>& req);

    // ��� ���� (����ϴٰ� �����ϰ� ����; 0�̸� remove)
    static void ConsumeInputs(Inventory& inv,
        const std::unordered_map<std::string, int>& req);

    // ���� ���� (�ߺ� �ջ��ؼ� �� ���� add)
    static void GiveOutputs(Inventory& inv,
        const std::vector<Item>& outputs,
        int times);
};
