// Dragon.cpp
#include "Dragon.h"
#include "Item.h" // .cpp 파일에서 include
#include <iostream>
#include "AsciiArt.h"
#include <thread> // sleep_for 
#include <chrono>

// --- 생성자 구현 ---
Dragon::Dragon(int level)
    : Monster(level), turnCount(0), fireBreathCooldown(0), isEnraged(false) // 턴과 쿨타임 초기화
{
    // 1. 보스에 걸맞은 기본 능력치 설정
    int baseHealth = 1;
    int baseAttack = 40;
    
    this->baseExp = 300; // 기본 경험치 추가
    this->baseGold = 500; // 기본 골드 추가

    // 2. 레벨 스케일링 적용 (보스는 일반 몬스터보다 성장률이 높음)
    this->health = baseHealth + (this->level * 20);
    this->attack = baseAttack + (this->level * 5);
    this->maxHealth = this->health;
    // 3. 이름 설정
    this->name = "Lv." + std::to_string(this->level) + " 드래곤";

    // 4. 보스 전용 특별 드롭 아이템 설정
    /*dropItem.push_back(Item("드래곤의 비늘", 1000, 1, E_Type::Material));
    dropItem.push_back(Item("드래곤의 뿔", 3000, 1, E_Type::Material));
    dropItem.push_back(Item("드래곤의 발톱", 2000, 1, E_Type::Material));
    dropItem.push_back(Item("드래곤의 눈알", 5000, 1, E_Type::Material));
    dropItem.push_back(Item("드래곤의 날개", 5000, 1, E_Type::Material));
    dropItem.push_back(Item("드래곤의 심장", 10000, 1, E_Type::Material));*/

    std::cout << this->name << " 등장!" << std::endl;
    system("pause");


    std::cout << "\n\n... 하늘이 어두워지며 거대한 그림자가 땅을 뒤덮습니다 ...\n\n";
    system("pause"); // 잠시 멈춤

    AsciiArt::setConsoleSize(160, 160);
    AsciiArt::printFromFile("dragon_appear_raw_hq.txt");
    AsciiArt::printFromFile("dragon_appear_raw.txt");

    std::cout << "\n\n" << this->name << "이(가) 모습을 드러냈다!\n";
    system("pause");

}

// --- 행동 AI 구현 ---
int Dragon::performAction()
{
    turnCount++; // 턴 증가

    if (!isEnraged && this->health <= this->maxHealth / 2)
    {


        // 2페이즈 진입
       
        std::cout << this->name << " - 2페이즈 돌입!" << std::endl;
        system("pause");

        AsciiArt::setConsoleSize(160, 160);
        AsciiArt::printFromFile("dragon_phase2_raw_hq.txt");
        AsciiArt::printFromFile("dragon_phase2_raw.txt");

        isEnraged = true; // 분노 상태로 변경
        std::cout << name << "가 포효하며 형태를 변화합니다! 주변의 공기가 뜨거워집니다!" << std::endl;
        system("pause");

        // 공격력을 영구적으로 50% 상승

    }

    // 화염 브레스 쿨타임이 0이면 특수 공격 사용
    // 2페이즈 시 공격 패턴 강화
    if (fireBreathCooldown == 0)
    {
        // 2페이즈일 때는 쿨타임을 2턴으로, 아닌 때는 3턴으로 설정
        if (isEnraged)
        {
            fireBreathCooldown = 2;
        }
        else
        {
            fireBreathCooldown = 3; // 쿨타임을 3턴으로 다시 설정
        }

        return fireBreathAttack();
    }
    // 쿨타임이 남아있으면 일반 공격 사용
    else {
        fireBreathCooldown--; // 쿨타임 1 감소
        return normalAttack();
    }
}

// --- 개별 행동 함수 구현 ---
int Dragon::normalAttack() {
    std::cout << this->name << "이(가) 거대한 발톱으로 공격합니다!" << std::endl;
    return this->attack; // 기본 공격력 반환
}

int Dragon::fireBreathAttack() {
    int finalDamage = static_cast<int>(this->attack * 1.8); // 기본 공격력의 1.8배
    std::cout << this->name << "이(가) 모든 것을 태워버릴 듯한 화염 브레스를 내뿜습니다! (강력한 공격!)" << std::endl;
    return finalDamage; // 강화된 공격력 반환
}