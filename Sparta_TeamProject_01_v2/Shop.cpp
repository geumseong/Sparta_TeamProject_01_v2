#include <iostream>
#include <unordered_map>
#include <random>
#include <algorithm>
#include "Shop.h"
#include "ItemDB.h"
#include "Item.h"
#include "Inventory.h"
#include "drawtest.h"

Shop::Shop() {
    availableItems.clear();
}

Shop::~Shop() {
    availableItems.clear();
}

void Shop::openShop(ItemDB& db, const std::string& category)
{
    std::unordered_map<std::string, std::string> shopMap = {
        {u8"전사", "shop_warrior"},
        {u8"궁수", "shop_archer"},
        {u8"마법사", "shop_magician"},
        {u8"도적", "shop_thief"},
        {u8"포션", "shop_potions"},
        {u8"재료", "shop_material"}
    };

    auto it = shopMap.find(category);
    if (it == shopMap.end()) {
        RenderBoxFromCout(box_log.x, box_log.y, box_log.width, box_log.height, [&]() //로그 출력
        {
            std::cout << u8"[NPC]: 알 수 없는 상점 타입이네.\n";
        });
        
        return;
    }

    std::string shopKey = it->second;
    std::vector<Item> itemPool = db.getShopTable(shopKey);

    if (itemPool.empty()) {
        RenderBoxFromCout(box_log.x, box_log.y, box_log.width, box_log.height, [&]() //로그 출력
        {
            std::cout << u8"[NPC]: 아직 준비된 물건이 없네.\n";
        });
        return;
    }

    availableItems.clear();
    int numItems = 5;

    if (category == u8"포션" || category == u8"재료") {
        // 포션/재료는 순서 유지
        for (int i = 0; i < numItems && i < static_cast<int>(itemPool.size()); ++i) {
            availableItems.push_back(move(itemPool[i])); // 복사
        }
    }
    else {
        // 직업 상점은 랜덤 선택
        std::random_device rd;
        std::mt19937 g(rd());

        std::vector<size_t> indices(itemPool.size());
        std::iota(indices.begin(), indices.end(), 0);
        std::shuffle(indices.begin(), indices.end(), g);

        for (size_t i = 0; i < static_cast<size_t>(numItems) && i < indices.size(); ++i) {
            availableItems.push_back(move(move(itemPool[indices[i]]))); // 복사
        }
    }
    RenderBoxFromCout(box_log.x, box_log.y, box_log.width, box_log.height, [&]() //로그 출력
    {
        std::cout << u8"[NPC]: " << category << u8" 상점을 열었네!\n";
    });

    displayItems();
}

void Shop::buyItem(int index, Inventory& inven)
{
    if (index < 0 || index >= static_cast<int>(availableItems.size())) {
        RenderBoxFromCout(box_log.x, box_log.y, box_log.width, box_log.height, [&]() //로그 출력
        {
            std::cout << u8"[NPC]: 그런 물건은 없네.\n";
        });

        return;
    }

    Item& item = availableItems[index];
    if (inven.getGold() < item.getPrice()) {
        RenderBoxFromCout(box_log.x, box_log.y, box_log.width, box_log.height, [&]() //로그 출력
        {
            std::cout << u8"[NPC]: 골드가 부족하네. 다음에 다시 오게나.\n";
        });
        return;
    }

    inven.addItem(std::move(item));
    inven.setGold(inven.getGold() - item.getPrice());
    RenderBoxFromCout(box_log.x, box_log.y, box_log.width, box_log.height, [&]() //로그 출력
    {
        std::cout << u8"[NPC]: " << item.getName() << u8"(이)라… 좋은 선택이군!\n";
    });

    if (item.getCount() > 1)  
        item.setCount(item.getCount() - 1); 
    else
        availableItems.erase(availableItems.begin() + index);

   
}

void Shop::sellItem(int index, Inventory& inven)
{
    Item* item = inven.findItem(index);
    if (!item) {
        RenderBoxFromCout(box_log.x, box_log.y, box_log.width, box_log.height, [&]() //로그 출력
        {
            std::cout << u8"[NPC]: 그런 아이템은 없네.\n";
        });
        return;
    }

    std::string itemName = item->getName();
    int itemPrice = item->getPrice();
    int sellPrice = static_cast<int>(itemPrice * 0.6);

    inven.setGold(inven.getGold() + sellPrice);

    bool found = false;
    for (auto& shopItem : availableItems) {
        if (shopItem.getName() == itemName) {
            shopItem.setCount(shopItem.getCount() + 1);
            found = true;
            break;
        }
    }

    if (!found) {
        availableItems.push_back(move(Item(itemName, itemPrice, 1, item->getType())));
    }
    RenderBoxFromCout(box_log.x, box_log.y, box_log.width, box_log.height, [&]() //로그 출력
    {
        std::cout << u8"[NPC]: " << itemName << u8"을 " << sellPrice << u8"G 에 사겠네.\n";
    });
    if (item->getCount() > 1)
        item->setCount(item->getCount() - 1);
    else
        inven.removeItem(index);

   
}

void Shop::displayItems()
{
    RenderBoxFromCout(box_log.x, box_log.y, box_log.width, box_log.height, [&]() //로그 출력
    {
        std::cout << u8"[NPC]: 이것이 오늘의 상품이네! \n천천히 보게나.\n\n";	
    });


    RenderBoxFromCout(box_ETC.x, box_ETC.y, box_ETC.width, box_ETC.height, [&]() //etc 출력
    { // 오른쪽
        for (int i = 0; i < static_cast<int>(availableItems.size()); ++i) {

            std::cout << (i+1) << ": ";
            availableItems[i].printInfo();
            std::cout << "";
        }
        std::cout << "\n";
    });

}

void Shop::showItem(int index)
{
    RenderBoxFromCout(box_log.x, box_log.y, box_log.width, box_log.height, [&]() //로그 출력
    {
        if (index >= 0 && index < static_cast<int>(availableItems.size()))
            availableItems[index].printInfo();
        else
            std::cout << u8"존재하지 않는 아이템입니다.\n";
    });

}

int Shop::getItemCount() const
{
    return static_cast<int>(availableItems.size());
}

Item* Shop::getItem(int index) const
{
    if (index >= 0 && index < static_cast<int>(availableItems.size()))
        return const_cast<Item*>(&availableItems[index]);
    return nullptr;
}