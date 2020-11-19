#pragma once

#include <iostream>
#include <SDL.h>

#include "Tilemap.h"
#include "Player.h"
#include "Mouse.cpp"

class Gameloop {

public:

private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	Tilemap* tilemap;
	Player* player;
	Mouse* mouse;

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


