#include "Axe.h"
Axe::Axe(float x, float y, Game* game) :Tool("res/Items/Axe.png", x, y, game)
{
	allowMiningBlocks = true;
	identifier = ItemEnum::Axe;
}
