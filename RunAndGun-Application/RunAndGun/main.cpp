#include <iostream>
#include <future>

#include "Gameloop.h";
#include "Menu.h";


Gameloop* gameloop;


int main( int argc, char* args[]) {

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

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	return 0;
}