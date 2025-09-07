#pragma once
#include <vector>
#include "item.h"
#include "Character.h"
#include "Inventory.h"

class Shop { // ���� Ŭ����
private: 
	std::vector<Item*> availableItems; 


public: // �������� ���� ������ ������ ���
	Shop(); 
	void displayItems();
	void buyItem(int index, Inventory& inven);
	void sellItem(int index, Character* player); 
};


