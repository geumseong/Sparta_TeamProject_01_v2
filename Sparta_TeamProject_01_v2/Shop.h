#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Item.h"
#include "Inventory.h"

class Shop 
{
private:
    std::vector<Item*> availableItems; // 현재 상점 재고

public:
    Shop() = default;
    ~Shop();

    void openShop(); // 상점 열기(랜덤 라인업 생성)
    void buyItem(int index, Inventory& inven);
    void sellItem(int index, Inventory& inven);
    void showItem(int index);
    void displayItems();

    //  추가: 아이템 이름 가져오기
    std::string getItemName(int index) const;
};