#include "GameLayer.h"

GameLayer::GameLayer(Game* game)
	: Layer(game) {
	//llama al constructor del padre : Layer(renderer)
	//pause = true;
	message = new Actor("res/mensaje_como_jugar.png", WIDTH * 0.5, HEIGHT * 0.5,
		WIDTH, HEIGHT, game);

	//gamePad = SDL_GameControllerOpen(0);
	init();
}


void GameLayer::init() {

	space = new Space(1);
	scrollX = 0;
	scrollY = 0;
	mapaDeBloques.clear();
	selection = new Tile("res/Items/Seleccionado.png", 0.f, 0.f, game);
	breakingAnimation = new Animation("res/Items/Bloque_Rompiendose.png", blockSize, blockSize,
		blockSize * 3, blockSize, blockMiningSpeed, 3, false, game);
	audioBackground = new Audio("res/Sonido/musica_ambiente.mp3", true);
	audioBackground->play();

	background = new Background("res/fondo_2.png", WIDTH * 0.5, HEIGHT * 0.5, -1, game);
	

	enemies.clear(); // Vaciar por si reiniciamos el juego
	projectiles.clear(); // Vaciar por si reiniciamos el juego

	loadMap("res/Mapas/" + to_string(game->currentLevel) + ".txt");

}

void GameLayer::loadMap(string name) {
	char character;
	string line;
	ifstream streamFile(name.c_str());
	if (!streamFile.is_open()) {
		cout << "Falla abrir el fichero de mapa" << endl;
		return;
	}
	else {
		int numLines = 0;
		// Por l�nea
		for (int j = 0; getline(streamFile, line); j++) {
			numLines++;
			istringstream streamLine(line);
			mapWidth = line.length() * blockSize; // Ancho del mapa en pixels
			// Por car�cter (en cada l�nea)
			for (int i = 0; !streamLine.eof(); i++) {
				streamLine >> character; // Leer character 

				float x = blockSize / 2 + i * blockSize; // x central
				float y = blockSize + j * blockSize; // y suelo

				loadMapObject(character, x, y);
			}

		}
		mapHeight = numLines * blockSize; // Alto del mapa en pixels
	}
	streamFile.close();
}

void GameLayer::loadMapObject(char character, float x, float y)
{
	switch (character) {
	case 'Z': {
		Enemy* enemy = new Zombie(x, y, game);
		// modificaci�n para empezar a contar desde el suelo.
		enemy->y = enemy->y - enemy->height / 2;
		enemies.push_back(enemy);
		space->addDynamicActor(enemy);
		break;
	}
	case 'S': {
		Enemy* enemy = new Slime(x, y, 30, 30, game);
		// modificaci�n para empezar a contar desde el suelo.
		enemy->y = enemy->y - enemy->height / 2;
		enemies.push_back(enemy);
		space->addDynamicActor(enemy);
		break;
	}
	case '1': {
		player = new Player(x, y, game);
		// modificaci�n para empezar a contar desde el suelo.
		player->y = player->y - player->height / 2;
		startingPosition.first = player->x;
		startingPosition.second = player->y;
		space->addDynamicActor(player);
		break;
	}
	case '#': {
		Tile* tile = new DirtTile(x, y, game);

		loadBlockToTheWorld(tile, x, y);
		break;
	}
	case '[': {
		Tile* tile = new StoneTile(x, y, game);

		loadBlockToTheWorld(tile, x, y);
		break;
	}
	case 'M': {
		Tile* tile = new GrassTile(x, y, game);


		loadBlockToTheWorld(tile, x, y);
		break;
	}
	case 'T': {
		Tile* tile = new Tree_TrunkTile(x, y, game);

		loadBlockToTheWorld(tile, x, y);
		break;
	}
	case 'L': {
		Tile* tile = new Tree_LeavesTile(x, y, game);
		loadBlockToTheWorld(tile, x, y);
		break;
	}
	case 'B': {
		Tile* tile = new BedrockTile(x, y, game);
		loadBlockToTheWorld(tile, x, y);
		break;
	}
	}
}
Tile* GameLayer::getTileFromIndex(int i, int j) {

	if (mapaDeBloques.count({ i,j }) > 0)
		return mapaDeBloques.at({ i,j });
	else return NULL;
}
pair<int, int> GameLayer::getIndexFromCoor(int x, int y) {//Indices para la creacion del mapa
	//float x = 30 / 2 + i * 30; // x central
	//float y = 30 + j * 30; // y suelo

	int i = (int)trunc((x - blockSize / 2) / blockSize);
	int j = (int)trunc((y - blockSize) / blockSize);

	return { i + 1,j + 1 };
}

