
#include <iostream>
#include <vector>
#include "Monster.h"
#include "Character.h"
#include "GameManager.h"
#include "Magician.h"
#include "Shop.h"
#include "Inventory.h"
#include "itemDB.h"
#include <Windows.h>
#include "UIManager.h"
#include "Workshop.h"
using namespace std;



int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    
    // ... (EnableVirtualTerminalProcessing() 등 초기 설정) ...

    UIManager uiManager; // UIManager 객체 생성

    // 타이틀 화면 호출
    uiManager.showTitleScreen();

    // 타이틀이 끝나면 화면을 지우고 메인 게임 로직 시작
    system("cls");
    std::cout << "게임의 다음 단계가 시작됩니다..." << std::endl;

    // ... (GameManager 생성 및 게임 시작) ...

    GameManager* Game = GameManager::getInstance();
    Character* Character_;
    Monster* currentMonster;
    Shop* shop_ = new Shop();

    WorkShop workshop;
    Game->inven = new Inventory(100, 100);
    //Inventory inven(100, 100);
    ItemDB db;

    std::string err;
    if (!db.loadFromFile("../itemDB/itemDB.json", &err)) {
        std::cerr << err << "\n";
        return 1;
    }//db 로딩

    //vector<Item> test = db.getShopTable("shop_potions"); //shop_potions로딩

    //for (auto& item : test)
    //{
    //    inven.addItem(move(item));
    //}
    //inven.printItemlist();
    Game->inven->addItem(move(Item(u8"슬라임의 끈적한 젤리", 100, 1, E_Type::Material)));
    Game->inven->addItem(move(Item(u8"슬라임의 반짝이는 조각", 100, 1, E_Type::Material)));
    //slime 000, 002
    cout << "ADD material" << endl;
    Game->inven->addItem(move(Item(u8"고블린의 부러진 뼈", 100, 1, E_Type::Material)));
    Game->inven->addItem(move(Item(u8"트롤의 재생하는 심장", 100, 1, E_Type::Material)));
    cout << "ADD material" << endl;
    //goblin 000 troll 002
    Game->inven->printItemlist();
    workshop.printrecipe(db, "weapon");
    workshop.CraftItem(db, *Game->inven, "weapon", 0 );
    workshop.CraftItem(db, *Game->inven, "weapon", 1);
    cout << "craft and print" << endl;
    Game->inven->printItemlist();


    string input;
    Game->outputLog(u8"** 캐릭터 이름을 정하십시오.");
    Game->inputLog(input);
    Character_ = new Magician(input);
    Game->character_ = Character_;
    Game->outputLog(u8"캐릭터가 생성되었습니다.");
    cout << "===================================" << endl;
    Game->updateState(GameManager::Battle);
    while (true)
    {
        switch (Game->currentState)
        {
        case GameManager::Start:    //Game 시작 State
            break;

        case GameManager::Resting:  //Game 휴식 State
            //            while (true)
            //            {
            //                Game->outputLog(
            //                    "** 다음 행선지를 선택하세요. \n"
            //                    "1. 던전 입장\n"    //GameManager::Battle로 State 변경 / 던전으로 이동.
            //                    "2. 상점 입장\n"    //GameManager::Shopping으로 State 변경 / 상점으로 이동.
            //                    "3. 제작소 입장\n"  //GameManager::Crafting으로 State 변경 / 제작소로 이동.
            //                    "4. 상태창\n"       //GameManager::Resting에 남아 있지만, 상태창 한 번 출력.
            //                    "5. 인벤토리 열기\n"  //GameManager::Resting에 남아 있지만, 인벤토리 한 번 출력.
            //                    "0. 끝내기"    //GameManager::End로 State 변경 / 게임을 끝냄.
            //                );
            //                // Resting에서 선택지의 결과 코드
            //#pragma region RestChoiceResults
            //                Game->inputLog(input);
            //                if (input == "1" || input == "던전 입장")
            //                {
            //                    Game->updateState(GameManager::Battle);
            //                    break;
            //                }
            //                else if (input == "2" || input == "상점 입장")
            //                {
            //                    Game->updateState(GameManager::Shopping);
            //                    break;
            //                }
            //                else if (input == "3" || input == "제작소 입장")
            //                {
            //                    Game->updateState(GameManager::Crafting);
            //                    break;
            //                }
            //                else if (input == "4" || input == "상태창")
            //                {
            //                    Game->outputLog("상태창 출력.");
            //                    Character_->displayStatus();
            //                    system("pause");
            //                    break;
            //                }
            //                else if (input == "5" || input == "인벤토리 열기")
            //                {
            //                    Game->outputLog("**인벤토리 목록:");
            //                    //Game->inventory_->printItemlist();
            //                    system("pause");
            //                    break;
            //                }
            //                else if (input == "0" || input == "끝내기")
            //                {
            //                    Game->updateState(GameManager::End);
            //                    break;
            //                }
            //                else
            //                {
            //                    Game->outputLog("잘못된 입력입니다.");
            //                }
            //#pragma endregion  RestChoiceResults
            //            }
            break;

        case GameManager::Shopping: //Game 상점/쇼핑 State
            shop_->openShop(db, Character_->getJobName());    // 상점 목록 생성
            while (true)
            {
                Game->outputLog(
                    u8"상점에 입장했습니다. 다음 행동을 선택하세요. "
                    u8"(" + to_string(Game->inven->getGold()) + u8"G 보유중)\n"
                    u8"1. 아이템 구매\n"
                    u8"2. 아이템 판매\n"
                    u8"3. 인벤토리 확인\n"
                    u8"4. 상태창 출력\n"
                    u8"5. 던전 입장"
                );
                Game->inputLog(input);

                //아이템 구매
#pragma region BuyItem
                if (input == "1" || input == "아이템 구매")
                {
                    while (true)
                    {
                        shop_->displayItems();    // 상점 목록 출력
                        Game->outputLog(u8"0. 뒤로가기");
                        Game->inputLog(input);          // 선택지 선택
                        if (input == "0" || input == "뒤로가기")
                        {
                            break;                      // 상점 입장 씬으로 복귀
                        }
                        int index = stoi(input);
                        if (index > 0 && index < shop_->getItemCount() + 1)
                        {
                            //open shop -> index 입력 후 -> showItem(능력치 보여주고) -> 인벤 들어가기
                            shop_->showItem(index - 1);   // 고른 아이템 정보 출력
                            Game->outputLog(u8"그래서, 사겠나?");
                            Game->outputLog(u8"1. 예 \n2. 아니오");
                            Game->inputLog(input);          // 아이템 구매 여부 선택
                            if (input == "1" || input == "예")
                            {
                                shop_->buyItem(index - 1, *Game->inven);
                                //break;                      // 상점 입장 씬으로 복귀
                            }
                            else if (input == "2" || input == "아니오")
                            {
                                // 아무것도 하지 않음
                            }
                            else
                            {
                                Game->outputLog(u8"잘못된 입력입니다.");
                            }
                        }
                        else
                        {
                            Game->outputLog(u8"잘못된 입력입니다.");
                        }
                    }
                }
#pragma endregion BuyItem
                // 아이템 판매
                else if (input == "2" || input == "아이템 판매")
                {
                    while (true)
                    {
                        Game->outputLog(u8"어떤 아이템을 파시겠나?");
                        Game->inven->printItemlist();
                        Game->outputLog(u8"0. 뒤로가기");
                        Game->inputLog(input);
                        if (input == "0" || input == "뒤로가기")
                        {
                            break;
                        }
                        int index = stoi(input);
                        if (index > 0 && index < Game->inven->getSize() + 1)
                        {
                            Item* choiceItem = Game->inven->findItem(index - 1);
                            Game->outputLog(
                                choiceItem->getName() + u8"의 판매가는 "
                                + to_string(static_cast<int>(choiceItem->getPrice() * 0.6)) + u8"G 이네.\n"
                                + "파실겐가?"
                            );
                            Game->outputLog(u8"1. 예 \n2. 아니오");
                            Game->inputLog(input);
                            if (input == "1" || input == "예")
                            {
                                shop_->sellItem(index - 1, *Game->inven);
                                //break;
                            }
                            else if (input == "2" || input == "아니오")
                            {
                                //아무것도 하지 않는다
                            }
                            else
                            {
                                Game->outputLog(u8"잘못된 입력입니다.");
                            }
                        }
                        else
                        {
                            Game->outputLog(u8"없는 아이템을 어찌 팔겠단 말인가?");
                        }
                    }

                }

                // 인벤토리 확인
                else if (input == "3" || input == "인벤토리 확인")
                {
                    Game->inven->printItemlist();
                    system("pause");
                }

                // 상태창 출력
                else if (input == "4" || input == "상태창 출력")
                {
                    Character_->displayStatus();
                    system("pause");
                }

                // 던전 입장
                else if (input == "5" || input == "던전 입장")
                {
                    Game->updateState(GameManager::Battle);
                    break;
                }
                else
                {
                    Game->outputLog(u8"잘못된 입력입니다.");
                }
            }
            break;

        case GameManager::Crafting:
            Game->outputLog(
                u8"제작소에 입장했습니다. 다음 행동을 선택하세요."
            );
            workshop.Open(db, *Game->inven);
            while(true)
            {
                Game->inputLog(input);
                if (input == "1" || input == "포션 제작")
                {
                    while (true)
                    {
                        Game->outputLog(u8"어떤 것을 제작하실 건가요?");
                        int size = workshop.printrecipe(db, "alchemy");
                        Game->outputLog(u8"0. 뒤로가기");
                        Game->inputLog(input);
                        int choice = stoi(input);
                        if (choice > 0 && choice <= size)
                        {
                            workshop.CraftItem(db, *Game->inven, "alchemy", choice);
                        }
                        else if (input == "0" || input == "뒤로가기")
                        {
                            break;
                        }
                        else
                        {
                            Game->outputLog(u8"잘못된 입력입니다.");
                        }
                    }
                }
                else if (input == "2" || input == "장비 제작")
                {

                }
                else if (input == "3" || input == "무기 제작")
                {

                }
                else if (input == "4" || input == "액세서리 제작")
                {

                }
                else if (input == "5" || input == "나가기")
                {

                }
                else
                {
                    Game->outputLog(u8"잘못된 입력입니다.");
                }
            }
            break;

        case GameManager::Battle:   //Game 전투/싸움 State
            Game->roundTracker++;
            currentMonster = Game->generateMonster();
            Game->outputLog(
                u8"던전에 입장했습니다. \n"
                u8"적 " + currentMonster->getName() + u8"와 조우!"
            );
            Game->battle(Character_, currentMonster);
            break;

        case GameManager::End:      //Game 끝.
            cout << u8"게임이 끝납니다..." << endl;
            /*for (int i = 0; i < Game->log.size(); i++)
            {
                cout << Game->log[i] << endl;
            }*/
            return 0;
        }
    }
}
