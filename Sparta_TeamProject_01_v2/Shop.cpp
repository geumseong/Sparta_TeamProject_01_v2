#include "Shop.h"
#include <iostream>
#include <vector>
#include "Character.h"
#include "Inventory.h"
#include "Item.h"

Shop::Shop() {
    availableItems.push_back(new Item("�콼 ��", 50, 1, E_Type::Equipment));
    availableItems.push_back(new Item("���� HP ����", 10, 10, E_Type::Consumable));
    availableItems.push_back(new Item("ö����", 5, 20, E_Type::Material));
    availableItems.push_back(new Item("��Ű���� ����", 150, 1, E_Type::Accessory));
}

void Shop::buyItem(int index, Inventory& inven) // �÷��̾ ������ ����
{
	Item* item = availableItems[index];

	if (index < 0 || index >= availableItems.size())
	{
		std::cout << "�߸��� ������ ��ȣ�Դϴ�.\n";
		return;
	}

	if (inven.getGold() >= item->getPrice()) // ���� ���� ���� Ȯ��
	{
		auto inputItem = std::make_unique<Item>(
			item->getName(),
			item->getPrice(),
			item->getCount(),
			item->getType()
		);
		//���⿡ addEffect<BuffEffect>(50, 50, 50); �̷��� �߰��ؾ� ��
		inven.addItem(move(inputItem));
		inven.setGold(inven.getGold() - item->getPrice());
		std::cout << "����� " << item->getName() << " �� ���� �߽��ϴ�" << "!\n";
	}
	else
	{
		std::cout << "������ ��尡 �����մϴ�.\n";
	}
}