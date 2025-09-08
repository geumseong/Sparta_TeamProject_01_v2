#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <limits>
#include <memory>

// ---------- Safe input helpers ----------
int readInt() {
    int x;
    while (true) {
        if (std::cin >> x) return x;
        std::cout << "숫자를 입력하세요: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}
char readYesNo() {
    char c;
    while (true) {
        if (std::cin >> c && (c == 'y' || c == 'Y' || c == 'n' || c == 'N')) return c;
        std::cout << "(y/n)로 입력하세요: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

// ---------- UML: forward decl ----------
class Character;

// ---------- UML: Item (abstract) ----------
class Item {
public:
    virtual ~Item() {}
    virtual std::string getName() const = 0;
    virtual void use(Character& /*player*/) { /* not used here */ }
};

// 재료 정의
struct Ingredient { std::string name; int amount; };

// 제작 가능한 아이템(레시피 포함)
class CraftableItem : public Item {
    std::string name_;
    std::vector<Ingredient> recipe_;
public:
    enum class Category { Potion, Equipment };
private:
    Category category_;
public:
    CraftableItem(std::string n, std::vector<Ingredient> r, Category c)
        : name_(n), recipe_(r), category_(c) {
    }
    std::string getName() const { return name_; }
    const std::vector<Ingredient>& recipe() const { return recipe_; }
    Category category() const { return category_; }
};

// ---------- UML: Character ----------
class Character {
private:
    std::string name_;
    std::vector<std::unique_ptr<Item> > inventory_;     // 완성품
    std::unordered_map<std::string, int> materials_;     // 재료

public:
    explicit Character(std::string name) : name_(name) {}

    int materialCount(const std::string& m) const {
        std::unordered_map<std::string, int>::const_iterator it = materials_.find(m);
        return (it == materials_.end()) ? 0 : it->second;
    }
    bool consumeMaterial(const std::string& m, int cnt) {
        int have = materialCount(m);
        if (have < cnt) return false;
        materials_[m] -= cnt;
        return true;
    }
    void addMaterial(const std::string& m, int cnt) { materials_[m] += cnt; }
    void addItem(std::unique_ptr<Item> it) { inventory_.push_back(std::move(it)); }

    void displayInventory() const {
        std::cout << "\n[완성품 인벤토리]\n";
        if (inventory_.empty()) std::cout << "(비어 있음)\n";
        else {
            std::unordered_map<std::string, int> cnt;
            for (size_t i = 0; i < inventory_.size(); ++i) cnt[inventory_[i]->getName()]++;
            for (std::unordered_map<std::string, int>::const_iterator it = cnt.begin(); it != cnt.end(); ++it)
                std::cout << "- " << it->first << " : " << it->second << "\n";
        }
        std::cout << "\n[재료 보유량]\n";
        if (materials_.empty()) std::cout << "(비어 있음)\n";
        else {
            for (std::unordered_map<std::string, int>::const_iterator it = materials_.begin(); it != materials_.end(); ++it)
                std::cout << "- " << it->first << " : " << it->second << "\n";
        }
        std::cout << "----------------------------\n";
    }
};

// ---------- UML: Shop ----------
class Shop {
private:
    std::vector<std::unique_ptr<Item> > availableItems_;

    // 최대 제작 가능 개수 계산 (재료 기준 + 최대 10개 제한)
    int calcMaxCraft(const CraftableItem& ci, const Character& player) const {
        const std::vector<Ingredient>& rec = ci.recipe();
        long long maxCnt = (1LL << 30); // 충분히 큰 값으로 시작
        for (size_t i = 0; i < rec.size(); ++i) {
            int have = player.materialCount(rec[i].name);
            if (rec[i].amount <= 0) return 0;
            long long can = have / rec[i].amount;
            if (can < maxCnt) maxCnt = can;
        }
        if (maxCnt < 0) maxCnt = 0;
        if (maxCnt > 10) maxCnt = 10;  // 최대 10개 제한
        return (int)maxCnt;
    }

    void craftFlow(const CraftableItem& ci, Character& player) {
        // 최대 제작 가능 수량 안내
        int maxCraft = calcMaxCraft(ci, player);
        if (maxCraft == 0) { // ✅ 재료가 전혀 없거나 부족한 경우 즉시 안내
            std::cout << "재료가 부족합니다.\n";
            return;
        }
        std::cout << "[안내] 현재 재료로 최대 " << maxCraft << "개 제작 가능 (최대 10개 제한)\n";

        std::cout << "몇 개를 제작하시겠습니까? : ";
        int count = readInt();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (count <= 0) { std::cout << "1 이상 입력하세요.\n"; return; }
        if (count > maxCraft) { std::cout << "재료가 부족합니다.\n"; return; } // ✅ 초과 입력도 부족 처리

        std::cout << "\n[제작 확인] " << ci.getName() << " x" << count << "\n";
        bool enough = true;
        const std::vector<Ingredient>& rec = ci.recipe();
        for (size_t i = 0; i < rec.size(); ++i) {
            long long need = 1LL * rec[i].amount * count;
            int have = player.materialCount(rec[i].name);
            std::cout << " - " << rec[i].name << " : 보유 " << have << " / 필요 " << need << "\n";
            if (have < need) enough = false;
        }
        if (!enough) { std::cout << "재료가 부족합니다.\n"; return; } // ✅ 상세 검사도 같은 메시지

        std::cout << "정말 제작할까요? (y/n): ";
        char c = readYesNo();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (c == 'n' || c == 'N') { std::cout << "제작을 취소했습니다.\n"; return; }

        // 재료 차감
        for (size_t i = 0; i < rec.size(); ++i)
            player.consumeMaterial(rec[i].name, rec[i].amount * count);

        // 완성품 적재 (로컬 간단 아이템)
        struct SimpleItem : Item {
            std::string n;
            explicit SimpleItem(const std::string& s) : n(s) {}
            std::string getName() const { return n; }
        };
        for (int i = 0; i < count; i++) {
            std::unique_ptr<Item> p(new SimpleItem(ci.getName())); // C++11 방식
            player.addItem(std::move(p));
        }

        std::cout << "제작 완료: " << ci.getName() << " x" << count << "\n";
    }

public:
    void initDefaultBlueprints() {
        // 물약 (1: 체력 물약, 2: 마나 물약)
        availableItems_.push_back(
            std::unique_ptr<Item>(new CraftableItem(
                "체력 물약",
                std::vector<Ingredient>{ {"오크의 이빨", 1}, { "물병",1 }, { "실",1 } },
                CraftableItem::Category::Potion
            ))
        );
        availableItems_.push_back(
            std::unique_ptr<Item>(new CraftableItem(
                "마나 물약",
                std::vector<Ingredient>{ {"오크의 이빨", 1}, { "물병",1 }, { "실",1 } },
                CraftableItem::Category::Potion
            ))
        );

        // 장비 (1: 고블린의 몽둥이, 2: 오크의 목걸이)
        availableItems_.push_back(
            std::unique_ptr<Item>(new CraftableItem(
                "고블린의 몽둥이",
                std::vector<Ingredient>{ {"나무", 2}, { "실",1 } },
                CraftableItem::Category::Equipment
            ))
        );
        availableItems_.push_back(
            std::unique_ptr<Item>(new CraftableItem(
                "오크의 목걸이",
                std::vector<Ingredient>{ {"오크의 이빨", 3}, { "실",1 } },
                CraftableItem::Category::Equipment
            ))
        );
    }

    void displayItems() const {
        std::cout << "\n[물약 설계]\n";
        int num = 1;
        for (size_t i = 0; i < availableItems_.size(); ++i) {
            CraftableItem* ci = dynamic_cast<CraftableItem*>(availableItems_[i].get());
            if (!ci || ci->category() != CraftableItem::Category::Potion) continue;
            std::cout << num++ << ") " << ci->getName() << "\n";
        }
        std::cout << "\n[장비 설계]\n";
        num = 1;
        for (size_t i = 0; i < availableItems_.size(); ++i) {
            CraftableItem* ci = dynamic_cast<CraftableItem*>(availableItems_[i].get());
            if (!ci || ci->category() != CraftableItem::Category::Equipment) continue;
            std::cout << num++ << ") " << ci->getName() << "\n";
        }
    }

    // 카테고리별 번호로 제작
    void buyitem(int index, Character* player, CraftableItem::Category cat) {
        if (!player) return;
        int seen = 0;
        for (size_t i = 0; i < availableItems_.size(); ++i) {
            CraftableItem* ci = dynamic_cast<CraftableItem*>(availableItems_[i].get());
            if (!ci || ci->category() != cat) continue;
            ++seen;
            if (seen == index) {
                craftFlow(*ci, *player);
                return;
            }
        }
        std::cout << "잘못된 선택입니다.\n";
    }

    // UML 호환: (전역 인덱스용) buyItem(index, player)도 제공
    void buyItem(int index, Character* player) {
        if (!player) return;
        if (index < 1 || index >(int)availableItems_.size()) { std::cout << "잘못된 선택입니다.\n"; return; }
        CraftableItem* ci = dynamic_cast<CraftableItem*>(availableItems_[index - 1].get());
        if (!ci) { std::cout << "제작 가능한 아이템이 아닙니다.\n"; return; }
        craftFlow(*ci, *player);
    }
};

// ---------- UML: GameManager ----------
class GameManager {
private:
    Shop shop_;
public:
    GameManager() { shop_.initDefaultBlueprints(); }

    void visitShop(Character* player) {
        while (true) {
            std::cout << "\n[Shop]\n"
                << "1. 물약 설계 보기\n"
                << "2. 장비 설계 보기\n"
                << "3. 물약 제작\n"
                << "4. 장비 제작\n"
                << "5. 캐릭터 인벤토리 보기\n"
                << "6. 나가기\n"
                << "선택: ";
            int sel = readInt();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (sel == 1 || sel == 2) {
                shop_.displayItems();
            }
            else if (sel == 3) {
                std::cout << "\n--- 물약 제작 ---\n";
                std::cout << "1) 체력 물약\n";
                std::cout << "2) 마나 물약\n";
                std::cout << "번호 선택: ";
                int idx = readInt();
                shop_.buyitem(idx, player, CraftableItem::Category::Potion);
            }
            else if (sel == 4) {
                std::cout << "\n--- 장비 제작 ---\n";
                std::cout << "1) 고블린의 몽둥이\n";
                std::cout << "2) 오크의 목걸이\n";
                std::cout << "번호 선택: ";
                int idx = readInt();
                shop_.buyitem(idx, player, CraftableItem::Category::Equipment);
            }
            else if (sel == 5) {
                player->displayInventory();
            }
            else if (sel == 6) {
                std::cout << "Shop을 떠납니다.\n";
                break;
            }
            else {
                std::cout << "잘못된 선택입니다.\n";
            }
        }
    }
};

// ---------- Main ----------
int main() {
    Character player("Hero");
    GameManager gm;

    while (true) {
        std::cout << "\n메인 메뉴\n1. 상점 방문(제작)\n2. 종료\n선택: ";
        int sel = readInt();
        if (sel == 1) gm.visitShop(&player);
        else if (sel == 2) break;
        else std::cout << "잘못된 선택입니다.\n";
    }
    return 0;
}
