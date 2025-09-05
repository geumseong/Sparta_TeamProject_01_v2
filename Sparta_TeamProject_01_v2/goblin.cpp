#include "Goblin.h"
#include "GameManager.h"
#include "Character.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "Item.h"


// 몬스터의 전체 행동을 결정하는 메인 함수
void Goblin::performAction() 
{
    turnCount++;

    if (type == "겁쟁이") { performCowardlyAction(); }
    else if (type == "재벌") { performRichAction(); }
    else if (type == "건방진") { performCheekyAction(); }
    else if (type == "사나운") { performFierceAction(); }
    else { performNormalAction(); }
}

// 일반 고블린의 행동
void Goblin::performNormalAction() 
{
    std::cout << name << "가 몽둥이를 휘두릅니다! 공격력: " << attack << std::endl;
}

// 겁쟁이 고블린의 행동
void Goblin::performCowardlyAction() 
{
    if (turnCount >= 2) {
        if (rand() % 100 < 20) {
            std::cout << name << "가 겁에 질려 도망치려 합니다! (도주 성공!)" << std::endl;
            this->health = 0;
            this->isFled = true;
        }
        else {
            std::cout << name << "가 도망치려다 실패하고 당신을 공격합니다! 공격력: " << attack << std::endl;
        }
    }
    else {
        std::cout << name << "가 겁에 질려 몸을 웅크립니다." << std::endl;
    }
}

// 건방진 고블린의 행동
void Goblin::performCheekyAction() {
    std::cout << name << "가 당신을 향해 손가락질하며 도발합니다! (메시지만 출력)" << std::endl;
}

// 사나운 고블린의 행동
void Goblin::performFierceAction()
{
    std::cout << name << "가 포효하며 무자비한 공격을 퍼붓습니다! 공격력: " << attack * 1.5 << "!" << std::endl;
}

// 재벌 고블린의 행동
void Goblin::performRichAction()
{
    if (turnCount == 3) 
    {
        std::cout << name << "가 당신을 비웃으며 도망쳤습니다! (도주 성공!)" << std::endl;
        this->health = 0;
        this->isFled = true;
    }

    else 
    {
        std::cout << name << "가 거만하게 재력을 과시합니다!" << std::endl;
    }
}
