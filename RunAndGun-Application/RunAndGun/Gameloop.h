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

	/// <summary>
	/// The Games Main Init Function
	/// </summary>
	/// <returns>Returns true if all Initialized correctly.</returns>
	bool Init();

	/// <summary>
	/// Processes the SDL Input Queue.
	/// </summary>
	/// <returns>Returns false if the gameloop is to be cancelled</returns>
	bool ProcessInput();

	/// <summary>
	/// The Games Main Update Function
	/// </summary>
	void Update();

	/// <summary>
	/// The Games Main Draw Function
	/// </summary>
	void Draw();

	/// <summary>
	/// Unloads assets before closing the game.
	/// </summary>
	/// <returns>Returns false if an error occurs.</returns>
	bool UnloadAssets();
};


