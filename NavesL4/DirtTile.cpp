#include "DirtTile.h"
DirtTile::DirtTile(float x, float y, Game* game) :Tile("res/Items/DirtBlock.png", x, y, game) {
	identifier = ItemEnum::DirtBlock;
}