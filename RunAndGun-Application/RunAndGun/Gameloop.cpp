#include "Gameloop.h"

#define RELEASEPOINTER(x) { if(x){ delete x; x = nullptr;} }

Gameloop::Gameloop() {
	window = nullptr;
	renderer = nullptr;

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
		window = SDL_CreateWindow("Run and Gun", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);
		if (window == NULL) {
			std::cerr << "Failed to Open Window: " << SDL_GetError() << std::endl;
			return false;
		}
	}
	if (IMG_Init(IMG_INIT_PNG) == 0) {
		std::cerr << "SDL_image Could not Initialize: " << SDL_GetError() << std::endl;
	}

	// Add Renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		std::cerr << "Failed to Create Renderer: " << SDL_GetError() << std::endl;
		return false;
	}

	// Setting all possible key press input to false
	for (int i = 0; i < 512; i++)
	{
		keyDown[i] = false;
	}

	tilemap = new Tilemap();
	if (!tilemap->init(this->renderer)) {
		std::cerr << "Failed to Initialize Tilemap: " << SDL_GetError() << std::endl;
		return false;
	}

	mouse = new Mouse(this->renderer);
	if (!mouse->init(this->renderer)) {
		std::cerr << "Failed to Initialize Mouse: " << SDL_GetError() << std::endl;
		return false;
	}

	player = new Player(this->mouse);
	if (!player->init(this->renderer)) {
		std::cerr << "Failed to Initialize Player: " << SDL_GetError() << std::endl;
		return false;
	}

	bulletManager = new BulletManager(this->player);
	if (!bulletManager->init(this->renderer)) {
		std::cerr << "Failed to Initialize BulletManager: " << SDL_GetError() << std::endl;
		return false;
	}
	
	return true;
}

/// <summary>
/// Function to process any user input to the game window
/// </summary>
bool Gameloop::ProcessInput() {

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
			break;
		case SDL_MOUSEBUTTONUP:
			break;
		default:
			break;
		}

	}

	player->processInput(keyDown);
	bulletManager->processInput(keyDown);
	mouse->processInput();
	
	return true;
}

/// <summary>
/// Function to Unload the Sprite assets allocated to memory
/// </summary>
bool Gameloop::UnloadAssets() {

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
	player->update();
	bulletManager->update();
	mouse->update();
}

/// <summary>
/// Function to draw the Game Enviroment to the window's surface.
/// </summary>
void Gameloop::Draw() {
	SDL_RenderClear(this->renderer);

	tilemap->draw(this->renderer);

	bulletManager->draw(this->renderer);
	player->draw(this->renderer);

	mouse->draw(this->renderer);

	SDL_RenderPresent(this->renderer);
	SDL_Delay(16);
}