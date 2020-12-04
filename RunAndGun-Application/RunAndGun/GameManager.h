#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include "BulletManager.h"
#include "GameObjects.h"

class GameManager {
public:

private:
	int score;
	
	Zombie enemies[];

public:
	GameManager();
	~GameManager();

	int getScore() {
		return score;
	}

	bool init();


private:

};