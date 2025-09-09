#pragma once
#include "Monster.h"
#include <string>

// 전방 선언
class Item;

class Slime : public Monster
{
private:
    std::string type;
    int turnCount;

    // 슬라임의 행동 패턴
    int normalAttack();
    int hardenDefense(); // 몸을 굳혀 방어하는 행동

public:
    // 생성자
    Slime(const std::string& type, int level);

    // 오버라이드
    int performAction() override;
};