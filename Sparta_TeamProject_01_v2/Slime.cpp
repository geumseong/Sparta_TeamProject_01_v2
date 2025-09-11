//#include "Slime.h"
//#include "Item.h"
//#include <iostream>
//#include "AsciiArt.h"
// 
//Slime::Slime(const std::string& type, int level)
//    : Monster(level), type(type), turnCount(0)
//{
//    int baseHealth = 0;
//    int baseAttack = 0;
//    std::string namePrefix = "";
//
//    // '일반' 타입을 가장 먼저 설정
//    if (type == "일반")
//    { AsciiArt::printFromFile("slime_art.txt");
//
//        namePrefix = "슬라임";
//        baseHealth = 25;
//        baseAttack = 4;
//        this->baseExp = 8;
//        this->baseGold = 4;
//        this->attackSpeed = 8;
//        // [방어구 재료] 드롭
//        dropItem.push_back(Item("끈적한 젤리", 10, 1, E_Type::Material));
//    }
//    else if (type == "단단한")
//    { AsciiArt::printFromFile("slime_art.txt");
//        namePrefix = "단단한 슬라임";
//        baseHealth = 40;
//        baseAttack = 6;
//        this->baseExp = 15;
//        this->baseGold = 8;
//        this->attackSpeed = 5; // 단단해서 느림
//        // [무기 재료] 드롭
//        dropItem.push_back(Item("슬라임의 핵", 50, 1, E_Type::Material));
//    }
//    else if (type == "보석")
//    { AsciiArt::printFromFile("slime_art.txt");
//        namePrefix = "보석 슬라임";
//        baseHealth = 60;
//        baseAttack = 10;
//        this->baseExp = 50;
//        this->baseGold = 50;
//        this->attackSpeed = 12; // 희귀해서 빠름
//        // [악세사리 재료]와 [재화] 드롭
//        dropItem.push_back(Item("반짝이는 조각", 150, 1, E_Type::Material));
//        dropItem.push_back(Item("금화 주머니", 200, 1, E_Type::Material));
//    }
//
//    this->health = baseHealth + (this->level * 4);
//    this->attack = baseAttack + (this->level * 2);
//    this->maxHealth = this->health;
//    this->name = "Lv." + std::to_string(this->level) + " " + namePrefix;
//}
//
//// 슬라임의 행동 AI: 25% 확률로 방어, 75% 확률로 공격
//int Slime::performAction()
//{
//    turnCount++;
//    if (rand() % 4 == 0) // 4로 나눈 나머지가 0일 확률 (25%)
//    {
//        return hardenDefense();
//    }
//    else
//    {
//        return normalAttack();
//    }
//}
//
//// 개별 행동 함수
//int Slime::normalAttack()
//{
//    std::cout << this->name << "이(가) 몸통 박치기를 시도합니다!" << std::endl;
//    return this->attack;
//}
//
//int Slime::hardenDefense()
//{
//    std::cout << this->name << "이(가) 몸을 단단하게 굳혔습니다. (방어 행동)" << std::endl;
//    return 0;
//}