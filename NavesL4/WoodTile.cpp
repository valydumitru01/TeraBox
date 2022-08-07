#include "WoodTile.h"
WoodTile::WoodTile(float x, float y, Game* game) :Tile("res/Items/WoodBlock.png", x, y, game) {
	identifier = ItemEnum::WoodBlock;
}