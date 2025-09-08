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
    cout << "[" << name << "] �� �ൿ�� �����ϼ���.\n";
    cout << "1. �Ϲ� ����\n";
    cout << "2. ��ų ���� (���� 10 �Ҹ�)\n";
    int choice;
    cin >> choice;

    if (choice == 1) {
        cout << name << "��(��) �Ϲ� ������ �մϴ�! (" << attackPower << " ����)" << endl;
    }
    else if (choice == 2) {
        int skillCost = 10;
        if (mp >= skillCost) {
            mp -= skillCost;
            int skillDamage = attackPower * 2;
            cout << name << "��(��) ��ų ������ ����մϴ�! (" << skillDamage
                << " ����, MP -" << skillCost << ")" << endl;
        }
        else {
            cout << "MP�� �����Ͽ� ��ų�� ����� �� �����ϴ�! ��� �Ϲ� ������ �մϴ�." << endl;
            cout << name << "��(��) �Ϲ� ������ �մϴ�! (" << attackPower << " ����)" << endl;
        }
    }
    else {
        cout << "�߸��� �Է��Դϴ�. �Ϲ� ������ �����մϴ�." << endl;
        cout << name << "��(��) �Ϲ� ������ �մϴ�! (" << attackPower << " ����)" << endl;
    }
}

void Thief::attack(Monster* monster)
{
    if (!monster) {
        cout << "���� ����� �����ϴ�.\n";
        return;
    }
    int damage = max(1, attackPower - monster->getHealth());

    cout << monster->getName() << "���� " << damage << "�� �������� �������ϴ�" << endl;

    int monsterHP = monster->getHealth() - damage;
    if (monster->setHP(monsterHP)) {
        cout << "������ ü���� " << monster->getHealth() << " �� ���ҽ��ϴ�." << endl;
    }
    else {
        cout << "������ ü���� 0�� �Ǿ����ϴ�." << endl;
        cout << "�÷��̾ �¸� �Ͽ����ϴ�." << endl;
    }
}
