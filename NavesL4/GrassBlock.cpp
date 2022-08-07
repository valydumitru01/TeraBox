#include "GrassBlock.h"

GrassBlock::GrassBlock(float x, float y, Game* game) : Bloque("res/Items/GrassBlock.png", x, y, game) {
	identifier = ItemEnum::GrassBlock;
}
Tile* GrassBlock::createTile(float x, float y, Game* game) {
	return new GrassTile(x, y, game);
	
}