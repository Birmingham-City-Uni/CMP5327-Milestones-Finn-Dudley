#pragma once

#include <iostream>
#include <vector>

#include <SDL.h>
#include <SDL_image.h>

#define PI 3.14159

struct Bullet {
	int isVisable, x, y, rotation, distance;
};

class BulletManager {
	friend class Zombie;
public:
	std::vector<Bullet> bullets;

private:
	SDL_Texture* pelletTexture;

	const int movementSpeed = 10;

	const int pistolTime = 300;
	const int rifleTime = 150;
	const int shotgunTime = 1000;

	unsigned int lastFire = 0;

public:
	BulletManager();
	~BulletManager();

	bool init(SDL_Renderer* _renderer);

	void shootPistol(int _x, int _y, int& _rotationAngle);
	void shootRifle(int _x, int _y, int& _rotationAngle);
	void shootShotgun(int _x, int _y, int& _rotationAngle);

	void changeWeaponTime() {
		lastFire = SDL_GetTicks() + 150;
	}

	void update();
	void draw(SDL_Renderer* _renderer);

	void clean();
private:

	void fireBullet(int _x, int _y, int _rotationAngle);


};