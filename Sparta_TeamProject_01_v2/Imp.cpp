#include "Imp.h"
#include "Item.h"
#include <iostream>

Imp::Imp(const std::string& type, int level)
    : Monster(level), type(type)
{
    int baseHealth = 0;
    int baseAttack = 0;
    std::string namePrefix = "";

    if (type == "�Ϲ�") {
        namePrefix = "����";
        baseHealth = 30;
        baseAttack = 12;
        this->baseExp = 20;
        this->baseGold = 10;
        this->attackSpeed = 22;
        dropItem.push_back(Item("������ ���� ��", 30, 1, E_Type::Material));
    }
    else if (type == "���̾�") {
        namePrefix = "���̾� ����";
        baseHealth = 40;
        baseAttack = 10; // ���� �����̶� �⺻ ���ݷ��� ����
        this->baseExp = 30;
        this->baseGold = 15;
        this->attackSpeed = 20;
        dropItem.push_back(Item("���� ����", 80, 1, E_Type::Material));
    }
    else if (type == "������") {
        namePrefix = "������ ����";
        baseHealth = 35;
        baseAttack = 8;
        this->baseExp = 40;
        this->baseGold = 30;
        this->attackSpeed = 25;
        dropItem.push_back(Item("������ ���� �Ȱ�", 180, 1, E_Type::Accessory));
        dropItem.push_back(Item("������ ������", 220, 1, E_Type::Material));
    }

    this->health = baseHealth + (this->level * 4);
    this->attack = baseAttack + (this->level * 2);
    this->maxHealth = this->health;
    this->name = "Lv." + std::to_string(this->level) + " " + namePrefix;
}

int Imp::performAction()
{
    if (type == "���̾�") {
        return fireBoltAttack();
    }
    // "������" Ÿ�Ե� �⺻ ������ ������� ����
    return scratchAttack();
}

int Imp::scratchAttack()
{
    std::cout << this->name << "��(��) �峭������ ������ �������ϴ�!" << std::endl;
    return this->attack;
}

int Imp::fireBoltAttack()
{
    int finalDamage = static_cast<int>(this->attack * 1.8);
    std::cout << this->name << "��(��) ���� ȭ������ �����ϴ�! (���� ����!)" << std::endl;
    return finalDamage;
}