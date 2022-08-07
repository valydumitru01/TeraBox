#include "Bow.h"
Bow::Bow(float x, float y, Game* game) :Weapon("res/Items/Bow.png", x, y, 10, 10, game)
{

	identifier = ItemEnum::Bow;
}
