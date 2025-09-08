#include <iostream>
#include "GameManager.h"
#include <random>
#include <vector>
#include <string>
using namespace std;

GameManager* GameManager::instance_ = nullptr;

GameManager::GameManager()
{
    outputLog("--GameManager�� �����Ǿ����ϴ�--");
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

    string navDialogue = "[State ����] �� " + stateStr;
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
//        rd = rand() % 4;  // 1-3 ���� ���� ���� ����
//    }
//    switch (rd)
//    {
//    case 1:
//        cout << "* ���� Ÿ�� 1 ����!" << endl;
//        //return new Monster();  // ���� Ÿ�� 1
//    case 2:
//        cout << "* ���� Ÿ�� 2 ����!" << endl;
//        //return new Monster();  // ���� Ÿ�� 2
//    case 3:
//        cout << "* ���� Ÿ�� 3 ����!" << endl;
//        //return new Monster();  // ���� Ÿ�� 3
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
        case GameManager::Start:    //Game ���� State
            navDialogue = "** ĳ���� �̸��� ���Ͻʽÿ�.";
            Game->outputLog(navDialogue);
            Game->inputLog(input);
            //Character = new Character(input);
            navDialogue = "ĳ���Ͱ� �����Ǿ����ϴ�.";
            Game->outputLog(navDialogue);
            Game->updateState(GameManager::Resting);
            break;
        case GameManager::Resting:  //Game �޽� State
            navDialogue =
                "���� �༱���� �����ϼ���. \n"
                "1. ���� ����\n"
                "2. ���� ����\n"
                "3. ���ۼ� ����";
            Game->outputLog(navDialogue);

            Game->updateState(GameManager::End);
            break;
        case GameManager::Shopping: //Game ����/���� State
            navDialogue =
                "������ �����߽��ϴ�. ���� �ൿ�� �����ϼ���. \n"
                "1. ������ ����\n"
                "2. ���� ����";
            Game->outputLog(navDialogue);
            break;
        case GameManager::Battle:   //Game ����/�ο� State
            //Game->generateMonster(int level);
            navDialogue =
                "������ �����߽��ϴ�. \n"
                "�� ****�� ����!"
                "1. ����\n"
                "2. ������ ���";
            Game->outputLog(navDialogue);
            break;
        case GameManager::End:      //Game ��.
            cout << "���ݺ��� ��� �α׸� ����մϴ�." << endl;
            for (int i = 0; i < Game->log.size(); i++)
            {
                cout << Game->log[i] << endl;
            }
            return 0;
        }
    }
}
