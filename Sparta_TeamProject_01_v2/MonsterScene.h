#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class MonsterScene
{
public:
    // �巡���� ���� ������ �����ִ� �Լ�
    void showDragonAppear(const std::string& bossName);

    // �巡���� 2������ ���� ������ �����ִ� �Լ�
    void showDragonPhase2(const std::string& bossName);

private:
    // SFML â�� ���� ���� �۾��� �����ϴ� ���� �Լ�
    void displayImage(const std::string& imagePath, const std::string& title);
};