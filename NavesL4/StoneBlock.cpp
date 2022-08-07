#include "StoneBlock.h"

StoneBlock::StoneBlock(float x, float y, Game* game) :Bloque("res/Items/StoneBlock.png", x, y, game) {
	identifier = ItemEnum::StoneBlock;
}
Tile* StoneBlock::createTile(float x, float y, Game* game) {
	return new StoneTile(x, y, game);
}