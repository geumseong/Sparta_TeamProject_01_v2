#pragma once
#include <vector>
#include "Item.h"

//추상 클래스 구현 class I_Inventory



class Inventory
{
private:
	vector<Item*> itemList; //map 으로 변경 -> key 이름 value Item 정보
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
	
	//카테고리별 분류
	



};