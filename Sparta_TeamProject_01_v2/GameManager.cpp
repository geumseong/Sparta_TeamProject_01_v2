#include <iostream>
#include "GameManager.h"
#include <random>
#include <vector>
#include <string>
#include "Magician.h"
#include "Monster.h"
#include "Inventory.h"
#include "orc.h"
#include "goblin.h"
#include "Dragon.h"

#include "drawtest.h"

class Orc;

// Instances
GameManager* GameManager::instance_ = nullptr;

GameManager::GameManager()
{
    //outputLog(u8"--GameManager가 생성되었습니다--");
    this->currentState = Start;
}


// StateMachine
void GameManager::updateState(States stateName)
{
    string stateStr = "";
    switch (stateName)
    {
    case Start:    stateStr = "Start"; break;
    case Battle:   stateStr = "Battle"; break;
    case Shopping: stateStr = "Shopping"; break;
    case Resting:  stateStr = "Resting"; break;
    case End:      stateStr = "End"; break;
    case Crafting:  stateStr = "Crafting"; break;
    }

    //cout << "===================================" << endl;
    //string navDialogue = u8"[State 변경] → " + stateStr;
    //outputLog(navDialogue);

    this->currentState = stateName;
}

// cout print
void GameManager::outputLog(string navDialogue)
{
    cout << navDialogue << endl;
    //log.push_back(navDialogue);
}

//cin input
void GameManager::inputLog(string& input)
{
    //cin.ignore();
    //cin >> input;
    getline(cin, input);
    //log.push_back(input);
}

int generatorRandInt(int max)
{
    int rd = rand() % max + 1;
    return rd;
}

Monster* GameManager::generateMonster()
{
    int lvlModifier = 0;
    int rand = generatorRandInt(2);
    if (rand == 1)
    {
        lvlModifier = 0;
    }
    else if(rand == 2)
    {
        lvlModifier = 1;
    }
    if (roundTracker % GameManager::bossRound == 0)
    {
        //outputLog(u8"보스 몬스터 생성!!!");
        generateBossMonster(lvlModifier);
    }
    else
    {
        switch (generatorRandInt(2))
        {
            int rd;
        case 1:
            //outputLog(u8"오크 몬스터 생성!");
            rd = generatorRandInt(3);
            switch (rd)
            {
            case 1:     // 일반 오크 생성
                return new Orc(u8"일반", GameManager::character_->getLevel() + lvlModifier);
                break;
            case 2:     // 야만적인 오크 생성
                return new Orc(u8"야만적인", GameManager::character_->getLevel() + lvlModifier);
                break;
            case 3:     // 광전사 오크 생성
                return new Orc(u8"광전사", GameManager::character_->getLevel() + lvlModifier);
                break;
            }
        case 2:
            //outputLog(u8"고블린 몬스터 생성!");
            rd = generatorRandInt(4);
            switch (rd)
            {
            case 1:     // 일반 고블린 생성
                return new Goblin(u8"일반", GameManager::character_->getLevel() + lvlModifier);
                break;
            case 2:     // 겁쟁이 고블린 생성
                return new Goblin(u8"겁쟁이", GameManager::character_->getLevel() + lvlModifier);
                break;
            case 3:     // 건방진 고블린 생성
                return new Goblin(u8"건방진", GameManager::character_->getLevel() + lvlModifier);
                break;
            case 4:     // 사나운 고블린 생성
                return new Goblin(u8"사나운", GameManager::character_->getLevel() + lvlModifier);
                break;
            case 5:     // 재벌 고블린 생성
                return new Goblin(u8"재벌", GameManager::character_->getLevel() + lvlModifier);
                break;
            }
        }
    }
}

Monster* GameManager::generateBossMonster(int lvlModif)
{
    //outputLog(u8"드래곤 몬스터 생성!");
    return new Dragon(GameManager::character_->getLevel() + lvlModif);
    //return new Goblin(u8"재벌", 1);
}

