#include "GameManager.h"

GameManager::GameManager(BulletManager* _bulletManager) : bulletManager(_bulletManager) {
	this->score = 0;
	this->currentWave = 0;

	this->lastSpawnTime = 0;
	this->newWaveTime = 5000;
}

GameManager::~GameManager() {

}

bool GameManager::init(SDL_Renderer* _renderer) {

	growPool(_renderer);
	spawnEnemy(_renderer, rand() % 1240, rand() % 680);

	return true;
}

void GameManager::update(SDL_Renderer* _renderer, int _playerX, int _playerY) {
	if (SDL_GetTicks() - lastSpawnTime > newWaveTime) {
		spawnEnemy(_renderer, rand() % 1240, rand() % 680);

		currentWave++;
		std::cout << "Current Wave: " << currentWave << std::endl;
		lastSpawnTime = SDL_GetTicks();
	}

	for (int i = 0; i < enemies.size(); i++) {
		if (enemies[i].visable) {
			enemies[i].rotateTowardsPoint(_playerX, _playerY);
			enemies[i].update(bulletManager);
		}
		else if (!enemies[i].visable) {
			addToPool(enemies[i]);
			enemies.erase(enemies.begin() + i);
			return;
		}
	}
}

void GameManager::draw(SDL_Renderer* _renderer) {
	for (auto& enemy : enemies) enemy.draw(_renderer);
}

void GameManager::clean() {
	for (auto& enemy : enemies) enemy.clean();
	
	if (!enemies.empty()) {
		for (auto enemy : enemies) enemy.clean();
		enemies.clear();
	}
	
	if (!enemyPool.empty()) {
		for (auto& enemy : enemies) enemy.clean();
		enemyPool.clear();
	}
}

void GameManager::growPool(SDL_Renderer* _renderer) {
	for (int i = 0; i < 5; i++) {
		Zombie enemy;
		if (!enemy.init(_renderer)) {
			std::cerr << "Zombie didn't Initialize Correctly: " << SDL_GetTicks() << std::endl;
		}

		addToPool(enemy);
	}
}

void GameManager::addToPool(Zombie _zombie) {
	_zombie.visable = false;

	_zombie.resetObjectHealth();
	_zombie.adjustHealthRect();

	enemyPool.push_back(_zombie);
	std::cout << "Added Zombie to Pool, Size Total: " << enemyPool.size() << std::endl;
}

void GameManager::spawnEnemy(SDL_Renderer* _renderer, int _x, int _y) {
	if (enemyPool.empty()) growPool(_renderer);
	Zombie enemy = enemyPool.front();
	enemyPool.pop_front();	

	enemy.resetObjectHealth();
	
	enemy.setPosition(_x, _y);
	enemy.visable = true;
	
		
	enemies.push_back(enemy);
}