#include "Kobold.h"
#include "Item.h"
#include <iostream>

Kobold::Kobold(const std::string& type, int level)
    : Monster(level), type(type), turnCount(0)
{
    int baseHealth = 0;
    int baseAttack = 0;
    std::string namePrefix = "";

    if (type == "�Ϲ�") {
        namePrefix = "�ں�Ʈ";
        baseHealth = 20;
        baseAttack = 6;
        this->baseExp = 7;
        this->baseGold = 5;
        this->attackSpeed = 15;
        dropItem.push_back(Item("���� ���� ����", 5, 1, E_Type::Material));
    }
    else if (type == "������") {
        namePrefix = "�ں�Ʈ ������";
        baseHealth = 25;
        baseAttack = 8;
        this->baseExp = 12;
        this->baseGold = 8;
        this->attackSpeed = 18;
        dropItem.push_back(Item("������ ���� ����", 25, 1, E_Type::Material));
    }

    this->health = baseHealth + (this->level * 3);
    this->attack = baseAttack + (this->level * 1);
    this->maxHealth = this->health;
    this->name = "Lv." + std::to_string(this->level) + " " + namePrefix;
}

int Kobold::performAction()
{
    turnCount++;
    if (type == "������" && rand() % 4 == 0) { // 25% Ȯ���� ��� ����
        return trapAttack();
    }
    return normalAttack();
}

int Kobold::normalAttack()
{
    std::cout << this->name << "��(��) ��ī�ο� �������� ��Ţ�ϴ�!" << std::endl;
    return this->attack;
}

int Kobold::trapAttack()
{
    int finalDamage = static_cast<int>(this->attack * 1.5);
    std::cout << this->name << "��(��) ���ܵ� ������ �Ͷ߸��ϴ�! (������ ����!)" << std::endl;
    return finalDamage;
}