#pragma once

#include <iostream>
#include <SDL.h>

class Player;

class Gameloop {

public:
	bool quitting;
private:
	SDL_Window* window;
	SDL_Surface* surface;

	Player* player;

	enum KeyStates {
		LEFT,
		RIGHT,
		UP,
		DOWN,
		KEYSTATES_COUNT
	};

public:

	Gameloop();
	~Gameloop();

	bool Init();

	bool ProcessInput();

	void Update();

	void Draw();

	void LoadAssests();

	void UnloadAssets();

};


