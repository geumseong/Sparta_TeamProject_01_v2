// AsciiArt.h �Ǵ� Util.h

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <windows.h>

namespace AsciiArt
{


    // ANSI ������ ���Ե� ������ '�� �پ�' �о� ���� �״�� ����ϴ� �Լ�
    inline void printFromFile(const std::string& filePath)
    {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            std::cerr << "����: " << filePath << " ������ �� �� �����ϴ�." << std::endl;
            return;
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        std::cout << buffer.str() << std::endl;
        file.close();
    }

}