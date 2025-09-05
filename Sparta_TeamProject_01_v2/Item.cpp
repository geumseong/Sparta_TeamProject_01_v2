#include "Item.h"

void Item::printInfo() const
{
	cout << "[이름: " << name << ", 가격: " << price << "G, " << count << "개 보유]" << endl;
}

void Item::useItem(/*Character& character*/)
{
	switch (type) //type의 종류에 따라 다르게 사용
	{
	case E_Type::Consumable:
		for (auto& e : effects) e->onConsume(/* character */ );
		// 여기서 추가 기능 구현
		break;
	case E_Type::Equipment:
	case E_Type::Accessory:
		for (auto& e : effects) e->onEquip(/* character */);
		// 여기서 추가 기능 구현
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



