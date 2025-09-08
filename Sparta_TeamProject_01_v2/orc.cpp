// Orc.cpp
// tt
#include "Orc.h"
#include <random>

void Orc::performAction() 
{
    if (type == "야만적인") { performSavageAction(); }
    else if (type == "광전사") { performBrutalCharge(); }
    else { performNormalAction(); }
}

void Orc::performNormalAction() 
{
    std::cout << name << "가 묵직한 공격을 시도합니다! 공격력: " << attack << std::endl;
}

void Orc::performSavageAction() 
{
    // 30% 확률로 더 강력한 공격을 시도
    if (rand() % 100 < 30) 
    {
        std::cout << name << "가 광기에 휩싸여 무자비한 일격을 날립니다! 공격력: " << attack * 1.5 << std::endl;
    }

    else 
    {
        performNormalAction();
    }
}

void Orc::performBrutalCharge() 
{
    // 체력이 낮아지면 강력한 돌진 공격을 사용
    if (health <= 50) 
    {
        std::cout << name << "가 돌진하며 당신을 맹공격합니다! 공격력: " << attack * 2 << std::endl;
    }

    else 
    {
        std::cout << name << "가 위협적인 포효를 내지릅니다." << std::endl;
    }
}
