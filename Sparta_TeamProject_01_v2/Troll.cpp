//#include "Troll.h"
//#include "Item.h"
//#include <iostream>
//#include <algorithm> // std::min 함수 사용
//#include "AsciiArt.h"
// 
//Troll::Troll(const std::string& type, int level)
//    : Monster(level), type(type)
//{
//    int baseHealth = 0;
//    int baseAttack = 0;
//    std::string namePrefix = "";
//
//    // '일반' 타입을 가장 먼저 설정
//    if (type == "일반") { AsciiArt::printFromFile("troll_art.txt");
//        namePrefix = "트롤";
//        baseHealth = 120;
//        baseAttack = 18;
//        this->baseExp = 50;
//        this->baseGold = 30;
//        this->attackSpeed = 4;
//        this->regenerationAmount = 5; // 턴당 5 회복
//        //dropItem.push_back(Item("트롤의 질긴 가죽", 50, 1, E_Type::Material));
//    }
//    else if (type == "재생하는") { AsciiArt::printFromFile("troll_art.txt");
//        namePrefix = "재생하는 트롤";
//        baseHealth = 100;
//        baseAttack = 22;
//        this->baseExp = 80;
//        this->baseGold = 45;
//        this->attackSpeed = 6;
//        this->regenerationAmount = 15; // 턴당 15 회복
//        //dropItem.push_back(Item("트롤의 피가 담긴 약병", 120, 1, E_Type::Material));
//        //dropItem.push_back(Item("트롤의 재생하는 심장", 300, 1, E_Type::Material));
//    }
//
//    this->health = baseHealth + (this->level * 12);
//    this->attack = baseAttack + (this->level * 3);
//    this->maxHealth = this->health;
//    this->name = "Lv." + std::to_string(this->level) + " " + namePrefix;
//}
//
//int Troll::performAction()
//{
//    // 행동 시작 전 체력 재생
//    this->health += this->regenerationAmount;
//    this->health = std::min(this->maxHealth, this->health); // 최대 체력을 넘지 않도록 보정
//
//    std::cout << this->name << "의 상처가 꾸물거리며 회복됩니다! (HP " << this->regenerationAmount << " 회복)" << std::endl;
//
//    return slamAttack();
//}
//
//int Troll::slamAttack()
//{
//    std::cout << this->name << "이(가) 거대한 주먹을 내리칩니다!" << std::endl;
//    return this->attack;
//}