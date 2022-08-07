#pragma once
#include "Bloque.h"
#include "WoodTile.h"
class WoodBlock : public Bloque
{
public:
	WoodBlock(float x, float y, Game* game);
	Tile* createTile(float x, float y, Game* game);
};

