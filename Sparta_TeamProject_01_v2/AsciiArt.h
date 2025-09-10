#pragma once

#include <windows.h> // Windows API 사용
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>   // 스레드(잠시 멈춤) 관련 헤더
#include <chrono>   // 시간 관련 헤더

namespace AsciiArt
{
    /**
     * @brief 콘솔 창의 크기를 조절합니다. (추가된 부분)
     * @param width 원하는 가로 글자 수
     * @param height 원하는 세로 줄 수
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
     * @brief ANSI 정보가 포함된 파일을 읽어 원본 그대로 출력합니다.
     * @param filePath 읽어올 .txt 파일 경로
     */
    inline void printFromFile(const std::string& filePath)
    {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            std::cerr << "경고: " << filePath << " 아스키 아트 파일을 열 수 없습니다." << std::endl;
            return;
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        std::cout << buffer.str() << std::endl;

        file.close();
    }

    // (기존에 있던 playAnimation 함수도 필요한 경우 여기에 유지)
}