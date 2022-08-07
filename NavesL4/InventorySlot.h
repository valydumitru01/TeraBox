#pragma once
#include "Actor.h"
#include "Item.h"
#include "Bloque.h"
#include "Text.h"
class InventorySlot : public Actor
{
public:
    InventorySlot(float x, float y, Game* game, Item* container);
    Item* container;
    Text* quantityText;
    int quantity = 0;
    bool isSelected = false;

    void draw(float scrollX = 0, float scrollY = 0) override; // Va a sobrescribir
    void update();
    void obtainItem();
    bool loseItem();

    void select();
    void deselect();
};

