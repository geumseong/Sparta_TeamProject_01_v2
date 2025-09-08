// Goblin.h
// ������ ���� �� �ϳ��� ����� �����ϴ� ��� ����
// Goblin Ŭ������ Monster Ŭ������ ��ӹ޾� ��� ���͸� ����
// Goblin Ŭ������ Ư���� ��ü�� ����� Ư���� �ൿ�� �Ӽ��� �߰��� ����


#pragma once
#include "Monster.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
// ��ȣ �ۿ� : GameManager, Character, Item
#include "Item.h"
#include "Character.h"
#include "GameManager.h"
// ���� ����
class GameManager;
class Character;
class Item;
// Goblin Ŭ������ Monster Ŭ������ ��ӹ޾� ��� ���͸� ����


class Goblin : public Monster
{
private:
	std::string type; // ����� ���� (��: �Ϲ� ���, ��� ���� ��)
	int bonusExp; // Ư�� ��ü óġ �� �߰� ����ġ
	int bonusGold; // Ư�� ��ü óġ �� �߰� ���
	int turnCount; // �� ī��Ʈ (Ư�� �ൿ�� ����)
	bool isFled; // ���� ����


	// �� ������ ���� �ൿ�� �����ϴ� �Լ�
	void performNormalAction();
	void performCowardlyAction();
	void performCheekyAction();
	void performFierceAction();
	void performRichAction();


public:
	// ��� ������
	// ����� �̸�, ü��, ���ݷ��� �ʱⰪ���� ����
	Goblin(const std::string& type)
		: Monster("", 0, 0), type(type), bonusExp(0), bonusGold(0), turnCount(0), isFled(false)
	{
		if (type == "�Ϲ�")
		{
			this->name = "���";
			this->health = 30;
			this->attack = 5;
			// this->commonWeight = 80; // �Ϲ� ������ ��� Ȯ��
			// this->rareWeight = 15;   // ��� ������ ��� Ȯ��
			// this->legendaryWeight = 5; // ���� ������ ��� Ȯ��

		}

		else if (type == "������")
		{
			this->name = "������ ���";
			this->health = 20;
			this->attack = 3;
			this->bonusExp = 10;
			this->bonusGold = 10;
			// this->commonWeight = 70; // �Ϲ� ������ ��� Ȯ��
			// this->rareWeight = 25;   // ��� ������ ��� Ȯ��
			// this->legendaryWeight = 5; // ���� ������ ��� Ȯ��

		}

		else if (type == "�ǹ���")
		{
			this->name = "�ǹ��� ���";
			this->health = 35;
			this->attack = 10;
			this->bonusExp = 15;
			this->bonusGold = 15;
			// this->commonWeight = 60; // �Ϲ� ������ ��� Ȯ��
			// this->rareWeight = 30;   // ��� ������ ��� Ȯ��
			// this->legendaryWeight = 10; // ���� ������ ��� Ȯ��

		}

		else if (type == "�糪��")
		{
			this->name = "�糪�� ���";
			this->health = 40;
			this->attack = 15;
			this->bonusExp = 20;
			this->bonusGold = 20;
			// this->commonWeight = 50; // �Ϲ� ������ ��� Ȯ��
			// this->rareWeight = 35;   // ��� ������ ��� Ȯ��
			// this->legendaryWeight = 15; // ���� ������ ��� Ȯ��

		}

		else if (type == "���")
		{
			this->name = "��� ���";
			this->health = 100;
			this->attack = 50;
			this->bonusExp = 50;
			this->bonusGold = 100;
			// this->commonWeight = 30; // �Ϲ� ������ ��� Ȯ��
			// this->rareWeight = 50;   // ��� ������ ��� Ȯ��
			// this->legendaryWeight = 20; // ���� ������ ��� Ȯ��

		}
	}

	// Goblin Ŭ�������� performAction() �Լ����� performAction()���� �����Ͽ�
	// Monster Ŭ������ virtual void performAction()�� �ùٸ��� �������̵��մϴ�.
	void performAction() override;

	bool hasFled() const { return isFled; }
	int getBonusExp() const { return bonusExp; }
	int getBonusGold() const { return bonusGold; }

};