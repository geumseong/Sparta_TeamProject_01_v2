#pragma once
#include "Character.h"

class Thief : public Character
{
public:
	Thief();
	Thief(string nickName);

	void attack() override;

};

