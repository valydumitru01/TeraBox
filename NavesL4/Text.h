#pragma once

#include "Game.h"

class Text
{
public:
	Text();
	Text(string content, float x, float y, Game* game);
	void draw(int r,int g, int b);
	void draw();
	string content; // texto
	int x;
	int y;
	int width;
	int height;
	Game* game; // referencia al juego
};

