#pragma once
#include "Enemy.h"
class Zombie : public Enemy
{
public:
	Zombie(float x, float y, Game* game);
	void updateChild() override;
};


