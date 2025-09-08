#include <iostream>
#include "Shop.h"
#include "Item.h"
#include "Character.h"

Shop::Shop() // ������ ������ �߰�
{
	availableItems.push_back(new Item("�⺻ ��", 50, 2, Equip ));
	availableItems.push_back(new Item("�⺻ Ȱ", 50 ,2, Equip));
	availableItems.push_back(new Item("�⺻ �ܰ�", 50, 2, Equip));
	availableItems.push_back(new Item("�⺻ ������", 50, 2, Equip));
	availableItems.push_back(new Item("������ ��", 100, 2, Equip));
	availableItems.push_back(new Item("������ Ȱ", 100, 2, Equip));
	availableItems.push_back(new Item("������ �ܰ�", 100, 2, Equip));
	availableItems.push_back(new Item("������ ������", 100, 2, Equip));

	availableItems.push_back(new Item("���� HP ����", 10,10, Potion));
	availableItems.push_back(new Item("���� MP ����", 10, 10, Potion));
	availableItems.push_back(new Item("���� HP ����", 20, 10, Potion));

	availableItems.push_back(new Item("���� MP ����", 20, 10, Potion));
	availableItems.push_back(new Item("���� HP ����", 30, 10, Potion));
	availableItems.push_back(new Item("���� MP ����", 30, 10, Potion));

	availableItems.push_back(new Item("���ݷ� ��ȭ", 15,50, Stuff));
	availableItems.push_back(new Item("���� ��ȭ", 15,50, Stuff));
	availableItems.push_back(new Item("���߷� ��ȭ", 15, 50,Stuff));

}

void Shop::displayItems() // ������ �ִ� ������ ���
{
	std::cout << "===== ������ ���Ű��� ȯ���մϴ�! =====\n";
	for (size_t i = 0; i < availableItems.size(); ++i)
	{
		std::cout << i << ": ";
		availableItems[i]->printInfo();

	}
}

void Shop::buyItem(int index, Character* player) // �÷��̾ ������ ����
{
	Item* item = availableItems[index];
{
	if (index < 0 || index >= availableItems.size())
	{
		std::cout << "�߸��� ������ ��ȣ�Դϴ�.\n";
		return;
	}

	if (player->getGold() >= item->getprice()) // ���� ���� ���� Ȯ��
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

void Shop::sellItem(int index, Character * player) // �÷��̾ ������ �Ǹ�
{
	Item* item = player->removeItem(index); // �κ��丮 ������ ����
	if (item) // �������� ������ ���
	{
		int sellPrice = static_cast<int>(item->getPrice() * 0.6); // 60% ȯ��
		player->earnGold(sellPrice); 
		availableItems.push_back(item); 
		std::cout << "����� " << item->getName() << "�� " << sellPrice << " ��忡 �Ǹ��߽��ϴ�.\n";
	}
	else // �������� �������� ���� ���
	{
		std::cout << "�������� ã�� �� �����ϴ�.\n";
	}
}

