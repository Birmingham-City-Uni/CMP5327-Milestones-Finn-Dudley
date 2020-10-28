#include <iostream>

#include "Gameloop.h";

Gameloop* gameloop;

bool quitting = false;

int main( int argc, char* args[])
{
	gameloop = new Gameloop();
	if (!gameloop->Init()) {
		return 1;
	}
	
	gameloop->LoadAssests();

	while (!gameloop->quitting){
		gameloop->Update();
		gameloop->Draw();

		SDL_Delay(16); // Cap FPS to 60
	}
	
	gameloop->UnloadAssets();

	delete gameloop;
	SDL_Quit();

	return 0;
}
