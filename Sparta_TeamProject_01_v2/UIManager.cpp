#include "UIManager.h"
#include "AsciiArt.h"   // AsciiArt.h�� �ʿ��մϴ�.
#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>

void UIManager::showTitleScreen()
{

    AsciiArt::printFromFile("title_image.txt"); // �̹��� �ƽ�Ű ��Ʈ ǥ��

    AsciiArt::printFromFile("title_text.txt"); // �ؽ�Ʈ(����) �ƽ�Ű ��Ʈ ǥ��

    // --- 3. ���� �ȳ� ���� �� �Է� ��� ---
    std::cout << "\n\n";
    std::cout << "                  < �ƹ� Ű�� ������ ������ ���۵˴ϴ� >" << std::endl;
    system("pause >nul"); // "����Ϸ���..." �޽��� ���� Ű �Է¸� ���
}

// (���߿� �߰��� �Լ� ����)
// int UIManager::showMainMenu() { ... }
// void UIManager::clearScreen() { ... }