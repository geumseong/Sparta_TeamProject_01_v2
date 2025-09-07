#include <iostream>
#include "Shop.h"


Shop::Shop() // ������ ������ �߰�
{
	availableItems.push_back(new Item("�⺻ ��", 50, 2, E_Type::Equipment));
	availableItems.push_back(new Item("�⺻ Ȱ", 50 ,2, E_Type::Equipment));
	availableItems.push_back(new Item("�⺻ �ܰ�", 50, 2, E_Type::Equipment));
	availableItems.push_back(new Item("�⺻ ������", 50, 2, E_Type::Equipment));
	availableItems.push_back(new Item("������ ��", 100, 2, E_Type::Equipment));
	availableItems.push_back(new Item("������ Ȱ", 100, 2, E_Type::Equipment));
	availableItems.push_back(new Item("������ �ܰ�", 100, 2, E_Type::Equipment));
	availableItems.push_back(new Item("������ ������", 100, 2, E_Type::Equipment));

	availableItems.push_back(new Item("���� HP ����", 10,10, E_Type::Consumable));
	availableItems.push_back(new Item("���� MP ����", 10, 10, E_Type::Consumable));
	availableItems.push_back(new Item("���� HP ����", 20, 10, E_Type::Consumable));

	availableItems.push_back(new Item("���� MP ����", 20, 10, E_Type::Consumable));
	availableItems.push_back(new Item("���� HP ����", 30, 10, E_Type::Consumable));
	availableItems.push_back(new Item("���� MP ����", 30, 10, E_Type::Consumable));

	availableItems.push_back(new Item("���ݷ� ��ȭ", 15,50, E_Type::Material));
	availableItems.push_back(new Item("���� ��ȭ", 15,50, E_Type::Material));
	availableItems.push_back(new Item("���߷� ��ȭ", 15, 50, E_Type::Material));

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


//availableItems.push_back(new Item("�⺻ ��", 50, 2, E_Type::Equipment));

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
		//���⿡ addEffect<BuffEffect>(50, 50, 50); �̰� �߰��ؾ� ��
		inven.addItem(move(inputItem));
		inven.setGold(inven.getGold() - item->getPrice());
		std::cout << "����� " << item->getName() << " �� ���� �߽��ϴ�" << "!\n";
	}
	else
	{
		std::cout << "������ ��尡 �����մϴ�.\n";
	}
}



//void Shop::sellItem(int index, Character * player) // �÷��̾ ������ �Ǹ�
//{
//	Item* item = player->removeItem(index); // �κ��丮 ������ ����
//	if (item) // �������� ������ ���
//	{
//		int sellPrice = static_cast<int>(item->getPrice() * 0.6); // 60% ȯ��
//		player->earnGold(sellPrice); 
//		availableItems.push_back(item); 
//		std::cout << "����� " << item->getName() << "�� " << sellPrice << " ��忡 �Ǹ��߽��ϴ�.\n";
//	}
//	else // �������� �������� ���� ���
//	{
//		std::cout << "�������� ã�� �� �����ϴ�.\n";
//	}
//}

