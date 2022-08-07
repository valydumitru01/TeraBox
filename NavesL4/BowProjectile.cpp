#include "BowProjectile.h"
BowProjectile::BowProjectile(float x, float y, int orientation, Game* game)
	: Projectile{ orientation == game->orientationRight ? Projectile("res/Items/Projectiles/Arrow_Projectile_Right.png",x,y,32,5,game)
	: Projectile("res/Items/Projectiles/Arrow_Projectile_Left.png", x, y, 32, 5, game) } {
	vx = 15;
	damageDone = 20;
}
void BowProjectile::update() {
	vy -= 0.5;
}