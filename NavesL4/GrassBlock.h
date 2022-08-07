#pragma once
#include "Bloque.h"
#include "GrassTile.h"
class GrassBlock : public Bloque
{
public:
	GrassBlock(float x, float y, Game* game);
	Tile* createTile(float x, float y, Game* game);
};

