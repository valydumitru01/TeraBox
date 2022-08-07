#include "StoneTile.h"
StoneTile::StoneTile(float x, float y, Game* game) :Tile("res/Items/StoneBlock.png", x, y, game) {
	identifier = ItemEnum::StoneBlock;
	
}