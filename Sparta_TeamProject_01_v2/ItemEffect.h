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
    int HP = 0;
    int MP = 0;
    HealEffect(int hp, int mp) : HP(hp), MP(mp) {}
    void onConsume(Character& character)
    {
        character.setHealth(min(character.getHealth() + HP, character.getMaxHealth()));
        character.setMp(min(character.getMp() + MP, character.getMaxMp()));
        //character.setHealth(min(character.getHealth() + int(character.getMaxHealth() * (HP / 100)), character.getMaxHealth()));
        //character.setMp(min(character.getMp() + int(character.getMaxMp() * (MP / 100)), character.getMaxMp()));
        //백분율로 회복되게 변경
    }
};

class BuffEffect : public I_Effect
{ //defbuff, spdbuff
public:
    int atkbuff = 0;
    int defbuff = 0;
    int spdbuff = 0;
    int hpbuff = 0;
    int mpbuff = 0;
    BuffEffect(int ab, int db, int sb, int hb, int mb) : atkbuff(ab), defbuff(db), spdbuff(sb), hpbuff(hb), mpbuff(mb) {}
    virtual void onEquip(Character& character) override
    {

        character.setAttack(character.getAttack() + atkbuff);
        character.setDefense(character.getDefense() + defbuff);
        character.setAttackSpeed(character.getAttackSpeed() + spdbuff);
        character.setMaxhealth(character.getMaxHealth() + hpbuff);
        character.setMaxMp(character.getMaxMp() + mpbuff);
    }
    virtual void onUnequip(Character& character) override
    {
        character.setAttack(character.getAttack() - atkbuff);
        character.setDefense(character.getDefense() - defbuff);
        character.setAttackSpeed(character.getAttackSpeed() - spdbuff);
        character.setMaxhealth(character.getMaxHealth() - hpbuff);
        character.setMaxMp(character.getMaxMp() - mpbuff);
    }
};