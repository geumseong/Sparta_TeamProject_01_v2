#include "Magician.h"
#include <iostream>

Magician::Magician()
{
	jobName = "Magician";
	health += 50;
	maxHealth += 50;
	attackPower += 10;
}

Magician::Magician(string nickName)
{
    this->jobName = "Magician";
    setName(nickName);
    this->level = 1;
    this->health = 200;
    this->maxHealth = 200;
    this->mp = 120;
    this->maxMp = 120;
    this->attackPower = 38;
    this->defense = 6;
    this->attackSpeed = 1;
}

void Magician::attack()
{
    
}

void Magician::attack(Monster* monster)
{
    if (!monster) {
        cout << "���� ����� �����ϴ�.\n";
        return;
    }

    cout << "[" << name << "] �� �ൿ�� �����ϼ���.\n";
    cout << "1. �Ϲ� ����\n";
    cout << "2. �������� (���� 10 �Ҹ�)\n";
    cout << "3. ���̾ (���� 30 �Ҹ�)\n";
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
            int finalDamage = attackPower * 2;
            cout << name << "��(��) ���������� ����մϴ�! (" << finalDamage
                << " ����, MP -" << skillCost << ")" << endl;
        }
        else {
            finalDamage = attackPower;
            cout << "MP�� �����Ͽ� ��ų�� ����� �� �����ϴ�! ��� �Ϲ� ������ �մϴ�." << endl;
            cout << name << "��(��) �Ϲ� ������ �մϴ�! (" << finalDamage << " ����)" << endl;
        }
    }
    else if (choice == 3) {
        int skillCost = 30;
        if (mp >= skillCost) {
            mp -= skillCost;
            int finalDamage = (attackPower * 2) + (attackPower / 2);
            cout << name << "��(��) ���̾�� ����մϴ�! (" << finalDamage
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

void Magician::levelUp()
{
    if (level < 11)
    {
        level++;
        health = (maxHealth + 70);
        maxHealth = (maxHealth + 70);
        mp = (maxMp + 70);
        maxMp = (maxMp + 70);
        attackPower = (attackPower + 8);
        experience = 0;
        defense = (defense + 5);
        attackSpeed = (attackSpeed + 5);
    }
    else
    {
        cout << "�� �̻� �������� �� �� �����ϴ�." << endl;
    }

}
