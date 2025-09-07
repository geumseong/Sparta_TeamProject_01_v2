#include <iostream>
#include "Shop.h"
#include "Item.h"
#include "Inventory.h"
#include "Character.h"




Shop::Shop() // 상점에 아이템 추가
{
	availableItems.push_back(new Item("기본 검", 50, 1, Equip ));
	availableItems.push_back(new Item("기본 활", 50 ,1, Equip));
	availableItems.push_back(new Item("기본 단검", 50, 1, Equip));
	availableItems.push_back(new Item("기본 지팡이", 50, 1, Equip));
	availableItems.push_back(new Item("영웅의 검", 100, 1, Equip));
	availableItems.push_back(new Item("영웅의 활", 100, 1, Equip));
	availableItems.push_back(new Item("영웅의 단검", 100, 1, Equip));
	availableItems.push_back(new Item("영웅의 지팡이", 100, 1, Equip));

	availableItems.push_back(new Item("소형 HP 포션", 10, 10, Potion));
	availableItems.push_back(new Item("소형 MP 포션", 10, 10, Potion));
	availableItems.push_back(new Item("중형 HP 포션", 20, 10, Potion));

	availableItems.push_back(new Item("중형 MP 포션", 20, 10, Potion));
	availableItems.push_back(new Item("대형 HP 포션", 30, 10, Potion));
	availableItems.push_back(new Item("대형 MP 포션", 30, 10, Potion));

	availableItems.push_back(new Item("공격력 강화", 15, 50, Stuff));
	availableItems.push_back(new Item("방어력 강화", 15, 50, Stuff));
	availableItems.push_back(new Item("명중률 강화", 15, 50,Stuff));

}

void Shop::displayItems() // 상점에 있는 아이템 출력
{
	std::cout << "===== 상점에 오신것을 환영합니다! =====\n";
	for (size_t i = 0; i < availableItems.size(); ++i)
	{
		std::cout << i << ": ";
		availableItems[i]->printInfo();

	}
}

void Shop::buyItem(Inventory& inven) {
	int index;
	std::cout << "구매할 아이템 번호를 입력하세요: ";
	std::cin >> index;

	if (index < 0 || index >= availableItems.size()) {
		std::cout << "잘못된 아이템 번호입니다.\n";
		return;
	}

	Item* item = availableItems[index];
	int currentGold = inven.getGold();

	if (currentGold >= item->getPrice()) {
		// 아이템 복제 후 unique_ptr로 감싸서 넘기기
		std::unique_ptr<Item> newItem = std::make_unique<Item>(*item);
		inven.addItem(std::move(newItem));

		inven.setGold(currentGold - item->getPrice());
		std::cout << item->getName() << "을 구매했습니다!\n";
	}
	else {
		std::cout << "골드가 부족합니다.\n";
	}
}



void Shop::sellItem(Inventory& inven) {
	int index;
	std::cout << "판매할 아이템 번호를 입력하세요: ";
	std::cin >> index;

	Item* item = inven.findItem(index);
	if (item) {
		int sellPrice = static_cast<int>(item->getPrice() * 0.6);
		int currentGold = inven.getGold();
		inven.setGold(currentGold + sellPrice);

		// 상점에 복제본을 다시 넣기
		availableItems.push_back(new Item(*item));

		inven.removeItem(index);
		std::cout << item->getName() << "을 " << sellPrice << " 골드에 판매했습니다.\n";
	}
	else {
		std::cout << "아이템을 찾을 수 없습니다.\n";
	}
}
