#include "Goblin.h"
#include "AsciiArt.h"
#include "Item.h"
#include <iostream>

Goblin::Goblin(const std::string& type, int level)
    : Monster(level), type(type), bonusExp(0), bonusGold(0), turnCount(0), isFled(false)
{

	{
		int baseHealth = 0; // 기본 체력
		int baseAttack = 0; // 기본 공격력
		int attackSpeed = 0; // 기본 공격속도
		std::string namePrefix = ""; // 이름


		if (type == u8"일반")
		{
			AsciiArt::printFromFile("goblin_art.txt");
			namePrefix = u8"고블린";
			baseHealth = 30;
			baseAttack = 5;
			attackSpeed = 0;
			
			this->baseExp = 10;   // 기본 경험치 추가
			this->baseGold = 5;    // 기본 골드 추가
			// this->commonWeight = 80; // 일반 아이템 드랍 확률
			// this->rareWeight = 15;   // 희귀 아이템 드랍 확률
			// this->legendaryWeight = 5; // 전설 아이템 드랍 확률
			dropItem.push_back(move(Item(u8"고블린의 부러진 뼈", 20, 1, E_Type::Material)));
			dropItem.push_back(move(Item(u8"깨진 투구 조각", 30, 1, E_Type::Material)));
		}

		else if (type == u8"겁쟁이")
		{
			AsciiArt::setConsoleSize(160, 160);
			AsciiArt::printFromFile("goblin_art.txt");
			namePrefix = u8"겁쟁이 고블린";
			baseHealth = 20;
			baseAttack = 3;
			attackSpeed = 0;
			bonusExp = 10;
			bonusGold = 10;
			this->baseExp = 10;   // 기본 경험치 추가
			this->baseGold = 10;    // 기본 골드 추가
			// this->commonWeight = 70; // 일반 아이템 드랍 확률
			// this->rareWeight = 25;   // 희귀 아이템 드랍 확률
			// this->legendaryWeight = 5; // 전설 아이템 드랍 확률
			dropItem.push_back(move(Item(u8"고블린의 얇은 가죽", 20, 1, E_Type::Material)));
			dropItem.push_back(move(Item(u8"가죽 조각", 25, 1, E_Type::Material)));
		}

		else if (type == u8"건방진")
		{
			AsciiArt::setConsoleSize(160, 160);
			AsciiArt::printFromFile("goblin_art.txt");
			namePrefix = u8"건방진 고블린";
			baseHealth = 35;
			baseAttack = 10;
			attackSpeed = 0;
			bonusExp = 15;
			bonusGold = 15;
			this->baseExp = 15;   // 기본 경험치 추가
			this->baseGold = 15;    // 기본 골드 추가
			// this->commonWeight = 60; // 일반 아이템 드랍 확률
			// this->rareWeight = 30;   // 희귀 아이템 드랍 확률
			// this->legendaryWeight = 10; // 전설 아이템 드랍 확률
			dropItem.push_back(move(Item(u8"고블린의 긴 손톱", 30, 1, E_Type::Material)));
			dropItem.push_back(move(Item(u8"녹슨 단검", 40, 1, E_Type::Material)));
		}

		else if (type == u8"사나운")
		{
			AsciiArt::setConsoleSize(160, 160);
			AsciiArt::printFromFile("goblin_art.txt");
			namePrefix = u8"사나운 고블린";
			baseHealth = 40;
			baseAttack = 15;
			attackSpeed = 0;
			bonusExp = 20;
			bonusGold = 20;
			this->baseExp = 20;   // 기본 경험치 추가
			this->baseGold = 20;    // 기본 골드 추가
			// this->commonWeight = 50; // 일반 아이템 드랍 확률
			// this->rareWeight = 35;   // 희귀 아이템 드랍 확률
			// this->legendaryWeight = 15; // 전설 아이템 드랍 확률
			dropItem.push_back(move(Item(u8"고블린의 날카로운 이빨", 50, 1, E_Type::Material)));
			dropItem.push_back(move(Item(u8"녹슨 대검", 60, 1, E_Type::Material)));
		}

		else if (type == u8"재벌")
		{
			AsciiArt::setConsoleSize(160, 160);
			AsciiArt::printFromFile("goblin_art.txt");
			namePrefix = u8"재벌 고블린";
			baseHealth = 100;
			baseAttack = 50;
			attackSpeed = 0;
			bonusExp = 50;
			bonusGold = 100;
			this->baseExp = 50;   // 기본 경험치 추가
			this->baseGold = 100;    // 기본 골드 추가
			// this->commonWeight = 30; // 일반 아이템 드랍 확률
			// this->rareWeight = 50;   // 희귀 아이템 드랍 확률
			// this->legendaryWeight = 20; // 전설 아이템 드랍 확률
			dropItem.push_back(move(Item(u8"고블린의 황금 조각", 100, 1, E_Type::Material)));
			dropItem.push_back(move(Item(u8"금화 주머니", 200, 1, E_Type::Material)));
		}
		//
		this->health = baseHealth + (this->level * 5); // 레벨당 체력 5 증가
		this->attack = baseAttack + (this->level * 2); // 레벨당 공격력 2 증가
		this->attackSpeed = attackSpeed + (this->level * 2); // 레벨당 공격속도 2) 증가

		this->name = "Lv." + std::to_string(level) + " " + namePrefix;

	}
}


