#include "UIManager.h"
#include "AsciiArt.h"   // AsciiArt.h�� �ʿ��մϴ�.
#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>

void UIManager::showTitleScreen()
{

    AsciiArt::printFromFile("title_image.txt"); // �̹��� �ƽ�Ű ��Ʈ ǥ��

    // 2�ʰ� �̹����� ������ �� �������� �Ѿ
    std::this_thread::sleep_for(std::chrono::seconds(2));

    AsciiArt::printFromFile("title_image2.txt"); // �̹��� �ƽ�Ű ��Ʈ ǥ��

    std::this_thread::sleep_for(std::chrono::seconds(2));


    AsciiArt::printFromFile("title_text.txt"); // �ؽ�Ʈ(����) �ƽ�Ű ��Ʈ ǥ��

    // --- 3. ���� �ȳ� ���� �� �Է� ��� ---
    std::cout << "\n\n";
    std::cout << u8"                  < �ƹ� Ű�� ������ ������ ���۵˴ϴ� >" << std::endl;
    system("pause >nul"); // "����Ϸ���..." �޽��� ���� Ű �Է¸� ���
}

// (���߿� �߰��� �Լ� ����)
// int UIManager::showMainMenu() { ... }
// void UIManager::clearScreen() { ... }