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

	growBulletPool();

	return true;
}

void BulletManager::update() {
	for (int i = 0; i < bullets.size(); i++) {
		if (bullets[i].isVisable && bullets[i].distance < 1400) {

			bullets[i].x += sin(bullets[i].rotation * PI / 180.0f) * movementSpeed;
			bullets[i].y -= cos(bullets[i].rotation * PI / 180.0f) * movementSpeed;
			bullets[i].distance += movementSpeed;
		}
		else if (!bullets[i].isVisable || bullets[i].distance >= 1400) {
			std::cout << "Removing Bullet From Scene To Pool" << std::endl;

			addBulletToPool(bullets[i]);
			bullets.erase(bullets.begin() + i);
		}
	}
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

	if (!bullets.empty()) {
		bullets.clear();
		bullets.shrink_to_fit();
	}

	if (!bulletPool.empty()) {
		bulletPool.clear();
		bulletPool.shrink_to_fit();
	}
}

// ----- //

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
	if (bulletPool.empty()) growBulletPool();
	Bullet bullet = bulletPool.front();
	bulletPool.pop_front();

	// Set Bullet Damage - if needed;
	bullet.isVisable = true;
	bullet.x = _x;
	bullet.y = _y;
	bullet.rotation = _rotationAngle;

	bullets.push_back(bullet);
}

void BulletManager::growBulletPool() {
	for (int i = 0; i < 10; i++)
	{
		Bullet bullet = { false, 0, 0, 0, 0 };

		addBulletToPool(bullet);
	}
}

void BulletManager::addBulletToPool(Bullet _bullet) {
	_bullet.distance = 0;
	_bullet.isVisable = false;

	bulletPool.push_back(_bullet);
	std::cout << "Adding Bullet to Pool: " << bulletPool.size() << std::endl;
}