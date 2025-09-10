// AsciiArt.h 또는 Util.h

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <windows.h>

namespace AsciiArt
{
 /**
 * @brief 콘솔 창의 크기를 조절합니다.
 * @param width 원하는 가로 글자 수
 * @param height 원하는 세로 줄 수
 */

    // 콘솔 창의 크기를 조절하는 함수
    inline void setConsoleSize(int width, int height)
    {
            /**
     * @brief 콘솔 창의 크기를 조절합니다.
     * @param width 원하는 가로 글자 수
     * @param height 원하는 세로 줄 수
     */
        // 1. 콘솔 창 핸들 가져오기
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        // 2. 창 크기를 조절하기 위한 RECT와 COORD 구조체 설정
        SMALL_RECT rect = { 0, 0, (short)(width - 1), (short)(height - 1) };
        COORD bufferSize = { (short)width, (short)height };

        // 3. 콘솔 버퍼 크기 설정
        SetConsoleScreenBufferSize(hConsole, bufferSize);
        // 4. 실제 콘솔 창 크기 설정
        SetConsoleWindowInfo(hConsole, TRUE, &rect);
    }



    // ANSI 정보가 포함된 파일을 '한 줄씩' 읽어 원본 그대로 출력하는 함수
    inline void printFromFile(const std::string& filePath)
    {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            std::cerr << "오류: " << filePath << " 파일을 열 수 없습니다." << std::endl;
            return;
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        std::cout << buffer.str() << std::endl;
        file.close();
    }

}