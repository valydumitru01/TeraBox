#pragma once
#include "Actor.h"
#include "ItemEnum.h"
class Item : public Actor
{
public:
	Item(string filename, float x, float y, Game* game);
	string name;
	bool allowMiningBlocks=false;
	virtual bool equals(Item i);
	void update();
	virtual void show() {};
	void hide();
	bool isPlaceable=false;
	ItemEnum identifier = ItemEnum::Default;
	bool isStackable = true;
	bool attacks = false;
};

