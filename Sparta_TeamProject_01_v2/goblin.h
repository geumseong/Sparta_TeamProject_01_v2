// Goblin.h
// ������ ���� �� �ϳ��� ����� �����ϴ� ��� ����
// Goblin Ŭ������ Monster Ŭ������ ��ӹ޾� ��� ���͸� ����
// Goblin Ŭ������ Ư���� ��ü�� ����� Ư���� �ൿ�� �Ӽ��� �߰��� ����


#pragma once
#include "Monster.h"
#include <string>


// ���� ����
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
	int performNormalAction();
	int performCowardlyAction();
	int performCheekyAction();
	int performFierceAction();
	int performRichAction();


public:
	// ��� ������
	// ����� �̸�, ü��, ���ݷ��� �ʱⰪ���� ����
	Goblin(const std::string& type, int level);




	// Goblin Ŭ�������� performAction() �Լ����� performAction()���� �����Ͽ�
	// Monster Ŭ������ virtual void performAction()�� �ùٸ��� �������̵��մϴ�.
	int performAction() override;

	bool hasFled() const { return isFled; }
	int getBonusExp() const { return bonusExp; }
	int getBonusGold() const { return bonusGold; }


	//this->health = baseHealth + (this->level * 5); // ������ ü�� 5 ����
	//this->attack = baseAttack + (this->level * 2); // ������ ���ݷ� 2 ����
	//this->maxHealth = this->health; // �ִ� ü�� ����

	//this->name = "Lv." + std::to_string(level) + " " + this->name; // �̸��� ���� �߰�

};