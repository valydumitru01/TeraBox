#include "Tree_TrunkTile.h"
Tree_TrunkTile::Tree_TrunkTile(float x, float y, Game* game) :Tile("res/Items/TrunkBlock.png", x, y, game) {
	identifier = ItemEnum::Tree_TrunkBlock;
	isCollidable = false;
	toolNeededForBreaking = ItemEnum::Axe;
}