#include "Zombie.h"

Zombie::Zombie(float x, float y, Game* game)
	: Enemy("res/Enemigos/Zombie/Zombie.png", x, y, 30, 30, game) {


	orientation = game->orientationRight;
	state = game->stateMoving;

	aDyingRight = new Animation("res/Enemigos/Zombie/Animacion-Zombi-Muerte-Dcha.png", width, height,
		400, 50, 6, 8, false, game);
	aDyingLeft = new Animation("res/Enemigos/Zombie/Animacion-Zombi-Muerte-Izda.png", width, height,
		400, 50, 6, 8, false, game);

	aMovingRight = new Animation("res/Enemigos/Zombie/Animacion-Zombi-Camina-Dcha.png", width, height,
		260, 65, 6, 4, true, game);
	aMovingLeft = new Animation("res/Enemigos/Zombie/Animacion-Zombi-Camina-Izda.png", width, height,
		260, 65, 6, 4, true, game);

	aIdleRight = new Animation("res/Enemigos/Zombie/Animacion-Zombi-Camina-Dcha.png", width, height,
		260, 65, 6, 4, true, game);
	aIdleLeft = new Animation("res/Enemigos/Zombie/Animacion-Zombi-Camina-Izda.png", width, height,
		260, 65, 6, 4, true, game);

	animation = aMovingRight;

	maxLife = 100;
	strenght = 20;
	life = maxLife;
	vx = 1;
	vxIntelligence = -1;
	vx = vxIntelligence;

}

void Zombie::updateChild() {
	// Establecer velocidad
	if (state != game->stateDying && state != game->stateJumping) {
		// no est� muerto y se ha quedado parado
		if (vx == 0) {
			if (!followPlayer) {
				vxIntelligence = vxIntelligence * -1;
				vx = vxIntelligence;
			}
			else {
				jump();
			}
		}
		if (outRight) {
			// mover hacia la izquierda vx tiene que ser negativa
			if (vxIntelligence > 0) {
				vxIntelligence = vxIntelligence * -1;
			}
			vx = vxIntelligence;
		}
		if (outLeft) {
			// mover hacia la derecha vx tiene que ser positiva
			if (vxIntelligence < 0) {
				vxIntelligence = vxIntelligence * -1;
			}
			vx = vxIntelligence;
		}

	}
	else {
		vx = 0;
	}
}