#include "Slime.h"
#include "Item.h"
#include <iostream>

Slime::Slime(const std::string& type, int level)
    : Monster(level), type(type), turnCount(0)
{
    int baseHealth = 0;
    int baseAttack = 0;
    std::string namePrefix = "";

    // '�Ϲ�' Ÿ���� ���� ���� ����
    if (type == "�Ϲ�")
    {
        namePrefix = "������";
        baseHealth = 25;
        baseAttack = 4;
        this->baseExp = 8;
        this->baseGold = 4;
        this->attackSpeed = 8;
        // [�� ���] ���
        dropItem.push_back(Item("������ ����", 10, 1, E_Type::Material));
    }
    else if (type == "�ܴ���")
    {
        namePrefix = "�ܴ��� ������";
        baseHealth = 40;
        baseAttack = 6;
        this->baseExp = 15;
        this->baseGold = 8;
        this->attackSpeed = 5; // �ܴ��ؼ� ����
        // [���� ���] ���
        dropItem.push_back(Item("�������� ��", 50, 1, E_Type::Material));
    }
    else if (type == "����")
    {
        namePrefix = "���� ������";
        baseHealth = 60;
        baseAttack = 10;
        this->baseExp = 50;
        this->baseGold = 50;
        this->attackSpeed = 12; // ����ؼ� ����
        // [�Ǽ��縮 ���]�� [��ȭ] ���
        dropItem.push_back(Item("��¦�̴� ����", 150, 1, E_Type::Material));
        dropItem.push_back(Item("��ȭ �ָӴ�", 200, 1, E_Type::Material));
    }

    this->health = baseHealth + (this->level * 4);
    this->attack = baseAttack + (this->level * 2);
    this->maxHealth = this->health;
    this->name = "Lv." + std::to_string(this->level) + " " + namePrefix;
}

// �������� �ൿ AI: 25% Ȯ���� ���, 75% Ȯ���� ����
int Slime::performAction()
{
    turnCount++;
    if (rand() % 4 == 0) // 4�� ���� �������� 0�� Ȯ�� (25%)
    {
        return hardenDefense();
    }
    else
    {
        return normalAttack();
    }
}

// ���� �ൿ �Լ�
int Slime::normalAttack()
{
    std::cout << this->name << "��(��) ���� ��ġ�⸦ �õ��մϴ�!" << std::endl;
    return this->attack;
}

int Slime::hardenDefense()
{
    std::cout << this->name << "��(��) ���� �ܴ��ϰ� �������ϴ�. (��� �ൿ)" << std::endl;
    return 0;
}