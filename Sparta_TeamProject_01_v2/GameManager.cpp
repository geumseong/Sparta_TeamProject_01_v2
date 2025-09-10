#include <iostream>
#include "GameManager.h"
#include <random>
#include <vector>
#include <string>
#include "Magician.h"
#include "Monster.h"
#include "Inventory.h"
#include "orc.h"
#include "goblin.h"
#include "Dragon.h"

class Orc;

// Instances
GameManager* GameManager::instance_ = nullptr;

GameManager::GameManager()
{
    outputLog(u8"--GameManager가 생성되었습니다--");
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
    string navDialogue = u8"[State 변경] → " + stateStr;
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
    int lvlModifier = 0;
    int rand = generatorRandInt(2);
    if (rand == 1)
    {
        lvlModifier = 0;
    }
    else if(rand == 2)
    {
        lvlModifier = 1;
    }
    if (roundTracker % GameManager::bossRound == 0)
    {
        outputLog(u8"보스 몬스터 생성!!!");
        generateBossMonster(lvlModifier);
    }
    else
    {
        switch (generatorRandInt(2))
        {
            int rd;
        case 1:
            outputLog(u8"오크 몬스터 생성!");
            rd = generatorRandInt(3);
            switch (rd)
            {
            case 1:     // 일반 오크 생성
                return new Orc(u8"일반", GameManager::character_->getLevel() + lvlModifier);
                break;
            case 2:     // 야만적인 오크 생성
                return new Orc(u8"야만적인", GameManager::character_->getLevel() + lvlModifier);
                break;
            case 3:     // 광전사 오크 생성
                return new Orc(u8"광전사", GameManager::character_->getLevel() + lvlModifier);
                break;
            }
        case 2:
            outputLog(u8"고블린 몬스터 생성!");
            rd = generatorRandInt(4);
            switch (rd)
            {
            case 1:     // 일반 고블린 생성
                return new Goblin(u8"일반", GameManager::character_->getLevel() + lvlModifier);
                break;
            case 2:     // 겁쟁이 고블린 생성
                return new Goblin(u8"겁쟁이", GameManager::character_->getLevel() + lvlModifier);
                break;
            case 3:     // 건방진 고블린 생성
                return new Goblin(u8"건방진", GameManager::character_->getLevel() + lvlModifier);
                break;
            case 4:     // 사나운 고블린 생성
                return new Goblin(u8"사나운", GameManager::character_->getLevel() + lvlModifier);
                break;
            case 5:     // 재벌 고블린 생성
                return new Goblin(u8"재벌", GameManager::character_->getLevel() + lvlModifier);
                break;
            }
        }
    }
}

Monster* GameManager::generateBossMonster(int lvlModif)
{
    outputLog(u8"드래곤 몬스터 생성!");
    //return new Dragon(GameManager::character_->getLevel() + lvlModif);
    return new Goblin(u8"재벌", 1);
}

void GameManager::battle(Character* player, Monster* currentMonster)
{
    if (player->getAttackSpeed() < currentMonster->getAttackSpeed())    //빠른 공속이 선빵
    {
        int beforeHealth = player->getHealth();
        instance_->outputLog(currentMonster->getName() + u8"의 선제공격!");
        player->takeCharacterDamage(currentMonster->performAction());   // 몬스터가 공격
        instance_->outputLog(
            u8"현재 플레이어의 HP: "
            + to_string(beforeHealth) + " / " + to_string(player->getMaxHealth())
            + " ===> "
            + to_string(player->getHealth()) + " / " + to_string(player->getMaxHealth())
        );
        if (player->getHealth() <= 0)
        {
            instance_->updateState(GameManager::End);
        }
    }
    while (!currentMonster->isDead() && player->getHealth() > 0)  // 어느 한쪽이라도 죽지 않는 한 진행
    {
        instance_->outputLog(
            u8"플레이어의 턴입니다. \n"
            u8"1. 공격\n"
            u8"2. 아이템 사용\n"
            "==================================="
        );
        string input;
        instance_->inputLog(input);
        if (input == "1" || input == "공격")
        {
            player->attack(currentMonster);     // 캐릭터가 몬스터에게 공격
            if (!currentMonster->isDead())      //몬스터가 죽지 않았다면 몬스터가 공격
            {
                int beforeHealth = player->getHealth();
                player->takeCharacterDamage(currentMonster->performAction()); // 몬스터가 공격
                instance_->outputLog(
                    u8"현재 플레이어의 HP: "
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
            else        // 몬스터가 죽었다면
            {
                if (roundTracker == GameManager::victoryRound)
                {
                    outputLog(u8"** Victory!!!!");
                    instance_->updateState(GameManager::End);
                    //break;
                }
                else
                {
                    // 보상 지급
                    for (int i = 0; i < currentMonster->getDropItemsSize(); i++)
                    {
                        vector<Item> a = currentMonster->getDropItems();
                        instance_->inven->addItem(move(Item(a[i].getName(), a[i].getPrice(), 1, E_Type::Material)));
                        instance_->inven->addItem(move(Item(u8"슬라임의 끈적한 젤리", 100, 1, E_Type::Material)));
                    }
                    instance_->updateState(GameManager::Shopping);
                    //break;
                }
                if (roundTracker % eventRound == 0)
                {
                    instance_->updateState(GameManager::Crafting);
                    //break;
                }
                delete currentMonster;  // 몬스터 메모리 해제
                break;
            }
        }
        else if (input == "2" || input == "아이템 사용")
        {

        }
        else
        {
            instance_->outputLog(u8"잘못된 입력입니다.");
        }
    }
}
//
//
/*
void GameManager::visitShop(Character* player) {
}
void GameManager::displayInventory(Character* player) {
}
*/