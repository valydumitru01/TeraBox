#pragma once
#include "Bloque.h"
#include "StoneTile.h"
class StoneBlock : public Bloque
{
public:
	StoneBlock(float x, float y, Game* game);
	Tile* createTile(float x, float y, Game* game);
};

