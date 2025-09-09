#pragma once
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
    void buyItem(int index, Inventory& inven); // 아이템 구매
    void sellItem(int index, Inventory& inven); // 아이템 판매
    void showItem(int index); // 특정 아이템 정보 출력
    void displayItems(); // 상점 아이템 목록 출력

    std::string getItemName(int index) const; // 아이템 이름 가져오기
    int getItemCount() const; // 아이템 개수 가져오기
};