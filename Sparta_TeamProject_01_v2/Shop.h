#pragma once
#include <vector>
#include <string>
#include "Item.h"
#include "Inventory.h"
#include "ItemDB.h"
//
class Shop {
public:
    Shop();
    ~Shop();

    void openShop(ItemDB& db, const std::string& category); // 상점 열기
    void buyItem(int index, Inventory& inven);              // 아이템 구매
    void sellItem(int index, Inventory& inven);             // 아이템 판매
    void showItem(int index);                               // 특정 아이템 정보 출력
    void displayItems();                                    // 전체 아이템 출력

    std::string getItemName(int index) const;               // 아이템 이름 반환
    int getItemCount() const
    {
        return availableItems.size();
    }                               // 아이템 개수 반환
    Item* getItem(int index) const;
    // 아이템 객체 반환

private:
    std::vector<Item> availableItems;                       // 진열 아이템 목록
};