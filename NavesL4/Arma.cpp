#include "Arma.h"
#include <iostream>

Arma::Arma(string filename, float x, float y, Game* game)
	: Actor(filename, x, y, 32, 32, game) {

	cout << "Arma: "+filename << endl;

}

void Arma::show(Player* player) {
	this->x = player->x + 10;
	this->y = player->y;
	cout << "Dibujando arma: x: "+this->x << endl;
	cout << "Player: x: " + player->x << endl;
	this->draw();
}
