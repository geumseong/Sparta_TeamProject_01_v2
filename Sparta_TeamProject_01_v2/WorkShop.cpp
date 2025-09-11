#include "Workshop.h"
#include <cctype>
#include "itemDB.h"
#include <iostream>
#include "Inventory.h"
#include "drawtest.h"
using namespace std;


void WorkShop::Open(const ItemDB& db, Inventory& inv )
{
    int index = 1;
    //while (true) {

        std::cout 
            << u8"1. 포션 제작\n"
            << u8"2. 무기 제작\n"
            << u8"3. 장비 제작\n"
            << u8"4. 액세서리 제작\n"
            /*<< u8"5. 레시피\n"*/
            << u8"5. 나가기\n";



        /*int sel = AskIntInRange("", 1, 5);
        if (sel == 1) CraftItem(db, inv, "weapon" , index );
        else if (sel == 2) CraftEquipment(inv, db);
        else if (sel == 3) CraftAccessory(inv, db);
        else if (sel == 4) ShowRecipes(db);
        else { std::cout << u8"제작 공방을 종료합니다.\n"; return; }*/
    //}
}

bool WorkShop::CraftItem(const ItemDB& db, Inventory& inv, string tableName, int index)
{
    /*
    recipeTables 세부 테이블
    weapon
    armor
    accessory
    alchemy
    */
    auto recipelist = db.getRecipeTable(tableName);
    RenderBoxFromCout(box_log.x, box_log.y, box_log.width, box_log.height, [&]() //로그 출력
    {
        if (checkrecipe(recipelist.inputs, inv, index))//재료템이 인벤에 있다면
        {
            removeInputinInven(recipelist.inputs, inv, index);//인벤에서 아이템 제거
            addOutputItem(recipelist.outputs, inv, index); //인벤에 아이템 추가
            cout << u8"제작에 성공하였습니다." << endl;
            return true;
        }
        cout << u8"제작에 실패하였습니다." << endl;
    });
    system("pause");
    return false;
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


int WorkShop::printrecipe(const ItemDB& db, string tableName)
{
    auto vec = db.getRecipeTable(tableName);
    RenderBoxFromCout(box_ETC.x, box_ETC.y, box_ETC.width, box_ETC.height, [&]() //etc 출력
    { // 오른쪽
        for (size_t i = 0; i < vec.outputs.size(); i++)
        {
            std::cout << i <<u8": [이름: " << vec.outputs[i].getName() << "] \n [재료 : ";

            for (size_t j = 0; j < vec.inputs[i].size(); j++)
            {
                std::cout << vec.inputs[i][j].getName() << ", ";
            }

            std::cout << "]" << endl;
        }
    });

    return vec.outputs.size();
}


bool checkrecipe(vector<vector<Item>>& inputDB, Inventory& inven, int index)//인벤토리에 재료템이 있는지 확인 하나라도 없으면 리턴
{
    for (auto& input : inputDB[index])
    {
        int index = inven.findIndex(input.getName());
        if (index == -1 || inven.findItem(index)->getCount() < input.getCount()) return false;
    }
    return true;
}// 천 인벤 2개 필요한게 3개다

void removeInputinInven(vector<vector<Item>>& inputDB, Inventory& inven, int index)//인벤에 재료 아이템 삭제
{
    for (auto& input : inputDB[index])
    {
        int index = inven.findIndex(input.getName());
        if (inven.findItem(index)->getCount() == input.getCount()) inven.removeItem(index);
        else if (inven.findItem(index)->getCount() > input.getCount())
        {
            inven.findItem(index)->setCount(inven.findItem(index)->getCount() - input.getCount());
        }
    }
}

void addOutputItem(vector<Item>& outputDB, Inventory& inven, int index)//인벤에 제작 아이템 추가
{

    auto outputItem = std::make_unique<Item>(outputDB[index]);
    inven.addItem(std::move(outputItem));
    
}

//