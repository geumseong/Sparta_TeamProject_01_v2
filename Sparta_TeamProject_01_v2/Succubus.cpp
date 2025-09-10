//#include "Succubus.h"
// #include "AsciiArt.h"
//#include "Item.h"
//#include <iostream>
//#include <algorithm> // std::min 함수 사용
//
//Succubus::Succubus(const std::string& type, int level)
//    : Monster(level), type(type), isEnraged(false)
//{
// AsciiArt::printFromFile("succubus_art_hq.txt");
// AsciiArt::printFromFile("succubus_art.txt");
//    int baseHealth = 250;
//    int baseAttack = 25;
//    std::string namePrefix = "서큐버스";
//
//    this->baseExp = 250;
//    this->baseGold = 300;
//    this->attackSpeed = 16;
//
//    dropItem.push_back(Item("매혹적인 향수", 150, 1, E_Type::Accessory));
//    dropItem.push_back(Item("검은 박쥐 날개", 80, 1, E_Type::Material));
//    dropItem.push_back(Item("타락한 영혼석", 500, 1, E_Type::Material));
//
//    this->health = baseHealth + (this->level * 18);
//    this->attack = baseAttack + (this->level * 4);
//    this->maxHealth = this->health;
//    this->name = "Lv." + std::to_string(this->level) + " " + namePrefix;
//}
//
//int Succubus::performAction()
//{
//    // 2페이즈 진입 조건 확인
//    if (!isEnraged && this->health <= this->maxHealth / 2) {
// AsciiArt::printFromFile("succubus_phase2_hq.txt");
// AsciiArt::printFromFile("succubus_phase2.txt");
//        isEnraged = true;
//        std::cout << this->name << "의 눈빛이 변하며 주변에 사악한 기운이 감돕니다! (2페이즈 돌입!)" << std::endl;
//        this->attack = static_cast<int>(this->attack * 1.3); // 공격력 30% 증가
//    }
//
//    // 2페이즈일 경우 2회 공격
//    if (isEnraged) {
//        std::cout << this->name << "이(가) 연속으로 공격합니다!" << std::endl;
//        int totalDamage = lifeDrainAttack() + charmAttack();
//        return totalDamage;
//    }
//    // 1페이즈일 경우 기존 패턴
//    else {
//        if (rand() % 2 == 0) {
//            return lifeDrainAttack();
//        }
//        return charmAttack();
//    }
//}
//
//int Succubus::charmAttack()
//{
//    std::cout << this->name << "이(가) 매혹적인 채찍을 휘두릅니다!" << std::endl;
//    return this->attack;
//}
//
//int Succubus::lifeDrainAttack()
//{
//    int damage = static_cast<int>(this->attack * 0.8);
//    int healAmount = static_cast<int>(damage * 0.5);
//
//    this->health = std::min(this->maxHealth, this->health + healAmount);
//
//    std::cout << this->name << "이(가) 생명력을 흡수합니다! (HP " << healAmount << " 회복)" << std::endl;
//    return damage;
//}