#include "Shop.h"
#include <algorithm> // std::shuffle을 위한 헤더
#include <random>    // 난수 생성기 및 셔플에 필요한 mt19937
#include <chrono>    // 시드 생성을 위한 현재 시간
#include <iostream>

void Shop::openShop()
{
    for (auto item : availableItems) {
        delete item;
    }
    availableItems.clear();

    std::vector<Item*> itemPool = {
        // 전사 무기
        new Item("초보자의 검", 50, 1, E_Type::Equipment),
        new Item("붉은 강철 검", 150, 1, E_Type::Equipment),
        new Item("그림자 카타나", 200, 1, E_Type::Equipment),
        new Item("용맹의 대검", 300, 1, E_Type::Equipment),
        new Item("붉은 용의 송곳니", 350, 1, E_Type::Equipment),

        // 궁수 무기
        new Item("초보자의 활", 50, 1, E_Type::Equipment),
        new Item("바람의 활", 150, 1, E_Type::Equipment),
        new Item("고요한 숲의 활", 200, 1, E_Type::Equipment),
        new Item("달빛 추적자", 300, 1, E_Type::Equipment),
		new Item("달 그림자 장궁", 350, 1, E_Type::Equipment),

        // 마법사 무기
        new Item("초보자의 지팡이", 50, 1, E_Type::Equipment),
        new Item("별빛 지팡이", 150, 1, E_Type::Equipment),
        new Item("심연의 지팡이", 200, 1, E_Type::Equipment),
        new Item("금단의 룬 지팡이", 300, 1, E_Type::Equipment),
        new Item("마나의 고동", 350, 1, E_Type::Equipment),

        // 도적 무기
        new Item("초보자의 단검", 50, 1, E_Type::Equipment),
        new Item("그림자 단검", 150, 1, E_Type::Equipment),
        new Item("망령의 송곳", 200, 1, E_Type::Equipment),
        new Item("무음의 칼날", 300, 1, E_Type::Equipment),
        new Item("침묵의 추적자", 350, 1, E_Type::Equipment),

        // 방어구 (전사)
        new Item("낡은 가죽 갑옷", 50, 1, E_Type::Equipment),
        new Item("훈련병의 철갑", 100, 1, E_Type::Equipment),
        new Item("단련된 전사의 갑옷", 150, 1, E_Type::Equipment),
        new Item("무명 투사의 판금 갑옷", 250, 1, E_Type::Equipment),
        new Item("용사의 갑옷", 350, 1, E_Type::Equipment),

        // 방어구 (궁수)
        new Item("허름한 초원 사냥꾼 튜닉", 50, 1, E_Type::Equipment),
        new Item("정찰자의 가죽 조끼", 100, 1, E_Type::Equipment),
        new Item("바람 추적자의 경갑", 150, 1, E_Type::Equipment),
        new Item("숲길 견습생의 튜닉", 250, 1, E_Type::Equipment),
        new Item("민첩한 활잡이의 갑주", 350, 1, E_Type::Equipment),

        // 방어구 (마법사)
        new Item("낡은 마법사의 로브", 50, 1, E_Type::Equipment),
        new Item("초보 마도사의 망토", 100, 1, E_Type::Equipment),
        new Item("별빛 견습생의 로브", 150, 1, E_Type::Equipment),
        new Item("마력의 별빛 로브", 250, 1, E_Type::Equipment),
        new Item("현자의 로브", 350, 1, E_Type::Equipment),

        // 방어구 (도적)
        new Item("허름한 그림자 연습복", 50, 1, E_Type::Equipment),
        new Item("초보 도적의 가죽조끼", 100, 1, E_Type::Equipment),
        new Item("은신자의 경량 튜닉", 150, 1, E_Type::Equipment),
        new Item("밤의 발걸음 튜닉", 250, 1, E_Type::Equipment),
        new Item("무형의 잠입복", 350, 1, E_Type::Equipment),

        // 소비 아이템
        new Item("소형 HP 포션", 10, 10, E_Type::Consumable),
        new Item("중형 HP 포션", 30, 10, E_Type::Consumable),
        new Item("대형 HP 포션", 60, 10, E_Type::Consumable),
        new Item("소형 MP 포션", 10, 10, E_Type::Consumable),
        new Item("중형 MP 포션", 30, 10, E_Type::Consumable),
        new Item("대형 MP 포션", 60, 10, E_Type::Consumable),

        // 액세서리
        new Item("철 목걸이", 60, 1, E_Type::Accessory),
        new Item("은 반지", 120, 1, E_Type::Accessory),
		new Item("마법사의 부적", 250, 1, E_Type::Accessory),
		new Item("도적의 귀걸이", 250, 1, E_Type::Accessory), 
		new Item("궁수의 팔찌", 250, 1, E_Type::Accessory),  
		new Item("전사의 휘장", 250, 1, E_Type::Accessory),
        new Item("황금 왕관", 300, 1, E_Type::Accessory),


        // 재료
        new Item("나무 조각", 5, 20, E_Type::Material),
        new Item("철 조각", 15, 15, E_Type::Material),
        new Item("강철 조각", 25, 10, E_Type::Material),
        new Item("미스릴 조각", 50, 5, E_Type::Material)
    };

    availableItems = itemPool;
}

    // static으로 선언해서 seed를 한 번만 생성
    static std::mt19937 g(static_cast<unsigned>(
        std::chrono::system_clock::now().time_since_epoch().count()));
    std::shuffle(itemPool.begin(), itemPool.end(), g);

    int numItems = 5;
    for (int i = 0; i < numItems && i < itemPool.size(); ++i) {
        availableItems.push_back(itemPool[i]);
    }

    for (int i = numItems; i < itemPool.size(); ++i) {
        delete itemPool[i];
    }
}

Shop::~Shop()
{
    for (auto item : availableItems) {
        delete item;
    }
    availableItems.clear();
}

void Shop::buyItem(int index, Inventory& inven)
{
    if (index < 0 || index >= availableItems.size()) {
        std::cout << "[NPC]: 그런 물건은 없네.\n";
        return;
    }

    Item* item = availableItems[index];

    if (inven.getGold() >= item->getPrice()) {
        std::string boughtName = item->getName();
        auto inputItem = std::make_unique<Item>(item->getName(), item->getPrice(), 1, item->getType());

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
        item = nullptr;
    }

    std::cout << "[NPC]: " << itemName << "을 " << sellPrice << "골드에 사겠네.\n";
}

void Shop::showItem(int index)
{
    if (index >= 0 && index < availableItems.size()) {
        availableItems[index]->printInfo();
    }
    else {
        std::cout << "존재하지 않는 아이템입니다.\n";
    }
}

void Shop::displayItems()
{
    std::cout << "[NPC]: 이것이 오늘의 상품이네! 천천히 보게나.\n\n";
    for (int i = 0; i < availableItems.size(); ++i) {
        std::cout << i << ": ";
        availableItems[i]->printInfo();
        std::cout << "\n";
    }
    std::cout << "\n";
}

std::string Shop::getItemName(int index) const
{
    if (index >= 0 && index < availableItems.size()) {
        return availableItems[index]->getName();
    }
    return "(없는 아이템)";
}

int Shop::getItemCount() const
{
    return static_cast<int>(availableItems.size());
}
