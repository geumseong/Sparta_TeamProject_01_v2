#pragma once

// ��ȣ �ۿ� : GameManager, Character, Item
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "Item.h"

// ���� ����
class GameManager;
class Character;



class Monster // ��� ������ �������� �Ӽ��� ����� �����ϴ� �θ� Ŭ����
{ 

protected:
	// ��� ���� (�Ӽ�)
	// ������ ����(������)
	// protected�� �����Ͽ� �ڽ� Ŭ�������� ���� �����ϵ��� ��
	std::string name; // ���� �̸�
	int level; // ���� ����
	int health; // ���� ü��
	int attack; // ���� ���ݷ�
	int attackSpeed; // ���� ���ݼӵ�
	int baseExp; // �⺻ ���� ����ġ
	int baseGold; // �⺻ ���� ���
	std::vector<Item> dropItem; // ���Ͱ� ����ϴ� ������ ���


public:
	// ���� ������
	// ���� ��ü�� ������ �� ���� ���� ȣ���
	// �̸�, ü��, ���ݷ��� �ʱⰪ���� ����
	Monster(int level); // ������ �޾Ƽ� �ʱ�ȭ
	
	virtual ~Monster() {} // ���� �Ҹ���


	// ��� �Լ�


	// getter �Լ�
	// ������ �Ӽ����� ����
	std::string getName() const { return name; }
	int getLevel() const { return level; }
	int getHealth() const { return health; }
	int getAttack() const { return attack; }
	int getAttackSpeed() const { return attackSpeed; }
	

	// setter �Լ�?
	// ������ �Ӽ����� ����
	// ���Ϳ��� ���ظ� ������ �Լ� 
	// ���Ϳ��� ���������� �Ӽ����� �����ϴ� ���� ������ �� �����Ƿ�
	// setter �Լ��� �������� ����?
	void takeDamage(int damage) 
	{ 
		health -= damage;
		
		if (health < 0)
		{
			health = 0;
		}
	} // ����
	

	// ������ �ൿ�� ���� �ϴ� �Լ�
	
	// ������ ��� ���θ� Ȯ���ϴ� �Լ�
	bool isDead() const { return health <= 0; } // ���
	
	// ���Ͱ� �׾��� �� �������� ����ϴ� �Լ�
	//void dropItem() { /* ������ ��� ���� */ return nullptr; } // ������ ���

	// ������ �Ϲ� �ൿ (�⺻ ����)
	virtual int performAction()
	{
		// �⺻ �ൿ: ���Ͱ� �����ϴ� �ൿ
		std::cout << name << " �� �����մϴ� :  " << attack << " �������� �������ϴ�!" << std::endl;
		return attack; // ���ݷ��� ����
	}
	
	Item getDropItem() const // ������ ���
	{
		if (dropItem.empty())
		{
			return Item("����", 0, 0, E_Type::Material); // ��� �������� ������ "����" ��ȯ
		}

		// �������� ������ ����
		int randomIndex = rand() % dropItem.size();
		return dropItem[randomIndex];
	}

};

