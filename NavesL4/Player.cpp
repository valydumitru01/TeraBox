#include "Player.h"
#include "Inventory.h"
Player::Player(float x, float y, Game* game)
	: Actor("res/Jugador/jugador.png", x, y, 30, 30, game) {

	onAir = false;
	orientation = game->orientationRight;
	state = game->stateMoving;
	audioShoot = new Audio("res/efecto_disparo.wav", false);
	aActionRight = new Animation("res/Jugador/jugador_usando_derecha.png",
		width, height, 160, 40, 6, 4, true, game);
	aActionLeft = new Animation("res/Jugador/jugador_usando_izquierda.png",
		width, height, 160, 40, 6, 4, true, game);

	aJumpingRight = new Animation("res/Jugador/jugador_saltando_derecha.png",
		width, height, 160, 40, 6, 4, true, game);
	aJumpingLeft = new Animation("res/Jugador/jugador_saltando_izquierda.png",
		width, height, 160, 40, 6, 4, true, game);
	aIdleRight = new Animation("res/Jugador/jugador_idle_derecha.png", width, height,
		320, 40, 6, 8, true, game);
	aIdleLeft = new Animation("res/Jugador/jugador_idle_izquierda.png", width, height,
		320, 40, 6, 8, true, game);
	aRunningRight = new Animation("res/Jugador/jugador_corriendo_derecha.png", width, height,
		320, 40, 6, 8, true, game);
	aRunningLeft = new Animation("res/Jugador/jugador_corriendo_izquierda.png", width, height,
		320, 40, 6, 8, true, game);
	aRunningLeft = new Animation("res/Jugador/jugador_corriendo_izquierda.png", width, height,
		320, 40, 6, 8, true, game);
	vida = new BarraDeVida(maxLife, WIDTH*0.95, HEIGHT*0.7, game);
	maxLife = 100;
	life = maxLife;
	lifeText = new Text(to_string(maxLife), x, y , game);
	damageText = new Text("0", x, y, game);

	animation = aIdleRight;
	this->inventory = new Inventory(20, 20, game);
}

void Player::reset() {
	vida = new BarraDeVida(maxLife, WIDTH * 0.95, HEIGHT * 0.7, game);
	life = maxLife;
	notDamaged = false;
}
void Player::update() {
	if (invulnerableTime > 0) {
		invulnerableTime--;
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


	if (invulnerableTime > 0) {
		invulnerableTime--;
	}

	bool endAnimation = animation->update();

	if (collisionDown == true) {
		onAir = false;
	}
	else {
		onAir = true;
	}
	// Acabo la animaci�n, no sabemos cual
	if (endAnimation) {
		// Estaba disparando
		if (state == game->stateAction) {
			state = game->stateMoving;
		}
		
	}


	// Establecer orientaci�n
	if (vx > 0) {
		orientation = game->orientationRight;
	}
	if (vx < 0) {
		orientation = game->orientationLeft;
	}


	// Selecci�n de animaci�n basada en estados
	if (state == game->stateJumping) {
		if (orientation == game->orientationRight) {
			animation = aJumpingRight;
		}
		if (orientation == game->orientationLeft) {
			animation = aJumpingLeft;
		}
	}
	if (state == game->stateAction) {
		if (orientation == game->orientationRight) {
			animation = aActionRight;
		}
		if (orientation == game->orientationLeft) {
			animation = aActionLeft;
		}
	}
	if (state == game->stateMoving) {
		if (vx != 0) {
			if (orientation == game->orientationRight) {
				animation = aRunningRight;
			}
			if (orientation == game->orientationLeft) {
				animation = aRunningLeft;
			}
		}
		if (vx == 0) {
			if (orientation == game->orientationRight) {
				animation = aIdleRight;
			}
			if (orientation == game->orientationLeft) {
				animation = aIdleLeft;
			}
		}
	}
	if (shootTime > 0) {
		shootTime--;
	}

}
Projectile* Player::shootArrow() {

	if (shootTime == 0) {
		state = game->stateAction;
		audioShoot->play();
		shootTime = shootCadence;
		Projectile* projectile = new BowProjectile(x, y, orientation, game);
		if (orientation == game->orientationLeft) {
			projectile->vx = projectile->vx * -1; // Invertir
		}
		return projectile;
	}
	else {
		return NULL;
	}
}
Projectile* Player::cutWithSword() {

	if (shootTime == 0) {
		state = game->stateAction;
		audioShoot->play();
		shootTime = shootCadence;
		Projectile* projectile = NULL;
		if (orientation == game->orientationRight) {
			projectile = new SwordProjectile(x + width, y, orientation, game);
		}
		else if (orientation == game->orientationLeft) {
			projectile = new SwordProjectile(x - width, y, orientation, game);
		}
		
		if (orientation == game->orientationLeft) {
			projectile->vx = projectile->vx * -1; // Invertir
		}
		return projectile;


	}
	else {
		return NULL;
	}
}
void Player::moveX(float axis) {
	vx = axis * 3;
}

void Player::moveY(float axis) {
	vy = axis * 3;
}
void Player::stopUsing() {
	state = game->stateMoving;
}
void Player::use() {
	state = game->stateAction;
}

void Player::draw(float scrollX, float scrollY) {
	if (invulnerableTime == 0) {
		animation->draw(x - scrollX, y - scrollY);
	}
	else {
		if (invulnerableTime % 10 >= 0 && invulnerableTime % 10 <= 5) {
			animation->draw(x - scrollX, y - scrollY);
		}
	}
	vida->draw();
	for (PuntoDeVida* punto : vida->puntosDeVida) {
		punto->draw();
	}
	if (state != game->stateDying && state != game->stateDead) {
		lifeText->draw(254 - (254 * life) / maxLife, (life * 254) / maxLife, 0);
		lifeText->x = x - scrollX;
		lifeText->y = y - scrollY - height;
		if (!notDamaged) {
			actualTimeOfShowDamageDone = timeOfShowDamageDone;
		}
		cout << actualTimeOfShowDamageDone << endl;
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
	}
	notDamaged = true;
}

void Player::jump() {
	if (!onAir) {
		vy = -12;
		onAir = true;
	}
}

void Player::recieveDamage(int damage) {
	if (invulnerableTime == 0) {
		notDamaged = false;
		damageJustDone = damage;
		this->life -= damage;
		vida->update(damage);
		invulnerableTime = invulnerabilityTimeConstant;
	}
}
