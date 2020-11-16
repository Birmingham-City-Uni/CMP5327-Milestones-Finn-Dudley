#pragma once

#include <iostream>
#include <SDL.h>

#include "GameCharacters.h"

class Gameloop {

public:

private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	Player* player;

	bool keyDown[512];
public:

	Gameloop();
	~Gameloop();

	bool Init();

	bool ProcessInput();

	void Update();

	void Draw();

	bool UnloadAssets();

};


