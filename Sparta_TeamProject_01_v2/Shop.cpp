#include <iostream>
#include <algorithm>
#include "Shop.h"
#include "ItemDB.h"
#include "Inventory.h"
#include "Item.h"

Shop::Shop() {
    availableItems.clear();
}

Shop::~Shop() {
    availableItems.clear();
}

void Shop::openShop(ItemDB& db, const std::string& category) // 상점 열기
{
    std::cout << "[디버그] 전달받은 category: [" << category << "]\n"; 

	std::string shopKey; // 상점 키 변수

    if (category == "전사")       shopKey = "shop_warrior";
    else if (category == "궁수")  shopKey = "shop_archer";
    else if (category == u8"마법사") shopKey = "shop_magician";
    else if (category == "도적")   shopKey = "shop_thief";
    else if (category == "포션")   shopKey = "shop_potions";
    else if (category == "재료")   shopKey = "shop_material";
    else {
        std::cout << u8"[NPC]: 알 수 없는 상점 타입이네.\n";
        return;
    }

    std::vector<Item> itemPool = db.getShopTable(shopKey);

    // 디버깅: itemPool 상태 확인
    std::cout << "[디버그] itemPool 크기: " << itemPool.size() << "\n";
    for (auto& item : itemPool) {
        std::cout << "[디버그] item 이름: " << item.getName() << "\n";
    }

    availableItems.clear();
    int numItems = 5;
    for (int i = 0; i < numItems && i < static_cast<int>(itemPool.size()); ++i) {
        availableItems.push_back(std::move(itemPool[i]));
    }

    // 디버깅: availableItems 상태 확인
    std::cout << "[디버그] availableItems 크기: " << availableItems.size() << "\n";
    for (auto& item : availableItems) {
        std::cout << "[디버그] 진열된 아이템: " << item.getName() << "\n";
    }

    std::cout << u8"[NPC]: " << category << u8" 상점을 열었네!\n";
	displayItems(); // 진열된 아이템 표시
}

void Shop::buyItem(int index, Inventory& inven) // 아이템 구매
{
	if (index < 0 || index >= static_cast<int>(availableItems.size())) { // 인덱스 유효성 검사
        std::cout << u8"[NPC]: 그런 물건은 없네.\n";
        return;
    }

	Item& item = availableItems[index]; // 구매할 아이템 참조
	if (inven.getGold() < item.getPrice()) {  //골드 부족 검사
        std::cout << u8"[NPC]: 골드가 부족하네. 다음에 다시 오게나.\n";
        return;
    }

	inven.addItem(Item(item.getName(), item.getPrice(), 1, item.getType())); // 인벤토리에 아이템 추가
	inven.setGold(inven.getGold() - item.getPrice()); // 골드 차감

	if (item.getCount() > 1) item.setCount(item.getCount() - 1); // 아이템 개수 감소
	else availableItems.erase(availableItems.begin() + index); // 개수가 0이면 진열 목록에서 제거

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


void Shop::displayItems()
{
    std::cout << u8"[NPC]: 이것이 오늘의 상품이네! 천천히 보게나.\n\n";
    for (int i = 0; i < static_cast<int>(availableItems.size()); ++i) {
        std::cout << (i + 1) << ": ";
        availableItems[i].printInfo();
        std::cout << "\n";
    }
    std::cout << "\n";
}

void Shop::showItem(int index)
{
    if (index >= 0 && index < static_cast<int>(availableItems.size()))
        availableItems[index].printInfo();
    else
        std::cout << u8"존재하지 않는 아이템입니다.\n";
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