#pragma once

#include <windows.h> // Windows API ���
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>   // ������(��� ����) ���� ���
#include <chrono>   // �ð� ���� ���

namespace AsciiArt
{
    /**
     * @brief �ܼ� â�� ũ�⸦ �����մϴ�. (�߰��� �κ�)
     * @param width ���ϴ� ���� ���� ��
     * @param height ���ϴ� ���� �� ��
     */
    inline void setConsoleSize(int width, int height)
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SMALL_RECT rect = { 0, 0, static_cast<SHORT>(width - 1), static_cast<SHORT>(height - 1) };
        COORD bufferSize = { static_cast<SHORT>(width), static_cast<SHORT>(height) };
        SetConsoleScreenBufferSize(hConsole, bufferSize);
        SetConsoleWindowInfo(hConsole, TRUE, &rect);
    }

    /**
     * @brief ANSI ������ ���Ե� ������ �о� ���� �״�� ����մϴ�.
     * @param filePath �о�� .txt ���� ���
     */
    inline void printFromFile(const std::string& filePath)
    {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            std::cerr << "���: " << filePath << " �ƽ�Ű ��Ʈ ������ �� �� �����ϴ�." << std::endl;
            return;
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        std::cout << buffer.str() << std::endl;

        file.close();
    }

    // (������ �ִ� playAnimation �Լ��� �ʿ��� ��� ���⿡ ����)
}