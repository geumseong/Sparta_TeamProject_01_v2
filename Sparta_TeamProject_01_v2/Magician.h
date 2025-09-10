#pragma once
#include "Character.h"

class Magician : public Character
{
public:
	Magician();
	Magician(string nickName);

	void attack() override;
	void attack(Monster* monster) override;
	void levelUp() override;
};

//