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
    outputLog("--GameManager�� �����Ǿ����ϴ�--");
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

    string navDialogue = "[State ����] �� " + stateStr;
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
        outputLog("��ũ ���� ����!");
        //int rd = generatorRandInt(3);
        //switch (rd)
        //{
        //case 1:     // �Ϲ� ��ũ ����
        //    return new Orc("�Ϲ�", GameManager::character_->getLevel(), "�Ϲ�");
        //    break;
        //case 2:     // �߸����� ��ũ ����
        //    return new Orc("�߸�����", GameManager::character_->getLevel(), "�߸�����");
        //    break;
        //case 3:     // ������ ��ũ ����
        //    return new Orc("������", GameManager::character_->getLevel(), "������");
        //    break;
        //}
    case 2:
        outputLog("��� ���� ����!");
        //int rd = generatorRandInt(4);
        //switch (rd)
        //{
        //case 1:     // �Ϲ� ��� ����
        //    return new Goblin("�Ϲ�", GameManager::character_->getLevel());
        //    break;
        //case 2:     // ������ ��� ����
        //    return new Goblin("������", GameManager::character_->getLevel());
        //    break;
        //case 3:     // �ǹ��� ��� ����
        //    return new Goblin("�ǹ���", GameManager::character_->getLevel());
        //    break;
        //case 4:     // �糪�� ��� ����
        //    return new Goblin("�糪��", GameManager::character_->getLevel());
        //    break;
        //case 5:     // ��� ��� ����
        //    return new Goblin("���", GameManager::character_->getLevel());
        //    break;
        //}
    case 3:     // �巡�� ����
        outputLog("�巡�� ���� ����!");
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
            while (true)
            {
                Game->outputLog(
                    "** ���� �༱���� �����ϼ���. \n"
                    "1. ���� ����\n"    //GameManager::Battle�� State ���� / �������� �̵�.
                    "2. ���� ����\n"    //GameManager::Shopping���� State ���� / �������� �̵�.
                    "3. ���ۼ� ����\n"  //GameManager::Crafting���� State ���� / ���ۼҷ� �̵�.
                    "4. ����â\n"       //GameManager::Resting�� ���� ������, ����â �� �� ���.
                    "5. �κ��丮 ����\n"  //GameManager::Resting�� ���� ������, �κ��丮 �� �� ���.
                    "0. ������"    //GameManager::End�� State ���� / ������ ����.
                );
                // Resting���� �������� ��� �ڵ�
                #pragma region RestChoiceResults
                Game->inputLog(input);
                if (input == "1" || input == "���� ����")
                {
                    Game->updateState(GameManager::Battle);
                    break;
                }
                else if (input == "2" || input == "���� ����")
                {
                    Game->updateState(GameManager::Shopping);
                    break;
                }
                else if (input == "3" || input == "���ۼ� ����")
                {
                    Game->updateState(GameManager::Crafting);
                    break;
                }
                else if (input == "4" || input == "����â")
                {
                    Game->outputLog("����â ���.");
                    Character_->displayStatus();
                    system("pause");
                    break;
                }
                else if (input == "5" || input == "�κ��丮 ����")
                {
                    Game->outputLog("**�κ��丮 ���:");
                    inventory_->printItemlist();
                    system("pause");
                    break;
                }
                else if (input == "0" || input == "������")
                {
                    Game->updateState(GameManager::End);
                    break;
                }
                else
                {
                    Game->outputLog("�߸��� �Է��Դϴ�.");
                }
                #pragma endregion  RestChoiceResults
            }
            // Game->updateState(GameManager::End);
            break;

        case GameManager::Shopping: //Game ����/���� State
            while (true)
            {
                Game->outputLog(
                    "������ �����߽��ϴ�. ���� �ൿ�� �����ϼ���. \n"
                    "1. ������ ����\n"
                    "2. ������ �Ǹ�"
                );
                Game->inputLog(input);
                if (input == "1" || input == "������ ����")
                {

                }
                else if (input == "1" || input == "������ �Ǹ�")
                {

                }
                else
                {
                    Game->outputLog("�߸��� �Է��Դϴ�.");
                }
            }
            break;

        case GameManager::Crafting:
            Game->outputLog(
                "���ۼҿ� �����߽��ϴ�. ���� �ൿ�� �����ϼ���."
            );
            break;

        case GameManager::Inventory:
            break;

        case GameManager::Battle:   //Game ����/�ο� State
            //currentMonster = Game->generateMonster();
            Game->generateMonster();
            Game->roundTracker++;
            /*if (Character_->getAttackSpeed() < currentMonster->getAttackSpeed())
            {

            }*/
            Game->outputLog(
                "������ �����߽��ϴ�. \n"
                "�� ****�� ����!"
                "1. ����\n"
                "2. ������ ���"
            );
            system("pause");
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
