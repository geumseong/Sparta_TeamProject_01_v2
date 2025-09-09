#pragma once
#include "Monster.h"
#include <string>

// ���� ����
class Item;

class Orc : public Monster
{
private:
    std::string type;
    int bonusExp;
    int bonusGold;
    int turnCount;
    bool isCharging; // ���� ���� ����

    // �� ������ ���� �ൿ�� �����ϴ� �Լ���
    int performNormalAction();
    int performSavageAction();
    int performBerserkerAction();

public:
    // ��ũ ������: Ÿ�Կ� ���� �Ӽ��� �޶�����
    Orc(const std::string& type, int level);

    // �������̵�
    int performAction() override;

    // ���� ���� Ȯ�� �Լ�
    bool isOrcCharging() const { return isCharging; }

    // ���� ���� �Լ�
    int getBonusExp() const { return bonusExp; }
    int getBonusGold() const { return bonusGold; }
};