#include "Inventory.h"
#include "InventorySlot.h"
#include "Item.h"
#include "Sword.h"
#include "Bow.h"
#include "Pickaxe.h"
#include "Axe.h"
#include "DirtBlock.h"
#include "WoodBlock.h"
#include "StoneBlock.h"
#include <string>
#include <iostream>

Inventory::Inventory(float x, float y, Game* game)
	: Actor(x, y, 190, 360, game) {
	
	Item* ironShortsword = new Sword(x + 0 * 36, y,game);
	Item* bow = new Bow(x + 1 * 36, y, game);
	Item* pickaxe = new Pickaxe(x + 2 * 36, y, game);
	Item* axe = new Axe(x + 3 * 36, y, game);
	Item* dirtblock = new DirtBlock(x + 4 * 36, y, game);
	Item* wood = new WoodBlock(x + 5 * 36, y, game);
	Item* stone = new StoneBlock(x + 6 * 36, y, game);

	int numItems = 8;
	InventorySlot* slot;
	slot = new InventorySlot(x + 0 * 36, y, game, ironShortsword);
	hotBar.push_back(slot);
	slot = new InventorySlot(x + 1 * 36, y, game, bow);
	hotBar.push_back(slot);
	slot = new InventorySlot(x + 2 * 36, y, game, pickaxe);
	hotBar.push_back(slot);
	slot = new InventorySlot(x + 3 * 36, y, game, axe);
	hotBar.push_back(slot);
	slot = new InventorySlot(x + 4 * 36, y, game, dirtblock);
	hotBar.push_back(slot);
	slot = new InventorySlot(x + 5 * 36, y, game, wood);
	hotBar.push_back(slot);
	slot = new InventorySlot(x + 6 * 36, y, game, stone);
	hotBar.push_back(slot);

	hotBar[selectedSlot]->select();
	

}

void Inventory::update() {
	for (auto const& slot : hotBar) 
	{
		slot->update();
	}
}

void Inventory::draw(float scrollX, float scrollY) {

	for (auto const& slot : hotBar) {
		slot->draw();
	}
}

bool Inventory::isOpen() {
	return opened;
}

void Inventory::open() {
	opened = true;
}

void Inventory::close() {
	opened = false;
}

void Inventory::selectSlot(int n) {
	hotBar[selectedSlot]->deselect();
	hotBar[n]->select();
	selectedSlot = n;
}
Item* Inventory::getSelectedItem() {
	return hotBar[selectedSlot]->container;
}

InventorySlot* Inventory::getSelectedSlot()
{
	return hotBar[selectedSlot];
}

