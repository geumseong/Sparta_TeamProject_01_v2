#include <iostream>
#include "GameManager.h"
#include <random>
#include <vector>
#include <string>
#include "Magician.h"
#include "Monster.h"
#include "Inventory.h"
#include "Shop.h"
#include "orc.h"
#include "goblin.h"
#include "Dragon.h"

class Orc;

// Instances
GameManager* GameManager::instance_ = nullptr;
//Inventory* inventory_ = new Inventory(100, 10);
//Shop* shop_;
//int roundTracker = 0;

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

    cout << "===================================" << endl;
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

Monster* GameManager::generateMonster()
{
    if (roundTracker % GameManager::bossRound == 0)
    {
        outputLog("���� ���� ����!!!");
        generateBossMonster();
    }
    else
    {
        switch (generatorRandInt(2))
        {
            int rd;
        case 1:
            outputLog("��ũ ���� ����!");
            rd = generatorRandInt(3);
            switch (rd)
            {
            case 1:     // �Ϲ� ��ũ ����
                return new Orc("�Ϲ�", GameManager::character_->getLevel());
                break;
            case 2:     // �߸����� ��ũ ����
                return new Orc("�߸�����", GameManager::character_->getLevel());
                break;
            case 3:     // ������ ��ũ ����
                return new Orc("������", GameManager::character_->getLevel());
                break;
            }
        case 2:
            outputLog("��� ���� ����!");
            rd = generatorRandInt(4);
            switch (rd)
            {
            case 1:     // �Ϲ� ��� ����
                return new Goblin("�Ϲ�", GameManager::character_->getLevel());
                break;
            case 2:     // ������ ��� ����
                return new Goblin("������", GameManager::character_->getLevel());
                break;
            case 3:     // �ǹ��� ��� ����
                return new Goblin("�ǹ���", GameManager::character_->getLevel());
                break;
            case 4:     // �糪�� ��� ����
                return new Goblin("�糪��", GameManager::character_->getLevel());
                break;
            case 5:     // ��� ��� ����
                return new Goblin("���", GameManager::character_->getLevel());
                break;
            }
        }
    }
}

Monster* GameManager::generateBossMonster()
{
    outputLog("�巡�� ���� ����!");
    return new Dragon(GameManager::character_->getLevel());
}

void GameManager::battle(Character* player, Monster* currentMonster)
{
    if (player->getAttackSpeed() < currentMonster->getAttackSpeed())    //���� ������ ����
    {
        int beforeHealth = player->getHealth();
        instance_->outputLog(currentMonster->getName() + "�� ��������!");
        player->takeCharacterDamage(currentMonster->performAction());   // ���Ͱ� ����
        instance_->outputLog(
            "���� �÷��̾��� HP: "
            + to_string(beforeHealth) + " / " + to_string(player->getMaxHealth())
            + " ===> "
            + to_string(player->getHealth()) + " / " + to_string(player->getMaxHealth())
        );
        if (player->getHealth() <= 0)
        {
            instance_->updateState(GameManager::End);
        }
    }
    while (!currentMonster->isDead() && player->getHealth() > 0)  // ��� �����̶� ���� �ʴ� �� ����
    {
        instance_->outputLog(
            "�÷��̾��� ���Դϴ�. \n"
            "1. ����\n"
            "2. ������ ���\n"
            "==================================="
        );
        string input;
        instance_->inputLog(input);
        if (input == "1" || input == "����")
        {
            player->attack(currentMonster);     // ĳ���Ͱ� ���Ϳ��� ����
            if (!currentMonster->isDead())      //���Ͱ� ���� �ʾҴٸ� ���Ͱ� ����
            {
                int beforeHealth = player->getHealth();
                player->takeCharacterDamage(currentMonster->performAction()); // ���Ͱ� ����
                instance_->outputLog(
                    "���� �÷��̾��� HP: "
                    + to_string(beforeHealth) + " / " + to_string(player->getMaxHealth())
                    + " ===> "
                    + to_string(player->getHealth()) + " / " + to_string(player->getMaxHealth())
                );
                if (player->getHealth() <= 0)
                {
                    instance_->updateState(GameManager::End);
                    break;
                }
            }
            else        // ���Ͱ� �׾��ٸ�
            {
                delete currentMonster;  // �޸� ����
                if (roundTracker == GameManager::victoryRound)
                {
                    outputLog("** Victory!!!!");
                    instance_->updateState(GameManager::End);
                    break;
                }
                else
                {
                    // ���� ����
                    instance_->updateState(GameManager::Resting);
                    break;
                }
            }
        }
        else if (input == "2" || input == "������ ���")
        {

        }
        else
        {
            instance_->outputLog("�߸��� �Է��Դϴ�.");
        }
    }
}

/*
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
    cout << "===================================" << endl;
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
                    //inventory_->printItemlist();
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
                
                //������ ����
                #pragma region BuyItem
                if (input == "1" || input == "������ ����")
                {
                    while (true)
                    {
                        //shop_->displayItems();
                        Game->inputLog(input);
                        int index = stoi(input);
                        //shop_->showItem(index);
                        Game->outputLog("�׷���, ��ڳ�?");
                        Game->inputLog(input);
                        if (input == "1" || "��")
                        {
                            //shop_->buyItem(index, *inventory_);
                            break;
                        }
                        else if (input == "2" || "�ƴϿ�")
                        {
                            break;
                        }
                        else
                        {
                            Game->outputLog("�߸��� �Է��Դϴ�.");
                            break;
                        }
                    }
                }
                #pragma endregion BuyItem
                // ������ �Ǹ�
                else if (input == "1" || input == "������ �Ǹ�")
                {
                    //inventory_->printItemlist();
                    Game->outputLog("� �������� �Ľðڳ�?");
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

        case GameManager::Battle:   //Game ����/�ο� State
            Game->roundTracker++;
            currentMonster = Game->generateMonster();
            Game->outputLog(
                "������ �����߽��ϴ�. \n"
                "�� " + currentMonster->getName() + "�� ����!"
            );
            Game->battle(Character_, currentMonster);
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
