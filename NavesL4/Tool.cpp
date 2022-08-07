#include "Tool.h"

Tool::Tool(string filename, float x, float y, Game* game)
	: Item(filename, x, y, game) {
	this->isStackable = false;
}
