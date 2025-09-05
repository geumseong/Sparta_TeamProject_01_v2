#pragma once
#include <vector>
#include "Item.h"

//�߻� Ŭ���� ���� class I_Inventory



class Inventory
{
private:
	vector<Item*> itemList; //map ���� ���� -> key �̸� value Item ����
	int maxSize;
	int gold;


public:
	Inventory(int gold, int maxsize) : gold(gold), maxSize(maxsize) {}


	//getter
	int getmaxSize() { return maxSize; }
	int getGold() { return gold; }

	//setter
	void setGold(int gold);

	void printitemList();
	void addItem(Item* item);
	void removeItem(int index);
	int findIndex(string name);
	
	//ī�װ��� �з�
	



};