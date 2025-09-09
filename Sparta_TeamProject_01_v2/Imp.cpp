#include "Imp.h"
#include "Item.h"
#include <iostream>

Imp::Imp(const std::string& type, int level)
    : Monster(level), type(type)
{
    int baseHealth = 0;
    int baseAttack = 0;
    std::string namePrefix = "";

    if (type == "일반") {
        namePrefix = "임프";
        baseHealth = 30;
        baseAttack = 12;
        this->baseExp = 20;
        this->baseGold = 10;
        this->attackSpeed = 22;
        dropItem.push_back(Item("임프의 작은 뿔", 30, 1, E_Type::Material));
    }
    else if (type == "파이어") {
        namePrefix = "파이어 임프";
        baseHealth = 40;
        baseAttack = 10; // 마법 공격이라 기본 공격력은 낮음
        this->baseExp = 30;
        this->baseGold = 15;
        this->attackSpeed = 20;
        dropItem.push_back(Item("불의 정수", 80, 1, E_Type::Material));
    }
    else if (type == "범생이") {
        namePrefix = "범생이 임프";
        baseHealth = 35;
        baseAttack = 8;
        this->baseExp = 40;
        this->baseGold = 30;
        this->attackSpeed = 25;
        dropItem.push_back(Item("임프의 낡은 안경", 180, 1, E_Type::Accessory));
        dropItem.push_back(Item("지혜의 페이지", 220, 1, E_Type::Material));
    }

    this->health = baseHealth + (this->level * 4);
    this->attack = baseAttack + (this->level * 2);
    this->maxHealth = this->health;
    this->name = "Lv." + std::to_string(this->level) + " " + namePrefix;
}

int Imp::performAction()
{
    if (type == "파이어") {
        return fireBoltAttack();
    }
    // "범생이" 타입도 기본 공격은 할퀴기로 설정
    return scratchAttack();
}

int Imp::scratchAttack()
{
    std::cout << this->name << "이(가) 장난스럽게 할퀴며 괴롭힙니다!" << std::endl;
    return this->attack;
}

int Imp::fireBoltAttack()
{
    int finalDamage = static_cast<int>(this->attack * 1.8);
    std::cout << this->name << "이(가) 작은 화염구를 던집니다! (마법 공격!)" << std::endl;
    return finalDamage;
}