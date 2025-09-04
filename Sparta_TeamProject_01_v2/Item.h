#pragma once
#include <string>
#include <iostream>

using namespace std;

enum E_Type
{
	Potion,
	Equip,
	Stuff,

};

class Item
{
private:
	string name;
	int price;
	int count;
	E_Type type;

public:
	Item(string name, int price, int count, E_Type type) : name(name), price(price), count(count), type(type) {}
	virtual void useItem(/* player */) const {}

	void printInfo() const;

	//getter
	string getName() { return name; }
	int getPrice() { return price; }
	int getCount() { return count; }
	E_Type getType() { return type; }

	//setter
	void setName(string name);
	void setPrice(int price);
	void setCount(int count);
	void setType(E_Type type);

};

class Potion : public Item
{
private:

public:
	Potion(string name, int price, int count, E_Type type) : Item(name, price, count, type) {}

	void useItem(/* player */) const override ;
};