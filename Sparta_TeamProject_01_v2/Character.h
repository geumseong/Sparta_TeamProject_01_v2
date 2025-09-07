#pragma once

#include <string>
#include <vector>
using namespace std;

class Character
{
public:
	Character();

    void displayStatus();
    void levelUp();
    void useItem(int index);
    void visitShop();
    void characterDeath();
    void characterAttack();

    // getter 함수
    string getName() const;
    int getLevel() const;
    int getHealth() const;
    int getMaxhealth() const;
    int getAttack() const;
    int getExperience() const;
    int getGold() const;


    // setter 함수
    void setName(string _name);
    bool setHealth(int _health);
    bool setMaxhealth(int _maxHealth);
    void setAttack(int _attack);
    void setExperience(int _experience);
    void setGold(int _gold);

private:
    string name;
    int level;
    int health;
    int maxHealth;
    int attack;
    int experience;
    int gold;
};