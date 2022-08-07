#pragma once

#include "Actor.h"


class Projectile : public Actor
{
public:
	Projectile(string filename, float x, float y,  int width, int height, Game* game);
	virtual void update();
	int maxLifeTime = 9999;
	int actualLifetime=0;
	int damageDone = 30;
};

