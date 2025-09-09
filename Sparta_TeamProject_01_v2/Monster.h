#pragma once

// 상호 작용 : GameManager, Character, Item
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "Item.h"

// 전방 선언
class GameManager;
class Character;



class Monster // 모든 몬스터의 공통적인 속성과 기능을 정의하는 부모 클래스
{ 

protected:
	// 멤버 변수 (속성)
	// 몬스터의 상태(데이터)
	// protected로 설정하여 자식 클래스에서 접근 가능하도록 함
	std::string name; // 몬스터 이름
	int level; // 몬스터 레벨
	int health; // 몬스터 체력
	int attack; // 몬스터 공격력
	int attackSpeed; // 몬스터 공격속도
	int baseExp; // 기본 보상 경험치
	int baseGold; // 기본 보상 골드
	std::vector<Item> dropItem; // 몬스터가 드롭하는 아이템 목록


public:
	// 몬스터 생성자
	// 몬스터 객체를 생성할 때 가장 먼저 호출됨
	// 이름, 체력, 공격력을 초기값으로 설정
	Monster(int level); // 레벨만 받아서 초기화
	
	virtual ~Monster() {} // 가상 소멸자


	// 멤버 함수


	// getter 함수
	// 몬스터의 속성값을 리턴
	std::string getName() const { return name; }
	int getLevel() const { return level; }
	int getHealth() const { return health; }
	int getAttack() const { return attack; }
	int getAttackSpeed() const { return attackSpeed; }
	

	// setter 함수?
	// 몬스터의 속성값을 변경
	// 몬스터에게 피해를 입히는 함수 
	// 몬스터에게 직접적으로 속성값을 변경하는 것은 위험할 수 있으므로
	// setter 함수는 제공하지 않음?
	void takeDamage(int damage) 
	{ 
		health -= damage;
		
		if (health < 0)
		{
			health = 0;
		}
	} // 피해
	

	// 몬스터의 행동을 정의 하는 함수
	
	// 몬스터의 사망 여부를 확인하는 함수
	bool isDead() const { return health <= 0; } // 사망
	
	// 몬스터가 죽었을 때 아이템을 드롭하는 함수
	//void dropItem() { /* 아이템 드랍 로직 */ return nullptr; } // 아이템 드랍

	// 몬스터의 일반 행동 (기본 구현)
	virtual int performAction()
	{
		// 기본 행동: 몬스터가 공격하는 행동
		std::cout << name << " 가 공격합니다 :  " << attack << " 데미지를 입혔습니다!" << std::endl;
		return attack; // 공격력을 리턴
	}
	
	Item getDropItem() const // 아이템 드롭
	{
		if (dropItem.empty())
		{
			return Item("없음", 0, 0, E_Type::Material); // 드롭 아이템이 없으면 "없음" 반환
		}

		// 랜덤으로 아이템 선택
		int randomIndex = rand() % dropItem.size();
		return dropItem[randomIndex];
	}

};

