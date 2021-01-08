#pragma once

#include <iostream>
#include <SDL.h>

#include "Menu.h"
#include "GameManager.h"
#include "UIManager.h"
#include "Tilemap.h"
#include "Mouse.cpp"
#include "GameObjects.h"
#include "BulletManager.h"

#define SCREEN_HEIGHT 1280
#define SCREEN_WIDTH 720

class Gameloop {

public:

private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	Menu* menu;
	GameManager* gameManager;
	UIManager* uiManager;


	Tilemap* tilemap;
	Mouse* mouse;
	BulletManager* bulletManager;
	Player* player;

	bool keyDown[512];
	bool buttonDown[4];
public:

	Gameloop();
	~Gameloop();

	bool Init();

	bool ProcessInput();

	void Update();

	void Draw();

	bool UnloadAssets();
};


