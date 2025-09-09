#include "Orc.h"
#include "Item.h" 
#include <iostream> 
#include <random>   

// --- ������ ���� ---
Orc::Orc(const std::string& type, int level)
    : Monster(level), type(type), bonusExp(0), bonusGold(0), turnCount(0), isCharging(false)
{
    int baseHealth = 0;
    int baseAttack = 0;
    int attackSpeed = 0;
    std::string namePrefix = "";

    if (type == "�Ϲ�") {
        namePrefix = "��ũ";
        baseHealth = 80;
        baseAttack = 15;
        attackSpeed = 2;
        this->baseExp = 25;
        this->baseGold = 10;
        dropItem.push_back(Item("�η��� ��ũ�� ��", 20, 1, E_Type::Material));
        dropItem.push_back(Item("��ũ�� ���� ����", 30, 1, E_Type::Material));
    }
    else if (type == "�߸�����") {
        namePrefix = "�߸����� ��ũ";
        baseHealth = 100;
        baseAttack = 20;
        attackSpeed = 2;
        this->baseExp = 40;
        this->baseGold = 20;
        dropItem.push_back(Item("��ũ�� ��ģ ����", 30, 1, E_Type::Material));
        dropItem.push_back(Item("��ũ�� ���� ����", 40, 1, E_Type::Material));
    }
    else if (type == "������") {
        namePrefix = "������ ��ũ";
        baseHealth = 150;
        baseAttack = 30;
        attackSpeed = 2;
        this->baseExp = 100;
        this->baseGold = 50;
        dropItem.push_back(Item("��ũ�� ��ī�ο� �۰���", 50, 1, E_Type::Material));
        dropItem.push_back(Item("��ũ�� ���� ��ġ", 70, 1, E_Type::Material));
    }

    this->health = baseHealth + (this->level * 10);
    this->attack = baseAttack + (this->level * 3);
    this->attackSpeed = attackSpeed + (this->level * 2);

    this->name = "Lv." + std::to_string(this->level) + " " + namePrefix;
}


// --- �ൿ AI ���� ---
int Orc::performAction()
{
    turnCount++;

    if (type == "�߸�����") {
        return performSavageAction();
    }
    else if (type == "������") {
        return performBerserkerAction();
    }
    else {
        return performNormalAction();
    }
}


// --- ���� �ൿ �Լ� ���� ---
int Orc::performNormalAction()
{
    std::cout << this->name << "�� ������ ������ �õ��մϴ�!" << std::endl;
    return this->attack;
}

int Orc::performSavageAction()
{
    if (rand() % 100 < 30)
    {
        int finalDamage = static_cast<int>(this->attack * 1.5);
        std::cout << this->name << "�� ���⿡ �۽ο� ���ں��� �ϰ��� �����ϴ�! (������ ����!)" << std::endl;
        return finalDamage;
    }
    else
    {
        return performNormalAction();
    }
}

int Orc::performBerserkerAction()
{
    if (!isCharging)
    {
        std::cout << this->name << "�� ������ �غ��մϴ�! ���� ������ �ſ� ���������ϴ�!" << std::endl;
        isCharging = true;
        return 0;
    }
    else
    {
        int finalDamage = this->attack * 2;
        std::cout << this->name << "�� �����ϸ� ����� �Ͱ����մϴ�! (�ſ� ������ ����!)" << std::endl;
        isCharging = false;
        return finalDamage;
    }
}