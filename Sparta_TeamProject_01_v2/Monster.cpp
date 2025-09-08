// Monster.cpp
// tt
#include "Monster.h"

// 몬스터 클래스의 생성자 구현
Monster::Monster(std::string name, int health, int attack)
    : name(name), health(health), attack(attack) {}

// 몬스터의 이름 반환
std::string Monster::getName() const { return name; }

// 몬스터의 체력 반환
int Monster::getHealth() const { return health; }

// 몬스터의 공격력 반환
int Monster::getAttack() const { return attack; }

// 몬스터가 피해를 입었을 때
void Monster::takeDamage(int damage) 
{
    health -= damage;
    if (health < 0) { health = 0; }
}

// 몬스터의 행동 (기본 구현)
// 자식 클래스에서 오버라이드될 것이다.
void Monster::performAction() { std::cout << "몬스터가 행동을 준비합니다." << std::endl; }