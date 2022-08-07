#include "Pickaxe.h"
Pickaxe::Pickaxe(float x, float y, Game* game) :Tool("res/Items/Pickaxe.png", x, y, game)
{
	allowMiningBlocks = true;
	identifier = ItemEnum::Pickaxe;
}
