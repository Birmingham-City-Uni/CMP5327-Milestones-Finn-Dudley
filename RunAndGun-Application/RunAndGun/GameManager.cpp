#include "GameManager.h"

GameManager::GameManager(BulletManager* _bulletManager) : bulletManager(_bulletManager) {
	this->score = 0;
	this->currentWave = 0;

	this->lastSpawnTime = 0;
	this->newWaveTime = 2500;
}

GameManager::~GameManager() {

}

bool GameManager::init(SDL_Renderer* _renderer) {

	growPool(_renderer);

	return true;
}

void GameManager::update(SDL_Renderer* _renderer, Player* _player, std::vector<Tile> _collideableTiles) {
	if (SDL_GetTicks() - lastSpawnTime > newWaveTime) {
		int ranNum = rand() % 4 + 1;
		switch (ranNum) {
			default:
			case 1:
				spawnEnemy(_renderer, -30, 340);
				break;

			case 2:
				
				spawnEnemy(_renderer, 1270, 340);
				break;

			case 3:
				spawnEnemy(_renderer, 620, -30);
				break;

			case 4:
				spawnEnemy(_renderer, 620, 750);
				break;
		}

		currentWave++;
		std::cout << "Current Wave: " << currentWave << std::endl;
		lastSpawnTime = SDL_GetTicks();
	}

	for (int i = 0; i < enemies.size(); i++) {
		if (enemies[i].visable) {
			enemies[i].rotateTowardsPoint(_player->getCentreX(), _player->getCentreY());
			enemies[i].update(bulletManager, _player, _collideableTiles);
		}
		else if (!enemies[i].visable) {
			score += 10;
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
	if (!enemies.empty()) {
		for (auto enemy : enemies) enemy.clean();
		enemies.clear();
		enemies.shrink_to_fit();
	}
	
	if (!enemyPool.empty()) {
		for (auto& enemy : enemies) enemy.clean();
		enemyPool.clear();
		enemyPool.shrink_to_fit();
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