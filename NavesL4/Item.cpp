#include "Item.h"

Item::Item(string filename, float x, float y, Game* game) : Actor(filename, x, y, 30, 30, game) {
	
	name = filename.substr(10,filename.size());
}

bool Item::equals(Item i) {
	if (name._Equal(i.name))
		return true;
	return false;
}

void Item::update() {

}