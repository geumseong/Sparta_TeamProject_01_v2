#pragma once

#include <string>
#include <vector>
#include "Monster.h"
using namespace std;



class Monster;
class Character
{
public:
	Character();

    Character(string name);

    virtual void attack() = 0;
    virtual void attack(Monster* monster) = 0;
    virtual void levelUp() = 0;
    void displayStatus();
    void visitShop();
    void characterDeath();
    void takeCharacterDamage(int damage);
    //
    // getter 함수
    string getName() const;
    int getLevel() const;
    int getHealth() const;
    int getMaxHealth() const;
    int getMp() const;
    int getMaxMp() const;
    int getAttack() const;
    int getDefense() const;
    int getAttackSpeed() const;
    int getExperience() const;
    string getJobName() { return jobName; }


    // setter 함수
    void setName(string _name);
    bool setHealth(int _health);
    bool setMaxhealth(int _maxHealth);
    bool setMp(int _mp);
    bool setMaxMp(int _maxMp);
    void setAttack(int _attack);
    void setDefense(int _defense);
    void setAttackSpeed(int _attackSpeed);
    void setExperience(int _experience);


protected:
    string name;        // 캐릭터 이름
    string jobName;     // 캐릭터 직업 이름
    int level;          // 캐릭터 레벨 수치
    int health;         // 캐릭터 체력 수치
    int maxHealth;      // 캐릭터 최대 체력 수치
    int mp;             // 캐릭터 마나 수치
    int maxMp;          // 캐릭터 최대 마나 수치
    int attackPower;         // 캐릭터 공격 수치
    int defense;        // 방어력 고정 수치
    int attackSpeed;    // 공격속도 (속도에 따라서 공격턴이 결정된다)
    int experience;     // 캐릭터 경험치
    int gold;           // 캐릭터 골드 수치
};