//#pragma once
//
//// 상호 작용 : GameManager, Character, Item
//#include <string>
//#include <iostream>
//#include <cstdlib>
//#include <ctime>
//#include "Item.h"
//#include "Character.h"
//#include "GameManager.h"
//
//// 전방 선언
//class GameManager;
//class Character;
//class Item;
//
//
//
//class Monster // 모든 몬스터의 공통적인 속성과 기능을 정의하는 부모 클래스
//{ 
//
//protected:
//	// 멤버 변수 (속성)
//	// 몬스터의 상태(데이터)
//	// protected로 설정하여 자식 클래스에서 접근 가능하도록 함
//	std::string name; // 몬스터 이름
//	int health; // 몬스터 체력
//	int attack; // 몬스터 공격력
//
//
//public:
//	// 몬스터 생성자
//	// 몬스터 객체를 생성할 때 가장 먼저 호출됨
//	// 이름, 체력, 공격력을 초기값으로 설정
//	Monster(std::string name, int health, int attack)
//	{
//		this->name = name;
//		this->health = health;
//		this->attack = attack;
//	}
//
//
//	// 멤버 함수
//
//
//	// getter 함수
//	// 몬스터의 속성값을 리턴
//	std::string getName() { return name; }
//	int getHealth() { return health; }
//	int getAttack() { return attack; }
//
//	// setter 함수?
//	// 몬스터의 속성값을 변경
//	// 몬스터에게 피해를 입히는 함수 
//	// 몬스터에게 직접적으로 속성값을 변경하는 것은 위험할 수 있으므로
//	// setter 함수는 제공하지 않음?
//	void takeDamage(int damage) { health -= damage; } // 피해
//	
//
//	// 몬스터의 행동을 정의 하는 함수
//	
//	// 몬스터의 사망 여부를 확인하는 함수
//	bool isDead() { return health <= 0; } // 사망
//	
//	// 몬스터가 죽었을 때 아이템을 드롭하는 함수
//	void dropItem() { /* 아이템 드랍 로직 */ return nullptr; } // 아이템 드랍 
