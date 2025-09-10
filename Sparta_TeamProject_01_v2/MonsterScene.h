#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class MonsterScene
{
public:
    // 드래곤의 등장 연출을 보여주는 함수
    void showDragonAppear(const std::string& bossName);

    // 드래곤의 2페이즈 진입 연출을 보여주는 함수
    void showDragonPhase2(const std::string& bossName);

private:
    // SFML 창을 띄우는 실제 작업을 수행하는 내부 함수
    void displayImage(const std::string& imagePath, const std::string& title);
};