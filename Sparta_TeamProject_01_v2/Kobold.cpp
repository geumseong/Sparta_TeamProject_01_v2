#include "Kobold.h"
#include "Item.h"
#include <iostream>

Kobold::Kobold(const std::string& type, int level)
    : Monster(level), type(type), turnCount(0)
{
    int baseHealth = 0;
    int baseAttack = 0;
    std::string namePrefix = "";

    if (type == "일반") {
        namePrefix = "코볼트";
        baseHealth = 20;
        baseAttack = 6;
        this->baseExp = 7;
        this->baseGold = 5;
        this->attackSpeed = 15;
        dropItem.push_back(Item("작은 가죽 조각", 5, 1, E_Type::Material));
    }
    else if (type == "함정꾼") {
        namePrefix = "코볼트 함정꾼";
        baseHealth = 25;
        baseAttack = 8;
        this->baseExp = 12;
        this->baseGold = 8;
        this->attackSpeed = 18;
        dropItem.push_back(Item("조잡한 함정 도구", 25, 1, E_Type::Material));
    }

    this->health = baseHealth + (this->level * 3);
    this->attack = baseAttack + (this->level * 1);
    this->maxHealth = this->health;
    this->name = "Lv." + std::to_string(this->level) + " " + namePrefix;
}

int Kobold::performAction()
{
    turnCount++;
    if (type == "함정꾼" && rand() % 4 == 0) { // 25% 확률로 기습 공격
        return trapAttack();
    }
    return normalAttack();
}

int Kobold::normalAttack()
{
    std::cout << this->name << "이(가) 날카로운 발톱으로 할큅니다!" << std::endl;
    return this->attack;
}

int Kobold::trapAttack()
{
    int finalDamage = static_cast<int>(this->attack * 1.5);
    std::cout << this->name << "이(가) 숨겨둔 함정을 터뜨립니다! (강력한 공격!)" << std::endl;
    return finalDamage;
}