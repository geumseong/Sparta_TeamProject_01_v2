// Orc.cpp
#include "Orc.h"
#include <random>

int Orc::performAction() 
{
    if (type == "야만적인") { return performSavageAction(); }
    else if (type == "광전사") { return performBerserkerAction(); }
    else { return performNormalAction(); }
}

int Orc::performNormalAction() 
{
    std::cout << name << "가 묵직한 공격을 시도합니다! 공격력: " << attack << std::endl;
    return attack;
}

int Orc::performSavageAction() 
{
    // 30% 확률로 더 강력한 공격을 시도
    if (rand() % 100 < 30) 
    {
        std::cout << name << "가 광기에 휩싸여 무자비한 일격을 날립니다! 공격력: " << attack * 1.5 << std::endl;
        return attack * 1.5;
    }

    else 
    {
        return performNormalAction();
    }
}

int Orc::performBerserkerAction()
{
    if (!isCharging)
    {
        std::cout << name << "가 돌진을 준비합니다! 다음 공격이 매우 강력해집니다!" << std::endl;
        isCharging = true;
        return 0; // 준비 상태, 데미지 없음
    }

    else
    {
        std::cout << name << "가 돌진하며 당신을 맹공격합니다! 공격력: " << attack * 2 << std::endl;
        isCharging = false; // 돌진 후 상태 초기화
        return attack * 2;
    }
}