#pragma once
#include "Actor.h"
#include "Player.h"
class Arma : public Actor
{
public:
	Arma(string filename, float x, float y, Game* game);
	void show();
};

