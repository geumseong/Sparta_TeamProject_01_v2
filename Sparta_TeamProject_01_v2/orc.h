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

    // 각 유형별 고유 행동을 정의하는 함수들
    void performNormalAction();
    void performSavageAction();
    void performBrutalCharge();

public:
    // 오크 생성자: 타입에 따라 속성이 달라진다
    Orc(const std::string& type)
        : Monster("", 0, 0), type(type), bonusExp(0), bonusGold(0) {

        if (type == "일반") 
        {
            this->name = "오크";
            this->health = 80;
            this->attack = 15;
            this->bonusExp = 25;
            this->bonusGold = 10;
        }

        else if (type == "야만적인") 
        {
            this->name = "야만적인 오크";
            this->health = 100;
            this->attack = 20;
            this->bonusExp = 40;
            this->bonusGold = 20;
        }
        else if (type == "광전사") {
            this->name = "광전사 오크";
            this->health = 150;
            this->attack = 30;
            this->bonusExp = 100;
            this->bonusGold = 50;
        }
    }

    // 오버라이드
    void performAction() override;

    // 보상 관련 함수
    int getBonusExp() const { return bonusExp; }
    int getBonusGold() const { return bonusGold; }
};