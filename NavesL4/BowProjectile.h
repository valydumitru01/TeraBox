#pragma once
#include "Projectile.h"
class BowProjectile :
    public Projectile
{
public:
    BowProjectile(float x, float y, int orientation, Game* game);
    void update() override;
};

