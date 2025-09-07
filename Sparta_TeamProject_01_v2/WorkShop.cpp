//#include <iostream>
//#include <vector>
//#include <string>
//#include <unordered_map>
//#include <limits>
//
//
//
///*
//// -------------------- 기본 자료형 --------------------
//// 재료 구조체: 이름(name)과 개수(amount)를 가진다
//struct Ingredient {
//    std::string name;
//    int amount;
//};
//
//// 레시피 구조체: 결과물 이름(name)과 필요한 재료 목록(ingredients)을 가진다
//struct Recipe {
//    std::string name;
//    std::vector<Ingredient> ingredients;
//};
//
//// -------------------- 유틸 입력 --------------------
//// 안전한 정수 입력 함수
//int readInt() {
//    int x;
//    while (true) {
//        if (std::cin >> x) return x;  // 정수를 입력받으면 반환
//        std::cout << "숫자를 입력하세요: ";
//        std::cin.clear(); // 오류 상태 플래그 해제
//        // 입력 버퍼에서 잘못된 입력 제거
//        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//    }
//}
//
//// y/n 입력을 안전하게 처리하는 함수
//char readYesNo() {
//    char c;
//    while (true) {
//        if (std::cin >> c) {
//            if (c == 'y' || c == 'Y' || c == 'n' || c == 'N') return c;
//        }
//        std::cout << "(y/n)로 입력하세요: ";
//        std::cin.clear();
//        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//    }
//}
//
//// -------------------- 공방 --------------------
//class Workshop {
//private:
//    // 인벤토리: 아이템 이름(string) → 개수(int) 로 저장
//    std::unordered_map<std::string, int> inv;
//
//    // 레시피 목록
//    std::vector<Recipe> potions; // 물약 레시피
//    std::vector<Recipe> equips;  // 장비 레시피
//
//    // 특정 아이템을 인벤토리에서 얼마나 가지고 있는지 반환
//    int have(const std::string& item) const {
//        auto it = inv.find(item);
//        return (it == inv.end()) ? 0 : it->second;
//    }
//
//    
//
//// -------------------- 메인 --------------------
//int main() {
//    Workshop ws;
//    ws.addDefaultRecipes(); // 기본 레시피 등록
//
//    while (true) {
//        std::cout << "\n메뉴\n"
//            << "1. 물약 제작\n"
//            << "2. 장비 제작\n"
//            << "3. 인벤토리 보기\n"
//            << "4. 레시피 보기\n"
//            << "5. 종료\n"
//            << "선택: ";
//        int sel = readInt();
//        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//
//        if (sel == 1) {
//            ws.craftPotion();
//        }
//        else if (sel == 2) {
//            ws.craftEquip();
//        }
//        else if (sel == 3) {
//            ws.showInventory();
//        }
//        else if (sel == 4) {
//            ws.showAllRecipes();
//        }
//        else if (sel == 5) {
//            std::cout << "종료합니다.\n";
//            break;
//        }
//        else {
//            std::cout << "잘못된 선택입니다.\n";
//        }
//    }
//    return 0;
//}
//
//*/