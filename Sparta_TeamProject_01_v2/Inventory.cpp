#include "Inventory.h"

void Inventory::setGold(int gold)
{
	this->gold = gold;
}

void Inventory::addItem(unique_ptr<Item> item) // �������� �������� ������ �� �ڿ� �߰�
{
	int index = findIndex(item->getName());
	if (index == -1) 
	{
		this->itemList.push_back(move(item));
	}
	else // �������� �����Ѵٸ� �κ��� �ִ� �������� ������ �߰��� ������ ������ŭ ����
	{
		auto invenitem = findItem(index);
		invenitem->setCount(invenitem->getCount() + item->getCount());
	}
}

void Inventory::removeItem(int index)
{
	this->itemList.erase(itemList.begin() + index);
}

void Inventory::printItemlist()
{
	for (int i = 0; i < this->itemList.size(); i++)
	{
		this->itemList[i]->printInfo();
	}
}

int Inventory::findIndex(string name)
{
	for (int i = 0; i < this->itemList.size(); i++)
	{
		if (this->itemList[i]->getName() == name)
		{
			return i;
		}
	}
	return -1;
}

Item* Inventory::findItem(int index)
{
	return itemList[index].get();

}
