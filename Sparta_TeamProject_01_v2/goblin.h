// Goblin.h
// 몬스터의 종류 중 하나인 고블린을 정의하는 헤더 파일
// Goblin 클래스는 Monster 클래스를 상속받아 고블린 몬스터를 구현
// Goblin 클래스는 특수한 개체의 고블린의 특수한 행동과 속성을 추가로 정의


#pragma once
#include "Monster.h"
#include <string>


// 전방 선언
class Item;

// Goblin 클래스는 Monster 클래스를 상속받아 고블린 몬스터를 구현


class Goblin : public Monster
{
private:
	std::string type; // 고블린의 종류 (예: 일반 고블린, 고블린 전사 등)
	int bonusExp; // 특수 개체 처치 시 추가 경험치
	int bonusGold; // 특수 개체 처치 시 추가 골드
	int turnCount; // 턴 카운트 (특수 행동을 위한)
	bool isFled; // 도주 여부


	// 각 유형별 고유 행동을 정의하는 함수
	int performNormalAction();
	int performCowardlyAction();
	int performCheekyAction();
	int performFierceAction();
	int performRichAction();


public:
	// 고블린 생성자
	// 고블린의 이름, 체력, 공격력을 초기값으로 설정
	Goblin(const std::string& type, int level);




	// Goblin 클래스에서 performAction() 함수명을 performAction()으로 수정하여
	// Monster 클래스의 virtual void performAction()을 올바르게 오버라이드합니다.
	int performAction() override;

	bool hasFled() const { return isFled; }
	int getBonusExp() const { return bonusExp; }
	int getBonusGold() const { return bonusGold; }


	//this->health = baseHealth + (this->level * 5); // 레벨당 체력 5 증가
	//this->attack = baseAttack + (this->level * 2); // 레벨당 공격력 2 증가
	//this->maxHealth = this->health; // 최대 체력 설정

	//this->name = "Lv." + std::to_string(level) + " " + this->name; // 이름에 레벨 추가

};