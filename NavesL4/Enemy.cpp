#include "Enemy.h"

Enemy::Enemy(string filename, float x, float y, int width, int heigth, Game* game)
	: Actor(filename, x, y, width, heigth, game) {


	lifeText = new Text(to_string(maxLife), x, y , game);
	damageText = new Text("0", x, y, game);
	
}

void Enemy::update() {

	if (hitTime > 0) {
		hitTime--;
	}
	// En el aire y movi�ndose, PASA a estar saltando
	if (onAir && state == game->stateMoving) {
		state = game->stateJumping;
	}
	// No est� en el aire y estaba saltando, PASA a moverse
	if (!onAir && state == game->stateJumping) {
		state = game->stateMoving;
	}
	
	lifeText->content = to_string(life);
	
	// Actualizar la animaci�n
	bool endAnimation = animation->update();

	if (collisionDown == true) {
		onAir = false;
	}
	else {
		onAir = true;
	}


	// Acabo la animaci�n, no sabemos cual
	if (endAnimation) {
		// Estaba muriendo
		if (state == game->stateDying) {
			state = game->stateDead;
		}

	}
	
	// Establecer orientaci�n
	if (vx > 0 && hitTime <= 0) {
		orientation = game->orientationRight;
	}
	if (vx < 0 && hitTime <= 0) {
		orientation = game->orientationLeft;
	}

	//Seleccion de animacion basada en estados
	
	if (state == game->stateMoving) {
		if (orientation == game->orientationRight) {
			animation = aMovingRight;
		}
		if (orientation == game->orientationLeft) {
			animation = aMovingLeft;
		}
	}
	if (state == game->stateDying) {
		vx = 0;
		if (orientation == game->orientationRight) {
			animation = aDyingRight;
		}
		if (orientation == game->orientationLeft) {
			animation = aDyingLeft;
		}
	}

	notDamaged = true;
	updateChild();


}



void Enemy::draw(float scrollX, float scrollY) {


	if (state != game->stateDying) {
		lifeText->draw(254 - (254 * life) / maxLife, (life * 254) / maxLife, 0);
		lifeText->x = x - scrollX;
		lifeText->y = y - scrollY - height;
		animation->draw(x - scrollX, y - scrollY);
		if (!notDamaged) {
			actualTimeOfShowDamageDone = timeOfShowDamageDone;
		}
		if (actualTimeOfShowDamageDone > 0) {
			damageText->content = to_string(damageJustDone);
			damageText->x = x - scrollX - width;
			damageText->y = y - scrollY - height;
			damageText->draw(120, 120, 0);
			actualTimeOfShowDamageDone--;
		}

	}
	else {
		lifeText->x = x - scrollX;
		lifeText->y = y - scrollY - height;
		lifeText->content = "DEAD!";
		lifeText->draw(255, 0, 0);
		animation->draw(x - scrollX, y - scrollY);
		vx = 0;
	}


	
}

void Enemy::jump() {
	if (!onAir) {
		vy = -12;
		onAir = true;
	}
}
void Enemy::recieveDamage(int damage) {
	notDamaged = false;
	damageJustDone = damage;
	this->life -= damage;
	if (life <= 0) {
		state = game->stateDying;
	}

}

