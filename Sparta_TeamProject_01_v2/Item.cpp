#include "Item.h"

void Item::printInfo() const
{
	cout << u8"[�̸�: " << name << u8", ����: " << price << u8"G, " << count << u8"�� ����]" << endl;
}


//setter
void Item::setName(string name)
{
	this->name = name;
}

void Item::setPrice(int price)
{
	this->price = price;
}

void Item::setCount(int count)
{
	this->count = count;
}

void Item::setType(E_Type type)
{
	this->type = type;
}




void Potion::useItem() const
{

}
