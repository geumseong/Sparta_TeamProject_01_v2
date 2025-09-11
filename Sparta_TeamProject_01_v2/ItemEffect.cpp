#include "ItemEffect.h"
#include "Character.h"

void HealEffect::onConsume(Character* character)
{
    //character->setHealth(min(character->getHealth() + HP, character->getMaxHealth()));
    //character->setMp(min(character->getMp() + MP, character->getMaxMp()));
    character->setHealth( std::min(character->getHealth() + int(character->getMaxHealth() * (HP / 100.0f)), character->getMaxHealth()));
    character->setMp( std::min(character->getMp() + int(character->getMaxMp() * (MP / 100.0f)), character->getMaxMp()));
    //백분율로 회복되게 변경
}

void BuffEffect::onEquip(Character* character)
{

    character->setAttack(character->getAttack() + atkbuff);
    character->setDefense(character->getDefense() + defbuff);
    character->setAttackSpeed(character->getAttackSpeed() + spdbuff);
    character->setMaxhealth(character->getMaxHealth() + hpbuff);
    character->setMaxMp(character->getMaxMp() + mpbuff);
}

void BuffEffect::onUnequip(Character* character)
{
    character->setAttack(character->getAttack() - atkbuff);
    character->setDefense(character->getDefense() - defbuff);
    character->setAttackSpeed(character->getAttackSpeed() - spdbuff);
    character->setMaxhealth(character->getMaxHealth() - hpbuff);
    character->setMaxMp(character->getMaxMp() - mpbuff);
}
//