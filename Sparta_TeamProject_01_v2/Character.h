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
    void displayStatus();
    void levelUp();
    void visitShop();
    void characterDeath();

    // getter �Լ�
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


    // setter �Լ�
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
    string name;        // ĳ���� �̸�
    string jobName;     // ĳ���� ���� �̸�
    int level;          // ĳ���� ���� ��ġ
    int health;         // ĳ���� ü�� ��ġ
    int maxHealth;      // ĳ���� �ִ� ü�� ��ġ
    int mp;             // ĳ���� ���� ��ġ
    int maxMp;          // ĳ���� �ִ� ���� ��ġ
    int attackPower;         // ĳ���� ���� ��ġ
    int defense;        // ���� ���� ��ġ
    int attackSpeed;    // ���ݼӵ� (�ӵ��� ���� �������� �����ȴ�)
    int experience;     // ĳ���� ����ġ
    int gold;           // ĳ���� ��� ��ġ
};