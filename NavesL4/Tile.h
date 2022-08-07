#pragma once
#include "Actor.h"
#include "ItemEnum.h"

class Tile : public Actor
{
public:
	Tile(string filename, float x, float y, Game* game);
	string name;
	ItemEnum identifier= ItemEnum::Default;
	ItemEnum toolNeededForBreaking = ItemEnum::Pickaxe;
	int timeNeededToBreak=15;
	int currentBrokenTime = 0;
};

