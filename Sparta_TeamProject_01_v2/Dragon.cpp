// Dragon.cpp
#include "Dragon.h"
#include "Item.h" // .cpp ���Ͽ��� include
#include <iostream>

// --- ������ ���� ---
Dragon::Dragon(int level)
    : Monster(level), turnCount(0), fireBreathCooldown(0) // �ϰ� ��Ÿ�� �ʱ�ȭ
{
    // 1. ������ �ɸ��� �⺻ �ɷ�ġ ����
    int baseHealth = 500;
    int baseAttack = 40;

    // 2. ���� �����ϸ� ���� (������ �Ϲ� ���ͺ��� ������� ����)
    this->health = baseHealth + (this->level * 20);
    this->attack = baseAttack + (this->level * 5);

    // 3. �̸� ����
    this->name = "Lv." + std::to_string(this->level) + " �巡��";

    // 4. ���� ���� Ư�� ��� ������ ����
    dropItem.push_back(Item("�巡���� ���", "���", 1000));
    dropItem.push_back(Item("�巡���� ����", "���", 5000));
}

// --- �ൿ AI ���� ---
int Dragon::performAction()
{
    turnCount++; // �� ����

    // ȭ�� �극�� ��Ÿ���� 0�̸� Ư�� ���� ���
    if (fireBreathCooldown == 0) {
        fireBreathCooldown = 3; // ��Ÿ���� 3������ �ٽ� ����
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