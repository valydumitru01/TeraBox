#pragma once

#include "Actor.h"
#include "Animation.h" 
#include "Text.h"

class Enemy : public Actor
{
public:
	Enemy(string filename, float x, float y, int width, int heigth, Game* game);
	void draw(float scrollX = 0, float scrollY = 0) override; // Va a sobrescribir
	void update();
	void jump();
	
	virtual void updateChild() {};
	float vxIntelligence;
	int state;
	bool onAir;
	int orientation;
	bool followPlayer = false;

	void recieveDamage(int damage); //Recibe daño
	int life;
	int maxLife=100;
	Text* lifeText;
	Text* damageText;
	bool notDamaged = true;
	int damageJustDone = 0;
	int timeOfShowDamageDone=15; //Tiempo que tarda en desaparecer en texto del daño hecho al enemigo
	int actualTimeOfShowDamageDone = 0;
	int strenght = 10;

	int hitTime = 0;
	int noJumpTime = 20;
	Animation* aDyingRight;
	Animation* aDyingLeft;
	Animation* aMovingRight;
	Animation* aMovingLeft;
	Animation* aIdleRight;
	Animation* aIdleLeft;
	Animation* animation; // Referencia a la animaci�n mostrada

};
