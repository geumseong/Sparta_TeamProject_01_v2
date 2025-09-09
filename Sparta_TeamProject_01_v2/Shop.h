#pragma once
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
    void buyItem(int index, Inventory& inven); // ������ ����
    void sellItem(int index, Inventory& inven); // ������ �Ǹ�
    void showItem(int index); // Ư�� ������ ���� ���
    void displayItems(); // ���� ������ ��� ���

    std::string getItemName(int index) const; // ������ �̸� ��������
    int getItemCount() const; // ������ ���� ��������
};