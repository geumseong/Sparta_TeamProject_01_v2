
#include <iostream>
#include <vector>
#include "Monster.h"
#include "Character.h"
#include "GameManager.h"
#include "Magician.h"
using namespace std;

int main()
{
    GameManager* Game = GameManager::getInstance();
    Character* Character_;
    Monster* currentMonster;
    string input;
    Game->outputLog("** 캐릭터 이름을 정하십시오.");
    Game->inputLog(input);
    Character_ = new Magician(input);
    Game->character_ = Character_;
    Game->outputLog("캐릭터가 생성되었습니다.");
    cout << "===================================" << endl;
    Game->updateState(GameManager::Resting);
    while (true)
    {
        switch (Game->currentState)
        {
        case GameManager::Start:    //Game 시작 State
            break;

        case GameManager::Resting:  //Game 휴식 State
            while (true)
            {
                Game->outputLog(
                    "** 다음 행선지를 선택하세요. \n"
                    "1. 던전 입장\n"    //GameManager::Battle로 State 변경 / 던전으로 이동.
                    "2. 상점 입장\n"    //GameManager::Shopping으로 State 변경 / 상점으로 이동.
                    "3. 제작소 입장\n"  //GameManager::Crafting으로 State 변경 / 제작소로 이동.
                    "4. 상태창\n"       //GameManager::Resting에 남아 있지만, 상태창 한 번 출력.
                    "5. 인벤토리 열기\n"  //GameManager::Resting에 남아 있지만, 인벤토리 한 번 출력.
                    "0. 끝내기"    //GameManager::End로 State 변경 / 게임을 끝냄.
                );
                // Resting에서 선택지의 결과 코드
#pragma region RestChoiceResults
                Game->inputLog(input);
                if (input == "1" || input == "던전 입장")
                {
                    Game->updateState(GameManager::Battle);
                    break;
                }
                else if (input == "2" || input == "상점 입장")
                {
                    Game->updateState(GameManager::Shopping);
                    break;
                }
                else if (input == "3" || input == "제작소 입장")
                {
                    Game->updateState(GameManager::Crafting);
                    break;
                }
                else if (input == "4" || input == "상태창")
                {
                    Game->outputLog("상태창 출력.");
                    Character_->displayStatus();
                    system("pause");
                    break;
                }
                else if (input == "5" || input == "인벤토리 열기")
                {
                    Game->outputLog("**인벤토리 목록:");
                    //inventory_->printItemlist();
                    system("pause");
                    break;
                }
                else if (input == "0" || input == "끝내기")
                {
                    Game->updateState(GameManager::End);
                    break;
                }
                else
                {
                    Game->outputLog("잘못된 입력입니다.");
                }
#pragma endregion  RestChoiceResults
            }
            break;

        case GameManager::Shopping: //Game 상점/쇼핑 State
            while (true)
            {
                Game->outputLog(
                    "상점에 입장했습니다. 다음 행동을 선택하세요. \n"
                    "1. 아이템 구매\n"
                    "2. 아이템 판매"
                );
                Game->inputLog(input);

                //아이템 구매
#pragma region BuyItem
                if (input == "1" || input == "아이템 구매")
                {
                    while (true)
                    {
                        //shop_->displayItems();
                        Game->inputLog(input);
                        int index = stoi(input);
                        //shop_->showItem(index);
                        Game->outputLog("그래서, 사겠나?");
                        Game->inputLog(input);
                        if (input == "1" || "예")
                        {
                            //shop_->buyItem(index, *inventory_);
                            break;
                        }
                        else if (input == "2" || "아니오")
                        {
                            break;
                        }
                        else
                        {
                            Game->outputLog("잘못된 입력입니다.");
                            break;
                        }
                    }
                }
#pragma endregion BuyItem
                // 아이템 판매
                else if (input == "1" || input == "아이템 판매")
                {
                    //inventory_->printItemlist();
                    Game->outputLog("어떤 아이템을 파시겠나?");
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
