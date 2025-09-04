#include "Shop.h"
#include "Item.h"
#include "Character.h"
#include <iostream>

Shop::Shop() 
{
	availableItems.push_back(new Item("기본 검", 50));
	availableItems.push_back(new Item("기본 활", 50 ,type));
	availableItems.push_back(new Item("기본 단검", 50));
	availableItems.push_back(new Item("기본 지팡이", 50));
	availableItems.push_back(new Item("영웅의 검", 100));
	availableItems.push_back(new Item("영웅의 활", 100));
	availableItems.push_back(new Item("영웅의 단검", 100));
	availableItems.push_back(new Item("영웅의 지팡이", 100));

	availableItems.push_back(new Item("소형 HP 포션", 10));
	availableItems.push_back(new Item("소형 MP 포션", 10));
	availableItems.push_back(new Item("중형 HP 포션", 20));

	availableItems.push_back(new Item("중형 MP 포션", 20));
	availableItems.push_back(new Item("대형 HP 포션", 30));
	availableItems.push_back(new Item("대형 MP 포션", 30));

	availableItems.push_back(new Item("공격력 강화, 15"));
	availableItems.push_back(new Item("방어력 강화, 15"));
	availableItems.push_back(new Item("명중률 강화, 15"));

}

void Shop::displayItems() 
{
	std::cout << "===== 상점에 오신것을 환영합니다! =====\n";
	for (size_t i = 0; i < availableItems.size(); ++i)
	{
		std::cout << i << ": ";
		availableItems[i]->printInfo();

	}
}

void Shop::buyItem(int index, Character* player)
{
	if (index < 0 || index >= availableItems.size())
	{
		std::cout << "잘못된 아이템 번호입니다.\n";
		return;
	}

	if (player->getGold() >= item->getprice()) 
	{
		player->addItem(item);
		player->spendGold(item->getprice());
		std::cout << "당신은 " << item->getName() << " 을 구매 했습니다" << "!\n";
	}
	else
	{
		std::cout << "소지한 골드가 부족합니다.\n";
	}
}

void Shop::sellItem(int index, Character* player)
{
	Item* item = player->removeItem(index);
	if(item)
	{
		int sellPrice = item->getPrice() / 2;
		player->earnGold(sellPrice);
		availableItems.push_back(item);
		std::cout << "당신은 " << item->getName() << "을 " << sellPrice << " 골드에 판매했습니다.\n";
	}
	else
	{
		std::cout << "아이템을 찾을 수 없습니다.\n";

	}
}
