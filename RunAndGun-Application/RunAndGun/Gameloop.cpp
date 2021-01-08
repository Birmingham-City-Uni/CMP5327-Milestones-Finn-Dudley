#include "Gameloop.h"

#define RELEASEPOINTER(x) { if(x){ delete x; x = nullptr;} }

Gameloop::Gameloop() {
	window = nullptr;
	renderer = nullptr;

	gameManager = nullptr;
	uiManager = nullptr;
	bulletManager = nullptr;
	tilemap = nullptr;
	player = nullptr;
	mouse = nullptr;
}

/// <summary>
/// Decontructor the Gameloop Class
/// </summary>
Gameloop::~Gameloop() {
	
	RELEASEPOINTER(player);
	RELEASEPOINTER(tilemap);
	RELEASEPOINTER(mouse);
}

/// <summary>
/// Function to initialize the game window
/// </summary>
bool Gameloop::Init() {

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "SDL Could not Initialize: " << SDL_GetError() << std::endl;
	}
	else {
		// Create SDL Window
		window = SDL_CreateWindow("Run and Gun", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_HEIGHT, SCREEN_WIDTH, SDL_WINDOW_SHOWN);
		if (window == NULL) {
			std::cerr << "Failed to Open Window: " << SDL_GetError() << std::endl;
			return false;
		}
	}
	if (IMG_Init(IMG_INIT_PNG) == 0) {
		std::cerr << "SDL_image Could not Initialize: " << SDL_GetError() << std::endl;
	}
	if (TTF_Init() == -1) {
		std::cerr << "SDL_ttf Could not Initialize: " << SDL_GetError() << std::endl;
	}

	// Add Renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		std::cerr << "Failed to Create Renderer: " << SDL_GetError() << std::endl;
		return false;
	}

	// Setting all possible key/button press input to false
	for (int i = 0; i < 512; i++){
		keyDown[i] = false;
	}
	for (int i = 0; i < 3; i++) {
		buttonDown[i] = false;
	}

	uiManager = new UIManager();
	if (!uiManager->init(this->renderer)) {
		std::cerr << "Failed to Initialize UIManager: " << SDL_GetError() << std::endl;
	}

	
	menu = new Menu();
	menu->init(this->renderer, this->uiManager);
	menu->draw(this->renderer);
	while (menu->processInput()) { }
	int selectedMap = menu->selectedMap;

	bulletManager = new BulletManager();
	if (!bulletManager->init(this->renderer)) {
		std::cerr << "Failed to Initialize Bullet Manager: " << SDL_GetError() << std::endl;
		return false;
	}

	gameManager = new GameManager(this->bulletManager);
	if (!gameManager->init(this->renderer)) {
		std::cerr << "Failed to Initialize GameManager: " << SDL_GetError() << std::endl;
	}

	tilemap = new Tilemap(selectedMap);
	if (!tilemap->init(this->renderer)) {
		std::cerr << "Failed to Initialize Tilemap: " << SDL_GetError() << std::endl;
		return false;
	}

	mouse = new Mouse(this->renderer);
	if (!mouse->init(this->renderer)) {
		std::cerr << "Failed to Initialize Mouse: " << SDL_GetError() << std::endl;
		return false;
	}

	player = new Player(this->mouse, this->bulletManager);
	if (!player->init(this->renderer)) {
		std::cerr << "Failed to Initialize Player: " << SDL_GetError() << std::endl;
		return false;
	}
	

	return true;
}

/// <summary>
/// Function to process any user input to the game window
/// </summary>
bool Gameloop::ProcessInput() {
	if (!player->visable) return false;

	SDL_Event e;

	while ( SDL_PollEvent(&e) != 0 ) {
		switch (e.type){
		case SDL_QUIT:
			return false;
			break;
		case SDL_KEYDOWN:
			if (e.key.keysym.scancode < 512) {
				keyDown[e.key.keysym.scancode] = true;
			}
			break;
		case SDL_KEYUP:
			if (e.key.keysym.scancode < 512) {
				keyDown[e.key.keysym.scancode] = false;
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (e.button.button < 4) {
				buttonDown[e.button.button] = true;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (e.button.button < 3) {
				buttonDown[e.button.button] = false;
			}
			break;
		default:
			break;
		}

	}

	player->processInput(keyDown, buttonDown);
	mouse->processInput();
	
	return true;
}

/// <summary>
/// Function to Unload the Sprite assets allocated to memory
/// </summary>
bool Gameloop::UnloadAssets() {

	gameManager->clean();
	uiManager->clean();
	bulletManager->clean();

	tilemap->clean();
	player->clean();
	mouse->clean();

	SDL_DestroyRenderer(renderer);
	renderer = nullptr;
	SDL_DestroyWindow( window );
	window = nullptr;

	return true;
}

/// <summary>
/// Function to Update the game enviroment
/// </summary>
void Gameloop::Update() {
	player->update(tilemap->collideableTiles);
	mouse->update();

	bulletManager->update();
	gameManager->update(this->renderer, this->player, tilemap->collideableTiles);
	uiManager->updateScoreText(this->renderer, gameManager->getScore());
}

/// <summary>
/// Function to draw the Game Enviroment to the window's surface.
/// </summary>
void Gameloop::Draw() {
	SDL_RenderClear(this->renderer);

	tilemap->draw(this->renderer);

	bulletManager->draw(this->renderer);
	gameManager->draw(this->renderer);
	player->draw(this->renderer);

	mouse->draw(this->renderer);

	uiManager->draw(this->renderer, player->getSelectedWeapon());

	SDL_RenderPresent(this->renderer);
	SDL_Delay(16);
}