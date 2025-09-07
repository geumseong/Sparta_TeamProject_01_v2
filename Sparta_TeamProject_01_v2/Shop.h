#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Item.h"
#include "Inventory.h"

class Shop 
{
private:
    std::vector<Item*> availableItems; // ���� ���� ���

public:
    Shop() = default;
    ~Shop();

    void openShop(); // ���� ����(���� ���ξ� ����)
    void buyItem(int index, Inventory& inven);
    void sellItem(int index, Inventory& inven);
    void showItem(int index);
    void displayItems();

    //  �߰�: ������ �̸� ��������
    std::string getItemName(int index) const;
};