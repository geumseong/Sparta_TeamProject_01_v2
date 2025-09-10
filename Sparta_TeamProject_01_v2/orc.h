#pragma once
#include "Monster.h"
#include <string>

// 전방 선언
class Item;

class Orc : public Monster
{
private:
    std::string type;
    int bonusExp;
    int bonusGold;
    int turnCount;
    bool isCharging; // 돌진 상태 여부

    // 각 유형별 고유 행동을 정의하는 함수들
    int performNormalAction();
    int performSavageAction();
    int performBerserkerAction();
    //
public:
    // 오크 생성자: 타입에 따라 속성이 달라진다
    Orc(const std::string& type, int level);

    // 오버라이드
    int performAction() override;

    // 돌진 상태 확인 함수
    bool isOrcCharging() const { return isCharging; }

    // 보상 관련 함수
    int getBonusExp() const { return bonusExp; }
    int getBonusGold() const { return bonusGold; }
};