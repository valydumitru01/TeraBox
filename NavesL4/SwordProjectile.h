#pragma once
#include "Projectile.h"
class SwordProjectile :
    public Projectile
{
public:
    SwordProjectile(float x, float y, int orientation, Game* game);
    
};

