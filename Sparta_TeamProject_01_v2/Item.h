#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "ItemEffect.h"

using namespace std;

enum E_Type
{
	Consumable,
	Equipment,
	Accessory,
	Material,

};

class Item
{
private:
	string name;
	int price;
	int count;
	E_Type type;
	vector<unique_ptr<I_Effect>> effects;

public:
	//생성자
	Item(string name, int price, int count, E_Type type) : name(name), price(price), count(count), type(type) {}//
	
	//아이템 정보 출력
	void printInfo() const;

	//아이템 효과 등록
	template <typename T, typename... Args>
	T* AddEffect(Args&&... args) 
	{
		auto ptr = make_unique<T>(forward<Args>(args)...);
		T* raw = ptr.get();
		effects.push_back(move(ptr));
		return raw;
	}

	//아이템 사용
	void useItem(/*Character& character*/);


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
