#include "Weapon.h"
Weapon::Weapon(string filename,float x, float y,int damage, int attackSpeed, Game* game):Tool(filename,x,y,game) {
	this->attackSpeed = 10;
	this->damage = 10;
	this->attacks = true;
}