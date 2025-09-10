#pragma once
#if defined(_MSC_VER)
#  pragma execution_character_set("utf-8")
#endif

#include <string>
#include <vector>

class Inventory;   
class ItemDB;      

#include "Item.h"

class WorkShop {
public:
    void Open(Inventory& inv, const ItemDB& db);

private:
    void CraftPotion(Inventory& inv, const ItemDB& db);
    void CraftEquipment(Inventory& inv, const ItemDB& db);
    void CraftAccessory(Inventory& inv, const ItemDB& db);
    void ShowRecipes(const ItemDB& db) const;

    int  AskIntInRange(const std::string& prompt, int minVal, int maxVal) const;
    bool AskYesNo(const std::string& prompt) const;
};

bool checkrecipe(std::vector<std::vector<Item>>& vec);
bool checkrecipe(std::vector<Item> inputDB, Inventory& inven);
void removeInputinInven(std::vector<Item> inputDB, Inventory& inven);
void addOutputItem(std::vector<Item> outputDB, Inventory& inven);
