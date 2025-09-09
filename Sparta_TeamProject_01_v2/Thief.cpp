#include "Thief.h"
#include <iostream>

Thief::Thief()
{
	jobName = "Thief";
	health += 50;
	maxHealth += 50;
	attackPower += 10;

}

Thief::Thief(string nickName)
{
    this->jobName = "Thief";
    setName(nickName);
    this->level = 1;
    this->health = 200;
    this->maxHealth = 200;
    this->mp = 100;
    this->maxMp = 100;
    this->attackPower = 36;
    this->defense = 6;
    this->attackSpeed = 2;
}

void Thief::attack()
{
    
}

void Thief::attack(Monster* monster)
{
    if (!monster) {
        cout << "공격 대상이 없습니다.\n";
        return;
    }

    cout << "[" << name << "] 의 행동을 선택하세요.\n";
    cout << "1. 일반 공격\n";
    cout << "2. 더블어택 (마나 10 소모)\n";
    cout << "3. 백어택 (마나 20 소모)\n";
    int choice;
    int finalDamage;
    cin >> choice;

    if (choice == 1) {
        finalDamage = attackPower;
        cout << name << "이(가) 일반 공격을 합니다! (" << finalDamage << " 피해)" << endl;
    }
    else if (choice == 2) {
        int skillCost = 10;
        if (mp >= skillCost) {
            mp -= skillCost;
            int skillDamage = attackPower * 2;
            cout << name << "이(가) 더블어택을 사용합니다! (" << finalDamage
                << " 피해, MP -" << skillCost << ")" << endl;
        }
        else {
            finalDamage = attackPower;
            cout << "MP가 부족하여 스킬을 사용할 수 없습니다! 대신 일반 공격을 합니다." << endl;
            cout << name << "이(가) 일반 공격을 합니다! (" << finalDamage << " 피해)" << endl;
        }
    }
    else if (choice == 3) {
        int skillCost = 20;
        if (mp >= skillCost) {
            mp -= skillCost;
            int skillDamage = (attackPower * 2) + defense;
            cout << name << "이(가) 백어택을 사용합니다! (" << skillDamage
                << " 피해, MP -" << skillCost << ")" << endl;
        }
        else {
            finalDamage = attackPower;
            cout << "MP가 부족하여 스킬을 사용할 수 없습니다! 대신 일반 공격을 합니다." << endl;
            cout << name << "이(가) 일반 공격을 합니다! (" << finalDamage << " 피해)" << endl;
        }
    }
    else {
        finalDamage = attackPower;
        cout << "잘못된 입력입니다. 일반 공격을 실행합니다." << endl;
        cout << name << "이(가) 일반 공격을 합니다! (" << finalDamage << " 피해)" << endl;
    }

    int damage = finalDamage;
    cout << monster->getName() << "에게 " << damage << "의 데미지를 입혔습니다" << endl;

    if (!monster->isDead()) {
        monster->takeDamage(damage);
        cout << "몬스터의 체력이 " << monster->getHealth() << " 가 남았습니다." << endl;
    }
    else {
        cout << "몬스터의 체력이 0이 되었습니다." << endl;
        cout << "플레이어가 승리 하였습니다." << endl;
    }
}

void Thief::levelUp()
{
    if (level < 11)
    {
        level++;
        health = (maxHealth + 70);
        maxHealth = (maxHealth + 70);
        mp = (maxMp + 50);
        maxMp = (maxMp + 50);
        attackPower = (attackPower + 6);
        experience = 0;
        defense = (defense + 6);
        attackSpeed = (attackSpeed + 6);
    }
    else
    {
        cout << "더 이상 레벨업을 할 수 없습니다." << endl;
    }

}
