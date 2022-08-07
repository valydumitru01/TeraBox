#include "BarraDeVida.h"
BarraDeVida::BarraDeVida(int maxLife,float x, float y, Game* game) :Actor("res/Jugador/Vida/Barra_De_Vida.png",x, y,36,333, game) {
	this->maxLife = maxLife;
	this->actualLife = maxLife;


	//Generar los puntos de vida
	PuntoDeVida* v = new PuntoDeVida(this->x, this->y, game);
	for (size_t i = 1; i < 11; i++)
	{
		puntosDeVida.push_back(new PuntoDeVida(this->x, this-> y + i * (v->height+3) - (height+30)/2 ,game));
	}


	
}
void BarraDeVida::update(int damage) {
	this->actualLife -= damage;
	int puntosDeVidaDisponibles =trunc((10 * this->actualLife) / this->maxLife);


	for (size_t i = puntosDeVidaDisponibles; i < puntosDeVida.size(); i++)
	{
		Actor* punto = puntosDeVida[i];
		punto->x = this->x;
		punto->y = this->y * punto->height;
	}
}