pair<float, float> GameLayer::getCoorFromIndex(int i, int j) {//Coordenadas de los bloques para el mapa, se colocan en el suelo.
	float x = blockSize / 2 + i * blockSize; // x central
	float y = blockSize + j * blockSize; // y suelo
	return { x,y };
}

void GameLayer::loadBlockToTheWorld(Tile* tile, float x, float y) {//Crea un bloque en una posicion
	tile->y = tile->y - tile->height / 2;// modificaci�n para empezar a contar desde el suelo.
	pair<int, int> pair = getIndexFromCoor(x, tile->y);
	if (mapaDeBloques.count(pair) == 0) {
		mapaDeBloques.insert({ pair,tile });
		space->addStaticActor(tile);
	}
}
void GameLayer::removeBlockFromWorld(Tile* tile, int i, int j) {//Elimina el bloque del mundo

	if (mapaDeBloques.count({ i,j }) >= 1) {
		mapaDeBloques.erase({ i,j });
		space->removeDynamicActor(tile);
		delete tile;
	}

}

void GameLayer::processControls() {
	// obtener controles
	SDL_Event event;
	while (SDL_PollEvent(&event)) {

		// Procesar teclas
		keysToControls(event);
		mouseToControls(event);

	}
	//procesar controles
	//procesar controles
	// Disparar
	if (controlContinue) {
		pause = false;
		controlContinue = false;
	}
	if (controlUse) {
		 player->use();

	}

	// Eje X
	if (controlMoveX > 0) {
		player->moveX(1);
	}
	else if (controlMoveX < 0) {
		player->moveX(-1);
	}
	else {
		player->moveX(0);
	}

	// Eje Y
	if (controlMoveY > 0) {

	}
	else if (controlMoveY < 0) {
		player->jump();
		if (player->hitTime <= 0) {
			//Saltan los enemigos que me persiguen
			for (auto const& enemy : enemies) {
				if (enemy->y == player->y && enemy->followPlayer && enemy->state != game->stateDying)
					enemy->jump();
			}
		}
	}
	else {

	}



}

