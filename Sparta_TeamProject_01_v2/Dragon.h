// Dragon.h
#pragma once
#include "Monster.h"
#include <string>

class Item; // ���� ����

class Dragon : public Monster
{
private:
    int turnCount; // �� ���� ���� ���� ����
    int fireBreathCooldown; // ȭ�� �극�� ��Ÿ���� �����ϴ� ����

    // �巡���� �ൿ ������ �����ϴ� private �Լ�
    int normalAttack();
    int fireBreathAttack();
    bool isEnraged; // 2������ �г� ���� ����

public:
    // ������: �巡���� Ÿ�� ���� ���������� ����
    Dragon(int level);

    // �������̵�: �巡���� �ൿ AI�� ����
    int performAction() override;
};