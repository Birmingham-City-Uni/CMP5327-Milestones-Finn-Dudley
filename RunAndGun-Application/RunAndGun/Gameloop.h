#pragma once

#include <iostream>
#include <SDL.h>

#include "Tilemap.h"
#include "Mouse.cpp"
#include "GameObjects.h"

class Gameloop {

public:

private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	Tilemap* tilemap;
	Mouse* mouse;
	Player* player;

	bool keyDown[512];
	bool buttonDown[3];
public:

	Gameloop();
	~Gameloop();

	bool Init();

	bool ProcessInput();

	void Update();

	void Draw();

	bool UnloadAssets();

};