void GameLayer::update() {
	if (pause) {
		return;
	}

	// Jugador se cae
	if (player->y > HEIGHT + 80) {
		init();
	}

	space->update();
	background->update();
	player->update();

	for (auto const& enemy : enemies) {
		enemy->update();
	}
	for (auto const& projectile : projectiles) {
		projectile->update();
	}

	//Colisiones jugador-item: recoger item
	list<Item*> pickUpItems;
	
	//ROMPER BLOQUES
	pair<int, int> index = getIndexFromCoorOfMouse(mousePos.first + scrollX, mousePos.second + scrollY);//Indice del bloque que vamos a romper
	Tile* tile = getTileFromIndex(index.first, index.second - 1);//Sacamos el tile para borrarlo
	indexBlockBeingBroken = index;
	if (changedBlockMouseOn) {
		breakingAnimation = new Animation("res/Items/Bloque_Rompiendose.png", blockSize, blockSize,
			blockSize * 3, blockSize, blockMiningSpeed, 3, false, game);
	}
	if (leftClickBeingPressed && playerReaches && tile != NULL && player->inventory->getSelectedSlot()->container->identifier == tile->toolNeededForBreaking) {
		bool blockIsBroken = breakingAnimation->update();
		if (blockIsBroken) {
			BreakBlock(tile);
			breakingAnimation = new Animation("res/Items/Bloque_Rompiendose.png", blockSize, blockSize,
				blockSize * 3, blockSize, blockMiningSpeed, 3, false, game);
		}
	}
	else {
		player->stopUsing();
	}

	//COLOCAR BLOQUES
	if (leftClickBeingPressed && playerReaches) {
		PlaceBlock();
		player->use();
	}
	else {
		player->stopUsing();
	}


	Projectile* launched=NULL;
	if (leftClickBeingPressed && player->inventory->getSelectedItem()->attacks) {
		if (Item* selected = dynamic_cast<Sword*>(player->inventory->getSelectedItem())) {
			launched = player->cutWithSword();
		}
		else if (Item* selected = dynamic_cast<Bow*>(player->inventory->getSelectedItem())) {
			launched = player->shootArrow();
		}
		if (launched != NULL) {
			space->addDynamicActor(launched);
			projectiles.push_back(launched);
		}
	}
	// Colisiones
	for (auto const& enemy : enemies) {
		if (player->isOverlap(enemy)) {
			//Salta hacia arriba y hacia atrás
			if (player->invulnerableTime <= 0 && enemy->state != game->stateDying) {
				controlMoveY = -1;
				player->hitTime = 10;
				if (player->x < enemy->x) {
					controlMoveX = -1;
				}
				else {
					controlMoveX = 1;
				}
			}
			player->recieveDamage(enemy->strenght);
			if (player->life <= 0) {
				player->x=startingPosition.first;
				player->y = startingPosition.second;
				
				player->reset();
				scrollX = 0;
				scrollY = 0;
				return;
			}
		}
	}
	if (player->hitTime == 1) {
		controlMoveX = 0;
		controlMoveY = 0;
	}

	// Colisiones , Enemy - Projectile

	list<Enemy*> deleteEnemies;
	list<Projectile*> deleteProjectiles;
	for (auto const& projectile : projectiles) {
		projectile->actualLifetime += 1;

		if (projectile->isInRender(scrollX, scrollY) == false || projectile->vx == 0) {
			bool pInList = std::find(deleteProjectiles.begin(),
				deleteProjectiles.end(),
				projectile) != deleteProjectiles.end();

			if (!pInList) {
				deleteProjectiles.push_back(projectile);
			}
		}

		if (projectile->actualLifetime == projectile->maxLifeTime) {
			bool pInList = std::find(deleteProjectiles.begin(),
				deleteProjectiles.end(),
				projectile) != deleteProjectiles.end();

			if (!pInList) {
				deleteProjectiles.push_back(projectile);
			}
		}
	}



	for (auto const& enemy : enemies) {
		for (auto const& projectile : projectiles) {
			if (enemy->isOverlap(projectile)) {
				//Salta hacia arriba y hacia atrás
				enemy->vy -= 10;
				
				if (player->x < enemy->x) {
					enemy->vx += 10;
				}
				else {
					enemy->vx -= 10;
				}

				bool pInList = std::find(deleteProjectiles.begin(),
					deleteProjectiles.end(),
					projectile) != deleteProjectiles.end();

				if (!pInList) {
					deleteProjectiles.push_back(projectile);
				}

				enemy->hitTime = 10;

				enemy->recieveDamage(projectile->damageDone);

				if (dynamic_cast<Slime*>(enemy)) {
					if (enemy->life <= 0 && enemy->width == 30) {
						Enemy* e = new Slime(enemy->x - 10, enemy->y, 15, 15, game);
							// modificaci�n para empezar a contar desde el suelo.
							e->y = e->y - e->height / 2;
							enemies.push_back(e);
							space->addDynamicActor(e);
							e->vy = -10;

							Enemy* e2 = new Slime(enemy->x + 10, enemy->y, 15, 15, game);
							// modificaci�n para empezar a contar desde el suelo.
							e2->y = e2->y - e2->height / 2;
							enemies.push_back(e2);
							space->addDynamicActor(e2);
							e2->vy = -10;
					}
				}

			


			}
		}
	}

	for (auto const& enemy : enemies) {
		//Compruebo si el enemigo está en el rango del jugador
		if (sqrt((enemy->x - player->x) * (enemy->x - player->x)
			+ (enemy->y - player->y) * (enemy->y - player->y)) < player->rangeEnemy) {
			enemy->followPlayer = true;
		}
		else {
			enemy->followPlayer = false;
		}

		if (enemy->followPlayer && enemy->hitTime==0) {
			if (enemy->noJumpTime <= 0) {
				enemy->vx = 0;
			}
			else {
				if (enemy->x < player->x) {
					enemy->vx = 1;
				}
				else {
					enemy->vx = -1;
				}
			}
			
		}
		
		//Compruebo si está muerto
		if (enemy->state == game->stateDead) {
			bool eInList = std::find(deleteEnemies.begin(),
				deleteEnemies.end(),
				enemy) != deleteEnemies.end();

			if (!eInList) {
				deleteEnemies.push_back(enemy);
			}
		}
	}

	for (auto const& delEnemy : deleteEnemies) {
		enemies.remove(delEnemy);
		space->removeDynamicActor(delEnemy);
	}
	deleteEnemies.clear();

	for (auto const& delProjectile : deleteProjectiles) {
		projectiles.remove(delProjectile);
		space->removeDynamicActor(delProjectile);
		delete delProjectile;
	}
	deleteProjectiles.clear();

	for (auto const& pickUpItem : pickUpItems) {
		space->removeDynamicActor(pickUpItem);
		delete pickUpItem;
	}
	pickUpItems.clear();

}


