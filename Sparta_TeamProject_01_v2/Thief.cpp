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
        cout << "���� ����� �����ϴ�.\n";
        return;
    }

    cout << "[" << name << "] �� �ൿ�� �����ϼ���.\n";
    cout << "1. �Ϲ� ����\n";
    cout << "2. ������� (���� 10 �Ҹ�)\n";
    cout << "3. ����� (���� 20 �Ҹ�)\n";
    int choice;
    int finalDamage;
    cin >> choice;

    if (choice == 1) {
        finalDamage = attackPower;
        cout << name << "��(��) �Ϲ� ������ �մϴ�! (" << finalDamage << " ����)" << endl;
    }
    else if (choice == 2) {
        int skillCost = 10;
        if (mp >= skillCost) {
            mp -= skillCost;
            int skillDamage = attackPower * 2;
            cout << name << "��(��) ��������� ����մϴ�! (" << finalDamage
                << " ����, MP -" << skillCost << ")" << endl;
        }
        else {
            finalDamage = attackPower;
            cout << "MP�� �����Ͽ� ��ų�� ����� �� �����ϴ�! ��� �Ϲ� ������ �մϴ�." << endl;
            cout << name << "��(��) �Ϲ� ������ �մϴ�! (" << finalDamage << " ����)" << endl;
        }
    }
    else if (choice == 3) {
        int skillCost = 20;
        if (mp >= skillCost) {
            mp -= skillCost;
            int skillDamage = (attackPower * 2) + defense;
            cout << name << "��(��) ������� ����մϴ�! (" << skillDamage
                << " ����, MP -" << skillCost << ")" << endl;
        }
        else {
            finalDamage = attackPower;
            cout << "MP�� �����Ͽ� ��ų�� ����� �� �����ϴ�! ��� �Ϲ� ������ �մϴ�." << endl;
            cout << name << "��(��) �Ϲ� ������ �մϴ�! (" << finalDamage << " ����)" << endl;
        }
    }
    else {
        finalDamage = attackPower;
        cout << "�߸��� �Է��Դϴ�. �Ϲ� ������ �����մϴ�." << endl;
        cout << name << "��(��) �Ϲ� ������ �մϴ�! (" << finalDamage << " ����)" << endl;
    }

    int damage = finalDamage;
    cout << monster->getName() << "���� " << damage << "�� �������� �������ϴ�" << endl;

    if (!monster->isDead()) {
        monster->takeDamage(damage);
        cout << "������ ü���� " << monster->getHealth() << " �� ���ҽ��ϴ�." << endl;
    }
    else {
        cout << "������ ü���� 0�� �Ǿ����ϴ�." << endl;
        cout << "�÷��̾ �¸� �Ͽ����ϴ�." << endl;
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
        cout << "�� �̻� �������� �� �� �����ϴ�." << endl;
    }

}
