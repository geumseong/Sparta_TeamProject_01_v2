#include "Workshop.h"
#include <cctype>
#include "itemDB.h"
#include <iostream>
#include "Inventory.h"
using namespace std;


void WorkShop::Open(Inventory& inv, const ItemDB& db)
{
    while (true) {
        std::cout << "\n=== 제작 공방 ===\n"
            << "1. 포션 제작\n"
            << "2. 장비 제작\n"
            << "3. 악세사리 제작\n"
            << "4. 레시피\n"
            << "5. 나가기\n"
            << "선택: ";

        int sel = AskIntInRange("", 1, 5);
        if (sel == 1) CraftPotion(inv, db);
        else if (sel == 2) CraftEquipment(inv, db);
        else if (sel == 3) CraftAccessory(inv, db);
        else if (sel == 4) ShowRecipes(db);
        else { std::cout << "제작 공방을 종료합니다.\n"; return; }
    }
}

void WorkShop::CraftPotion(Inventory& inv, const ItemDB& db)
{
}

void WorkShop::CraftEquipment(Inventory& inv, const ItemDB& db)
{
}

void WorkShop::CraftAccessory(Inventory& inv, const ItemDB& db)
{
}

void WorkShop::ShowRecipes(const ItemDB& db) const
{
}

int WorkShop::AskIntInRange(const std::string& prompt, int minVal, int maxVal) const
{
    return 0;
}

bool WorkShop::AskYesNo(const std::string& prompt) const
{
    return false;
}


bool checkrecipe(std::vector<std::vector<Item>>& vec)
{
    for (size_t i = 0; i < vec[1].size(); i++)
    {
        if (i == 0)
        {
            auto& output = vec[0][0];
            std::cout << output.getName();
            if (output.getCount() > 1)
                std::cout << " x" << output.getCount();
            std::cout << ": ";
        }

        auto& input = vec[1][i];
        std::cout << input.getName();
        if (input.getCount() > 1)
            std::cout << " x" << input.getCount();

        if (i + 1 < vec[1].size())
            std::cout << " + ";
    }
    std::cout << "\n";

    std::cout << "\n0. 나가기\n선택: ";
    int sel;
    std::cin >> sel;

    if (sel == 0)
    {
        std::cout << "레시피 보기를 종료합니다.\n";
        return true;
    }
    return false;
}

bool checkrecipe(vector<Item> inputDB, Inventory& inven)
{
    for (auto input : inputDB)
    {
        int index = inven.findIndex(input.getName());
        if (index == -1 || inven.findItem(index)->getCount() < input.getCount()) return false;
    }
    return true;
}// 천 인벤 2개 필요한게 3개다

void removeInputinInven(vector<Item> inputDB, Inventory& inven)
{
    for (auto input : inputDB)
    {
        int index = inven.findIndex(input.getName());
        if (inven.findItem(index)->getCount() == input.getCount()) inven.removeItem(index);
        else if (inven.findItem(index)->getCount() > input.getCount())
        {
            inven.findItem(index)->setCount(inven.findItem(index)->getCount() - input.getCount());
        }
    }
}

void addOutputItem(vector<Item> outputDB, Inventory& inven)
{
    for (auto output : outputDB)
    {
        auto outputItem = std::make_unique<Item>(output.getName(), output.getPrice(), 1, output.getType());
        inven.addItem(std::move(outputItem));
    }
}