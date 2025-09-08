#pragma once
#include "Character.h"

class Archer : public Character
{
public:
	Archer();
	Archer(string nickName);

	void attack() override;

};

