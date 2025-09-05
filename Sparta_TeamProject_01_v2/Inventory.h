#pragma once
#include <vector>
#include "Item.h"

//추상 클래스 구현 class I_Inventory



class Inventory
{
private:
	vector<unique_ptr<Item>> itemList;
	int maxSize;
	int gold;


public:
	Inventory(int gold, int maxsize) : gold(gold), maxSize(maxsize) {}

	void printItemlist();
	void addItem(unique_ptr<Item> item);

	void removeItem(int index);
	int findIndex(string name);
	Item* findItem(int index);

	//getter
	int getmaxSize() { return maxSize; }
	int getGold() { return gold; }

	//setter
	void setGold(int gold);

	//카테고리별 분류
};

//Inventory 사용예시
//
//Inventory inven(100, 10);
//
//inven.addItem(make_unique<Item>("examplePotion", 100, 1, E_Type::Consumable));
//int num = inven.findIndex("examplePotion");
//inven.findItem(num)->AddEffect<HealEffect>(50);
//inven.findItem(num)->useItem();
//
//inven.addItem(make_unique<Item>("exampleAccessory", 500, 1, E_Type::Accessory));
//num = inven.findIndex("exampleAccessory");
//inven.findItem(num)->AddEffect<BuffEffect>(50, 50, 50);
//inven.findItem(num)->useItem();
//
//inven.addItem(make_unique<Item>("exampleEquipment", 300, 1, E_Type::Equipment));
//num = inven.findIndex("exampleEquipment");
//inven.findItem(num)->AddEffect<BuffEffect>(50, 30, 30);
//inven.findItem(num)->useItem();
//
//inven.addItem(make_unique<Item>("exampleMaterial", 50, 10, E_Type::Material));
//num = inven.findIndex("exampleMaterial");
//inven.findItem(num)->AddEffect<HealEffect>(50);
//inven.findItem(num)->useItem();
//
//inven.setGold(50000);
//inven.printItemlist();
//
//return 0;