void GameLayer::calculateScroll() {
	// limite izquierda
	if (player->x > WIDTH * 0.5) {
		if (player->x - scrollX < WIDTH * 0.5) {
			scrollX = player->x - WIDTH * 0.5;
		}
	}

	// limite derecha
	if (player->x < mapWidth - WIDTH * 0.5) {
		if (player->x - scrollX > WIDTH * 0.5) {
			scrollX = player->x - WIDTH * 0.5;
		}
	}

	//limite arriba
	if (player->y > HEIGHT * 0.5) {
		if (player->y - scrollY < HEIGHT * 0.5) {
			scrollY = player->y - HEIGHT * 0.5;
		}
	}

	//limite abajo
	if (player->y < mapHeight - HEIGHT * 0.5) {
		if (player->y - scrollY > HEIGHT * 0.5) {
			scrollY = player->y - HEIGHT * 0.5;
		}
	}
}


void GameLayer::draw() {
	calculateScroll();

	background->draw();

	for (const auto& coorTile : mapaDeBloques) {
		Tile* tile = coorTile.second;
		tile->draw(scrollX, scrollY);
	}
	for (auto const& projectile : projectiles) {
		projectile->draw(scrollX, scrollY);
	}
	player->draw(scrollX, scrollY);
	for (auto const& enemy : enemies) {
		enemy->draw(scrollX, scrollY);
	}
	for (auto const& item : itemsOnTheGround) {
		item->draw(scrollX, scrollY);
	}

	player->inventory->draw();

	
	selection->draw(scrollX, scrollY);


	pair<float, float> coordsOfBreaking = getCoorFromIndexOfMouse(indexBlockBeingBroken.first, indexBlockBeingBroken.second);
	Tile* tile = getTileFromIndex(indexBlockBeingBroken.first, indexBlockBeingBroken.second - 1);
	if (leftClickBeingPressed && playerReaches && tile != NULL
		&& player->inventory->getSelectedSlot()->container->identifier == tile->toolNeededForBreaking) {
		breakingAnimation->draw(coordsOfBreaking.first - scrollX, coordsOfBreaking.second - scrollY);
	}
	SDL_RenderPresent(game->renderer); // Renderiza
}



