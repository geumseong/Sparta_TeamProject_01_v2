// Dragon.cpp
#include "Dragon.h"
#include "Item.h" // .cpp ���Ͽ��� include
#include <iostream>

// --- ������ ���� ---
Dragon::Dragon(int level)
    : Monster(level), turnCount(0), fireBreathCooldown(0), isEnraged(false) // �ϰ� ��Ÿ�� �ʱ�ȭ
{
    // 1. ������ �ɸ��� �⺻ �ɷ�ġ ����
    int baseHealth = 500;
    int baseAttack = 40;
    
    this->baseExp = 300; // �⺻ ����ġ �߰�
    this->baseGold = 500; // �⺻ ��� �߰�

    // 2. ���� �����ϸ� ���� (������ �Ϲ� ���ͺ��� ������� ����)
    this->health = baseHealth + (this->level * 20);
    this->attack = baseAttack + (this->level * 5);
    this->maxHealth = this->health;
    // 3. �̸� ����
    this->name = "Lv." + std::to_string(this->level) + " �巡��";

    // 4. ���� ���� Ư�� ��� ������ ����
    dropItem.push_back(Item("�巡���� ���", 1000, 1, E_Type::Material));
    dropItem.push_back(Item("�巡���� ��", 3000, 1, E_Type::Material));
    dropItem.push_back(Item("�巡���� ����", 2000, 1, E_Type::Material));
    dropItem.push_back(Item("�巡���� ����", 5000, 1, E_Type::Material));
    dropItem.push_back(Item("�巡���� ����", 5000, 1, E_Type::Material));
    dropItem.push_back(Item("�巡���� ����", 10000, 1, E_Type::Material));
}

// --- �ൿ AI ���� ---
int Dragon::performAction()
{
    turnCount++; // �� ����

    if (!isEnraged && this->health <= this->maxHealth / 2)
    {
        // 2������ ����
        isEnraged = true; // �г� ���·� ����
        std::cout << name << "�� ��ȿ�ϸ� ���¸� ��ȭ�մϴ�! �ֺ��� ���Ⱑ �߰ſ����ϴ�!" << std::endl;

            // ���ݷ��� ���������� 50% ���
            this->attack = static_cast<int>(this->attack * 1.5);
    }

    // ȭ�� �극�� ��Ÿ���� 0�̸� Ư�� ���� ���
    // 2������ �� ���� ���� ��ȭ
    if (fireBreathCooldown == 0)
    {
        // 2�������� ���� ��Ÿ���� 2������, �ƴ� ���� 3������ ����
        if (isEnraged)
        {
            fireBreathCooldown = 2;
        }
        else
        {
            fireBreathCooldown = 3; // ��Ÿ���� 3������ �ٽ� ����
        }

        return fireBreathAttack();
    }
    // ��Ÿ���� ���������� �Ϲ� ���� ���
    else {
        fireBreathCooldown--; // ��Ÿ�� 1 ����
        return normalAttack();
    }
}

// --- ���� �ൿ �Լ� ���� ---
int Dragon::normalAttack() {
    std::cout << this->name << "��(��) �Ŵ��� �������� �����մϴ�!" << std::endl;
    return this->attack; // �⺻ ���ݷ� ��ȯ
}

int Dragon::fireBreathAttack() {
    int finalDamage = static_cast<int>(this->attack * 1.8); // �⺻ ���ݷ��� 1.8��
    std::cout << this->name << "��(��) ��� ���� �¿����� ���� ȭ�� �극���� ���ս��ϴ�! (������ ����!)" << std::endl;
    return finalDamage; // ��ȭ�� ���ݷ� ��ȯ
}