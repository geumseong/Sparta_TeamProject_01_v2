#include <iostream>
#include <random>
#include <chrono>
#include <algorithm>
#include "Shop.h"
#include "ItemDB.h"
#include "Inventory.h"
#include "Item.h"

Shop::Shop() { availableItems.clear(); }
Shop::~Shop() { availableItems.clear(); }

void Shop::openShop(ItemDB& db, const std::string& category) // category: "전사", "궁수", "마법사", "도적", "포션", "재료"
{
    std::string shopKey;

	if (category == "전사")       shopKey = "shop_warrior"; // shop_warrior
	else if (category == "궁수")  shopKey = "shop_archer"; // shop_archer
	else if (category == "마법사") shopKey = "shop_mage"; // shop_mage
	else if (category == "도적")   shopKey = "shop_thief"; // shop_thief
	else if (category == "포션")   shopKey = "shop_potions"; // shop_potions 
	else if (category == "재료")   shopKey = "shop_material"; // shop_material
    else 
    {
        std::cout << u8"[NPC]: 알 수 없는 상점 타입이네.\n";
        return;
    }

    std::vector<Item> itemPool = db.getShopTable(shopKey);

    if (itemPool.empty())
    {
        std::cout << u8"[NPC]: 아직 준비된 물건이 없네.\n";
        return;
    }

    // 셔플 제거 → 고정 순서 유지

    availableItems.clear();
    int numItems = 5;
    for (int i = 0; i < numItems && i < static_cast<int>(itemPool.size()); ++i)
    {
        availableItems.push_back(move(itemPool[i]));
    }

    std::cout << u8"[NPC]: " << category << u8" 상점을 열었네!\n";
    displayItems();
}

void Shop::buyItem(int index, Inventory& inven)
{
    if (index < 0 || index >= static_cast<int>(availableItems.size()))
    {
        std::cout << u8"[NPC]: 그런 물건은 없네.\n";
        return;
    }

    Item& item = availableItems[index];
    if (inven.getGold() < item.getPrice()) 
    {
        std::cout << u8"[NPC]: 골드가 부족하네. 다음에 다시 오게나.\n";
        return;
    }
    //
    inven.addItem(Item(item.getName(), item.getPrice(), 1, item.getType()));
    inven.setGold(inven.getGold() - item.getPrice());

    if (item.getCount() > 1) item.setCount(item.getCount() - 1);
    else availableItems.erase(availableItems.begin() + index);

    std::cout << u8"[NPC]: " << item.getName() << u8"(이)라… 좋은 선택이군!\n";
}

void Shop::sellItem(int index, Inventory& inven)
{
    Item* item = inven.findItem(index);
    if (!item)
    {
        std::cout << u8"[NPC]: 그런 아이템은 없네.\n";
        return;
    }

    std::string itemName = item->getName();
    int itemPrice = item->getPrice();

    int sellPrice = static_cast<int>(itemPrice * 0.6);
    inven.setGold(inven.getGold() + sellPrice);

    bool found = false;
    for (auto& shopItem : availableItems)
    {
        if (shopItem.getName() == itemName)
        {
            shopItem.setCount(shopItem.getCount() + 1);
            found = true;
            break;
        }
    }
    if (!found)
    {
        availableItems.push_back(Item(itemName, itemPrice, 1, item->getType()));
    }

    if (item->getCount() > 1) item->setCount(item->getCount() - 1);
    else inven.removeItem(index);

    std::cout << u8"[NPC]: " << itemName << u8"을 " << sellPrice << u8"G 에 사겠네.\n";
}


void Shop::displayItems() // 전체 아이템 출력
{
    std::cout << u8"[NPC]: 이것이 오늘의 상품이네! 천천히 보게나.\n\n";
    for (int i = 0; i < static_cast<int>(availableItems.size()); ++i) {
        std::cout << (i + 1) << ": "; // 사용자에게는 1부터 보이게
        availableItems[i].printInfo();
        std::cout << "\n";
    }
        std::cout << "\n";
}

void Shop::showItem(int index) // 특정 아이템 정보 출력
{
	if (index >= 0 && index < static_cast<int>(availableItems.size())) // index 유효성 검사
        availableItems[index].printInfo();
    else
        std::cout << u8"존재하지 않는 아이템입니다.\n";
}