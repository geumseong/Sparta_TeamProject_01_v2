#include "Archer.h"
#include "iostream"

Archer::Archer()
{
	jobName = "Archer";
	health += 50;
	maxHealth += 50;
	attackPower += 10;
}

Archer::Archer(string nickName)
{
    this->jobName = "Archer";
    setName(nickName);
    this->level = 1;
    this->health = 200;
    this->maxHealth = 200;
    this->mp = 100;
    this->maxMp = 100;
    this->attackPower = 37;
    this->experience = 0;
    this->defense = 0;
    this->attackSpeed = 3;
}

void Archer::attack()
{
    
}

void Archer::attack(Monster* monster)
{
    if (!monster) {
        cout << "���� ����� �����ϴ�.\n";
        return;
    }

    cout << "[" << name << "] �� �ൿ�� �����ϼ���.\n";
    cout << "1. �Ϲ� ����\n";
    cout << "2. ���� (���� 10 �Ҹ�)\n";
    cout << "3. ���� (���� 20 �Ҹ�)\n";
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
            finalDamage = attackPower * 2;
            cout << name << "��(��) ������ ����մϴ�! (" << finalDamage
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
            finalDamage = (attackPower * 2) + attackSpeed;
            cout << name << "��(��) ������ ����մϴ�! (" << finalDamage
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

    int monsterHP = monster->getHealth() - damage;
    if (!monster->isDead()) {
        monster->takeDamage(damage);
        cout << "������ ü���� " << monster->getHealth() << " �� ���ҽ��ϴ�." << endl;
    }
    else {
        cout << "������ ü���� 0�� �Ǿ����ϴ�." << endl;
        cout << "�÷��̾ �¸� �Ͽ����ϴ�." << endl;
    }
}

void Archer::levelUp()
{
    if (level < 11)
    {
        level++;
        health = (maxHealth + 70);
        maxHealth = (maxHealth + 70);
        mp = (maxMp + 50);
        maxMp = (maxMp + 50);
        attackPower = (attackPower + 5);
        experience = 0;
        defense = (defense + 5);
        attackSpeed = (attackSpeed + 5);
    }
    else
    {
        cout << "�� �̻� �������� �� �� �����ϴ�." << endl;
    }

}
