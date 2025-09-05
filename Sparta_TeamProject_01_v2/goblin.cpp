#include "Goblin.h"
#include "GameManager.h"
#include "Character.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "Item.h"


// ������ ��ü �ൿ�� �����ϴ� ���� �Լ�
void Goblin::performAction() 
{
    turnCount++;

    if (type == "������") { performCowardlyAction(); }
    else if (type == "���") { performRichAction(); }
    else if (type == "�ǹ���") { performCheekyAction(); }
    else if (type == "�糪��") { performFierceAction(); }
    else { performNormalAction(); }
}

// �Ϲ� ����� �ൿ
void Goblin::performNormalAction() 
{
    std::cout << name << "�� �����̸� �ֵθ��ϴ�! ���ݷ�: " << attack << std::endl;
}

// ������ ����� �ൿ
void Goblin::performCowardlyAction() 
{
    if (turnCount >= 2) {
        if (rand() % 100 < 20) {
            std::cout << name << "�� �̿� ���� ����ġ�� �մϴ�! (���� ����!)" << std::endl;
            this->health = 0;
            this->isFled = true;
        }
        else {
            std::cout << name << "�� ����ġ���� �����ϰ� ����� �����մϴ�! ���ݷ�: " << attack << std::endl;
        }
    }
    else {
        std::cout << name << "�� �̿� ���� ���� ��ũ���ϴ�." << std::endl;
    }
}

// �ǹ��� ����� �ൿ
void Goblin::performCheekyAction() {
    std::cout << name << "�� ����� ���� �հ������ϸ� �����մϴ�! (�޽����� ���)" << std::endl;
}

// �糪�� ����� �ൿ
void Goblin::performFierceAction()
{
    std::cout << name << "�� ��ȿ�ϸ� ���ں��� ������ �ۺ׽��ϴ�! ���ݷ�: " << attack * 1.5 << "!" << std::endl;
}

// ��� ����� �ൿ
void Goblin::performRichAction()
{
    if (turnCount == 3) 
    {
        std::cout << name << "�� ����� ������� �����ƽ��ϴ�! (���� ����!)" << std::endl;
        this->health = 0;
        this->isFled = true;
    }

    else 
    {
        std::cout << name << "�� �Ÿ��ϰ� ����� �����մϴ�!" << std::endl;
    }
}
