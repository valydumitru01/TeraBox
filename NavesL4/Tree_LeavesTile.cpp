#include "Tree_LeavesTile.h"
Tree_LeavesTile::Tree_LeavesTile(float x, float y, Game* game):Tile("res/Items/LeavesBlock.png",x,y,game) {
	identifier = ItemEnum::Tree_LeavesBlock;
	isCollidable = false;
	toolNeededForBreaking = ItemEnum::Axe;
}