#include "Succubus.h"
#include "Item.h"
#include <iostream>
#include <algorithm> // std::min �Լ� ���

Succubus::Succubus(const std::string& type, int level)
    : Monster(level), type(type), isEnraged(false)
{
    int baseHealth = 250;
    int baseAttack = 25;
    std::string namePrefix = "��ť����";

    this->baseExp = 250;
    this->baseGold = 300;
    this->attackSpeed = 16;

    dropItem.push_back(Item("��Ȥ���� ���", 150, 1, E_Type::Accessory));
    dropItem.push_back(Item("���� ���� ����", 80, 1, E_Type::Material));
    dropItem.push_back(Item("Ÿ���� ��ȥ��", 500, 1, E_Type::Material));

    this->health = baseHealth + (this->level * 18);
    this->attack = baseAttack + (this->level * 4);
    this->maxHealth = this->health;
    this->name = "Lv." + std::to_string(this->level) + " " + namePrefix;
}

int Succubus::performAction()
{
    // 2������ ���� ���� Ȯ��
    if (!isEnraged && this->health <= this->maxHealth / 2) {
        isEnraged = true;
        std::cout << this->name << "�� ������ ���ϸ� �ֺ��� ����� ����� �����ϴ�! (2������ ����!)" << std::endl;
        this->attack = static_cast<int>(this->attack * 1.3); // ���ݷ� 30% ����
    }

    // 2�������� ��� 2ȸ ����
    if (isEnraged) {
        std::cout << this->name << "��(��) �������� �����մϴ�!" << std::endl;
        int totalDamage = lifeDrainAttack() + charmAttack();
        return totalDamage;
    }
    // 1�������� ��� ���� ����
    else {
        if (rand() % 2 == 0) {
            return lifeDrainAttack();
        }
        return charmAttack();
    }
}

int Succubus::charmAttack()
{
    std::cout << this->name << "��(��) ��Ȥ���� ä���� �ֵθ��ϴ�!" << std::endl;
    return this->attack;
}

int Succubus::lifeDrainAttack()
{
    int damage = static_cast<int>(this->attack * 0.8);
    int healAmount = static_cast<int>(damage * 0.5);

    this->health = std::min(this->maxHealth, this->health + healAmount);

    std::cout << this->name << "��(��) ������� ����մϴ�! (HP " << healAmount << " ȸ��)" << std::endl;
    return damage;
}