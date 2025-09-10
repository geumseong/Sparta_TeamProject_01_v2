#include "Inventory.h"

void Inventory::setGold(int gold)
{
	this->gold = gold;
}
//
void Inventory::addItem(unique_ptr<Item> item) // 아이템이 존재하지 않으면 맨 뒤에 추가
{
	int index = findIndex(item->getName());
	if (index == -1) 
	{
		this->itemList.push_back(move(item));
	}
	else // 아이템이 존재한다면 인벤에 있는 아이템의 개수를 추가할 아이템 개수만큼 증가
	{
		auto invenitem = findItem(index);
		invenitem->setCount(invenitem->getCount() + item->getCount());
	}
}

void Inventory::addItem(Item item) // 아이템이 존재하지 않으면 맨 뒤에 추가
{
	int index = findIndex(item.getName());
	if (index == -1)
	{
		this->itemList.push_back(make_unique<Item>(move(item)));
	}
	else // 아이템이 존재한다면 인벤에 있는 아이템의 개수를 추가할 아이템 개수만큼 증가
	{
		auto invenitem = findItem(index);
		invenitem->setCount(invenitem->getCount() + item.getCount());
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
		cout << i << ": ";
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
