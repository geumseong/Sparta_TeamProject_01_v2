#include <iostream>
#include "GameManager.h"
#include <random>
#include <vector>
#include <string>
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
    getline(cin, input);
    log.push_back(input);
}

//Monster* GameManager::generateMonster(int level)
//{
//    int rd = 0;
//    while (rd != 0)
//    {
//        rd = rand() % 4;  // 1-3 사이 랜덤 정수 생성
//    }
//    switch (rd)
//    {
//    case 1:
//        cout << "* 몬스터 타입 1 생성!" << endl;
//        //return new Monster();  // 몬스터 타입 1
//    case 2:
//        cout << "* 몬스터 타입 2 생성!" << endl;
//        //return new Monster();  // 몬스터 타입 2
//    case 3:
//        cout << "* 몬스터 타입 3 생성!" << endl;
//        //return new Monster();  // 몬스터 타입 3
//    }
//}

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
    // Character* Character;
    string navDialogue;
    string input;
    while (true)
    {
        switch (Game->currentState)
        {
        case GameManager::Start:    //Game 시작 State
            navDialogue = "** 캐릭터 이름을 정하십시오.";
            Game->outputLog(navDialogue);
            Game->inputLog(input);
            //Character = new Character(input);
            navDialogue = "캐릭터가 생성되었습니다.";
            Game->outputLog(navDialogue);
            Game->updateState(GameManager::Resting);
            break;
        case GameManager::Resting:  //Game 휴식 State
            navDialogue =
                "다음 행선지를 선택하세요. \n"
                "1. 던전 입장\n"
                "2. 상점 입장\n"
                "3. 제작소 입장";
            Game->outputLog(navDialogue);

            Game->updateState(GameManager::End);
            break;
        case GameManager::Shopping: //Game 상점/쇼핑 State
            navDialogue =
                "상점에 입장했습니다. 다음 행동을 선택하세요. \n"
                "1. 아이템 구매\n"
                "2. 상점 입장";
            Game->outputLog(navDialogue);
            break;
        case GameManager::Battle:   //Game 전투/싸움 State
            //Game->generateMonster(int level);
            navDialogue =
                "던전에 입장했습니다. \n"
                "적 ****와 조우!"
                "1. 공격\n"
                "2. 아이템 사용";
            Game->outputLog(navDialogue);
            break;
        case GameManager::End:      //Game 끝.
            cout << "지금부터 모든 로그를 출력합니다." << endl;
            for (int i = 0; i < Game->log.size(); i++)
            {
                cout << Game->log[i] << endl;
            }
            return 0;
        }
    }
}
