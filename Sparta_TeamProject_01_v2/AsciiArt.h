// AsciiArt.h �Ǵ� Util.h

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <windows.h>

namespace AsciiArt
{
 /**
 * @brief �ܼ� â�� ũ�⸦ �����մϴ�.
 * @param width ���ϴ� ���� ���� ��
 * @param height ���ϴ� ���� �� ��
 */

    // �ܼ� â�� ũ�⸦ �����ϴ� �Լ�
    inline void setConsoleSize(int width, int height)
    {
            /**
     * @brief �ܼ� â�� ũ�⸦ �����մϴ�.
     * @param width ���ϴ� ���� ���� ��
     * @param height ���ϴ� ���� �� ��
     */
        // 1. �ܼ� â �ڵ� ��������
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        // 2. â ũ�⸦ �����ϱ� ���� RECT�� COORD ����ü ����
        SMALL_RECT rect = { 0, 0, (short)(width - 1), (short)(height - 1) };
        COORD bufferSize = { (short)width, (short)height };

        // 3. �ܼ� ���� ũ�� ����
        SetConsoleScreenBufferSize(hConsole, bufferSize);
        // 4. ���� �ܼ� â ũ�� ����
        SetConsoleWindowInfo(hConsole, TRUE, &rect);
    }



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