#pragma once

#include <iostream>
#include <vector>
#include <deque>

#include <SDL.h>
#include <SDL_image.h>

#define PI 3.14159

/// <summary>
/// Base Bullet Struct, contains the info for each bullet info.
/// </summary>
struct Bullet {
	int isVisable, x, y, rotation, distance;
};

class BulletManager {
	friend class Zombie;
public:
	/// <summary>
	/// Vector For bullets to iterate through, and double ended queue for object pooling due to being dynamic.
	/// </summary>
	std::vector<Bullet> bullets;
	std::deque<Bullet> bulletPool;

private:
	SDL_Texture* pelletTexture;

	const int movementSpeed = 10;

	const int pistolTime = 300;
	const int rifleTime = 150;
	const int shotgunTime = 800;

	unsigned int lastFire = 0;

public:
	BulletManager();
	~BulletManager();

	/// <summary>
	/// The Init Function for the BulletManager.
	/// </summary>
	/// <param name="_renderer"> - The Renderer for the Scene.</param>
	/// <returns></returns>
	bool init(SDL_Renderer* _renderer);

	/// <summary>
	/// BulletManagers Update Function, where all bullets are checked for collisions and applies movement.
	/// </summary>
	void update();

	/// <summary>
	/// BulletManagers Draw Function, which draws all the bullets in the bullets vector.
	/// </summary>
	/// <param name="_renderer"></param>
	void draw(SDL_Renderer* _renderer);

	/// <summary>
	/// Cleans the variables assosiated with the BulletManager Class.
	/// </summary>
	void clean();

	/// <summary>
	/// Shoots a bullet from a pistol with the Pistols assosiations.
	/// </summary>
	/// <param name="_x"> - The X position to fire the bullet from.</param>
	/// <param name="_y"> - The Y position to fire the bullet from.</param>
	/// <param name="_rotationAngle"> - The rotation the bullet has when it fires.</param>
	void shootPistol(int _x, int _y, int& _rotationAngle);

	/// <summary>
	/// Shoots a bullet with the Rifles assosiations.
	/// </summary>
	/// <param name="_x"> - The X position to fire the bullet from.</param>
	/// <param name="_y"> - The Y position to fire the bullet from.</param>
	/// <param name="_rotationAngle"> - The rotation the bullet has when it fires.</param>
	void shootRifle(int _x, int _y, int& _rotationAngle);

	/// <summary>
	/// Shoots a bullet with the Shotguns assosiations.
	/// </summary>
	/// <param name="_x"> - The X position to fire the bullet from.</param>
	/// <param name="_y"> - The Y position to fire the bullet from.</param>
	/// <param name="_rotationAngle"> - The rotation the bullet has when it is fired.</param>
	void shootShotgun(int _x, int _y, int& _rotationAngle);

	/// <summary>
	/// Adjusts the nextFire time so the player cannot instantly shoot.
	/// </summary>
	void changeWeaponTime() {
		lastFire = SDL_GetTicks() + 150;
	}

private:

	/// <summary>
	/// Fires a bullet instance from the given X and Y position with the given rotation.
	/// </summary>
	/// <param name="_x"> - The X position t0 fire the bullet from.</param>
	/// <param name="_y"> - The Y position to fire the bullet from.</param>
	/// <param name="_rotationAngle"> - The rotaion of the fired bullet.</param>
	void fireBullet(int _x, int _y, int _rotationAngle);

	/// <summary>
	/// Grows the Bullets Pool.
	/// </summary>
	void growBulletPool();

	/// <summary>
	/// Adds an already instantiated bullet back into the pool.
	/// </summary>
	/// <param name="_bullet"> - The bullet instance to add back to the pool.</param>
	void addBulletToPool(Bullet _bullet);

};