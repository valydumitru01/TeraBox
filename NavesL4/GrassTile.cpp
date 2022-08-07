#include "GrassTile.h"
GrassTile::GrassTile(float x, float y, Game* game) :Tile("res/Items/GrassBlock.png", x, y, game) {
	identifier = ItemEnum::GrassBlock;
}