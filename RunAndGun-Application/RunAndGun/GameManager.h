#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include "BulletManager.h"
#include "GameObjects.h"

class GameManager {
public:

private:
	int score;
	int currentWave;

	int lastSpawnTime;
	int newWaveTime;

	std::vector<Zombie> enemies;

public:
	GameManager();
	~GameManager();

	int getScore() {
		return score;
	}
	int getCurrentWave() {
		return currentWave;
	}

	bool init();

	void update(SDL_Renderer* _renderer, int _playerX, int _playerY);
	void draw(SDL_Renderer* _renderer);

	void clean();

private:

	void spawnEnemy(SDL_Renderer* _renderer, int _x, int _y) {
		Zombie enemy;
		if (!enemy.init(_renderer)) {
			std::cerr << "Zombie didn't Initialize Correctly: " << SDL_GetTicks() << std::endl;
		}
		enemy.setPosition(_x, _y);
		
		enemies.push_back(enemy);
	}

};