#include "Ogre.h"
#include "Item.h"
#include <iostream>

Ogre::Ogre(const std::string& type, int level)
    : Monster(level), type(type)
{
    int baseHealth = 0;
    int baseAttack = 0;
    std::string namePrefix = "";

    if (type == "�Ϲ�") {
        namePrefix = "����";
        baseHealth = 200;
        baseAttack = 30;
        this->baseExp = 120;
        this->baseGold = 80;
        this->attackSpeed = 3;
        dropItem.push_back(Item("������ �����", 100, 1, E_Type::Material));
    }
    else if (type == "�� ���") {
        namePrefix = "�� ��� ����";
        baseHealth = 250;
        baseAttack = 25;
        this->baseExp = 180;
        this->baseGold = 110;
        this->attackSpeed = 2;
        dropItem.push_back(Item("������ �ֵ��� �����", 250, 1, E_Type::Accessory));
    }
    else if (type == "Ǯ�Ƹ�") {
        namePrefix = "Ǯ�Ƹ� ����";
        baseHealth = 300;
        baseAttack = 20;
        this->baseExp = 200;
        this->baseGold = 150;
        this->attackSpeed = 1;
        dropItem.push_back(Item("������ ��ö �ֱ�", 280, 1, E_Type::Material));
        dropItem.push_back(Item("������ ��ȭ ö��", 400, 1, E_Type::Material));
    }

    this->health = baseHealth + (this->level * 15);
    this->attack = baseAttack + (this->level * 4);
    this->maxHealth = this->health;
    this->name = "Lv." + std::to_string(this->level) + " " + namePrefix;
}

int Ogre::performAction()
{
    if (type == "�� ���" && rand() % 3 == 0) { // 33% Ȯ���� 2�� ����
        return doubleAttack();
    }
    return smashAttack();
}

int Ogre::smashAttack()
{
    std::cout << this->name << "��(��) ������ �����̸� �ֵθ��ϴ�!" << std::endl;
    return this->attack;
}

int Ogre::doubleAttack()
{
    int finalDamage = this->attack * 2;
    std::cout << this->name << "�� �Ӹ� �� ���� ���� �Ҹ�ġ�� ���ÿ� �����մϴ�! (2ȸ ����!)" << std::endl;
    return finalDamage;
}