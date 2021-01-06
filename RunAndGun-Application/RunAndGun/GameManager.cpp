#include "GameManager.h"

GameManager::GameManager() {
	this->score = 0;
	this->currentWave = 0;

	this->lastSpawnTime = 0;
	this->newWaveTime = 5000;
}

GameManager::~GameManager() {

}

bool GameManager::init() {

	return true;
}

void GameManager::update(SDL_Renderer* _renderer, int _playerX, int _playerY) {
	if (SDL_GetTicks() - lastSpawnTime > newWaveTime) {
		spawnEnemy(_renderer, 300, 300);

		currentWave++;
		std::cout << "Current Wave: " << currentWave << std::endl;
		lastSpawnTime = SDL_GetTicks();
	}

	for (auto& enemy : enemies) {
		enemy.rotateTowardsPoint(_playerX, _playerY);
		enemy.update();
	}
}

void GameManager::draw(SDL_Renderer* _renderer) {
	for (auto& enemy : enemies) enemy.draw(_renderer);
}

void GameManager::clean() {
	for (auto& enemy : enemies) enemy.clean();
}