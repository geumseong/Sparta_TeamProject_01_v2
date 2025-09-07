#include <iostream>
#include "Character.h"
#include "Inventory.h"
#include "Shop.h"

int main()
{
	Inventory inven(10000, 10);
	Character player("tester");
	Shop* shop = new Shop();
	shop->displayItems();

	shop->buyItem(0, inven);

	cout << "print inventory list" << endl;
	inven.printItemlist();
	

	//player.setHealth(50);
	//cout << player.getHealth() << endl;
	//player.displayStatus();

	//inven.addItem(make_unique<Item>("examplePotion", 100, 1, E_Type::Consumable)); // 아이템 추가 예시
	//int num = inven.findIndex("examplePotion"); // 이름을 통해 인벤토리 벡터의 인덱스 검색
	//inven.findItem(num)->addEffect<HealEffect>(50); // 인덱스를 통해 아이템 검색, addEffect매개변수는 힐량을 나타냄
	//inven.findItem(num)->useItem(player); // use를 사용해야 회복됨

}