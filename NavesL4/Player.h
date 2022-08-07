#pragma once

#include "Actor.h"
#include "Projectile.h" 
#include "BowProjectile.h"
#include "SwordProjectile.h"
#include "Audio.h"
#include "Animation.h" // incluir animacion 
#include "Inventory.h"
#include "BarraDeVida.h"
class Player : public Actor
{
public:
	Player(float x, float y, Game* game);
	void use();
	Projectile* shootArrow();
	Projectile* cutWithSword();
	void stopUsing();
	void update();
	void jump();
	void moveX(float axis);
	void moveY(float axis);
	void draw(float scrollX = 0, float scrollY = 0) override; // Va a sobrescribir
	void recieveDamage(int damage);
	void reset();

	
	bool onAir;
	int orientation;
	int state;
	Animation* aIdleRight;
	Animation* aIdleLeft;
	Animation* aJumpingRight;
	Animation* aJumpingLeft;
	Animation* aRunningRight;
	Animation* aRunningLeft;
	Animation* aActionRight;
	Animation* aActionLeft;
	Animation* animation; // Referencia a la animaci�n mostrada
	Audio* audioShoot;
	BarraDeVida* vida;
	int shootCadence = 10;
	int shootTime = 0;
	int range = 100;
	int rangeEnemy = 400;
	Inventory* inventory;
	int hitTime = 0;
	const int invulnerabilityTimeConstant = 100;
	int invulnerableTime = 0;
	
	int life;
	int maxLife = 100;
	Text* lifeText;
	Text* damageText;
	bool notDamaged = true;
	int damageJustDone = 0;
	int timeOfShowDamageDone = 15; //Tiempo que tarda en desaparecer en texto del daño hecho al enemigo
	int actualTimeOfShowDamageDone = 0;
};

