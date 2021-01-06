#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <deque>

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
	std::deque<Zombie> enemyPool;

	BulletManager* bulletManager;
	SDL_Renderer* renderer;

public:
	GameManager(BulletManager* _bulletManager);
	~GameManager();

	int getScore() {
		return score;
	}
	int getCurrentWave() {
		return currentWave;
	}

	bool init(SDL_Renderer* _renderer);

	void update(SDL_Renderer* _renderer, int _playerX, int _playerY);
	void draw(SDL_Renderer* _renderer);

	void clean();

private:

	void growPool(SDL_Renderer* _renderer);
	void addToPool(Zombie _zombie);

	void spawnEnemy(SDL_Renderer* _renderer, int _x, int _y);
};