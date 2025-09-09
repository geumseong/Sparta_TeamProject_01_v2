#include <iostream>
#include "GameManager.h"
#include <random>
#include <vector>
#include <string>
#include "Magician.h"
#include "Monster.h"
#include "Inventory.h"

class Orc;

// Instances
GameManager* GameManager::instance_ = nullptr;
Inventory* inventory_ = new Inventory(100, 10);

GameManager::GameManager()
{
    outputLog("--GameManager가 생성되었습니다--");
    this->currentState = Start;
}


// StateMachine
void GameManager::updateState(States stateName)
{
    string stateStr = "";
    switch (stateName)
    {
    case Start:    stateStr = "Start"; break;
    case Battle:   stateStr = "Battle"; break;
    case Shopping: stateStr = "Shopping"; break;
    case Resting:  stateStr = "Resting"; break;
    case End:      stateStr = "End"; break;
    case Crafting:  stateStr = "Crafting"; break;
    }

    string navDialogue = "[State 변경] → " + stateStr;
    outputLog(navDialogue);

    this->currentState = stateName;
}

// cout print
void GameManager::outputLog(string navDialogue)
{
    cout << navDialogue << endl;
    //log.push_back(navDialogue);
}

//cin input
void GameManager::inputLog(string& input)
{
    //cin.ignore();
    //cin >> input;
    getline(cin, input);
    //log.push_back(input);
}

int generatorRandInt(int max)
{
    int rd = rand() % max + 1;
    return rd;
}

/*Monster**/ void GameManager::generateMonster()
{
    switch (generatorRandInt(3))
    {
    case 1:
        outputLog("오크 몬스터 생성!");
        //int rd = generatorRandInt(3);
        //switch (rd)
        //{
        //case 1:     // 일반 오크 생성
        //    return new Orc("일반", GameManager::character_->getLevel(), "일반");
        //    break;
        //case 2:     // 야만적인 오크 생성
        //    return new Orc("야만적인", GameManager::character_->getLevel(), "야만적인");
        //    break;
        //case 3:     // 광전사 오크 생성
        //    return new Orc("광전사", GameManager::character_->getLevel(), "광전사");
        //    break;
        //}
    case 2:
        outputLog("고블린 몬스터 생성!");
        //int rd = generatorRandInt(4);
        //switch (rd)
        //{
        //case 1:     // 일반 고블린 생성
        //    return new Goblin("일반", GameManager::character_->getLevel());
        //    break;
        //case 2:     // 겁쟁이 고블린 생성
        //    return new Goblin("겁쟁이", GameManager::character_->getLevel());
        //    break;
        //case 3:     // 건방진 고블린 생성
        //    return new Goblin("건방진", GameManager::character_->getLevel());
        //    break;
        //case 4:     // 사나운 고블린 생성
        //    return new Goblin("사나운", GameManager::character_->getLevel());
        //    break;
        //case 5:     // 재벌 고블린 생성
        //    return new Goblin("재벌", GameManager::character_->getLevel());
        //    break;
        //}
    case 3:     // 드래곤 생성
        outputLog("드래곤 몬스터 생성!");
        break;
    }

}

/*
BossMonster* GameManager::generateBossMonster(int level) {
}
void GameManager::battle(Character* player) {
}
void GameManager::visitShop(Character* player) {
}
void GameManager::displayInventory(Character* player) {
}
*/

//#include <iostream>
//#include <vector>
//#include "Monster.h"
//#include "Character.h"
//#include "GameManager.h"
//using namespace std;

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
                    inventory_->printItemlist();
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
            // Game->updateState(GameManager::End);
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
                if (input == "1" || input == "아이템 구매")
                {

                }
                else if (input == "1" || input == "아이템 판매")
                {

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

        case GameManager::Inventory:
            break;

        case GameManager::Battle:   //Game 전투/싸움 State
            //currentMonster = Game->generateMonster();
            Game->generateMonster();
            Game->roundTracker++;
            /*if (Character_->getAttackSpeed() < currentMonster->getAttackSpeed())
            {

            }*/
            Game->outputLog(
                "던전에 입장했습니다. \n"
                "적 ****와 조우!"
                "1. 공격\n"
                "2. 아이템 사용"
            );
            system("pause");
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
