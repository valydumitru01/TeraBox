#pragma once
#include "Tool.h"
#include "Projectile.h"
class Weapon : public Tool {
public:
	Weapon(string filename,float x, float y,int damage,int attackSpeed, Game* game);
	int damage;
	int attackSpeed;
	Projectile* weaponProjectile;
};