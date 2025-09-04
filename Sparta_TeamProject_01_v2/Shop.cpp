#include "Shop.h"
#include "Item.h"
#include "Character.h"
#include <iostream>

Shop::Shop() 
{
	availableItems.push_back(new Item("�⺻ ��", 50));
	availableItems.push_back(new Item("�⺻ Ȱ", 50 ,type));
	availableItems.push_back(new Item("�⺻ �ܰ�", 50));
	availableItems.push_back(new Item("�⺻ ������", 50));
	availableItems.push_back(new Item("������ ��", 100));
	availableItems.push_back(new Item("������ Ȱ", 100));
	availableItems.push_back(new Item("������ �ܰ�", 100));
	availableItems.push_back(new Item("������ ������", 100));

	availableItems.push_back(new Item("���� HP ����", 10));
	availableItems.push_back(new Item("���� MP ����", 10));
	availableItems.push_back(new Item("���� HP ����", 20));

	availableItems.push_back(new Item("���� MP ����", 20));
	availableItems.push_back(new Item("���� HP ����", 30));
	availableItems.push_back(new Item("���� MP ����", 30));

	availableItems.push_back(new Item("���ݷ� ��ȭ, 15"));
	availableItems.push_back(new Item("���� ��ȭ, 15"));
	availableItems.push_back(new Item("���߷� ��ȭ, 15"));

}

void Shop::displayItems() 
{
	std::cout << "===== ������ ���Ű��� ȯ���մϴ�! =====\n";
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
		std::cout << "�߸��� ������ ��ȣ�Դϴ�.\n";
		return;
	}

	if (player->getGold() >= item->getprice()) 
	{
		player->addItem(item);
		player->spendGold(item->getprice());
		std::cout << "����� " << item->getName() << " �� ���� �߽��ϴ�" << "!\n";
	}
	else
	{
		std::cout << "������ ��尡 �����մϴ�.\n";
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
		std::cout << "����� " << item->getName() << "�� " << sellPrice << " ��忡 �Ǹ��߽��ϴ�.\n";
	}
	else
	{
		std::cout << "�������� ã�� �� �����ϴ�.\n";

	}
}
