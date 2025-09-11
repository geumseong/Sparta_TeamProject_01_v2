// Dragon.h
#pragma once
#include "Monster.h"
#include <string>

class Item; // 전방 선언

class Dragon : public Monster
{
private:
    int turnCount; // 턴 수를 세기 위한 변수
    int fireBreathCooldown; // 화염 브레스 쿨타임을 관리하는 변수

    // 드래곤의 행동 패턴을 정의하는 private 함수
    int normalAttack();
    int fireBreathAttack();
    bool isEnraged; // 2페이즈 분노 상태 여부

public:
    // 생성자: 드래곤은 타입 없이 레벨만으로 생성
    Dragon(int level);

    // 오버라이드: 드래곤의 행동 AI를 결정
    int performAction() override;
};