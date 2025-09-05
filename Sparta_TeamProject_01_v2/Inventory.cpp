#include "Inventory.h"

void Inventory::setGold(int gold)
{
	this->gold = gold;
}

void Inventory::addItem(Item* item)
{
	this->itemList.push_back(item);
}

void Inventory::removeItem(int index)
{
	this->itemList.erase(itemList.begin() + index);
}

void Inventory::printitemList()
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