void GameLayer::mouseToControls(SDL_Event event) {
	bool mouseDown = event.type == SDL_MOUSEBUTTONDOWN;
	bool mouseUp = event.type == SDL_MOUSEBUTTONUP;
	bool clickIsLeft = event.button.button == SDL_BUTTON_LEFT;
	bool mouseIsMoving = event.type == SDL_MOUSEMOTION;



	// Modificaci�n de coordenadas por posible escalado
	float motionX = event.motion.x / game->scaleLower;
	float motionY = event.motion.y / game->scaleLower;

	
	// Cada vez que se mueve
	if (mouseIsMoving) {
		int xMovMouse, yMovMouse;
		//Actualizar seleccion 
		SDL_GetMouseState(&xMovMouse, &yMovMouse);
		mousePos.first = xMovMouse;
		mousePos.second = yMovMouse;
		//cout <<"x raton: "<< xMovMouse + scrollX << endl;
		pair<int, int> indexs = getIndexFromCoorOfMouse(xMovMouse + scrollX, yMovMouse + scrollY);
		if ((int)indexs.first != (int)indexOfBlockPos.first) changedBlockMouseOn = true;
		else changedBlockMouseOn = false;

		indexOfBlockPos = indexs;
		//cout << "x index raton: " << indexs.first + scrollX << endl;
		pair<int, int> coords = getCoorFromIndexOfMouse(indexs.first, indexs.second);
		//cout << "pos x block raton: " << indexs.first + scrollX << endl;
		selection->x = coords.first;
		selection->y = coords.second;


	}
	

	

	//Calculamos el area en el que el jugador puede hacer click (circulo a su alreadedor de radio player->range
	
	
	//Actualiza si el jugador llega donde esta la posicion del raton
	playerReaches = sqrt((mousePos.first + scrollX - player->x) * (mousePos.first + scrollX - player->x) + (mousePos.second + scrollY - player->y) * (mousePos.second + scrollY - player->y)) < player->range;

	//Pone a true leftClickBeingPressed cuando el click izquierdo esta abajo y lo pone a false cuando esta arriba
	if (leftClickBeingPressed ||(mouseDown && clickIsLeft)) {
		leftClickBeingPressed = true;
		if (mouseUp == true && clickIsLeft) {
			leftClickBeingPressed = false;
		}
	}

}
void GameLayer::PlaceBlock() {
	Item* item = player->inventory->getSelectedItem();
	if (!item->isPlaceable) return;
	

	//COLOCAR ITEM (si es bloque)
	InventorySlot* slot = player->inventory->getSelectedSlot();
	Bloque* block = (Bloque*)item;
	pair<int, int> pos;
	pair<int, int> indexs = getIndexFromCoorOfMouse(mousePos.first + scrollX, mousePos.second + scrollY);
	int i = indexs.first;
	int j = indexs.second;
	bool noHayBloque = mapaDeBloques.count({ i,j - 1 }) == 0; //Buscamos cuantos bloques hay en la posicion donde hemos hecho click para saber si hay bloque 
	if (noHayBloque)
		if (slot->loseItem()) {
			pos = getCoorFromIndexOfMouse(i, j);
			Tile* tile = block->createTile(pos.first, pos.second, game);
			tile->y = tile->y + tile->height / 2;
			loadBlockToTheWorld(tile, pos.first, pos.second);
		}

	
}
void GameLayer::BreakBlock(Tile* tile) {
	Item* item = player->inventory->getSelectedItem();

	//ROMPER BLOQUE Y OBTENER
	ItemEnum brokenTileIdentifier = ItemEnum::Default;

	//Eliminar tile
	

	//cout << tile << endl;
	if(item->allowMiningBlocks)
	if (tile != NULL) {
		brokenTileIdentifier = tile->identifier;
		
		if (player->inventory->getSelectedSlot()->container->identifier == tile->toolNeededForBreaking) {//Si el identificador del item seleccionado del inventario es el mismo identificador del item necesario para romper el bloque, romperlo
			removeBlockFromWorld(tile, indexBlockBeingBroken.first, indexBlockBeingBroken.second - 1);
			//Obtener item
			for (auto const& slot : player->inventory->hotBar) {
				Item* item = slot->container;
				if (item->isPlaceable) {
					if (item->identifier == brokenTileIdentifier) {
						slot->obtainItem();
					}
					else if (item->identifier == ItemEnum::DirtBlock && brokenTileIdentifier == ItemEnum::GrassBlock) {//El bloque de grass y de dirt devuelve un bloque de tierra
						slot->obtainItem();
					}
					else if (item->identifier == ItemEnum::WoodBlock && brokenTileIdentifier == ItemEnum::Tree_TrunkBlock) {
						slot->obtainItem();
					}
				}

			}
		}
		
	}
}

