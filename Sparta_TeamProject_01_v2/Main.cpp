
#include <iostream>
#include <vector>
#include "Monster.h"
#include "Character.h"
#include "GameManager.h"

#include "Magician.h"
#include "Shop.h"
#include "Inventory.h"
#include "itemDB.h"
using namespace std;

int main()
{

    GameManager* Game = GameManager::getInstance();
    Character* Character_;
    Monster* currentMonster;
    Shop* shop_ = new Shop();

    Game->inven = new Inventory(100, 100);
    //Inventory* inven = new Inventory(100, 100);
    ItemDB db;

    std::string err;
    if (!db.loadFromFile("../itemDB/itemDB.json", &err)) {
        std::cerr << err << "\n";
        return 1;
    }//db 로딩

    vector<Item> test = db.getShopTable("shop_potions"); //shop_potions로딩

    for (auto& item : test)
    {
        Game->inven->addItem(move(item));
    }
    Game->inven->printItemlist();


    string input;
    Game->outputLog("** 캐릭터 이름을 정하십시오.");
    Game->inputLog(input);
    Character_ = new Magician(input);
    Game->character_ = Character_;
    Game->outputLog("캐릭터가 생성되었습니다.");
    cout << "===================================" << endl;
    Game->updateState(GameManager::Battle);
    while (true)
    {
        switch (Game->currentState)
        {
        case GameManager::Start:    //Game 시작 State
            break;

        case GameManager::Resting:  //Game 휴식 State
            //            while (true)
            //            {
            //                Game->outputLog(
            //                    "** 다음 행선지를 선택하세요. \n"
            //                    "1. 던전 입장\n"    //GameManager::Battle로 State 변경 / 던전으로 이동.
            //                    "2. 상점 입장\n"    //GameManager::Shopping으로 State 변경 / 상점으로 이동.
            //                    "3. 제작소 입장\n"  //GameManager::Crafting으로 State 변경 / 제작소로 이동.
            //                    "4. 상태창\n"       //GameManager::Resting에 남아 있지만, 상태창 한 번 출력.
            //                    "5. 인벤토리 열기\n"  //GameManager::Resting에 남아 있지만, 인벤토리 한 번 출력.
            //                    "0. 끝내기"    //GameManager::End로 State 변경 / 게임을 끝냄.
            //                );
            //                // Resting에서 선택지의 결과 코드
            //#pragma region RestChoiceResults
            //                Game->inputLog(input);
            //                if (input == "1" || input == "던전 입장")
            //                {
            //                    Game->updateState(GameManager::Battle);
            //                    break;
            //                }
            //                else if (input == "2" || input == "상점 입장")
            //                {
            //                    Game->updateState(GameManager::Shopping);
            //                    break;
            //                }
            //                else if (input == "3" || input == "제작소 입장")
            //                {
            //                    Game->updateState(GameManager::Crafting);
            //                    break;
            //                }
            //                else if (input == "4" || input == "상태창")
            //                {
            //                    Game->outputLog("상태창 출력.");
            //                    Character_->displayStatus();
            //                    system("pause");
            //                    break;
            //                }
            //                else if (input == "5" || input == "인벤토리 열기")
            //                {
            //                    Game->outputLog("**인벤토리 목록:");
            //                    //Game->inventory_->printItemlist();
            //                    system("pause");
            //                    break;
            //                }
            //                else if (input == "0" || input == "끝내기")
            //                {
            //                    Game->updateState(GameManager::End);
            //                    break;
            //                }
            //                else
            //                {
            //                    Game->outputLog("잘못된 입력입니다.");
            //                }
            //#pragma endregion  RestChoiceResults
            //            }
            break;

        case GameManager::Shopping: //Game 상점/쇼핑 State
            shop_->openShop();    // 상점 목록 생성
            while (true)
            {
                Game->outputLog(
                    "상점에 입장했습니다. 다음 행동을 선택하세요. "
                    "(" + to_string(Game->inven->getGold()) + "G 보유중)\n"
                    "1. 아이템 구매\n"
                    "2. 아이템 판매\n"
                    "3. 인벤토리 확인\n"
                    "4. 상태창 출력\n"
                    "5. 던전 입장"
                );
                Game->inputLog(input);

                //아이템 구매
#pragma region BuyItem
                if (input == "1" || input == "아이템 구매")
                {
                    while (true)
                    {
                        shop_->displayItems();    // 상점 목록 출력
                        Game->outputLog("0. 뒤로가기");
                        Game->inputLog(input);          // 선택지 선택
                        if (input == "0" || input == "뒤로가기")
                        {
                            break;                      // 상점 입장 씬으로 복귀
                        }
                        int index = stoi(input);
                        if(index > 0 && index < shop_->getItemCount() + 1)
                        {
                            //open shop -> index 입력 후 -> showItem(능력치 보여주고) -> 인벤 들어가기
                            shop_->showItem(index-1);   // 고른 아이템 정보 출력
                            Game->outputLog("그래서, 사겠나?");
                            Game->outputLog("1. 예 \n2. 아니오");
                            Game->inputLog(input);          // 아이템 구매 여부 선택
                            if (input == "1" || input == "예")
                            {
                                shop_->buyItem(index-1, Game->inven);
                                //break;                      // 상점 입장 씬으로 복귀
                            }
                            else if (input == "2" || input == "아니오")
                            {
                                // 아무것도 하지 않음
                            }
                            else
                            {
                                Game->outputLog("잘못된 입력입니다.");
                            }
                        }
                        else
                        {
                            Game->outputLog("잘못된 입력입니다.");
                        }
                    }
                }
#pragma endregion BuyItem
                // 아이템 판매
                else if (input == "2" || input == "아이템 판매")
                {
                    while(true)
                    {
                        Game->outputLog("어떤 아이템을 파시겠나?");
                        Game->inven->printItemlist();
                        Game->outputLog("0. 뒤로가기");
                        Game->inputLog(input);
                        if (input == "0" || input == "뒤로가기")
                        {
                            break;
                        }
                        int index = stoi(input);
                        if(index > 0 && index < Game->inven->getSize() + 1)
                        {
                            Item* choiceItem = Game->inven->findItem(index-1);
                            Game->outputLog(
                                choiceItem->getName() + "의 판매가는 "
                                + to_string(static_cast<int>(choiceItem->getPrice() * 0.6)) + "G 이네.\n"
                                + "파실겐가?"
                            );
                            Game->outputLog("1. 예 \n2. 아니오");
                            Game->inputLog(input);
                            if (input == "1" || input == "예")
                            {
                                shop_->sellItem(index-1, Game->inven);
                                //break;
                            }
                            else if (input == "2" || input == "아니오")
                            {
                                //아무것도 하지 않는다
                            }
                            else
                            {
                                Game->outputLog("잘못된 입력입니다.");
                            }
                        }
                        else
                        {
                            Game->outputLog("없는 아이템을 어찌 팔겠단 말인가?");
                        }
                    }
                    
                }

                // 인벤토리 확인
                else if (input == "3" || input == "인벤토리 확인")
                {
                    Game->inven->printItemlist();
                    system("pause");
                }

                // 상태창 출력
                else if (input == "4" || input == "상태창 출력")
                {
                    Character_->displayStatus();
                    system("pause");
                }

                // 던전 입장
                else if (input == "5" || input == "던전 입장")
                {
                    Game->updateState(GameManager::Battle);
                    break;
                }
                else
                {
                    Game->outputLog("잘못된 입력입니다.");
                }
            }
            break;

        case GameManager::Crafting:
            Game->outputLog(
                "제작소에 입장했습니다. 다음 행동을 선택하세요."
            );
            break;

        case GameManager::Battle:   //Game 전투/싸움 State
            Game->roundTracker++;
            currentMonster = Game->generateMonster();
            Game->outputLog(
                "던전에 입장했습니다. \n"
                "적 " + currentMonster->getName() + "와 조우!"
            );
            Game->battle(Character_, currentMonster);
            break;

        case GameManager::End:      //Game 끝.
            cout << "게임이 끝납니다..." << endl;
            /*for (int i = 0; i < Game->log.size(); i++)
            {
                cout << Game->log[i] << endl;
            }*/
            return 0;
        }
    }
}
