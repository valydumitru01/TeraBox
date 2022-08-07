#pragma once
#include "Item.h"
#include "Arma.h"
class ArmaItem : public Item
{
public:
	Arma* arma;
	ArmaItem(string filename, float x, float y, Game* game);
	void show() override;
	void hide();

};

