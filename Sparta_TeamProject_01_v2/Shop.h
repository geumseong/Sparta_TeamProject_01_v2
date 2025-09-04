#pragma once
#include <vector>
#include "item.h"
#include "Character.h"

class Shop{
private :
	std::vector<Item*> availableItems;


public :
	Shop();
	void displayItems();
	void buyItem(int index, Character* player);
	void sellItem(int index, Character* player);
};


