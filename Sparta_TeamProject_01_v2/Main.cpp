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

	//inven.addItem(make_unique<Item>("examplePotion", 100, 1, E_Type::Consumable)); // ������ �߰� ����
	//int num = inven.findIndex("examplePotion"); // �̸��� ���� �κ��丮 ������ �ε��� �˻�
	//inven.findItem(num)->addEffect<HealEffect>(50); // �ε����� ���� ������ �˻�, addEffect�Ű������� ������ ��Ÿ��
	//inven.findItem(num)->useItem(player); // use�� ����ؾ� ȸ����

}