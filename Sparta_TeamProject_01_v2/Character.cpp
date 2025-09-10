#include "Character.h"
#include <iostream>

Character::Character()
{
	jobName = "Beginner";
	name = "Character";
	level = 1;
	health = 200;
	maxHealth = 200;
	mp = 100;
	maxMp = 100;
	attackPower = 30;
	experience = 0;
	gold = 0;
	defense = 0;
	attackSpeed = 1;
}

Character::Character(string name)
{
	this -> jobName = "Beginner";
	this -> name = "Character";
	this -> level = 1;
	this -> health = 200;
	this -> maxHealth = 200;
	this -> mp = 100;
	this -> maxMp = 100;
	this -> attackPower = 30;
	this -> experience = 0;
	this -> gold = 0;
	this -> defense = 0;
	this -> attackSpeed = 1;
}

void Character::displayStatus()
{
	cout << u8"------------------------------------" << endl;
	cout << u8"* 현재 능력치" << endl;
	cout << u8"이름: " << name << endl;
	cout << u8"직업: " << jobName << endl;
	cout << u8"Lv. " << level << endl;
	cout << u8"HP: " << health << endl;
	cout << u8"MP: " << mp << endl;
	cout << u8"공격력: " << attackPower << endl;
	cout << u8"방어력: " << defense << endl;
	cout << u8"공격속도: " << attackSpeed << endl;
	cout << u8"경험치: " << experience << endl;
	cout << u8"------------------------------------" << endl;
}

void Character::visitShop()
{

}

void Character::characterDeath()
{
	cout << u8"캐릭터가 사망하였습니다." << endl;
}

void Character::takeCharacterDamage(int damage)
{
	health -= damage;

	if (health <= 0)
	{
		health = 0;
		characterDeath();
	}
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

int Character::getMaxHealth() const
{
	return maxHealth;
}

int Character::getMp() const
{
	return mp;
}
//
int Character::getMaxMp() const
{
	return maxMp;
}

int Character::getAttack() const
{
	return attackPower;
}

int Character::getDefense() const
{
	return defense;
}

int Character::getAttackSpeed() const
{
	return attackSpeed;
}

int Character::getExperience() const
{
	return experience;
}

void Character::setName(string _name)
{
	this->name = _name;
}

bool Character::setHealth(int _health)
{
	this->health = _health;
	return health >= 1 ? true : false;
}

bool Character::setMaxhealth(int _maxHealth)
{
	this->maxHealth = _maxHealth;
	return maxHealth >= 1 ? true : false;
}

bool Character::setMp(int _mp)
{
	this->mp = _mp;
	return mp >= 1 ? true : false;
}

bool Character::setMaxMp(int _maxMp)
{
	this->maxMp = _maxMp;
	return maxMp >= 1 ? true : false;
}

void Character::setAttack(int _attack)
{
	this->attackPower = _attack;
}

void Character::setDefense(int _defense)
{
	this->defense = _defense;
}

void Character::setAttackSpeed(int _attackSpeed)
{
	this->attackSpeed = _attackSpeed;
}

void Character::setExperience(int _experience)
{
	this->experience = _experience;
}

