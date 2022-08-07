#include "ArmaItem.h"

ArmaItem::ArmaItem(string filename, float x, float y, Game* game)
	: Item(filename, x, y, game) {

	this->arma = new Arma(filename, x, y, game);
}

void ArmaItem::show(Player* player) {
	this->arma->show(player);
	
}