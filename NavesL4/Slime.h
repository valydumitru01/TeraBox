#pragma once
#include "Enemy.h"
class Slime : public Enemy
{
public:
	Slime(float x, float y, int width, int heigth, Game* game);
	void updateChild() override;
	int noJumpTime = 20;
};



