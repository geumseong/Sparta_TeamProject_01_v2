#include "Item.h"

void Item::printInfo() const
{
	cout << "[�̸�: " << name << ", ����: " << price << "G, " << count << "�� ����]" << endl;
}

void Item::useItem(/*Character& character*/)
{
	switch (type) //type�� ������ ���� �ٸ��� ���
	{
	case E_Type::Consumable:
		for (auto& e : effects) e->onConsume(/* character */ );
		// ���⼭ �߰� ��� ����
		break;
	case E_Type::Equipment:
	case E_Type::Accessory:
		for (auto& e : effects) e->onEquip(/* character */);
		// ���⼭ �߰� ��� ����
		break;
		break;
	case E_Type::Material:
		break;

	}
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



