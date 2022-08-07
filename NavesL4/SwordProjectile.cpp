#include "SwordProjectile.h"
SwordProjectile::SwordProjectile(float x, float y, int orientation, Game* game) 
	:Projectile{ orientation == game->orientationRight ? Projectile("res/Items/Projectiles/Sword_Projectile_Right.png", x, y, 42, 19, game) 
	:Projectile("res/Items/Projectiles/Sword_Projectile_Left.png", x, y, 42, 19, game) } {
	vx = 2;
	maxLifeTime = 5;
	damageDone = 50;
}
