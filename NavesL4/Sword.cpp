#include "Sword.h"
Sword::Sword(float x, float y, Game* game):Weapon("res/Items/Sword.png", x, y, 10, 5, game)
{
	identifier = ItemEnum::Sword;
}
