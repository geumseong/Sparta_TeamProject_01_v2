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
        new Item("녹슨 검", 50, 1, E_Type::Equipment),
        new Item("강철 검", 150, 1, E_Type::Equipment),
        new Item("듀랑달", 200, 1, E_Type::Equipment),
        new Item("타르빙", 300, 1, E_Type::Equipment),
        new Item("엑스칼리버", 350, 1, E_Type::Equipment),
        new Item("가죽 갑옷", 50, 1, E_Type::Equipment),
        new Item("강철 갑옷", 100, 1, E_Type::Equipment),
        new Item("미스릴 갑옷", 250, 1, E_Type::Equipment),
        new Item("소형 HP 포션", 10, 10, E_Type::Consumable),
        new Item("중형 HP 포션", 30, 10, E_Type::Consumable),
        new Item("대형 HP 포션", 60, 10, E_Type::Consumable),
        new Item("소형 MP 포션", 20, 5, E_Type::Consumable),
        new Item("중형 MP 포션", 50, 5, E_Type::Consumable),
        new Item("대형 MP 포션", 80, 5, E_Type::Consumable),
        new Item("철 목걸이", 60, 1, E_Type::Accessory),
        new Item("은 반지", 120, 1, E_Type::Accessory),
        new Item("황금 왕관", 300, 1, E_Type::Accessory),
        new Item("나무 조각", 5, 20, E_Type::Material),
        new Item("철 조각", 15, 15, E_Type::Material),
        new Item("은 조각", 30, 10, E_Type::Material),
        new Item("미스릴 조각", 50, 5, E_Type::Material)
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
    int index = userIndex - 1; // 유저 입력 보정

    if (index < 0 || index >= availableItems.size()) {
        std::cout << "[NPC]: 그런 물건은 없네.\n";
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

        std::cout << "[NPC]: " << boughtName << "(이)라… 좋은 선택이군!\n";
    }
    else {
        std::cout << "[NPC]: 골드가 부족하네. 다음에 다시 오게나.\n";
    }
}

void Shop::sellItem(int index, Inventory& inven) {
    Item* item = inven.findItem(index);

    if (!item) {
        std::cout << "[NPC]: 그런 아이템은 없네.\n";
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

    std::cout << "[NPC]: " << itemName << "을 " << sellPrice << "골드에 사겠네.\n";
}

void Shop::showItem(int index) {
    if (index >= 0 && index < availableItems.size()) {
        availableItems[index]->printInfo();
    }
    else {
        std::cout << "존재하지 않는 아이템입니다.\n";
    }
}

void Shop::displayItems() {
    std::cout << "[NPC]: 이것이 오늘의 상품이네! 천천히 보게나.\n\n";
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
    return "(없는 아이템)";
}

int Shop::getItemCount() const {
    return static_cast<int>(availableItems.size());
}