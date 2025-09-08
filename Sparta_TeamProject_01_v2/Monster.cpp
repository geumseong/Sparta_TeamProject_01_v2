// Monster.cpp
// tt
#include "Monster.h"

// ���� Ŭ������ ������ ����
Monster::Monster(std::string name, int health, int attack)
    : name(name), health(health), attack(attack) {}

// ������ �̸� ��ȯ
std::string Monster::getName() const { return name; }

// ������ ü�� ��ȯ
int Monster::getHealth() const { return health; }

// ������ ���ݷ� ��ȯ
int Monster::getAttack() const { return attack; }

// ���Ͱ� ���ظ� �Ծ��� ��
void Monster::takeDamage(int damage) 
{
    health -= damage;
    if (health < 0) { health = 0; }
}

// ������ �ൿ (�⺻ ����)
// �ڽ� Ŭ�������� �������̵�� ���̴�.
void Monster::performAction() { std::cout << "���Ͱ� �ൿ�� �غ��մϴ�." << std::endl; }