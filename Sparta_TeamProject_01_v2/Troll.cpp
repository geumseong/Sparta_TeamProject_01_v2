//#include "Troll.h"
//#include "AsciiArt.h"
//#include "Item.h"
//#include <iostream>
//#include <algorithm> // std::min �Լ� ���
//
//Troll::Troll(const std::string& type, int level)
//    : Monster(level), type(type), regenerationAmount(0), turnCount(0)
//{
//    int baseHealth = 0;
//    int baseAttack = 0;
//    std::string namePrefix = "";
//
//    // '�Ϲ�' Ÿ���� ���� ���� ����
//    if (type == "�Ϲ�") {
// AsciiArt::printFromFile("troll_art.txt");
//        namePrefix = "Ʈ��";
//        baseHealth = 120;
//        baseAttack = 18;
//        this->baseExp = 50;
//        this->baseGold = 30;
//        this->attackSpeed = 4;
//        this->regenerationAmount = 5; // �ϴ� 5 ȸ��
//        dropItem.push_back(Item("Ʈ���� ���� ����", 50, 1, E_Type::Material));
//    }
//    else if (type == "����ϴ�") {
// AsciiArt::printFromFile("troll_art.txt");
//        namePrefix = "����ϴ� Ʈ��";
//        baseHealth = 100;
//        baseAttack = 22;
//        this->baseExp = 80;
//        this->baseGold = 45;
//        this->attackSpeed = 6;
//        this->regenerationAmount = 15; // �ϴ� 15 ȸ��
//        dropItem.push_back(Item("Ʈ���� �ǰ� ��� �ິ", 120, 1, E_Type::Material));
//        dropItem.push_back(Item("Ʈ���� ����ϴ� ����", 300, 1, E_Type::Material));
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
//    // �ൿ ���� �� ü�� ���
//    this->health += this->regenerationAmount;
//    this->health = std::min(this->maxHealth, this->health); // �ִ� ü���� ���� �ʵ��� ����
//
//    std::cout << this->name << "�� ��ó�� �ٹ��Ÿ��� ȸ���˴ϴ�! (HP " << this->regenerationAmount << " ȸ��)" << std::endl;
//
//    return slamAttack();
//}
//
//int Troll::slamAttack()
//{
//    std::cout << this->name << "��(��) �Ŵ��� �ָ��� ����Ĩ�ϴ�!" << std::endl;
//    return this->attack;
//}