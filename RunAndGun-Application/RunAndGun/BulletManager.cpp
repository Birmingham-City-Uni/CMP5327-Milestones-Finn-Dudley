#include "BulletManager.h"

BulletManager::BulletManager(Player* _player) : player(_player) {

}

BulletManager::~BulletManager() {
	if (player) {
		delete player;
		player = nullptr;
	}
}

bool BulletManager::init(SDL_Renderer* _renderer) {

	for (auto& bullet : bullets) {
		if (!bullet.init(_renderer)) {
			return false;
		}
	}

	return true;
}

void BulletManager::processInput(bool* keyDown) {
	if (keyDown[SDL_SCANCODE_SPACE]) {
		if (SDL_GetTicks() - lastFire > FireTimer) {
			bullets.push_back(Bullet(player->getAngle()));
			lastFire = SDL_GetTicks();
		}
	}
}

void BulletManager::update() {
	for (auto& bullet : bullets) {
		bullet.update();
	}

	auto remove = std::remove_if(bullets.begin(), bullets.end(),
		[](const Bullet& bullet) { return bullet.distance > 1000; });
	bullets.erase(remove, bullets.end());
}

void BulletManager::draw(SDL_Renderer* _renderer) {
	for (auto& bullet : bullets) {
		bullet.draw(_renderer);
	}
}
