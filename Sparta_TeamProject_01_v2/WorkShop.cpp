//#include "Workshop.h"
//#include <cctype>
//
//void Workshop::Open(Inventory& inv, const ItemDB& db)
//{
//    while (true) {
//        std::cout << "\n=== 제작 공방 ===\n"
//            << "1. 포션 제작\n"
//            << "2. 장비 제작\n"
//            << "3. 악세사리 제작\n"
//            << "4. 레시피\n"
//            << "5. 나가기\n"
//            << "선택: ";
//
//        int sel = AskIntInRange("", 1, 5);
//        if (sel == 1) CraftPotion(inv, db);
//        else if (sel == 2) CraftEquipment(inv, db);
//        else if (sel == 3) CraftAccessory(inv, db);
//        else if (sel == 4) ShowRecipes(db);
//        else { std::cout << "제작 공방을 종료합니다.\n"; return; }
//    }
//}
//
//// ────────────────────────────────────────────────────────────
//// 포션: "alchemy" 테이블 사용, 수량 1~10
//// ────────────────────────────────────────────────────────────
//void Workshop::CraftPotion(Inventory& inv, const ItemDB& db)
//{
//    auto recipes = db.getRecipes("alchemy");      // 여러 레시피를 지원
//    if (recipes.empty()) { std::cout << "레시피가 없습니다.\n"; return; }
//
//    // 하나만 있다고 가정해도 되고, 여러 개면 선택
//    std::cout << "\n[포션 제작]\n";
//    for (size_t i = 0; i < recipes.size(); ++i) {
//        const auto& r = recipes[i];
//        const std::string outName = r.outputs.empty() ? r.id : r.outputs.front().getName();
//        std::cout << (i + 1) << ") " << outName << "\n";
//    }
//    std::cout << recipes.size() + 1 << ") 뒤로가기\n선택: ";
//    int sel = AskIntInRange("", 1, (int)recipes.size() + 1);
//    if (sel == (int)recipes.size() + 1) return;
//
//    const auto& pick = recipes[sel - 1];
//
//    int want = AskIntInRange("몇 개 제작할까요? (1~10) ", 1, 10);
//
//    auto need = CountByName(pick.inputs);
//    // 필요량을 want 배수로
//    for (auto& kv : need) kv.second *= want;
//
//    // 보유/필요 출력
//    std::cout << "\n[필요 재료]\n";
//    bool enough = true;
//    for (auto& kv : need) {
//        int own = GetOwnedCount(inv, kv.first);
//        std::cout << " - " << kv.first << " : 필요 " << kv.second
//            << " / 보유 " << own << (own >= kv.second ? " (OK)\n" : " (부족)\n");
//        if (own < kv.second) enough = false;
//    }
//    if (!enough) { std::cout << "재료가 부족합니다.\n"; return; }
//
//    if (!AskYesNo("제작하시겠습니까? (Y/N) ")) return;
//
//    // 차감 후 지급
//    ConsumeInputs(inv, need);
//    GiveOutputs(inv, pick.outputs, want);
//
//    const std::string outName = pick.outputs.empty() ? pick.id : pick.outputs.front().getName();
//    std::cout << "[완료] " << outName << " x" << want << " 제작!\n";
//}
//
//// ────────────────────────────────────────────────────────────
//// 장비: "blacksmith" 테이블 사용, 1회 1개
//// ────────────────────────────────────────────────────────────
//void Workshop::CraftEquipment(Inventory& inv, const ItemDB& db)
//{
//    auto recipes = db.getRecipes("blacksmith");
//    if (recipes.empty()) { std::cout << "레시피가 없습니다.\n"; return; }
//
//    std::cout << "\n[장비 제작] (1회 1개)\n";
//    for (size_t i = 0; i < recipes.size(); ++i) {
//        const auto& r = recipes[i];
//        const std::string outName = r.outputs.empty() ? r.id : r.outputs.front().getName();
//        std::cout << (i + 1) << ") " << outName << "\n";
//    }
//    std::cout << recipes.size() + 1 << ") 뒤로가기\n선택: ";
//    int sel = AskIntInRange("", 1, (int)recipes.size() + 1);
//    if (sel == (int)recipes.size() + 1) return;
//
//    const auto& pick = recipes[sel - 1];
//    auto need = CountByName(pick.inputs);
//
//    std::cout << "\n[필요 재료]\n";
//    bool enough = true;
//    for (auto& kv : need) {
//        int own = GetOwnedCount(inv, kv.first);
//        std::cout << " - " << kv.first << " : 필요 " << kv.second
//            << " / 보유 " << own << (own >= kv.second ? " (OK)\n" : " (부족)\n");
//        if (own < kv.second) enough = false;
//    }
//    if (!enough) { std::cout << "재료가 부족합니다.\n"; return; }
//
//    if (!AskYesNo("제작하시겠습니까? (Y/N) ")) return;
//
//    ConsumeInputs(inv, need);
//    GiveOutputs(inv, pick.outputs, /*times=*/1);
//
//    const std::string outName = pick.outputs.empty() ? pick.id : pick.outputs.front().getName();
//    std::cout << "[완료] " << outName << " 제작!\n";
//}
//
//// ────────────────────────────────────────────────────────────
//// 악세사리: "accessory" 테이블 사용 (있을 때만)
//// ────────────────────────────────────────────────────────────
//void Workshop::CraftAccessory(Inventory& inv, const ItemDB& db)
//{
//    auto recipes = db.getRecipes("accessory");
//    if (recipes.empty()) { std::cout << "악세사리 레시피가 없습니다.\n"; return; }
//
//    std::cout << "\n[악세사리 제작] (1회 1개)\n";
//    for (size_t i = 0; i < recipes.size(); ++i) {
//        const auto& r = recipes[i];
//        const std::string outName = r.outputs.empty() ? r.id : r.outputs.front().getName();
//        std::cout << (i + 1) << ") " << outName << "\n";
//    }
//    std::cout << recipes.size() + 1 << ") 뒤로가기\n선택: ";
//    int sel = AskIntInRange("", 1, (int)recipes.size() + 1);
//    if (sel == (int)recipes.size() + 1) return;
//
//    const auto& pick = recipes[sel - 1];
//    auto need = CountByName(pick.inputs);
//
//    std::cout << "\n[필요 재료]\n";
//    bool enough = true;
//    for (auto& kv : need) {
//        int own = GetOwnedCount(inv, kv.first);
//        std::cout << " - " << kv.first << " : 필요 " << kv.second
//            << " / 보유 " << own << (own >= kv.second ? " (OK)\n" : " (부족)\n");
//        if (own < kv.second) enough = false;
//    }
//    if (!enough) { std::cout << "재료가 부족합니다.\n"; return; }
//
//    if (!AskYesNo("제작하시겠습니까? (Y/N) ")) return;
//
//    ConsumeInputs(inv, need);
//    GiveOutputs(inv, pick.outputs, /*times=*/1);
//
//    const std::string outName = pick.outputs.empty() ? pick.id : pick.outputs.front().getName();
//    std::cout << "[완료] " << outName << " 제작!\n";
//}
//
//// ────────────────────────────────────────────────────────────
//// 레시피 요약
//// ────────────────────────────────────────────────────────────
//void Workshop::ShowRecipes(const ItemDB& db) const
//{
//    auto show = [&](const char* title, const std::string& table) {
//        auto list = db.getRecipes(table);
//        if (list.empty()) return;
//        std::cout << "\n[" << title << "]\n";
//        for (auto& r : list) {
//            auto in = CountByName(r.inputs);
//            auto out = CountByName(r.outputs);
//            bool first = true;
//            for (auto& kv : in) {
//                if (!first) std::cout << " + ";
//                std::cout << kv.first << " x" << kv.second;
//                first = false;
//            }
//            std::cout << "  ->  ";
//            first = true;
//            for (auto& kv : out) {
//                if (!first) std::cout << " + ";
//                std::cout << kv.first << " x" << kv.second;
//                first = false;
//            }
//            std::cout << "\n";
//        }
//        };
//
//    std::cout << "\n=== 레시피 ===\n";
//    show("포션(연금술)", "alchemy");
//    show("장비(대장간)", "blacksmith");
//    show("악세사리", "accessory");
//}
//
//// ────────────────────────────────────────────────────────────
//// 유틸
//// ────────────────────────────────────────────────────────────
//int Workshop::AskIntInRange(const std::string& prompt, int minVal, int maxVal) const
//{
//    if (!prompt.empty()) std::cout << prompt;
//    int v;
//    while (true) {
//        if (std::cin >> v && v >= minVal && v <= maxVal) return v;
//        std::cout << "잘못 입력되었습니다. (" << minVal << " ~ " << maxVal << ")\n> ";
//        std::cin.clear();
//        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//    }
//}
//
//bool Workshop::AskYesNo(const std::string& prompt) const
//{
//    std::cout << prompt;
//    char c;
//    while (true) {
//        if (std::cin >> c) {
//            c = (char)std::tolower((unsigned char)c);
//            if (c == 'y') return true;
//            if (c == 'n') return false;
//        }
//        std::cout << "Y 또는 N 을 입력하세요: ";
//        std::cin.clear();
//        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//    }
//}
//
//std::unordered_map<std::string, int>
//Workshop::CountByName(const std::vector<Item>& items)
//{
//    std::unordered_map<std::string, int> m;
//    for (const auto& it : items) m[it.getName()]++;
//    return m;
//}
//
//int Workshop::GetOwnedCount(const Inventory& inv, const std::string& name)
//{
//    int idx = inv.findIndex(name);
//    if (idx == -1) return 0;
//    const Item* it = inv.findItem(idx);
//    return it ? it->getCount() : 0;
//}
//
//bool Workshop::HasAllInputs(const Inventory& inv,
//    const std::unordered_map<std::string, int>& req)
//{
//    for (auto& kv : req) {
//        if (GetOwnedCount(inv, kv.first) < kv.second) return false;
//    }
//    return true;
//}
//
//void Workshop::ConsumeInputs(Inventory& inv,
//    const std::unordered_map<std::string, int>& req)
//{
//    for (auto& kv : req) {
//        const std::string& name = kv.first;
//        int need = kv.second;
//
//        int idx = inv.findIndex(name);
//        if (idx == -1) continue; // 방어
//        Item* it = inv.findItem(idx);
//        if (!it) continue;
//
//        int left = it->getCount() - need;
//        if (left <= 0) {
//            inv.removeItem(idx);
//        }
//        else {
//            it->setCount(left);
//        }
//    }
//}
//
//void Workshop::GiveOutputs(Inventory& inv,
//    const std::vector<Item>& outputs,
//    int times)
//{
//    struct Acc { int price = 0; int count = 0; E_Type type = E_Type::Material; };
//    std::unordered_map<std::string, Acc> give;
//    for (const auto& it : outputs) {
//        auto& g = give[it.getName()];
//        g.price = it.getPrice();
//        g.type = it.getType();
//        g.count += 1;
//    }
//    for (auto& kv : give) {
//        const std::string& name = kv.first;
//        const int totalCount = kv.second.count * times;
//        inv.addItem(std::make_unique<Item>(name, kv.second.price, totalCount, kv.second.type));
//    }
//}
