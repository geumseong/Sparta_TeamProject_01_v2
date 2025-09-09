#include "Goblin.h"
#include "Item.h"

Goblin::Goblin(const std::string& type, int level)
    : Monster(level), type(type), bonusExp(0), bonusGold(0), turnCount(0), isFled(false)
{

	{
		int baseHealth = 0; // �⺻ ü��
		int baseAttack = 0; // �⺻ ���ݷ�
		std::string namePrefix = ""; // �̸�

		if (type == "�Ϲ�")
		{
			namePrefix = "���";
			baseHealth = 30;
			baseAttack = 5;
			// this->commonWeight = 80; // �Ϲ� ������ ��� Ȯ��
			// this->rareWeight = 15;   // ��� ������ ��� Ȯ��
			// this->legendaryWeight = 5; // ���� ������ ��� Ȯ��
			dropItem.push_back(Item("����� �η��� ��", 20, 1));
			dropItem.push_back(Item("���� ���� ����", 30, 1));
		}

		else if (type == "������")
		{
			namePrefix = "������ ���";
			baseHealth = 20;
			baseAttack = 3;
			bonusExp = 10;
			bonusGold = 10;
			// this->commonWeight = 70; // �Ϲ� ������ ��� Ȯ��
			// this->rareWeight = 25;   // ��� ������ ��� Ȯ��
			// this->legendaryWeight = 5; // ���� ������ ��� Ȯ��
			dropItem.push_back(Item("����� ���� ����", 20, 1));
			dropItem.push_back(Item("���� ����", 25, 1));
		}

		else if (type == "�ǹ���")
		{
			namePrefix = "�ǹ��� ���";
			baseHealth = 35;
			baseAttack = 10;
			bonusExp = 15;
			bonusGold = 15;
			// this->commonWeight = 60; // �Ϲ� ������ ��� Ȯ��
			// this->rareWeight = 30;   // ��� ������ ��� Ȯ��
			// this->legendaryWeight = 10; // ���� ������ ��� Ȯ��
			dropItem.push_back(Item("����� �� ����", 30, 1));
			dropItem.push_back(Item("�콼 �ܰ�", 40, 1));
		}

		else if (type == "�糪��")
		{
			namePrefix = "�糪�� ���";
			baseHealth = 40;
			baseAttack = 15;
			bonusExp = 20;
			bonusGold = 20;
			// this->commonWeight = 50; // �Ϲ� ������ ��� Ȯ��
			// this->rareWeight = 35;   // ��� ������ ��� Ȯ��
			// this->legendaryWeight = 15; // ���� ������ ��� Ȯ��
			dropItem.push_back(Item("����� ��ī�ο� �̻�", 50, 1));
			dropItem.push_back(Item("�콼 ���", 60, 1));
		}

		else if (type == "���")
		{
			namePrefix = "��� ���";
			baseHealth = 100;
			baseAttack = 50;
			bonusExp = 50;
			bonusGold = 100;
			// this->commonWeight = 30; // �Ϲ� ������ ��� Ȯ��
			// this->rareWeight = 50;   // ��� ������ ��� Ȯ��
			// this->legendaryWeight = 20; // ���� ������ ��� Ȯ��
			dropItem.push_back(Item("����� Ȳ�� ����", 100, 1));
			dropItem.push_back(Item("��ȭ �ָӴ�", 200, 1));
		}

		this->health = baseHealth + (this->level * 5); // ������ ü�� 5 ����
		this->attack = baseAttack + (this->level * 2); // ������ ���ݷ� 2 ����

		this->name = "Lv." + std::to_string(level) + " " + namePrefix;

	}
}


// ������ ��ü �ൿ�� �����ϴ� ���� �Լ�
int Goblin::performAction() 
{
    turnCount++;

    if (type == "������") { return performCowardlyAction(); }
    else if (type == "���") { return performRichAction(); }
    else if (type == "�ǹ���") { return performCheekyAction(); }
    else if (type == "�糪��") { return performFierceAction(); }
    else { return performNormalAction(); }
}

// �Ϲ� ����� �ൿ
int Goblin::performNormalAction() 
{
    std::cout << this->name << "�� �����̸� �ֵθ��ϴ�!" << attack << std::endl;
	return this->attack; // ���ݷ� ��ȯ

}

// ������ ����� �ൿ
int Goblin::performCowardlyAction() 
{
    if (turnCount >= 2) {
        if (rand() % 100 < 20) {
            std::cout << name << "�� �̿� ���� ����ġ�� �մϴ�! (���� ����!)" << std::endl;
            this->health = 0;
            this->isFled = true;
			return 0; // ���� ����, ������ ����
        }
        else {
            std::cout << name << "�� ����ġ���� �����ϰ� ����� �����մϴ�! ���ݷ�: " << attack << std::endl;
			return attack; // ���ݷ� ��ȯ
		}
    }
    else {
        std::cout << name << "�� �̿� ���� ���� ��ũ���ϴ�." << std::endl;
		return 0; // ��ũ��, ������ ����
    
	}
}

// �ǹ��� ����� �ൿ
int Goblin::performCheekyAction() {
    std::cout << name << "�� ����� ���� �հ������ϸ� �����մϴ�! (�޽����� ���)" << std::endl;
	return 0; // ����, ������ ����
}

// �糪�� ����� �ൿ
int Goblin::performFierceAction()
{
	int finalDamage = static_cast<int>(this->attack * 1.5);
    std::cout << name << "�� ��ȿ�ϸ� ���ں��� ������ �ۺ׽��ϴ�! ���ݷ�: " << finalDamage << "!" << std::endl;
	return finalDamage; // ��ȭ�� ���ݷ� ��ȯ

}

// ��� ����� �ൿ
int Goblin::performRichAction()
{
    if (turnCount == 3) 
    {
        std::cout << this->name << "�� ����� ������� �����ƽ��ϴ�! (���� ����!)" << std::endl;
        this->health = 0;
        this->isFled = true;
		return 0; // ���� ����, ������ ����
    }

    else 
    {
        std::cout << this->name << "�� �Ÿ��ϰ� ����� �����մϴ�!" << std::endl;
		return 0; // ��� ����, ������ ����
	}
}
