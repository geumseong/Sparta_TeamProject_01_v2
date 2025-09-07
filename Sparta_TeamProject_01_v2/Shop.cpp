#include "Shop.h"
#include <algorithm> // shuffle
#include <random>    // mt19937
#include <chrono>    // system_clock

void Shop::openShop() {
    // 기존 재고 비우기
    for (auto item : availableItems) 
    {
        delete item;
    }
    availableItems.clear();

    // 아이템 풀
    std::vector<Item*> itemPool = 
    {
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

    // 현재 시간 기반 시드 생성 → 매번 다른 순서
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 g(seed);

    // 아이템 풀 섞기
    std::shuffle(itemPool.begin(), itemPool.end(), g);

    // 앞에서 N개만 재고로
    int numItems = 5;
    for (int i = 0; i < numItems && i < itemPool.size(); ++i) 
    {
        availableItems.push_back(itemPool[i]);
    }

    // 나머지는 메모리 해제
    for (int i = numItems; i < itemPool.size(); ++i)
    {
        delete itemPool[i];
    }
}

Shop::~Shop() {
    for (auto item : availableItems) 
    {
        delete item;
    }
    availableItems.clear();
}

void Shop::buyItem(int index, Inventory& inven) 
{
    if (index < 0 || index >= availableItems.size())
    {
        std::cout << "[NPC]: 그런 물건은 없네.\n";
        return;
    }

    Item* item = availableItems[index];

    if (inven.getGold() >= item->getPrice()) 
    {
        std::string boughtName = item->getName();

        auto inputItem = std::make_unique<Item>
            (item->getName(),item->getPrice(),1,item->getType());

        inven.addItem(std::move(inputItem));
        inven.setGold(inven.getGold() - item->getPrice());

        if (item->getCount() > 1) 
        {
            item->setCount(item->getCount() - 1);
        }
        else {
            delete availableItems[index];
            availableItems.erase(availableItems.begin() + index);
        }

        std::cout << "[NPC]: " << boughtName << "이라… 좋은 선택이군!\n";
    }
    else 
    {
        std::cout << "[NPC]: 골드가 부족하네. 다음에 다시 오게나.\n";
    }
}

void Shop::sellItem(int index, Inventory& inven) 
{
    Item* item = inven.findItem(index);

    if (!item) 
    {
        std::cout << "[NPC]: 그런 아이템은 없네.\n";
        return;
    }

    int sellPrice = static_cast<int>(item->getPrice() * 0.6);
    inven.setGold(inven.getGold() + sellPrice);

    bool found = false;
    for (auto* shopItem : availableItems) 
    {
        if (shopItem->getName() == item->getName()) 
        {
            shopItem->setCount(shopItem->getCount() + 1);
            found = true;
            break;
        }
    }

    if (!found) 
    {
        availableItems.push_back(new Item(item->getName(),item->getPrice(),1,item->getType()));
    }

    if (item->getCount() > 1) 
    {
        item->setCount(item->getCount() - 1);
    }
    else {
        inven.removeItem(index);
    }

    std::cout << "[NPC]: " << item->getName() << "을 " << sellPrice << "골드에 사겠네.\n";
}

void Shop::showItem(int index) // 특정 아이템 정보 출력 
{ 
    if (index >= 0 && index < availableItems.size()) 
    {
        availableItems[index]->printInfo();
    }
    else
    {
        std::cout << "존재하지 않는 아이템입니다.\n";
    }
}

void Shop::displayItems() { // 상점 아이템 목록 출력
    std::cout << "[NPC]: 오늘의 상품을 보게나.\n\n";
    for (int i = 0; i < availableItems.size(); ++i) 
    {
        std::cout << i << ": ";
        availableItems[i]->printInfo();
        std::cout << "\n";
    }
    std::cout << "\n";
}

    //아이템 이름 가져오기
std::string Shop::getItemName(int index) const 
{
    if (index >= 0 && index < availableItems.size())
    {
        return availableItems[index]->getName();
    }
    return "(없는 아이템)";
}