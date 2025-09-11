#include "Item.h"
void Item::printInfo() const
{
	cout << u8"[이름: " << name << u8", 가격: " << price << u8"G, " << count << u8"개 보유]\n" << endl;
}

void Item::useItem(Character* character)
{
	switch (type) //type
	{
	case E_Type::Consumable:
		for (auto& e : effects) e->onConsume(character);
		// 여기서 추가 기능 구현
		break;
	case E_Type::Equipment:
	case E_Type::Accessory:
		if (isequip == false)
		{
			isequip = true;
			for (auto& e : effects) e->onEquip(character);
		}
		else if (isequip == true)
		{
			isequip = false;
			for (auto& e : effects) e->onUnequip(character);
		}
		// 여기서 추가 기능 구현
		break;
	case E_Type::Material:
		break;
		//
	}
}

void Item::unequipItem(Character* character)
{
	switch (type) //type
	{
	case E_Type::Consumable:
		break;
	case E_Type::Equipment:
	case E_Type::Accessory:
		for (auto& e : effects) e->onUnequip(character);
		// 여기서 추가 기능 구현
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

