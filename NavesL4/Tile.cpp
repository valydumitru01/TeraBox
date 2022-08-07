#include "Tile.h"

Tile::Tile(string filename, float x, float y, Game* game)
	: Actor(filename, x, y, 30, 30, game) {
	//TODO: resolucion bloque 8x8
	name = filename.substr(10, filename.size());
	
}
