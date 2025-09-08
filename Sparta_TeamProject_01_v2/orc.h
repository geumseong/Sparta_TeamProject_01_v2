// Orc.h
#pragma once
#include "Monster.h"
#include <iostream>
#include <string>

class Orc : public Monster {
private:
    std::string type;
    int bonusExp;
    int bonusGold;

    // �� ������ ���� �ൿ�� �����ϴ� �Լ���
    void performNormalAction();
    void performSavageAction();
    void performBrutalCharge();

public:
    // ��ũ ������: Ÿ�Կ� ���� �Ӽ��� �޶�����
    Orc(const std::string& type)
        : Monster("", 0, 0), type(type), bonusExp(0), bonusGold(0) {

        if (type == "�Ϲ�") 
        {
            this->name = "��ũ";
            this->health = 80;
            this->attack = 15;
            this->bonusExp = 25;
            this->bonusGold = 10;
        }

        else if (type == "�߸�����") 
        {
            this->name = "�߸����� ��ũ";
            this->health = 100;
            this->attack = 20;
            this->bonusExp = 40;
            this->bonusGold = 20;
        }
        else if (type == "������") {
            this->name = "������ ��ũ";
            this->health = 150;
            this->attack = 30;
            this->bonusExp = 100;
            this->bonusGold = 50;
        }
    }

    // �������̵�
    void performAction() override;

    // ���� ���� �Լ�
    int getBonusExp() const { return bonusExp; }
    int getBonusGold() const { return bonusGold; }
};