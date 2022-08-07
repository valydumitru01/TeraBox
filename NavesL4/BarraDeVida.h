#pragma once

#include "Actor.h"
#include <vector>
#include "PuntoDeVida.h"

class BarraDeVida : public Actor
{
public:
	BarraDeVida(int maxLife,float x, float y, Game* game);
	void update(int damage);
	int maxLife;
	int actualLife;
	vector<PuntoDeVida*> puntosDeVida;
};
