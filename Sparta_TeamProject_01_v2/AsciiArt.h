// AsciiArt.h 또는 Util.h

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <windows.h>

namespace AsciiArt
{


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