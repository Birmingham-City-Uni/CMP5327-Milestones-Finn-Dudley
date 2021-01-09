#pragma once

#include <SDL.h>
#include <SDL_image.h>
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

	/// <summary>
	/// Gets the Game Score
	/// </summary>
	/// <returns>Returns the Current Score</returns>
	int getScore() {
		return score;
	}

	/// <summary>
	/// Gets the Current Game Wave
	/// </summary>
	/// <returns></returns>
	int getCurrentWave() {
		return currentWave;
	}

	/// <summary>
	/// Adds an amount to the score
	/// </summary>
	/// <param name="_scoreToAdd"> - The Amount to add to the score.</param>
	void addScore(int _scoreToAdd) {
		score += _scoreToAdd;
	}

	/// <summary>
	/// The GameManagers init Function
	/// </summary>
	/// <param name="_renderer"> - The Games Renderer</param>
	/// <returns>Returns True if all loads correctly, false if an error occurs.</returns>
	bool init(SDL_Renderer* _renderer);

	/// <summary>
	/// The GameManagers Update Function
	/// </summary>
	/// <param name="_renderer"> - The Games Renderer</param>
	/// <param name="_player"> - The Players Class</param>
	/// <param name="_collideableTiles"> - The vector of all collideable tiles on field.</param>
	void update(SDL_Renderer* _renderer, Player* _player, std::vector<Tile> _collideableTiles);

	/// <summary>
	/// The Draw Function for the GameManager
	/// </summary>
	/// <param name="_renderer"> - The Games Renderer</param>
	void draw(SDL_Renderer* _renderer);

	/// <summary>
	/// Cleans any Assets from GameManager
	/// </summary>
	void clean();

private:

	/// <summary>
	/// Grows the Enemy Pool
	/// </summary>
	/// <param name="_renderer"> - The Games Renderer</param>
	void growPool(SDL_Renderer* _renderer);

	/// <summary>
	/// Adds an Already instantiated enemy to the pool
	/// </summary>
	/// <param name="_zombie"> - The Enemy to add to the pool</param>
	void addToPool(Zombie _zombie);

	/// <summary>
	/// Spawns an Enemy in the given location
	/// </summary>
	/// <param name="_renderer"> - The Games Renderer</param>
	/// <param name="_x"> - The Desired X position of the Enemy</param>
	/// <param name="_y"> - The Desired Y position of the Enemy</param>
	void spawnEnemy(SDL_Renderer* _renderer, int _x, int _y);
};