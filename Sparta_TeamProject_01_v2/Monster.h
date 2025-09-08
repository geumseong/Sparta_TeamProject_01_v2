#pragma once

// ��ȣ �ۿ� : GameManager, Character, Item
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Item.h"
#include "Character.h"
#include "GameManager.h"

// ���� ����
class GameManager;
class Character;
class Item;



class Monster // ��� ������ �������� �Ӽ��� ����� �����ϴ� �θ� Ŭ����
{ 

protected:
	// ��� ���� (�Ӽ�)
	// ������ ����(������)
	// protected�� �����Ͽ� �ڽ� Ŭ�������� ���� �����ϵ��� ��
	std::string name; // ���� �̸�
	int health; // ���� ü��
	int attack; // ���� ���ݷ�


public:
	// ���� ������
	// ���� ��ü�� ������ �� ���� ���� ȣ���
	// �̸�, ü��, ���ݷ��� �ʱⰪ���� ����
	Monster(std::string name, int health, int attack)
	{
		this->name = name;
		this->health = health;
		this->attack = attack;
	}


	// ��� �Լ�


	// getter �Լ�
	// ������ �Ӽ����� ����
	std::string getName() { return name; }
	int getHealth() const { return health; }
	int getAttack() const { return attack; }

	// setter �Լ�?
	// ������ �Ӽ����� ����
	// ���Ϳ��� ���ظ� ������ �Լ� 
	// ���Ϳ��� ���������� �Ӽ����� �����ϴ� ���� ������ �� �����Ƿ�
	// setter �Լ��� �������� ����?
	void takeDamage(int damage) { health -= damage; } // ����
	

	// ������ �ൿ�� ���� �ϴ� �Լ�
	
	// ������ ��� ���θ� Ȯ���ϴ� �Լ�
	bool isDead() const { return health <= 0; } // ���
	
	// ���Ͱ� �׾��� �� �������� ����ϴ� �Լ�
	//void dropItem() { /* ������ ��� ���� */ return nullptr; } // ������ ���

	// ������ �Ϲ� �ൿ (�⺻ ����)
	virtual void performAction()
	{
		// �⺻ �ൿ: ���Ͱ� �����ϴ� �ൿ
		std::cout << name << " attacks for " << attack << " damage!" << std::endl;
	}

};

