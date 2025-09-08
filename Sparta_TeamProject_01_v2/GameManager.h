#pragma once
#include <iostream>
#include "Monster.h"
#include <vector>
//#include "Character.h"

using namespace std;

class GameManager
{
private:
    static GameManager* instance_;
    GameManager();
    GameManager(const GameManager&);
    GameManager& operator=(const GameManager&);

public:
    static GameManager* getInstance()
    {
        if (instance_ == nullptr)
        {
            instance_ = new GameManager();
        }
        return instance_;
    }
    //Character* Character;

    const enum States { Start, Battle, Shopping, Resting, End };
    States currentState;

    vector<string> log;
    void outputLog(string navDialogue);
    void inputLog(string& input);

    //Monster* generateMonster(int level);
    void updateState(States stateName);
    /*BossMonster* generateBossMonster(int level);
    void battle(Character* player);
    void visitShop(Character* player);
    void displayInventory(Character* player);*/
};
