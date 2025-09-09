// Orc.cpp
#include "Orc.h"
#include <random>

int Orc::performAction() 
{
    if (type == "�߸�����") { return performSavageAction(); }
    else if (type == "������") { return performBerserkerAction(); }
    else { return performNormalAction(); }
}

int Orc::performNormalAction() 
{
    std::cout << name << "�� ������ ������ �õ��մϴ�! ���ݷ�: " << attack << std::endl;
    return attack;
}

int Orc::performSavageAction() 
{
    // 30% Ȯ���� �� ������ ������ �õ�
    if (rand() % 100 < 30) 
    {
        std::cout << name << "�� ���⿡ �۽ο� ���ں��� �ϰ��� �����ϴ�! ���ݷ�: " << attack * 1.5 << std::endl;
        return attack * 1.5;
    }

    else 
    {
        return performNormalAction();
    }
}

int Orc::performBerserkerAction()
{
    if (!isCharging)
    {
        std::cout << name << "�� ������ �غ��մϴ�! ���� ������ �ſ� ���������ϴ�!" << std::endl;
        isCharging = true;
        return 0; // �غ� ����, ������ ����
    }

    else
    {
        std::cout << name << "�� �����ϸ� ����� �Ͱ����մϴ�! ���ݷ�: " << attack * 2 << std::endl;
        isCharging = false; // ���� �� ���� �ʱ�ȭ
        return attack * 2;
    }
}