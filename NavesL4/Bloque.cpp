#include "Bloque.h"


Bloque::Bloque(string filename, float x, float y, Game* game)
	: Item(filename, x, y, game) {
	isPlaceable = true;
}

void Bloque::show() {}