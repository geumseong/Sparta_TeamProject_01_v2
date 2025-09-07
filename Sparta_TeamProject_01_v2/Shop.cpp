#include "Shop.h"
#include <iostream>
#include <vector>
#include "Character.h"
#include "Inventory.h"
#include "Item.h"

Shop::Shop() {
    availableItems.push_back(new Item("녹슨 검", 50, 1, E_Type::Equipment));
    availableItems.push_back(new Item("소형 HP 포션", 10, 10, E_Type::Consumable));
    availableItems.push_back(new Item("철광석", 5, 20, E_Type::Material));
    availableItems.push_back(new Item("발키리의 은총", 150, 1, E_Type::Accessory));
}

void Shop::buyItem(int index, Inventory& inven) // 플레이어가 아이템 구매
{
	Item* item = availableItems[index];

	if (index < 0 || index >= availableItems.size())
	{
		std::cout << "잘못된 아이템 번호입니다.\n";
		return;
	}

	if (inven.getGold() >= item->getPrice()) // 구매 가능 여부 확인
	{
		auto inputItem = std::make_unique<Item>(
			item->getName(),
			item->getPrice(),
			item->getCount(),
			item->getType()
		);
		//여기에 addEffect<BuffEffect>(50, 50, 50); 이런걸 추가해야 함
		inven.addItem(move(inputItem));
		inven.setGold(inven.getGold() - item->getPrice());
		std::cout << "당신은 " << item->getName() << " 을 구매 했습니다" << "!\n";
	}
	else
	{
		std::cout << "소지한 골드가 부족합니다.\n";
	}
}