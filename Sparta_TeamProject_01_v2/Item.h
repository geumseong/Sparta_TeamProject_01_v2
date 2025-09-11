#pragma once
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include "ItemEffect.h"


using namespace std;

enum E_Type
{
	Consumable,
	Equipment,
	Accessory,
	Material,
	Unknown1
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
	Item(string name, int price, int count, E_Type type) : name(name), price(price), count(count), type(type) {}

	Item(const Item& other) : name(other.name), price(other.price), count(other.count), type(other.type) {
		effects.reserve(other.effects.size());
		for (const auto& e : other.effects) {
			effects.emplace_back(e ? e->clone() : nullptr);
		}
	}

	Item& operator=(const Item& other) {
		if (this != &other) {
			name = other.name;
			price = other.price;
			count = other.count;
			type = other.type;

			effects.clear();
			effects.reserve(other.effects.size());
			for (const auto& e : other.effects) {
				effects.emplace_back(e ? e->clone() : nullptr);
			}
		}
		return *this;
	}

	// 이동 대입
	Item& operator=(Item&& other) noexcept = default;

	template <typename T, typename... Args>
	T* addEffect(Args&&... args)
	{
		auto ptr = make_unique<T>(forward<Args>(args)...);
		T* raw = ptr.get();
		effects.push_back(move(ptr));
		return raw;
	}

	void useItem(Character* character);
	void unequipItem(Character* character);

	void printInfo() const;

	//getter
	string getName() { return name; }
	int getPrice() { return price; }
	int getCount() { return count; }
	E_Type getType() { return type; }
	int getEffectsSize() { return effects.size(); }

	//setter
	void setName(string name);
	void setPrice(int price);
	void setCount(int count);
	void setType(E_Type type);
	//
};
