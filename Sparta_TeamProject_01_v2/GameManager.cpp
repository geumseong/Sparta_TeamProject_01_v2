#include <iostream>
#include "GameManager.h"
#include <random>
#include <vector>
#include <string>
#include "Magician.h"
#include "Monster.h"

class Orc;

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

int generatorRandInt(int max)
{
    int rd = 0;
    while (rd != 0)
    {
        rd = rand() % max + 1;
    }
    return rd;
}

Monster* GameManager::generateMonster()
{
    switch (generatorRandInt(1))
    {
    case 1:
        outputLog("��ũ ���� ����!");
        int rd = generatorRandInt(3);
        switch (rd)
        {
        case 1:     // �Ϲ� ��ũ ����
            return new Orc("�Ϲ�", GameManager::character_->getLevel(), "�Ϲ�");
            break;
        case 2:     // �߸����� ��ũ ����
            return new Orc("�߸�����", GameManager::character_->getLevel(), "�߸�����");
            break;
        case 3:     // ������ ��ũ ����
            return new Orc("������", GameManager::character_->getLevel(), "������");
            break;
        }
    case 2:
        //outputLog("��� ���� ����!");
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
        cout << "* ���� Ÿ�� 3 ����!" << endl;
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
            /*if (Character_->getAttackSpeed() < currentMonster->getAttackSpeed())
            {

            }*/
            Game->outputLog(
                "������ �����߽��ϴ�. \n"
                "�� ****�� ����!"
                "1. ����\n"
                "2. ������ ���"
            );
            Game->updateState(GameManager::End);
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
