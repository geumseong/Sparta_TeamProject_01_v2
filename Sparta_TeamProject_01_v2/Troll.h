#pragma once
#include "Monster.h"
#include <string>

class Item;

class Troll : public Monster
{
private:
    std::string type;
    int regenerationAmount; // 턴당 체력 재생량

    int slamAttack();

public:
    Troll(const std::string& type, int level);
    int performAction() override;
};