// 몬스터의 전체 행동을 결정하는 메인 함수
int Goblin::performAction() 
{
    turnCount++;

    if (type == u8"겁쟁이") { return performCowardlyAction(); }
    else if (type == u8"재벌") { return performRichAction(); }
    else if (type == u8"건방진") { return performCheekyAction(); }
    else if (type == u8"사나운") { return performFierceAction(); }
    else { return performNormalAction(); }
}

// 일반 고블린의 행동
int Goblin::performNormalAction() 
{
    std::cout << this->name << u8"가 몽둥이를 휘두릅니다!" << attack << std::endl;
	return this->attack; // 공격력 반환

}

// 겁쟁이 고블린의 행동
int Goblin::performCowardlyAction() 
{
    if (turnCount >= 2) {
        if (rand() % 100 < 20) {
            std::cout << name << u8"가 겁에 질려 도망치려 합니다! (도주 성공!)" << std::endl;
            this->health = 0;
            this->isFled = true;
			return 0; // 도주 성공, 데미지 없음
        }
        else {
            std::cout << name << u8"가 도망치려다 실패하고 당신을 공격합니다! 공격력: " << attack << std::endl;
			return attack; // 공격력 반환
		}
    }
    else {
        std::cout << name << u8"가 겁에 질려 몸을 웅크립니다." << std::endl;
		return 0; // 웅크림, 데미지 없음
    
	}
}

// 건방진 고블린의 행동
int Goblin::performCheekyAction() {
    std::cout << name << u8"가 당신을 향해 손가락질하며 도발합니다! (메시지만 출력)" << std::endl;
	return 0; // 도발, 데미지 없음
}

// 사나운 고블린의 행동
int Goblin::performFierceAction()
{
	int finalDamage = static_cast<int>(this->attack * 1.5);
    std::cout << name << u8"가 포효하며 무자비한 공격을 퍼붓습니다! 공격력: " << finalDamage << "!" << std::endl;
	return finalDamage; // 강화된 공격력 반환

}

// 재벌 고블린의 행동
int Goblin::performRichAction()
{
    if (turnCount == 3) 
    {
        std::cout << this->name << u8"가 당신을 비웃으며 도망쳤습니다! (도주 성공!)" << std::endl;
        this->health = 0;
        this->isFled = true;
		return 0; // 도주 성공, 데미지 없음
    }

    else 
    {
        std::cout << this->name << u8"가 거만하게 재력을 과시합니다!" << std::endl;
		return 0; // 재력 과시, 데미지 없음
	}
}
