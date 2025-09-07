#include <iostream>
#include "Shop.h"
#include "Item.h"
#include "Inventory.h"
#include "Character.h"




Shop::Shop() // ������ ������ �߰�
{
	availableItems.push_back(new Item("�⺻ ��", 50, 1, Equip ));
	availableItems.push_back(new Item("�⺻ Ȱ", 50 ,1, Equip));
	availableItems.push_back(new Item("�⺻ �ܰ�", 50, 1, Equip));
	availableItems.push_back(new Item("�⺻ ������", 50, 1, Equip));
	availableItems.push_back(new Item("������ ��", 100, 1, Equip));
	availableItems.push_back(new Item("������ Ȱ", 100, 1, Equip));
	availableItems.push_back(new Item("������ �ܰ�", 100, 1, Equip));
	availableItems.push_back(new Item("������ ������", 100, 1, Equip));

	availableItems.push_back(new Item("���� HP ����", 10, 10, Potion));
	availableItems.push_back(new Item("���� MP ����", 10, 10, Potion));
	availableItems.push_back(new Item("���� HP ����", 20, 10, Potion));

	availableItems.push_back(new Item("���� MP ����", 20, 10, Potion));
	availableItems.push_back(new Item("���� HP ����", 30, 10, Potion));
	availableItems.push_back(new Item("���� MP ����", 30, 10, Potion));

	availableItems.push_back(new Item("���ݷ� ��ȭ", 15, 50, Stuff));
	availableItems.push_back(new Item("���� ��ȭ", 15, 50, Stuff));
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

void Shop::buyItem(Inventory& inven) {
	int index;
	std::cout << "������ ������ ��ȣ�� �Է��ϼ���: ";
	std::cin >> index;

	if (index < 0 || index >= availableItems.size()) {
		std::cout << "�߸��� ������ ��ȣ�Դϴ�.\n";
		return;
	}

	Item* item = availableItems[index];
	int currentGold = inven.getGold();

	if (currentGold >= item->getPrice()) {
		// ������ ���� �� unique_ptr�� ���μ� �ѱ��
		std::unique_ptr<Item> newItem = std::make_unique<Item>(*item);
		inven.addItem(std::move(newItem));

		inven.setGold(currentGold - item->getPrice());
		std::cout << item->getName() << "�� �����߽��ϴ�!\n";
	}
	else {
		std::cout << "��尡 �����մϴ�.\n";
	}
}



void Shop::sellItem(Inventory& inven) {
	int index;
	std::cout << "�Ǹ��� ������ ��ȣ�� �Է��ϼ���: ";
	std::cin >> index;

	Item* item = inven.findItem(index);
	if (item) {
		int sellPrice = static_cast<int>(item->getPrice() * 0.6);
		int currentGold = inven.getGold();
		inven.setGold(currentGold + sellPrice);

		// ������ �������� �ٽ� �ֱ�
		availableItems.push_back(new Item(*item));

		inven.removeItem(index);
		std::cout << item->getName() << "�� " << sellPrice << " ��忡 �Ǹ��߽��ϴ�.\n";
	}
	else {
		std::cout << "�������� ã�� �� �����ϴ�.\n";
	}
}
