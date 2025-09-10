#pragma once
#if defined(_MSC_VER)
#  pragma execution_character_set("utf-8")
#endif

#include <string>
#include <vector>

class Inventory;   
class ItemDB;      
//
#include "Item.h"

class WorkShop {
public:
    void Open(const ItemDB& db, Inventory& inv);
    bool CraftItem(const ItemDB& db, Inventory& inv, string tableName, int index);
    int printrecipe(const ItemDB& db, string tableName);
private:

    void CraftEquipment(Inventory& inv, const ItemDB& db);
    void CraftAccessory(Inventory& inv, const ItemDB& db);
    void ShowRecipes(const ItemDB& db) const;

    int  AskIntInRange(const std::string& prompt, int minVal, int maxVal) const;
    bool AskYesNo(const std::string& prompt) const;
};


bool checkrecipe(vector<vector<Item>>& inputDB, Inventory& inven, int index);
void removeInputinInven(vector<vector<Item>>& inputDB, Inventory& inven, int index);
void addOutputItem(std::vector<Item>& outputDB, Inventory& inven, int index);
