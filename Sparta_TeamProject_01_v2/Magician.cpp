#include "Magician.h"
#include "drawtest.h"
#include <iostream>

Magician::Magician()
{
	jobName = "Magician";
	health += 50;
	maxHealth += 50;
	attackPower += 10;
}
//
Magician::Magician(string nickName)
{
    this->jobName = u8"마법사";
    setName(nickName);
    this->level = 1;
    this->health = 200;
    this->maxHealth = 200;
    this->mp = 120;
    this->maxMp = 120;
    this->attackPower = 38;
    this->defense = 6;
    this->attackSpeed = 1;
}

void Magician::attack()
{
    
}

void Magician::attack(Monster* monster)
{
    if (!monster) {
        RenderBoxFromCout(box_log.x, box_log.y, box_log.width, box_log.height, [&]() //로그 출력
        {
            cout << u8"공격 대상이 없습니다.\n";
        });

        return;
    }
    RenderBoxFromCout(box_log.x, box_log.y, box_log.width, box_log.height, [&]() //로그 출력
    {
        cout << "[" << name << u8"] 의 행동을 선택하세요.\n";
    });

    RenderBoxFromCout(box_choose.x, box_choose.y, box_choose.width, box_choose.height, [&]() // 선택지 출력
    {
        cout << u8"1. 일반 공격\n";
        cout << u8"2. 매직어택 (마나 10 소모)\n";
        cout << u8"3. 파이어볼 (마나 30 소모)\n";
    });

    setCursorPosition(2, 27); // 커서위치 초기화
    string choice;
    int finalDamage = 0;
    getline(cin, choice);

    if (choice == "1")
    {
        finalDamage = attackPower;
        RenderBoxFromCout(box_log.x, box_log.y, box_log.width, box_log.height, [&]() //로그 출력
        {
             cout << name << u8"이(가) 일반 공격을 합니다! (" << finalDamage << u8" 피해)" << endl;
        });
        
    }
    else if (choice == "2")
    {
        int skillCost = 10;
        if (mp >= skillCost) {
            mp -= skillCost;
            finalDamage = attackPower * 2;
            RenderBoxFromCout(box_log.x, box_log.y, box_log.width, box_log.height, [&]() //로그 출력
            {
                cout << name << u8"이(가) 매직어택을 사용합니다! (" << finalDamage << u8" 피해, MP -" << skillCost << ")" << endl;
            });

        }
        else {
            finalDamage = attackPower;
            RenderBoxFromCout(box_log.x, box_log.y, box_log.width, box_log.height, [&]() //로그 출력
            {
                cout << u8"MP가 부족하여 스킬을 사용할 수 없습니다! 대신 일반 공격을 합니다." << endl;
                cout << name << u8"이(가) 일반 공격을 합니다! (" << finalDamage << u8" 피해)" << endl;
            });
            
        }
    }
    else if (choice == "3")
    {
        int skillCost = 30;
        if (mp >= skillCost) {
            mp -= skillCost;
            finalDamage = (attackPower * 2) + (attackPower / 2);
            RenderBoxFromCout(box_log.x, box_log.y, box_log.width, box_log.height, [&]() //로그 출력
            {
                cout << name << u8"이(가) 파이어볼을 사용합니다! (" << finalDamage << u8" 피해, MP -" << skillCost << ")" << endl;
            });
            
        }
        else {
            finalDamage = attackPower;
            RenderBoxFromCout(box_log.x, box_log.y, box_log.width, box_log.height, [&]() //로그 출력
            {
                cout << u8"MP가 부족하여 스킬을 사용할 수 없습니다! 대신 일반 공격을 합니다." << endl;
                cout << name << u8"이(가) 일반 공격을 합니다! (" << finalDamage << u8" 피해)" << endl;
            });
            
        }
    }
    else {
        finalDamage = attackPower;
        RenderBoxFromCout(box_log.x, box_log.y, box_log.width, box_log.height, [&]() //로그 출력
        {
            cout << u8"잘못된 입력입니다. 일반 공격을 실행합니다." << endl;
            cout << name << u8"이(가) 일반 공격을 합니다! (" << finalDamage << u8" 피해)" << endl;
        });
        
    }
    RenderBoxFromCout(box_choose.x, box_choose.y, box_choose.width, box_choose.height, [&]() // 선택지 출력
        {
            setCursorPosition(2, 27); // 커서위치 초기화
            system("pause");
        });

    RenderBoxFromCout(box_log.x, box_log.y, box_log.width, box_log.height, [&]() //로그 출력
    {
        cout << monster->getName() << u8"에게 " << finalDamage << u8"의 데미지를 입혔습니다" << endl;
        monster->takeDamage(finalDamage);
        if (!monster->isDead()) {
            cout << u8"몬스터의 체력이 " << monster->getHealth() << u8" 가 남았습니다." << endl;
        }
        else {
            cout << u8"몬스터의 체력이 0 이 되었습니다." << endl;
            cout << u8"플레이어가 승리 하였습니다." << endl;
        }
    });
    RenderBoxFromCout(box_choose.x, box_choose.y, box_choose.width, box_choose.height, [&]() // 선택지 출력
        {
            setCursorPosition(2, 27); // 커서위치 초기화
            system("pause");
        });

    //int damage = finalDamage;


}

void Magician::levelUp()
{
    if (level < 11)
    {
        level++;
        health = (maxHealth + 70);
        maxHealth = (maxHealth + 70);
        mp = (maxMp + 70);
        maxMp = (maxMp + 70);
        attackPower = (attackPower + 8);
        experience = 0;
        defense = (defense + 5);
        attackSpeed = (attackSpeed + 5);
    }
    else
    {
        RenderBoxFromCout(box_log.x, box_log.y, box_log.width, box_log.height, [&]() //로그 출력
        {
            cout << u8"더 이상 레벨업을 할 수 없습니다." << endl;
        });
        
    }

}
