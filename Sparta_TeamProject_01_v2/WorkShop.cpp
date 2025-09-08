#include "Workshop.h"

void Workshop::Open(Inventory& inv) 
{
    while (true) {
        std::cout << "\n=== 제작 공방 ===\n"
            << "1. 물약 제작\n"
            << "2. 장비 제작\n"
            << "3. 레시피\n"
            << "4. 나가기\n"
            << "선택: ";

        int sel = AskIntInRange("", 1, 4);
        if (sel == 1)      CraftPotion(inv);
        else if (sel == 2) CraftEquipment(inv);
        else if (sel == 3) ShowRecipes();
        else if (sel == 4) {
            std::cout << "제작 공방을 종료합니다.\n";
            return;
        }
    }
}

void Workshop::CraftPotion(Inventory& inv) 
{
    using namespace WIName;

    int want = AskIntInRange("몇 개 제작할까요? (1~10) ", 1, 10);

    int needBones = want * 4;
    if (!HasAllAndConsume(inv, { {GoblinBrokenBone, needBones} })) {
        std::cout << "재료가 부족합니다.\n";
        return;
    }

    inv.addItem(MakeHealthPotion(want));
    std::cout << "[완료] 체력 포션 x" << want << " 제작!\n";
}

void Workshop::CraftEquipment(Inventory& inv) 
{
    using namespace WIName;

    std::cout << "\n[장비 제작] (1회 1개만 제작 가능)\n"
        << "1) " << JaksenSword << "\n"
        << "2) " << OrcRing << "\n"
        << "3) " << CeramicGloves << "\n"
        << "4) 뒤로가기\n"
        << "선택: ";

    int sel = AskIntInRange("", 1, 4);
    if (sel == 4) return;

    switch (sel) 
    {
    case 1:
        if (!HasAllAndConsume(inv, {
                {GoblinBrokenBone, 8},
                {RustyGreatsword, 1}
            })) {
            std::cout << "재료가 부족합니다.\n";
            return;
        }
        inv.addItem(MakeJaksenSword());
        std::cout << "[완료] 작센 소드 제작!\n";
        break;

    case 2:
        if (!HasAllAndConsume(inv, {
                {BrokenOrcRing, 2}
            })) {
            std::cout << "재료가 부족합니다.\n";
            return;
        }
        inv.addItem(MakeOrcRing());
        std::cout << "[완료] 오크의 반지 제작!\n";
        break;

    case 3:
        if (!HasAllAndConsume(inv, {
                {BrokenOrcGloves, 1}
            })) {
            std::cout << "재료가 부족합니다.\n";
            return;
        }
        inv.addItem(MakeCeramicGloves());
        std::cout << "[완료] 세라믹 장갑 제작!\n";
        break;
    }
}

void Workshop::ShowRecipes() const 
{
    using namespace WIName;
    std::cout << "\n=== 레시피 ===\n"
        << "[물약]\n"
        << " - 체력 포션 : 고블린의 부러진 뼈 4개 → 1개 (최대 10개)\n"
        << "[장비]\n"
        << " - 작센 소드 : 뼈 8개 + 녹슨 대검 1개\n"
        << " - 오크의 반지 : 부서진 오크의 반지 2개\n"
        << " - 세라믹 장갑 : 부서진 오크의 장갑 1개\n\n";
}

int Workshop::AskIntInRange(const std::string& prompt, int minVal, int maxVal) const 
{
    if (!prompt.empty()) std::cout << prompt;
    int v;
    while (true) {
        if (std::cin >> v && v >= minVal && v <= maxVal) {
            return v;
        }
        std::cout << "잘못 입력되었습니다. (" << minVal << " ~ " << maxVal << ")\n> ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

bool Workshop::HasAllAndConsume(
    Inventory& inv,
    const std::initializer_list<std::pair<std::string, int>>& needs) const
{
    for (const auto& p : needs) {
        const std::string& name = p.first;
        const int need = p.second;

        const int index = inv.findIndex(name);
        if (index == -1) return false;

        Item* it = inv.findItem(index);
        if (!it) return false;                // nullptr 방지
        if (it->getCount() < need) return false;
    }
    return true;
}

