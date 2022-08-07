#pragma once
#include "Actor.h"
#include "InventorySlot.h"
#include <vector>
class Inventory : public Actor
{
public:
    Inventory(float x, float y, Game* game);
    //list<InventorySlot*> inventorySlots;
    vector<InventorySlot*> hotBar;
    void update();
    void draw(float scrollX = 0, float scrollY = 0) override; // Va a sobrescribir

    bool isOpen();
    
    void open();
    void close();
    void selectSlot(int n);
    Item* getSelectedItem();
    InventorySlot* getSelectedSlot();
private:
    bool opened = false;
    int selectedSlot = 0;
};

