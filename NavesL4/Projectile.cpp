#include "Projectile.h"

Projectile::Projectile(string filename, float x, float y,int width,int height, Game* game) :
	Actor(filename, x, y, width, height, game) {
	vx = 9;
	vy = -1;

}
void Projectile::update() {
	vy -= 1;
}