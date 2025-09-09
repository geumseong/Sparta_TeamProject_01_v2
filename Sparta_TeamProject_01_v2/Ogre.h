#pragma once
#include "Monster.h"
#include <string>

class Item;

class Ogre : public Monster
{
private:
    std::string type;

    int smashAttack();
    int doubleAttack();

public:
    Ogre(const std::string& type, int level);
    int performAction() override;
};