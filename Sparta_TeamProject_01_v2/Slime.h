#pragma once
#include "Monster.h"
#include <string>

// ���� ����
class Item;

class Slime : public Monster
{
private:
    std::string type;
    int turnCount;

    // �������� �ൿ ����
    int normalAttack();
    int hardenDefense(); // ���� ���� ����ϴ� �ൿ

public:
    // ������
    Slime(const std::string& type, int level);

    // �������̵�
    int performAction() override;
};