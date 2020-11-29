#include <iostream>
#include <future>

#include "Gameloop.h";

Gameloop* gameloop;

bool quitting = false;

int main( int argc, char* args[])
{
	gameloop = new Gameloop();
	if (!gameloop->Init()) {
		return 1;
	}
	
	while (gameloop->ProcessInput()){
		gameloop->Update();
		gameloop->Draw();
	}
	
	if (!gameloop->UnloadAssets()) {
		return 1;
	}

	delete gameloop;

	IMG_Quit();
	SDL_Quit();
	return 0;
}
