#include  "shop.h"
#include <algorithm>
#include <random>
#include <chrono>
#include <iostream>

Shop::~Shop()
{
    for (auto item : availableItems) 
    {
        delete item;
    }
    availableItems.clear();
}

void Shop::openShop()
{
    for (auto item : availableItems) 
    {
        delete item;
    }
    availableItems.clear();

    std::vector<Item*> itemPool = {

        //전사 무기
        new Item("초보자의 검", 50, 1, E_Type::Equipment),
		new Item("붉은 강철 검", 80, 1, E_Type::Equipment),   
		new Item("그림자 카타나", 100, 1, E_Type::Equipment),   
		new Item("용맹의 대검", 120, 1, E_Type::Consumable),
		new Item("붉은 용의 송곳니",150,1, E_Type::Consumable),

        // 궁수 무기
		new Item("초보자의 활", 60, 1, E_Type::Equipment),
		new Item("바람의 활", 20, 1, E_Type::Equipment),
		new Item("고요한 숲의 활", 30, 1, E_Type::Equipment),   
		new Item("달빛 추적자", 40, 1, E_Type::Equipment),
		new Item("달 그림자 장궁", 50, 1, E_Type::Equipment),    

            // 마법사 무기
        new Item("초보자의 지팡이", 60, 1, E_Type::Equipment),
        new Item("별빛 지팡이", 20, 1, E_Type::Equipment),
        new Item("심연의 지팡이", 30, 1, E_Type::Equipment),
        new Item("금단의 룬 지팡이", 40, 1, E_Type::Equipment),
        new Item("마나의 고동", 50, 1, E_Type::Equipment),

            // 도적 무기
		new Item("초보자의 단검", 60, 1, E_Type::Equipment),
		new Item("그림자 단검", 20, 1, E_Type::Equipment),   
		new Item("망령의 송곳", 30, 1, E_Type::Equipment),
		new Item("무음의 칼날", 40, 1, E_Type::Equipment),
		new Item("침묵의 추적자", 50, 1, E_Type::Equipment),

        //전사 방어구

		new Item("낡은 가죽 갑옷", 50, 1, E_Type::Equipment),
		new Item("훈련병의 철갑", 80, 1, E_Type::Equipment),
		new Item("단련된 전사의 갑옷", 100, 1, E_Type::Equipment),
	    new Item("무명 투사의 판금 갑옷", 120, 1, E_Type::Equipment),
		new Item("용사의 갑옷",150,1, E_Type::Equipment),

	    // 궁수 방어구

        new Item("허름한 초원 사냥꾼의 튜닉", 50, 1, E_Type::Equipment),
        new Item("정찰자의 가죽조끼", 80, 1, E_Type::Equipment),
        new Item("바람 추적자의 경갑", 100, 1, E_Type::Equipment),
        new Item("숲길 견습생의 튜닉", 120, 1, E_Type::Equipment),
        new Item("민첩한 활잡이의 갑주",150,1, E_Type::Equipment),

	    // 마법사 방어구

        new Item("낡은 마법사의 로브", 50, 1, E_Type::Equipment),
		new Item("초보 마도사의 망토", 80, 1, E_Type::Equipment),
		new Item("별빛 견습생의 로브", 100, 1, E_Type::Equipment),
	    new Item("마력의 별빛 로브", 120, 1, E_Type::Equipment),
		new Item("현자의 로브",150,1, E_Type::Equipment),


    // 도적 방어구
        new Item("허름한 그림자 연습복", 50, 1, E_Type::Equipment),
        new Item("초보 도적의 가죽조끼", 80, 1, E_Type::Equipment),
        new Item("은신자의 경량 튜닉", 100, 1, E_Type::Equipment),
        new Item("밤의 발걸음 튜닉", 120, 1, E_Type::Equipment),
        new Item("무형의 잠입복",150,1, E_Type::Equipment),



    // 악세서리 // 전사
	    new Item("무딘 강철반지", 200, 1, E_Type::Equipment),
		new Item("두꺼운 철제 반지", 250, 1, E_Type::Equipment),
		new Item("파편의 인장 반지", 300, 1, E_Type::Equipment),
		new Item("전장의 울림 반지", 350, 1, E_Type::Equipment),
		new Item("용사의 유산 반지",400,1, E_Type::Equipment),

	// 악세서리 // 궁수
        
        new Item("허름한 가죽 팔찌", 200, 1, E_Type::Equipment),
        new Item("바람 추적자의 반지", 250, 1, E_Type::Equipment),
        new Item("사냥의 잔향 팔찌", 300, 1, E_Type::Equipment),
        new Item("정찰자의 반지", 350, 1, E_Type::Equipment),
        new Item("사냥꾼의 유산 반지",400,1, E_Type::Equipment),

	// 악세서리 // 마법사

        new Item("미약한 룬 펜던트", 200, 1, E_Type::Equipment),
        new Item("각성된 룬 펜던트", 250, 1, E_Type::Equipment),
        new Item("응축된 마력의 룬 펜던트", 300, 1, E_Type::Equipment),
        new Item("별 무리의 룬 펜던트", 350, 1, E_Type::Equipment),
        new Item("현자의 유산 펜던트",400,1, E_Type::Equipment),

	// 악세서리 // 도적

        new Item("허름한 토시", 200, 1, E_Type::Equipment),
        new Item("각인된 토시", 250, 1, E_Type::Equipment),
        new Item("그림자 토시", 300, 1, E_Type::Equipment),
        new Item("침묵의 토시", 350, 1, E_Type::Equipment),
        new Item("무음자의 유산",400,1, E_Type::Equipment),


        // 소비 아이템
        new Item("소형 HP 포션", 10, 20, E_Type::Consumable),
        new Item("중형 HP 포션", 25, 20, E_Type::Consumable),
        new Item("대형 HP 포션", 50, 20, E_Type::Consumable),
        new Item("소형 MP 포션", 10, 20, E_Type::Consumable),
        new Item("중형 MP 포션", 25, 20, E_Type::Consumable),
        new Item("대형 MP 포션", 50, 20, E_Type::Consumable),
     
               // 재료 아이템
	    new Item("낡은 천조각", 15, 10, E_Type::Material),
        new Item("찢어진 가죽", 10, 10, E_Type::Material),
        new Item("낡은 실", 20, 10, E_Type::Material),
        new Item("녹슨 철", 50, 5, E_Type::Material),
        new Item("청동 체인", 25, 10, E_Type::Material),
        new Item("강철 반지", 40, 10, E_Type::Material),
        new Item("마모된 세라믹 팔찌", 100, 5, E_Type::Material)
  };   
    static std::mt19937 g(static_cast<unsigned>(
    std::chrono::system_clock::now().time_since_epoch().count()));
    std::shuffle(itemPool.begin(), itemPool.end(), g);

    int numItems = 5;
    for (int i = 0; i < numItems && i < itemPool.size(); ++i) {
        Item* original = itemPool[i];
        availableItems.push_back(new Item(
            original->getName(),
            original->getPrice(),
            original->getCount(),
            original->getType()
        ));
    }

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
        auto inputItem = std::make_unique<Item>(
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