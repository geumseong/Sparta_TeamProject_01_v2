#pragma once
#include "Character.h"

class Archer : public Character
{
public:
	Archer();
	Archer(string nickName);

	void attack() override;
	void attack(Monster* monster) override;
	void levelUp() override;
};

