#pragma once
#include <iostream>
#include "Monster.h"
#include <vector>
#include "Character.h"

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
    Character* Character_;

    const enum States { Start, Battle, Shopping, Resting, Crafting, End };
    States currentState;
    int roundTracker;

    vector<string> log;
    void outputLog(string navDialogue);
    void inputLog(string& input);

    Monster* generateMonster();
    void updateState(States stateName);
    //BossMonster* generateBossMonster(int level);
    void battle();
    //void visitShop(Character* player);
    //void displayInventory(Character* player);
};
