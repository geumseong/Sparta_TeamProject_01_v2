// Orc.cpp
// tt
#include "Orc.h"
#include <random>

void Orc::performAction() 
{
    if (type == "�߸�����") { performSavageAction(); }
    else if (type == "������") { performBrutalCharge(); }
    else { performNormalAction(); }
}

void Orc::performNormalAction() 
{
    std::cout << name << "�� ������ ������ �õ��մϴ�! ���ݷ�: " << attack << std::endl;
}

void Orc::performSavageAction() 
{
    // 30% Ȯ���� �� ������ ������ �õ�
    if (rand() % 100 < 30) 
    {
        std::cout << name << "�� ���⿡ �۽ο� ���ں��� �ϰ��� �����ϴ�! ���ݷ�: " << attack * 1.5 << std::endl;
    }

    else 
    {
        performNormalAction();
    }
}

void Orc::performBrutalCharge() 
{
    // ü���� �������� ������ ���� ������ ���
    if (health <= 50) 
    {
        std::cout << name << "�� �����ϸ� ����� �Ͱ����մϴ�! ���ݷ�: " << attack * 2 << std::endl;
    }

    else 
    {
        std::cout << name << "�� �������� ��ȿ�� �������ϴ�." << std::endl;
    }
}
