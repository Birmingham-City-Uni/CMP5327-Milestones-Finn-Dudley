#include "Gameloop.h"

#define RELEASEPOINTER(x) { if(x){ delete x; x = nullptr;} }

Gameloop::Gameloop() {

	window = nullptr;
	surface = nullptr;
	player = nullptr;

	quitting = false;
}

/// <summary>
/// Decontructor the Gameloop Class
/// </summary>
Gameloop::~Gameloop() {
	
	RELEASEPOINTER(player);
	RELEASEPOINTER(surface);

	SDL_DestroyWindow( window );
}

/// <summary>
/// Function to initialize the game window
/// </summary>
bool Gameloop::Init() {

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not Initialize: %s\n", SDL_GetError() );
	}
	else {
		// Create SDL Window
		window = SDL_CreateWindow("Run and Gun", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);
			if (window == NULL) {
				printf("Falied to Open window: %s\n", SDL_GetError() );
				return false;
			}
	}
	
	surface = SDL_GetWindowSurface( window );


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
			quitting = true;
			break;
		default:
			break;
		}

	}

	return true;
}

/// <summary>
/// Function to Load any sprite assets
/// </summary>
void Gameloop::LoadAssests() {

}

/// <summary>
/// Function to Unload the Sprite assets allocated to memory
/// </summary>
void Gameloop::UnloadAssets() {

}

/// <summary>
/// Function to Update the game enviroment
/// </summary>
void Gameloop::Update() {
	// Update the Scene Depending on User Input
	Gameloop::ProcessInput();
}

/// <summary>
/// Function to draw the Game Enviroment to the window's surface.
/// </summary>
void Gameloop::Draw() {
	// Background Draw Level

	// Player Draw Level

	// UI Draw Level
}