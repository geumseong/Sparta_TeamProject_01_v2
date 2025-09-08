#pragma once
#include "Character.h"

class Warrior : public Character
{
public:
	Warrior();
	Warrior(string nickName);

	void attack() override;

};

