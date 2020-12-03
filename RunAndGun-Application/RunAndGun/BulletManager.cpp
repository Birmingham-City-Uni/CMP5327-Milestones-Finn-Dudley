#include "BulletManager.h"

BulletManager::BulletManager(){

}

BulletManager::~BulletManager() {

}

bool BulletManager::init(SDL_Renderer* _renderer) {

	SDL_Surface* tmpSurface = IMG_Load("assets/bullet.png");
	this->texture = SDL_CreateTextureFromSurface(_renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	if (this->texture == NULL) {
		return false;
	}

	return true;
}

void BulletManager::fireBullet(int _x, int _y, int _rotationAngle) {
	if (FireTimer < SDL_GetTicks() - lastFire) {
			
		bullets.push_back(Bullet{ _x, _y, _rotationAngle, 0 });
		lastFire = SDL_GetTicks();
	}

}

void BulletManager::update() {
	for (auto& bullet : bullets) {
		bullet.x += sin(bullet.rotation * PI / 180.0f) * movementSpeed;
		bullet.y -= cos(bullet.rotation * PI / 180.0f) * movementSpeed;
		bullet.distance += movementSpeed;
	}

	auto remove = std::remove_if(bullets.begin(), bullets.end(),
		[](const Bullet& bullet) { return bullet.distance > 500; });
	bullets.erase(remove, bullets.end());
}

void BulletManager::draw(SDL_Renderer* _renderer) {
	SDL_Point center = { 0,0 };
	for (auto& bullet : bullets) {
		SDL_Rect pos = { bullet.x + 10, bullet.y, 10, 10 };
		SDL_RenderCopyEx(_renderer, this->texture, 0, &pos, bullet.rotation, &center, SDL_FLIP_NONE);
	}
}

void BulletManager::clean() {
	SDL_DestroyTexture(this->texture);
}