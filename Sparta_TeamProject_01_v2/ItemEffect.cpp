#include "ItemEffect.h"
#include "Character.h"
#include "drawtest.h"

void HealEffect::onConsume(Character* character)
{
    //character->setHealth(min(character->getHealth() + HP, character->getMaxHealth()));
    //character->setMp(min(character->getMp() + MP, character->getMaxMp()));
    character->setHealth( min(character->getHealth() + int(character->getMaxHealth() * (HP / 100.0f)), character->getMaxHealth()));
    character->setMp( min(character->getMp() + int(character->getMaxMp() * (MP / 100.0f)), character->getMaxMp()));
    //백분율로 회복되게 변경
}

void BuffEffect::onEquip(Character* character)
{

    character->setAttack(character->getAttack() + atkbuff);
    character->setDefense(character->getDefense() + defbuff);
    character->setAttackSpeed(character->getAttackSpeed() + spdbuff);
    character->setMaxhealth(character->getMaxHealth() + hpbuff);
    character->setMaxMp(character->getMaxMp() + mpbuff);

    RenderBoxFromCout(box_log.x, box_log.y, box_log.width, box_log.height, [&]() //로그 출력
    {
            cout << u8"장비를 장착했습니다.\n";
    });
}

void BuffEffect::onUnequip(Character* character)
{
    character->setAttack(character->getAttack() - atkbuff);
    character->setDefense(character->getDefense() - defbuff);
    character->setAttackSpeed(character->getAttackSpeed() - spdbuff);
    character->setMaxhealth(character->getMaxHealth() - hpbuff);
    character->setMaxMp(character->getMaxMp() - mpbuff);

    RenderBoxFromCout(box_log.x, box_log.y, box_log.width, box_log.height, [&]() //로그 출력
        {
            cout << u8"장비를 해제했습니다.\n";
        });
}
//