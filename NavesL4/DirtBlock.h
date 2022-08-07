#pragma once
#include "Bloque.h"
#include "DirtTile.h"
class DirtBlock : public Bloque
{
public:
	DirtBlock(float x, float y, Game* game);
	Tile* createTile(float x, float y, Game* game);

};