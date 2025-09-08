#include "Shop.h"
#include <algorithm>
#include <random>
#include <chrono>
#include <iostream>

void Shop::openShop() {
    for (auto item : availableItems) {
        delete item;
    }
    availableItems.clear();

    std::vector<Item*> itemPool = {
        new Item("�콼 ��", 50, 1, E_Type::Equipment),
        new Item("��ö ��", 150, 1, E_Type::Equipment),
        new Item("�����", 200, 1, E_Type::Equipment),
        new Item("Ÿ����", 300, 1, E_Type::Equipment),
        new Item("����Į����", 350, 1, E_Type::Equipment),
        new Item("���� ����", 50, 1, E_Type::Equipment),
        new Item("��ö ����", 100, 1, E_Type::Equipment),
        new Item("�̽��� ����", 250, 1, E_Type::Equipment),
        new Item("���� HP ����", 10, 10, E_Type::Consumable),
        new Item("���� HP ����", 30, 10, E_Type::Consumable),
        new Item("���� HP ����", 60, 10, E_Type::Consumable),
        new Item("���� MP ����", 20, 5, E_Type::Consumable),
        new Item("���� MP ����", 50, 5, E_Type::Consumable),
        new Item("���� MP ����", 80, 5, E_Type::Consumable),
        new Item("ö �����", 60, 1, E_Type::Accessory),
        new Item("�� ����", 120, 1, E_Type::Accessory),
        new Item("Ȳ�� �հ�", 300, 1, E_Type::Accessory),
        new Item("���� ����", 5, 20, E_Type::Material),
        new Item("ö ����", 15, 15, E_Type::Material),
        new Item("�� ����", 30, 10, E_Type::Material),
        new Item("�̽��� ����", 50, 5, E_Type::Material)
    };

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 g(seed);
    std::shuffle(itemPool.begin(), itemPool.end(), g);

    int numItems = 5;
    for (int i = 0; i < numItems && i < itemPool.size(); ++i) {
        availableItems.push_back(itemPool[i]);
    }

    for (int i = numItems; i < itemPool.size(); ++i) {
        delete itemPool[i];
    }
}

Shop::~Shop() {
    for (auto item : availableItems) {
        delete item;
    }
    availableItems.clear();
}

void Shop::buyItem(int userIndex, Inventory& inven) {
    int index = userIndex - 1; // ���� �Է� ����

    if (index < 0 || index >= availableItems.size()) {
        std::cout << "[NPC]: �׷� ������ ����.\n";
        return;
    }

    Item* item = availableItems[index];

    if (inven.getGold() >= item->getPrice()) {
        std::string boughtName = item->getName();

        auto inputItem = std::make_unique<Item>(
            item->getName(), item->getPrice(), 1, item->getType());

        inven.addItem(std::move(inputItem));
        inven.setGold(inven.getGold() - item->getPrice());

        if (item->getCount() > 1) {
            item->setCount(item->getCount() - 1);
        }
        else {
            delete availableItems[index];
            availableItems.erase(availableItems.begin() + index);
        }

        std::cout << "[NPC]: " << boughtName << "(��)�� ���� �����̱�!\n";
    }
    else {
        std::cout << "[NPC]: ��尡 �����ϳ�. ������ �ٽ� ���Գ�.\n";
    }
}

void Shop::sellItem(int index, Inventory& inven) {
    Item* item = inven.findItem(index);

    if (!item) {
        std::cout << "[NPC]: �׷� �������� ����.\n";
        return;
    }

    std::string itemName = item->getName();
    int sellPrice = static_cast<int>(item->getPrice() * 0.6);
    inven.setGold(inven.getGold() + sellPrice);

    bool found = false;
    for (auto* shopItem : availableItems) {
        if (shopItem->getName() == itemName) {
            shopItem->setCount(shopItem->getCount() + 1);
            found = true;
            break;
        }
    }

    if (!found) {
        availableItems.push_back(new Item(itemName, item->getPrice(), 1, item->getType()));
    }

    if (item->getCount() > 1) {
        item->setCount(item->getCount() - 1);
    }
    else {
        inven.removeItem(index);
        item = nullptr;
    }

    std::cout << "[NPC]: " << itemName << "�� " << sellPrice << "��忡 ��ڳ�.\n";
}

void Shop::showItem(int index) {
    if (index >= 0 && index < availableItems.size()) {
        availableItems[index]->printInfo();
    }
    else {
        std::cout << "�������� �ʴ� �������Դϴ�.\n";
    }
}

void Shop::displayItems() {
    std::cout << "[NPC]: �̰��� ������ ��ǰ�̳�! õõ�� ���Գ�.\n\n";
    for (int i = 0; i < availableItems.size(); ++i) {
        std::cout << (i + 1) << ": ";
        availableItems[i]->printInfo();
        std::cout << "\n";
    }
    std::cout << "\n";
}

std::string Shop::getItemName(int index) const {
    if (index >= 0 && index < availableItems.size()) {
        return availableItems[index]->getName();
    }
    return "(���� ������)";
}

int Shop::getItemCount() const {
    return static_cast<int>(availableItems.size());
}