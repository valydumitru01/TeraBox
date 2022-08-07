#include "WoodBlock.h"

WoodBlock::WoodBlock(float x, float y, Game* game) :Bloque("res/Items/WoodBlock.png", x, y, game) {
	identifier = ItemEnum::WoodBlock;
}
Tile* WoodBlock::createTile(float x, float y, Game* game) {
	return new WoodTile(x, y, game);
}