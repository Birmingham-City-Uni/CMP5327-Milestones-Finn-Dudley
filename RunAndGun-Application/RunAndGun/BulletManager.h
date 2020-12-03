#pragma once

#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>

#define PI 3.14159265

struct Bullet {
	int x, y, rotation, distance;
};

class BulletManager {
public:

private:
	SDL_Texture* texture;
	std::vector<Bullet> bullets;
	
	const int movementSpeed = 10;

	const int FireTimer = 200;
	unsigned int lastFire = 0;

public:
	BulletManager();
	~BulletManager();

	bool init(SDL_Renderer* _renderer, SDL_Texture* _texture);
	void fireBullet(int _x, int _y, int _rotationAngle);
	void update();
	void draw(SDL_Renderer* _renderer);

	void clean();
private:

	void pistolFire();
	void shotgunFire();
	void rifleFire();
};