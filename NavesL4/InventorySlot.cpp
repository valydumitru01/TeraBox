#include "InventorySlot.h"

InventorySlot::InventorySlot(float x, float y, Game* game, Item* container)
	: Actor("res/Inventory/Inventory_Slot.png", x, y, 40, 40, game) {
	
	this->container = container;
	
	quantityText = new Text(std::to_string(quantity), x + 7, y + 7, game);
}

void InventorySlot::draw(float scrollX, float scrollY) {
	
	Actor::draw(); // llamar al metodo del hijo
	
	if (container != NULL)
	{
		container->draw();
		if(container->isStackable)
			quantityText->draw();
	}
}

void InventorySlot::update() {

}

void InventorySlot::obtainItem() {
	if (container != NULL) {
		quantity++;
		quantityText->content = to_string(quantity);
	}
}

bool InventorySlot::loseItem() {
	if (quantity > 0) {
		quantity--;
		quantityText->content = to_string(quantity);
		return true;
	}
	return false;
}

void InventorySlot::select() {
	isSelected = true;
	container->show(); //TODO: Item::show vacío, Bloque::show() y Arma::show() muestra el arma seleccionado en la mano del jugador
	texture = game->getTexture("res/Inventory/Inventory_Slot_Seleccionado.png");
}

void InventorySlot::deselect() {
	isSelected = false;
	//item->hide(); TODO
	texture = game->getTexture("res/Inventory/Inventory_Slot.png");
}


