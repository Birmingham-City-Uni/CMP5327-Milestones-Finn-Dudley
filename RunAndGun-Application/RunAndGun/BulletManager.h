#pragma once

#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>

#include "GameObjects.h"

class BulletManager {
public:

private:
	std::vector<Bullet> bullets;

	Player* player;

	const int FireTimer = 200;
	unsigned int lastFire = 0;

public:
	BulletManager(Player* _player);
	~BulletManager();

	bool init(SDL_Renderer* _renderer);
	void processInput(bool* keyDown);
	void update();
	void draw(SDL_Renderer* _renderer);

private:

};