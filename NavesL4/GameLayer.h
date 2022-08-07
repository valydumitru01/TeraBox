#pragma once

#include "Layer.h"
#include "Player.h"
#include "Background.h"

#include "Enemy.h"
#include "Zombie.h"
#include "Slime.h"
#include "Projectile.h"
#include "Text.h"
#include "Weapon.h"
#include "Sword.h"
#include "Bow.h"
#include "Tile.h"
#include "Tree_LeavesTile.h"
#include "Tree_TrunkTile.h"
#include "GrassTile.h"
#include "StoneTile.h"
#include "DirtTile.h"
#include "WoodTile.h"
#include "BedrockTile.h"
#include "Bloque.h"
#include "Audio.h"
#include "Space.h" // importar

#include <fstream> // Leer ficheros
#include <sstream> // Leer l�neas / String
#include <list>
#include "Inventory.h"
#include <map>
#include <windows.h>

class GameLayer : public Layer
{
public:
	GameLayer(Game* game);
	void init() override;
	void processControls() override;
	void update() override;
	void draw() override;
	void keysToControls(SDL_Event event);
	void mouseToControls(SDL_Event event); // USO DE MOUSE
	void loadMap(string name);
	void loadMapObject(char character, float x, float y);
	void calculateScroll();

	void loadBlockToTheWorld(Tile* tile, float x, float y);
	void removeBlockFromWorld(Tile* tile, int i, int j);
	void BreakBlock(Tile* tile);
	void PlaceBlock();

	Tile* getTileFromIndex(int i, int j);
	pair<int, int> getIndexFromCoor(int x, int y);
	pair<float, float> getCoorFromIndex(int i, int j);
	pair<float, float> getCoorFromIndexOfMouse(int i, int j);
	pair<int, int> getIndexFromCoorOfMouse(float x, float y);
	

	Actor* message;
	Space* space;
	Audio* audioBackground;
	
	Player* player;
	Background* background;
	Tile* selection;
	Actor* barraDeVida;
	Animation* breakingAnimation;
	
	bool pause;
	bool controlContinue = false;
	bool controlUse = false;
	bool playerReaches;
	bool changedBlockMouseOn = false;
	bool leftClickBeingPressed = false;

	int mapWidth;
	int mapHeight;
	int blockMiningSpeed = 10;
	int newEnemyTime = 0;
	int controlMoveY = 0;
	int controlMoveX = 0;
	int blockSize=30;//En pixeles

	float scrollX;
	float scrollY;


	list<Enemy*> enemies;
	list<Projectile*> projectiles;
	list<Item*> itemsOnTheGround;

	map < pair<int, int>, Tile* > mapaDeBloques;
	pair<float, float> mousePos;
	pair<int, int> indexOfBlockPos;
	pair<int, int> indexBlockBeingBroken;
	pair<float, float> startingPosition;
	
	
	

	Inventory* inventory;
};

