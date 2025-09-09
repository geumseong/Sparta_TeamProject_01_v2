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
    jobName = "Thief";
    setName(name);
    health += 50;
    attackPower += 10;
    defense += 5;
}

void Thief::attack()
{
    cout << "[" << name << "] 의 행동을 선택하세요.\n";
    cout << "1. 일반 공격\n";
    cout << "2. 스킬 공격 (마나 10 소모)\n";
    int choice;
    cin >> choice;

    if (choice == 1) {
        cout << name << "이(가) 일반 공격을 합니다! (" << attackPower << " 피해)" << endl;
    }
    else if (choice == 2) {
        int skillCost = 10;
        if (mp >= skillCost) {
            mp -= skillCost;
            int skillDamage = attackPower * 2;
            cout << name << "이(가) 스킬 공격을 사용합니다! (" << skillDamage
                << " 피해, MP -" << skillCost << ")" << endl;
        }
        else {
            cout << "MP가 부족하여 스킬을 사용할 수 없습니다! 대신 일반 공격을 합니다." << endl;
            cout << name << "이(가) 일반 공격을 합니다! (" << attackPower << " 피해)" << endl;
        }
    }
    else {
        cout << "잘못된 입력입니다. 일반 공격을 실행합니다." << endl;
        cout << name << "이(가) 일반 공격을 합니다! (" << attackPower << " 피해)" << endl;
    }
}

void Thief::attack(Monster* monster)
{
    if (!monster) {
        cout << "공격 대상이 없습니다.\n";
        return;
    }
    int damage = max(1, attackPower - monster->getHealth());

    cout << monster->getName() << "에게 " << damage << "의 데미지를 입혔습니다" << endl;

    int monsterHP = monster->getHealth() - damage;
    if (monster->setHP(monsterHP)) {
        cout << "몬스터의 체력이 " << monster->getHealth() << " 가 남았습니다." << endl;
    }
    else {
        cout << "몬스터의 체력이 0이 되었습니다." << endl;
        cout << "플레이어가 승리 하였습니다." << endl;
    }
}
