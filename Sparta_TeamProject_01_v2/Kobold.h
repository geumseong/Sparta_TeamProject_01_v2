#pragma once
#include "Monster.h"
#include <string>

class Item;

class Kobold : public Monster
{
private:
    std::string type;
    int turnCount;

    int normalAttack();
    int trapAttack(); // �������� ��� ����

public:
    Kobold(const std::string& type, int level);
    int performAction() override;
};