pair<int, int> GameLayer::getIndexFromCoorOfMouse(float x, float y) { //Metodo que devuelve el indice del bloque dentro del mapa segun el click, llamar siempre que tenga que ver con clicks, romper bloque, seleccionar etc
	int i = (int)((x) / blockSize);
	int j = (int)((y) / blockSize);

	//cout << "x index raton: " << i << endl;
	return { i + 1,j + 1 };
}
pair<float, float> GameLayer::getCoorFromIndexOfMouse(int i, int j) {//Devuelve el la coordenada del centro del bloque de los indices creados por getIndexFromCoorOfMouse(), llamar solo para indices devueltos de ese metodo
	float x = -15 + i * blockSize; // x central
	float y = -15 + j * blockSize; // y suelo
	return { x,y };
}
void GameLayer::keysToControls(SDL_Event event) {
	if (event.type == SDL_KEYDOWN) {
		int code = event.key.keysym.sym;
		// Pulsada
		switch (code) {
		case SDLK_ESCAPE:
			game->loopActive = false;
			break;
		case SDLK_d: // derecha
			controlMoveX = 1;
			break;
		case SDLK_a: // izquierda
			controlMoveX = -1;
			break;
		case SDLK_w: // arriba
			controlMoveY = -1;
			break;
		case SDLK_s: // abajo
			controlMoveY = 1;
			break;
		case SDLK_1:
			player->inventory->selectSlot(0);
			break;
		case SDLK_2:
			player->inventory->selectSlot(1);
			break;
		case SDLK_3:
			player->inventory->selectSlot(2);
			break;
		case SDLK_4:
			player->inventory->selectSlot(3);
			break;
		case SDLK_5:
			player->inventory->selectSlot(4);
			break;
		case SDLK_6:
			player->inventory->selectSlot(5);
			break;
		case SDLK_7:
			player->inventory->selectSlot(6);
			break;
		case SDLK_8:
			player->inventory->selectSlot(7);
			break;
		}


	}
	if (event.type == SDL_KEYUP) {
		int code = event.key.keysym.sym;
		// Levantada
		switch (code) {
		case SDLK_d: // derecha
			if (controlMoveX == 1) {
				controlMoveX = 0;
			}
			break;
		case SDLK_a: // izquierda
			if (controlMoveX == -1) {
				controlMoveX = 0;
			}
			break;
		case SDLK_w: // arriba
			if (controlMoveY == -1) {
				controlMoveY = 0;
			}
			break;
		case SDLK_s: // abajo
			if (controlMoveY == 1) {
				controlMoveY = 0;
			}
			break;
		}

	}

}

