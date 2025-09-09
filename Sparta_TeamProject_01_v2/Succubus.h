#pragma once
#include "Monster.h"
#include <string>

class Item;

class Succubus : public Monster
{
private:
    std::string type;
    bool isEnraged; // 2������ ���� ����

    int charmAttack();
    int lifeDrainAttack();

public:
    Succubus(const std::string& type, int level);
    int performAction() override;
};