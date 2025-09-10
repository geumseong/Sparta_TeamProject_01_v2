// PanelBox_min.h
#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <windows.h>

// 콘솔 코드페이지만 UTF-8로 (필요시)
inline void InitConsoleUTF8Only() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

inline void setCursorPosition(int x, int y) {
    COORD c{ (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

inline void writeW(const std::wstring& w) {
    DWORD written = 0;
    WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), w.c_str(),
        (DWORD)w.size(), &written, nullptr);
}

// UTF-8 -> UTF-16
inline std::wstring utf8_to_wstring(const std::string& s) {
    if (s.empty()) return {};
    int n = MultiByteToWideChar(CP_UTF8, 0, s.data(), (int)s.size(), nullptr, 0);
    std::wstring out(n, 0);
    MultiByteToWideChar(CP_UTF8, 0, s.data(), (int)s.size(), &out[0], n);
    return out;
}

// 표시폭 계산(전각=2, 반각=1) - 단순 규칙
inline int wc_display_width(wchar_t ch) {
    if ((ch >= 0x1100 && ch <= 0x11FF) || (ch >= 0x3040 && ch <= 0x30FF) ||
        (ch >= 0x31F0 && ch <= 0x31FF) || (ch >= 0x3400 && ch <= 0x9FFF) ||
        (ch >= 0xAC00 && ch <= 0xD7A3) || (ch >= 0xFF01 && ch <= 0xFF60) ||
        (ch >= 0xFFE0 && ch <= 0xFFE6)) return 2;
    return 1;
}
inline int wcs_display_width(const std::wstring& s) { int w = 0;for (auto ch : s)w += wc_display_width(ch);return w; }
inline std::wstring trim_to_display_width(const std::wstring& s, int maxc) {
    std::wstring out; int w = 0; for (auto ch : s) { int cw = wc_display_width(ch); if (w + cw > maxc)break; out.push_back(ch); w += cw; } return out;
}
inline std::wstring pad_display_width(const std::wstring& s, int target) {
    int w = wcs_display_width(s); return (w >= target) ? s : (s + std::wstring(target - w, L' '));
}

// wstring 라인 박스 출력 (WriteConsoleW 사용)
inline void drawBoxW(int x, int y, int width, int height, const std::vector<std::wstring>& lines)
{
    setCursorPosition(x, y);
    writeW(L"┏"); writeW(std::wstring(width - 2, L'━')); writeW(L"┓");

    const int inner = width - 2;
    for (int row = 1; row < height - 1; ++row) {
        setCursorPosition(x, y + row);
        writeW(L"┃");
        std::wstring line;
        if (row - 1 < (int)lines.size()) {
            line = pad_display_width(trim_to_display_width(lines[row - 1], inner), inner);
        }
        else {
            line = std::wstring(inner, L' ');
        }
        writeW(line);
        writeW(L"┃");
    }

    setCursorPosition(x, y + height - 1);
    writeW(L"┗"); writeW(std::wstring(width - 2, L'━')); writeW(L"┛");
}

// UTF-8 라인 → 박스
inline void drawBoxUTF8(int x, int y, int width, int height, const std::vector<std::string>& utf8_lines) {
    std::vector<std::wstring> wl; wl.reserve(utf8_lines.size());
    for (auto& s : utf8_lines) wl.push_back(utf8_to_wstring(s));
    drawBoxW(x, y, width, height, wl);
}

// 줄 나누기
inline std::vector<std::string> splitLinesUTF8(const std::string& s) {
    std::vector<std::string> out; std::istringstream iss(s);
    for (std::string line; std::getline(iss, line); ) out.push_back(line);
    return out;
}

// cout 캡처 (RAII)
struct CoutCapture {
    std::streambuf* old = nullptr;
    std::ostringstream oss;
    CoutCapture() { old = std::cout.rdbuf(oss.rdbuf()); }
    ~CoutCapture() { std::cout.rdbuf(old); }
    std::string str() const { return oss.str(); }
};

// 기존 cout 코드 → 박스 렌더
template <class Fn>
inline void RenderBoxFromCout(int x, int y, int width, int height, Fn&& fn) {
    CoutCapture cap;
    fn(); // 기존 cout 코드 그대로 실행
    auto lines = splitLinesUTF8(cap.str());
    drawBoxUTF8(x, y, width, height, lines);
}


struct boxPosition
{
    int x;
    int y;
    int width;
    int height;
};