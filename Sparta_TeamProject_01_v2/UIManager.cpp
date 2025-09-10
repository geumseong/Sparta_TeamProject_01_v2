#include "UIManager.h"
#include "AsciiArt.h"   // AsciiArt.h가 필요합니다.
#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>

void UIManager::showTitleScreen()
{

    AsciiArt::printFromFile("title_image.txt"); // 이미지 아스키 아트 표시

    AsciiArt::printFromFile("title_text.txt"); // 텍스트(제목) 아스키 아트 표시

    // --- 3. 시작 안내 문구 및 입력 대기 ---
    std::cout << "\n\n";
    std::cout << "                  < 아무 키나 누르면 게임이 시작됩니다 >" << std::endl;
    system("pause >nul"); // "계속하려면..." 메시지 없이 키 입력만 대기
}

// (나중에 추가할 함수 예시)
// int UIManager::showMainMenu() { ... }
// void UIManager::clearScreen() { ... }