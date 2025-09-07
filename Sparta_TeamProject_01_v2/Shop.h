#pragma once
#include <vector>
#include "item.h"
#include "Character.h"
#include "Inventory.h"

class Shop { // 상점 클래스
private: 
	std::vector<Item*> availableItems; 


public: // 상점에서 구매 가능한 아이템 목록
	Shop(); 
	void displayItems();
	void buyItem(int index, Inventory& inven);
	void sellItem(int index, Character* player); 
};


