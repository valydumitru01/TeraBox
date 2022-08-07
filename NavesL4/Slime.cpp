#include "Slime.h"

Slime::Slime(float x, float y, int width, int height, Game* game)
	: Enemy("res/Enemigos/Slime/slime.png", x, y, width, height, game) {

	orientation = game->orientationRight;
	state = game->stateMoving;

	aDyingRight = new Animation("res/Enemigos/Slime/slime_dying.png", width, height,
		140, 60, 15, 2, false, game);
	aDyingLeft = new Animation("res/Enemigos/Slime/slime_dying.png", width, height,
		140, 60, 15, 2, false, game);

	aMovingRight = new Animation("res/Enemigos/Slime/slime_salto_right.png", width, height,
		140, 60, 15, 2, true, game);
	aMovingLeft = new Animation("res/Enemigos/Slime/slime_salto_left.png", width, height,
		140, 60, 15, 2, true, game);

	aIdleRight = new Animation("res/Enemigos/Slime/slime_idle_right.png", width, height,
		140, 60, 15, 2, true, game);
	aIdleLeft = new Animation("res/Enemigos/Slime/slime_idle_left.png", width, height,
		140, 60, 15, 2, true, game);

	animation = aMovingRight;

	maxLife = 70;
	strenght = 10;
	life = maxLife;

	vx = 1;
	vxIntelligence = -1;
	vx = vxIntelligence;

}

void Slime::updateChild() {
	// Establecer velocidad
	if (state != game->stateDying && state != game->stateJumping) {
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
	if (vx == 0) {
		if (!followPlayer && noJumpTime > 0) {
			vx = vxIntelligence;
		}
	}
	if (state == game->stateMoving) {
		if (orientation == game->orientationRight) {
			if (noJumpTime > 0) {
				animation = aIdleRight;
				noJumpTime--;
				vx = 0;
			}
			else {
				jump();
				animation = aMovingRight;
				noJumpTime = 20;
				
			}
		}
		if (orientation == game->orientationLeft) {
			if (noJumpTime > 0) {
				animation = aIdleLeft;
				noJumpTime--;
				vx = 0;
			}
			else {
				jump();
				animation = aMovingLeft;
				noJumpTime = 20;
			}
		}
	}
	
}