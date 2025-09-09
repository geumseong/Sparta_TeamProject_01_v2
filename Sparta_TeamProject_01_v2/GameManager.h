#pragma once
#include <iostream>
#include <vector>
#include "Character.h"

using namespace std;
class Monster;

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

    static void deleteInstance()
    {
        delete instance_;
        instance_ = nullptr;
    }
    ~GameManager() {}

    Character* character_;

    enum States { Start, Battle, Shopping, Resting, Crafting, End };
    States currentState;
    int roundTracker;
    int victoryRound = 10;
    int bossRound = 5;

    vector<string> log;
    void outputLog(string navDialogue);
    void inputLog(string& input);

    Monster* generateMonster();
    //Monster* generateMonster();
    void updateState(States stateName);
    Monster* generateBossMonster(int lvlModif);
    void battle(Character* character, Monster* currentMonster);
    //void visitShop(Character* player);
    //void displayInventory(Character* player);
};
