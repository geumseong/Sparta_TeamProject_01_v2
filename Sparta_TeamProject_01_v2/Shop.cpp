#include  "shop.h"
#include <algorithm>
#include <random>
#include <chrono>
#include <iostream>

#include "Item.h"
#include "itemDB.h"
//
Shop::~Shop()
{
    for (auto item : availableItems) 
    {
        delete item;
    }
    availableItems.clear();
}

void Shop::openShop(ItemDB db)
{
    /*
    shop_warrior
    shop_archer
    shop_magician
    shop_thief
    shop_potions
    shop_material
    */
    std::vector<Item> itemPool = db.getShopTable("shop_warrior");
    static std::mt19937 g(static_cast<unsigned>(
    std::chrono::system_clock::now().time_since_epoch().count()));
    std::shuffle(itemPool.begin(), itemPool.end(), g);

    int numItems = 5;
    //for (int i = 0; i < numItems && i < itemPool.size(); ++i) {
    //    Item original = itemPool[i];
    //    availableItems.push_back(new Item(
    //        original->getName(),
    //        original->getPrice(),
    //        original->getCount(),
    //        original->getType()
    //    ));
    //}

    for (auto item : itemPool)
    {  
        delete item;
    }
}

void Shop::buyItem(int index, Inventory& inven)
{
    if (index < 0 || index >= static_cast<int>(availableItems.size())) {
        std::cout << "[NPC]: 그런 물건은 없네.\n";
        return;
    }

    Item* item = availableItems[index];

    if (inven.getGold() >= item->getPrice()) {
        std::string boughtName = item->getName();
        auto inputItem = std::<Item>(
            item->getName(), item->getPrice(), 1, item->getType());

        inven.addItem(std::move(inputItem));
        inven.setGold(inven.getGold() - item->getPrice());

        if (item->getCount() > 1) {
            item->setCount(item->getCount() - 1);
        }
        else {
            delete item;
            availableItems.erase(availableItems.begin() + index);
        }

        std::cout << "[NPC]: " << boughtName << "(이)라… 좋은 선택이군!\n";
    }
    else {
        std::cout << "[NPC]: 골드가 부족하네. 다음에 다시 오게나.\n";
    }
}

void Shop::sellItem(int index, Inventory& inven)
{
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
    }

    std::cout << "[NPC]: " << itemName << "을 " << sellPrice << "골드에 사겠네.\n";
}

void Shop::showItem(int index)
{
    if (index >= 0 && index < static_cast<int>(availableItems.size())) {
        availableItems[index]->printInfo();
    }
    else {
        std::cout << "존재하지 않는 아이템입니다.\n";
    }
}

void Shop::displayItems()
{
    std::cout << "[NPC]: 이것이 오늘의 상품이네! 천천히 보게나.\n\n";
    for (int i = 0; i < static_cast<int>(availableItems.size()); ++i) {
        std::cout << i << ": ";
        availableItems[i]->printInfo();
        std::cout << "\n";
    }
    std::cout << "\n";
}

std::string Shop::getItemName(int index) const
{
    if (index >= 0 && index < static_cast<int>(availableItems.size())) {
        return availableItems[index]->getName();
    }
    return "(없는 아이템)";
}

int Shop::getItemCount() const
{
    return static_cast<int>(availableItems.size());
}