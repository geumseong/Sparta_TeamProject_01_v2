#pragma once
#include <algorithm>
#include "Character.h"
class Character;

struct I_Effect
{
    virtual ~I_Effect() = default;
    virtual void onConsume(Character& character) {}
    virtual void onEquip(Character& character) {}
    virtual void onUnequip(Character& character) {}
};

class HealEffect : public I_Effect
{
public:
    int heal = 0;
    HealEffect(int heal) : heal(heal) {}
    void onConsume(Character& character)
    {
        character.setHealth( min(character.getHealth() + heal, character.getMaxHealth()) );
    }
};

class BuffEffect : public I_Effect
{ //defbuff, spdbuff
public:
    int atkbuff = 0;
    int defbuff = 0;
    int spdbuff = 0;
    BuffEffect(int ab, int db, int sb) : atkbuff(ab), defbuff(db), spdbuff(sb) {}
    virtual void onEquip(Character& character) override
    {

        character.setAttack(character.getAttack() + atkbuff);
        character.setDefense(character.getDefense() + defbuff);
        character.setAttackSpeed(character.getAttackSpeed() + spdbuff);
    }
    virtual void onUnequip(Character& character) override
    {
        character.setAttack(character.getAttack() - atkbuff);
        character.setDefense(character.getDefense() - defbuff);
        character.setAttackSpeed(character.getAttackSpeed() - spdbuff);
    }
};