#pragma once
#include <vector>
class Inventory;
class Item;

class Shop { // ���� Ŭ����
private:
	std::vector<Item*> availableItems;


public: // �������� ���� ������ ������ ���
	Shop();
	//void displayItems();
	void buyItem(int index, Inventory& inven);
	//void sellItem(int index, Character* player);
};