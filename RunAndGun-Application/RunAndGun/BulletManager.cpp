#include "BulletManager.h"

BulletManager::BulletManager(){
	this->pelletTexture = nullptr;
}

BulletManager::~BulletManager() {

}

bool BulletManager::init(SDL_Renderer* _renderer){

	SDL_Surface* tmpSurface = IMG_Load("./assets/textures/pellet.png");
	this->pelletTexture = SDL_CreateTextureFromSurface(_renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	
	if (this->pelletTexture == NULL) {
		return false;
	}

	return true;
}

void BulletManager::shootPistol(int _x, int _y,int& _rotationAngle) {
	if (SDL_GetTicks() > lastFire) {
		lastFire = SDL_GetTicks() + pistolTime;

		fireBullet(_x, _y, _rotationAngle);
	}
}
void BulletManager::shootRifle(int _x, int _y, int& _rotationAngle) {
	if (SDL_GetTicks() > lastFire) {
		lastFire = SDL_GetTicks() + rifleTime;

		fireBullet(_x, _y, _rotationAngle);
	}
}
void BulletManager::shootShotgun(int _x, int _y, int& _rotationAngle) {
	if (SDL_GetTicks() > lastFire) {
		lastFire = SDL_GetTicks() + shotgunTime;

		fireBullet(_x, _y, _rotationAngle);
		fireBullet(_x, _y, _rotationAngle - 5);
		fireBullet(_x, _y, _rotationAngle + 5);
	}
}

void BulletManager::fireBullet(int _x, int _y, int _rotationAngle) {
		bullets.push_back(Bullet{ true, _x, _y, _rotationAngle, 0 });
}

void BulletManager::update() {
	for (auto& bullet : bullets) {
		if (bullet.isVisable) {
			bullet.x += sin(bullet.rotation * PI / 180.0f) * movementSpeed;
			bullet.y -= cos(bullet.rotation * PI / 180.0f) * movementSpeed;
			bullet.distance += movementSpeed;
		}
	}

	auto remove = std::remove_if(bullets.begin(), bullets.end(),
		[](const Bullet& bullet) { return bullet.distance > 1000; });
	bullets.erase(remove, bullets.end());
}

void BulletManager::draw(SDL_Renderer* _renderer) {
	SDL_Point center = { 0,0 };
	for (auto& bullet : bullets) {
		if (bullet.isVisable) {
			SDL_Rect pos = { bullet.x + 10, bullet.y, 6, 6 };
			SDL_RenderCopyEx(_renderer, this->pelletTexture, 0, &pos, bullet.rotation, &center, SDL_FLIP_NONE);
		}
	}
}

void BulletManager::clean() {
	SDL_DestroyTexture(this->pelletTexture);
}