void GameManager::battle(Character* player, Monster* currentMonster)
{
    if (player->getAttackSpeed() < currentMonster->getAttackSpeed())    //빠른 공속이 선빵
    {
        int beforeHealth = player->getHealth();

        RenderBoxFromCout(box_log.x, box_log.y, box_log.width, box_log.height, [&]() // 로그 출력
        {// 왼쪽 2
            instance_->outputLog(currentMonster->getName() + u8"의 선제공격!");
            player->takeCharacterDamage(currentMonster->performAction());   // 몬스터가 공격
            instance_->outputLog(
                u8"플레이어가 피해를 입었습니다.\n"
                + to_string(beforeHealth)
                + " => "
                + to_string(player->getHealth())
            );
        });
        

        RenderBoxFromCout(box_status.x, box_status.y, box_status.width, box_status.height, [&]() // 스탯 출력
        {
            player->displayStatus();
        });

        RenderBoxFromCout(box_enemystat.x, box_enemystat.y, box_enemystat.width, box_enemystat.height, [&]() // 적 스탯 출력
        {
                cout << currentMonster->getName() + u8"\n";
                cout << u8"HP : " << currentMonster->getHealth();
        });


        if (player->getHealth() <= 0)
        {
            instance_->updateState(GameManager::End);
        }
        RenderBoxFromCout(box_choose.x, box_choose.y, box_choose.width, box_choose.height, [&]() // 선택지 출력
        {
            setCursorPosition(2, 27); // 커서위치 초기화
            system("pause");
        });

    }
    while (!currentMonster->isDead() && player->getHealth() > 0)  // 어느 한쪽이라도 죽지 않는 한 진행
    {
        RenderBoxFromCout(box_log.x, box_log.y, box_log.width, box_log.height, [&]() {// 왼쪽 2
            // c.displayStatus(); // 기존 코드 그대로 호출
            instance_->outputLog(u8"플레이어의 턴입니다. \n");

        });
        
        RenderBoxFromCout(box_choose.x, box_choose.y, box_choose.width, box_choose.height, [&]()  // 선택지 출력
        {// 왼쪽 3

            instance_->outputLog(
                u8"\n"
                u8"1. 공격\n"
                u8"2. 아이템 사용\n"
            );
            
        });


        setCursorPosition(2, 27);// 커서위치 초기화
        string input;
        instance_->inputLog(input);
        if (input == "1" || input == "공격")
        {
            player->attack(currentMonster);     // 캐릭터가 몬스터에게 공격
            if (!currentMonster->isDead())      //몬스터가 죽지 않았다면 몬스터가 공격
            {
                int beforeHealth = player->getHealth();

                RenderBoxFromCout(box_log.x, box_log.y, box_log.width, box_log.height, [&]() //로그 출력
                {// 왼쪽 2
                    player->takeCharacterDamage(currentMonster->performAction());   // 몬스터가 공격
                    instance_->outputLog(
                        u8"플레이어가 피해를 입었습니다.\n"
                        + to_string(beforeHealth)
                        + " => "
                        + to_string(player->getHealth())
                    );
                });


                RenderBoxFromCout(box_status.x, box_status.y, box_status.width, box_status.height, [&]() // 스탯 출력
                { // 왼쪽 1
                    player->displayStatus();
                });

                system("pause");

                if (player->getHealth() <= 0)
                {
                    instance_->updateState(GameManager::End);
                    break;
                }
            }
            else        // 몬스터가 죽었다면
            {
                if (roundTracker == GameManager::victoryRound)
                {

                    RenderBoxFromCout(box_log.x, box_log.y, box_log.width, box_log.height, [&]() // 스탯 출력
                    {// 왼쪽 2
                        outputLog(u8"** Victory!!!!");
                    });

                    instance_->updateState(GameManager::End);
                    //break;
                    RenderBoxFromCout(box_choose.x, box_choose.y, box_choose.width, box_choose.height, [&]() // 선택지 출력
                    {
                        setCursorPosition(2, 27); // 커서위치 초기화
                        system("pause");
                    });
                }
                else
                {
                    // 보상 지급
                        //아이템 지급
                    RenderBoxFromCout(box_log.x, box_log.y, box_log.width, box_log.height, [&]() //로그 출력
                    {
                        outputLog(u8"아래의 아이템들을 획득했습니다.");
                        vector<Item> a = currentMonster->getDropItems();
                        for (int i = 0; i < a.size(); i++)
                        {
                            a[i].printInfo();
                            instance_->inven->addItem(move(Item(a[i].getName(), a[i].getPrice(), 1, E_Type::Material)));
                        }
                        //경험치 + 골드 지급               
                        outputLog(u8"경험치를 " + to_string(currentMonster->getBaseExp()) + u8"exp 만큼 획득했다!");
                        outputLog(u8"골드를 " + to_string(currentMonster->getBaseGold()) + u8"G 만큼 획득했다!)");

                        int beforeExp = character_->getExperience();
                        int beforeGold = inven->getGold();
                        int beforeLevel = character_->getLevel();
                        character_->setExperience(character_->getExperience() + currentMonster->getBaseExp());
                        inven->setGold(inven->getGold() + currentMonster->getBaseGold());
                        if (character_->getExperience() >= 100)
                        {
                            character_->levelUp();
                        }

                        outputLog(u8"Lvl. "
                            + to_string(beforeLevel) + " (" + to_string(beforeExp) + "/100) " + "==> Lvl. "
                            + to_string(character_->getLevel()) + " (" + to_string(character_->getExperience()) + "/100) "
                            + "\n"
                            + to_string(beforeGold) + "G ==> " + to_string(inven->getGold()) + "G"
                        );
                    });
                    RenderBoxFromCout(box_choose.x, box_choose.y, box_choose.width, box_choose.height, [&]() // 선택지 출력
                    {
                        setCursorPosition(2, 27); // 커서위치 초기화
                        system("pause");
                    });

                        



                    
                    instance_->updateState(GameManager::Shopping);
                    //break;
                }
                if (roundTracker % eventRound == 0)
                {
                    instance_->updateState(GameManager::Crafting);
                    //break;
                }
                delete currentMonster;  // 몬스터 메모리 해제
                break;
            }
        }
        else if (input == "2" || input == "아이템 사용")
        {

        }
        else
        {
            RenderBoxFromCout(box_log.x, box_log.y, box_log.width, box_log.height, [&]() //로그 출력
            {
                instance_->outputLog(u8"잘못된 입력입니다.");
            });


        }
    }
}
//
//
/*
void GameManager::visitShop(Character* player) {
}
void GameManager::displayInventory(Character* player) {
}
*/