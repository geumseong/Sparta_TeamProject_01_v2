// Goblin.h
// 몬스터의 종류 중 하나인 고블린을 정의하는 헤더 파일
// Goblin 클래스는 Monster 클래스를 상속받아 고블린 몬스터를 구현
// Goblin 클래스는 특수한 개체의 고블린의 특수한 행동과 속성을 추가로 정의


#pragma once
#include "Monster.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
// 상호 작용 : GameManager, Character, Item
#include "Item.h"
#include "Character.h"
#include "GameManager.h"
// 전방 선언
class GameManager;
class Character;
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
	void performNormalAction();
	void performCowardlyAction();
	void performCheekyAction();
	void performFierceAction();
	void performRichAction();


public:
	// 고블린 생성자
	// 고블린의 이름, 체력, 공격력을 초기값으로 설정
	Goblin(const std::string& type)
		: Monster("", 0, 0), type(type), bonusExp(0), bonusGold(0), turnCount(0), isFled(false)
	{
		if (type == "일반")
		{
			this->name = "고블린";
			this->health = 30;
			this->attack = 5;
			// this->commonWeight = 80; // 일반 아이템 드랍 확률
			// this->rareWeight = 15;   // 희귀 아이템 드랍 확률
			// this->legendaryWeight = 5; // 전설 아이템 드랍 확률

		}

		else if (type == "겁쟁이")
		{
			this->name = "겁쟁이 고블린";
			this->health = 20;
			this->attack = 3;
			this->bonusExp = 10;
			this->bonusGold = 10;
			// this->commonWeight = 70; // 일반 아이템 드랍 확률
			// this->rareWeight = 25;   // 희귀 아이템 드랍 확률
			// this->legendaryWeight = 5; // 전설 아이템 드랍 확률

		}

		else if (type == "건방진")
		{
			this->name = "건방진 고블린";
			this->health = 35;
			this->attack = 10;
			this->bonusExp = 15;
			this->bonusGold = 15;
			// this->commonWeight = 60; // 일반 아이템 드랍 확률
			// this->rareWeight = 30;   // 희귀 아이템 드랍 확률
			// this->legendaryWeight = 10; // 전설 아이템 드랍 확률

		}

		else if (type == "사나운")
		{
			this->name = "사나운 고블린";
			this->health = 40;
			this->attack = 15;
			this->bonusExp = 20;
			this->bonusGold = 20;
			// this->commonWeight = 50; // 일반 아이템 드랍 확률
			// this->rareWeight = 35;   // 희귀 아이템 드랍 확률
			// this->legendaryWeight = 15; // 전설 아이템 드랍 확률

		}

		else if (type == "재벌")
		{
			this->name = "재벌 고블린";
			this->health = 100;
			this->attack = 50;
			this->bonusExp = 50;
			this->bonusGold = 100;
			// this->commonWeight = 30; // 일반 아이템 드랍 확률
			// this->rareWeight = 50;   // 희귀 아이템 드랍 확률
			// this->legendaryWeight = 20; // 전설 아이템 드랍 확률

		}
	}

	// Goblin 클래스에서 performAction() 함수명을 performAction()으로 수정하여
	// Monster 클래스의 virtual void performAction()을 올바르게 오버라이드합니다.
	void performAction() override;

	bool hasFled() const { return isFled; }
	int getBonusExp() const { return bonusExp; }
	int getBonusGold() const { return bonusGold; }

};