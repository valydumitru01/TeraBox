#include "DirtBlock.h"

DirtBlock::DirtBlock(float x, float y, Game* game) : Bloque("res/Items/DirtBlock.png",x,y,game) {
	identifier = ItemEnum::DirtBlock;
}
Tile* DirtBlock::createTile(float x, float y, Game* game) {
	return new DirtTile(x, y, game);
	
}