#include "Character.h"
#include <iostream>

Character::Character()
{
	level = 1;
	health = 200;
	maxHealth = 200;
	attack = 30;
	experience = 0;
	gold = 0;
}

void Character::displayStatus()
{
	cout << "------------------------------------" << endl;
	cout << "* 현재 능력치" << endl;
	cout << "이름: " << name << endl;
	cout << "Lv. " << level << endl;
	cout << "HP: " << health << endl;
	cout << "공격력: " << attack << endl;
	cout << "경험치: " << experience << endl;
	cout << "골드: " << gold << endl;
	cout << "------------------------------------" << endl;
}

void Character::levelUp()
{
	if (level < 10)
	{
		level++;
		health = (maxHealth + (level * 20));
		maxHealth = (maxHealth + (level * 20));
		attack = (attack + (level * 5));
		experience = 0;
	}
	else
	{
		cout << "더 이상 레벨업을 할 수 없습니다." << endl;
	}

}

void Character::useItem(int index)
{

}

void Character::visitShop()
{

}

void Character::characterDeath()
{
	if(health >= 0)
		cout << "캐릭터가 사망하였습니다." << endl;
}

void Character::characterAttack()
{
}



string Character::getName() const
{
	return name;
}

int Character::getLevel() const
{
	return level;
}

int Character::getHealth() const
{
	return health;
}

int Character::getMaxhealth() const
{
	return maxHealth;
}

int Character::getAttack() const
{
	return attack;
}

int Character::getExperience() const
{
	return experience;
}

int Character::getGold() const
{
	return gold;
}

void Character::setName(string _name)
{
	name = _name;
}

bool Character::setHealth(int _health)
{
	health = _health;
	return health >= 1 ? true : false;
}

bool Character::setMaxhealth(int _maxHealth)
{
	maxHealth = _maxHealth;
	return maxHealth >= 1 ? true : false;
}

void Character::setAttack(int _attack)
{
	attack = _attack;
}

void Character::setExperience(int _experience)
{
	experience = _experience;
}

void Character::setGold(int _gold)
{
	gold = _gold;
}
