#include "Orc.h"
#include "Item.h" 
#include <iostream> 
#include <random>   

// --- 생성자 구현 ---
Orc::Orc(const std::string& type, int level)
    : Monster(level), type(type), bonusExp(0), bonusGold(0), turnCount(0), isCharging(false)
{
    int baseHealth = 0;
    int baseAttack = 0;
    int attackSpeed = 0;
    std::string namePrefix = "";

    if (type == "일반") {
        namePrefix = "오크";
        baseHealth = 80;
        baseAttack = 15;
        attackSpeed = 2;
        this->baseExp = 25;
        this->baseGold = 10;
        dropItem.push_back(Item("부러진 오크의 뼈", 20, 1, E_Type::Material));
        dropItem.push_back(Item("오크의 투구 조각", 30, 1, E_Type::Material));
    }
    else if (type == "야만적인") {
        namePrefix = "야만적인 오크";
        baseHealth = 100;
        baseAttack = 20;
        attackSpeed = 2;
        this->baseExp = 40;
        this->baseGold = 20;
        dropItem.push_back(Item("오크의 거친 가죽", 30, 1, E_Type::Material));
        dropItem.push_back(Item("오크의 갑옷 조각", 40, 1, E_Type::Material));
    }
    else if (type == "광전사") {
        namePrefix = "광전사 오크";
        baseHealth = 150;
        baseAttack = 30;
        attackSpeed = 2;
        this->baseExp = 100;
        this->baseGold = 50;
        dropItem.push_back(Item("오크의 날카로운 송곳니", 50, 1, E_Type::Material));
        dropItem.push_back(Item("오크의 전투 망치", 70, 1, E_Type::Material));
    }

    this->health = baseHealth + (this->level * 10);
    this->attack = baseAttack + (this->level * 3);
    this->attackSpeed = attackSpeed + (this->level * 2);

    this->name = "Lv." + std::to_string(this->level) + " " + namePrefix;
}


// --- 행동 AI 구현 ---
int Orc::performAction()
{
    turnCount++;

    if (type == "야만적인") {
        return performSavageAction();
    }
    else if (type == "광전사") {
        return performBerserkerAction();
    }
    else {
        return performNormalAction();
    }
}


// --- 개별 행동 함수 구현 ---
int Orc::performNormalAction()
{
    std::cout << this->name << "가 묵직한 공격을 시도합니다!" << std::endl;
    return this->attack;
}

int Orc::performSavageAction()
{
    if (rand() % 100 < 30)
    {
        int finalDamage = static_cast<int>(this->attack * 1.5);
        std::cout << this->name << "가 광기에 휩싸여 무자비한 일격을 날립니다! (강력한 공격!)" << std::endl;
        return finalDamage;
    }
    else
    {
        return performNormalAction();
    }
}

int Orc::performBerserkerAction()
{
    if (!isCharging)
    {
        std::cout << this->name << "가 돌진을 준비합니다! 다음 공격이 매우 강력해집니다!" << std::endl;
        isCharging = true;
        return 0;
    }
    else
    {
        int finalDamage = this->attack * 2;
        std::cout << this->name << "가 돌진하며 당신을 맹공격합니다! (매우 강력한 공격!)" << std::endl;
        isCharging = false;
        return finalDamage;
    }
}