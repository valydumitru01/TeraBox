#pragma once
#include "Item.h"
#include "Tile.h"
#include "GrassTile.h"
#include "Tool.h"
#include "Pickaxe.h"
class Bloque : public Item
{
public:
	Bloque(string filename, float x, float y, Game* game);
	void show() override;
	void hide();
	virtual Tile* createTile(float x, float y, Game* game) { return new GrassTile(x, y, game); };
	
};

