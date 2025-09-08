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
    case Crafting:  stateStr = "Crafting"; break;
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
        rd = rand() % 4;  // 1-3 ���� ���� ���� ����
    }
    switch (rd)
    {
    case 1:
        cout << "* ���� Ÿ�� 1 ����!" << endl;
        return new Monster("Type1Monster", 10, 10);  // ���� Ÿ�� 1
    case 2:
        cout << "* ���� Ÿ�� 2 ����!" << endl;
        return new Monster("Type2Monster", 10, 10);  // ���� Ÿ�� 2
    case 3:
        cout << "* ���� Ÿ�� 3 ����!" << endl;
        return new Monster("Type2Monster", 10, 10);  // ���� Ÿ�� 3
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
    Game->outputLog("** ĳ���� �̸��� ���Ͻʽÿ�.");
    Game->inputLog(input);
    Character_ = new Magician(input);
    Game->character_ = Character_;
    Game->outputLog("ĳ���Ͱ� �����Ǿ����ϴ�.");
    Game->updateState(GameManager::Resting);
    while (true)
    {
        switch (Game->currentState)
        {
        case GameManager::Start:    //Game ���� State
            break;
        case GameManager::Resting:  //Game �޽� State
            Game->outputLog(
                "** ���� �༱���� �����ϼ���. \n"
                "1. ���� ����\n"
                "2. ���� ����\n"
                "3. ���ۼ� ����\n"
                "4. ����â"
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
                    Game->outputLog("����â ���.");
                    Character_->displayStatus();
                }
                else
                {
                    Game->outputLog("�߸��� �Է��Դϴ�.");
                }
                break;
            }

            Game->updateState(GameManager::End);
            break;
        case GameManager::Shopping: //Game ����/���� State
            Game->outputLog(
                "������ �����߽��ϴ�. ���� �ൿ�� �����ϼ���. \n"
                "1. ������ ����\n"
                "2. ���� ����"
            );
            break;
        case GameManager::Crafting:
            Game->outputLog(
                "���ۼҿ� �����߽��ϴ�. ���� �ൿ�� �����ϼ���."
            );
        case GameManager::Battle:   //Game ����/�ο� State
            currentMonster = Game->generateMonster();
            Game->roundTracker++;
            if (Character_->getAttackSpeed() < currentMonster->getAttackSpeed())
            {

            }
            Game->outputLog(
                "������ �����߽��ϴ�. \n"
                "�� ****�� ����!"
                "1. ����\n"
                "2. ������ ���"
            );
            break;
        case GameManager::End:      //Game ��.
            cout << "������ �����ϴ�..." << endl;
            /*for (int i = 0; i < Game->log.size(); i++)
            {
                cout << Game->log[i] << endl;
            }*/
            return 0;
        }
    }
}
