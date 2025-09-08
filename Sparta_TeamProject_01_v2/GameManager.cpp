#include <iostream>
#include "GameManager.h"
#include <random>
#include <vector>
#include <string>
#include "Magician.h"
#include "Monster.h"
using namespace std;

GameManager* GameManager::instance_ = nullptr;

GameManager::GameManager()
{
    outputLog("--GameManager가 생성되었습니다--");
    this->currentState = Start;
}



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

void GameManager::outputLog(string navDialogue)
{
    cout << navDialogue << endl;
    log.push_back(navDialogue);
}

void GameManager::inputLog(string& input)
{
    cin.ignore();
    cin >> input;
    //getline(cin, input);
    log.push_back(input);
}

Monster* GameManager::generateMonster()
{
    int rd = 0;
    while (rd != 0)
    {
        rd = rand() % 4;  // 1-3 사이 랜덤 정수 생성
    }
    switch (rd)
    {
    case 1:
        cout << "* 몬스터 타입 1 생성!" << endl;
        return new Monster("Type1Monster", 10, 10);  // 몬스터 타입 1
    case 2:
        cout << "* 몬스터 타입 2 생성!" << endl;
        return new Monster("Type2Monster", 10, 10);  // 몬스터 타입 2
    case 3:
        cout << "* 몬스터 타입 3 생성!" << endl;
        return new Monster("Type2Monster", 10, 10);  // 몬스터 타입 3
    default:
        return new Monster("", 1, 1);
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
            Game->outputLog(
                "** 다음 행선지를 선택하세요. \n"
                "1. 던전 입장\n"
                "2. 상점 입장\n"
                "3. 제작소 입장\n"
                "4. 상태창"
            );
            
            while (true)
            {
                Game->inputLog(input);
                if (input == "1")
                {
                    Game->updateState(GameManager::Battle);
                }
                else if (input == "2")
                {
                    Game->updateState(GameManager::Shopping);
                }
                else if (input == "3")
                {
                    Game->updateState(GameManager::Crafting);
                }
                else if (input == "4")
                {
                    Game->outputLog("상태창 출력.");
                    Character_->displayStatus();
                }
                else
                {
                    Game->outputLog("잘못된 입력입니다.");
                }
                break;
            }

            Game->updateState(GameManager::End);
            break;
        case GameManager::Shopping: //Game 상점/쇼핑 State
            Game->outputLog(
                "상점에 입장했습니다. 다음 행동을 선택하세요. \n"
                "1. 아이템 구매\n"
                "2. 상점 입장"
            );
            break;
        case GameManager::Crafting:
            Game->outputLog(
                "제작소에 입장했습니다. 다음 행동을 선택하세요."
            );
        case GameManager::Battle:   //Game 전투/싸움 State
            currentMonster = Game->generateMonster();
            Game->roundTracker++;
            if (Character_->getAttackSpeed() < currentMonster->getAttackSpeed())
            {

            }
            Game->outputLog(
                "던전에 입장했습니다. \n"
                "적 ****와 조우!"
                "1. 공격\n"
                "2. 아이템 사용"
            );
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
