#pragma once
#include "Monster.h"
#include <string>

class Item;

class Troll : public Monster
{
private:
    std::string type;
    int regenerationAmount; // �ϴ� ü�� �����

    int slamAttack();

public:
    Troll(const std::string& type, int level);
    int performAction() override;
};