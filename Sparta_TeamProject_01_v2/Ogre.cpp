//#include "Ogre.h"
//#include "Item.h"
//#include <iostream>
//
//Ogre::Ogre(const std::string& type, int level)
//    : Monster(level), type(type)
//{
//    int baseHealth = 0;
//    int baseAttack = 0;
//    std::string namePrefix = "";
//
//    if (type == "일반") {
//        namePrefix = "오거";
//        baseHealth = 200;
//        baseAttack = 30;
//        this->baseExp = 120;
//        this->baseGold = 80;
//        this->attackSpeed = 3;
//        dropItem.push_back(Item("오거의 대퇴골", 50, 1, E_Type::Material));
//    }
//    else if (type == "투 헤드") {
//        namePrefix = "투 헤드 오거";
//        baseHealth = 250;
//        baseAttack = 25;
//        this->baseExp = 180;
//        this->baseGold = 110;
//        this->attackSpeed = 2;
//        dropItem.push_back(Item("오거의 쌍둥이 목걸이", 100, 1, E_Type::Accessory));
//    }
//    else if (type == "풀아머") {
//        namePrefix = "풀아머 오거";
//        baseHealth = 300;
//        baseAttack = 20;
//        this->baseExp = 200;
//        this->baseGold = 150;
//        this->attackSpeed = 1;
//        dropItem.push_back(Item("오염된 강철 주괴", 200, 1, E_Type::Material));
//        dropItem.push_back(Item("오거의 강화 철갑", 250, 1, E_Type::Material));
//    }
//
//    this->health = baseHealth + (this->level * 15);
//    this->attack = baseAttack + (this->level * 4);
//    this->maxHealth = this->health;
//    this->name = "Lv." + std::to_string(this->level) + " " + namePrefix;
//}
//
//int Ogre::performAction()
//{
//    if (type == "투 헤드" && rand() % 3 == 0) { // 33% 확률로 2번 공격
//        return doubleAttack();
//    }
//    return smashAttack();
//}
//
//int Ogre::smashAttack()
//{
//    std::cout << this->name << "이(가) 육중한 몽둥이를 휘두릅니다!" << std::endl;
//    return this->attack;
//}
//
//int Ogre::doubleAttack()
//{
//    int finalDamage = this->attack * 2;
//    std::cout << this->name << "의 머리 두 개가 각자 소리치며 동시에 공격합니다! (2회 공격!)" << std::endl;
//    return finalDamage;
//}