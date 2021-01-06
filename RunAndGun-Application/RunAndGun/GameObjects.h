#pragma once

#include <iostream>
#include <string>
#include <math.h>
#include <SDL.h>
#include <SDL_image.h>

#include "Mouse.cpp"
#include "BulletManager.h"

#define HEALTHBAR_WIDTH 75
#define HEALTHBAR_HEIGHT 5

#define MAX_MOVEMENT_SPEED 3

struct Circle {
	int radius, x, y;
};

#pragma region GameObject Class

class GameObject abstract {

public:
	bool visable;
	Circle collider_Circle;
	SDL_Rect collider_Box;

protected:
	int health;
	int maxHealth;

	SDL_Rect healthbarBackground = {75, 75, HEALTHBAR_WIDTH, HEALTHBAR_HEIGHT};
	SDL_Rect healthBar = { 75, 75, HEALTHBAR_WIDTH,  HEALTHBAR_HEIGHT};

	int movementSpeed;
	int velocityX, velocityY;
	int rotationAngle;

	SDL_Rect position;
	int* oldPosX; 
	int* oldPosY;
	SDL_Point rotationPoint;

	SDL_Texture* gameObjectTexture;

public:
	/// <summary>
	/// Initializes the Class' assets for use.
	/// </summary>
	/// <returns> true if Initialized, false if not.</returns>
	virtual bool init(SDL_Renderer* _renderer) = 0;

	/// <summary>
	/// Draws the GameObject onto the screen if Visable.
	/// </summary>
	virtual void draw(SDL_Renderer* _renderer);

	/// <summary>
	/// Cleans any assets linked to the class.
	/// </summary>
	virtual void clean();

	int getAngle() {
		return rotationAngle;
	}

	/// <summary>
	/// Gets the GameObjects X Position.
	/// </summary>
	/// <returns>The Gameobjects X Position</returns>
	int getX() {
		return position.x;
	}

	/// <summary>
	/// Gets the GameObjects Y Position.
	/// </summary>
	/// <returns>The Gameobjects Y Position</returns>
	int getY() {
		return position.x;
	}

	int getCentreX() {
		return position.x + rotationPoint.x;
	}

	int getCentreY() {
		return position.y + rotationPoint.y;
	}

	int getWidth() {
		return position.w;
	}

	int getHeight() {
		return position.h;
	}

	/// <summary>
	/// Sets the GameObjects X and Y Positions.
	/// </summary>
	/// <param name="_x">- The Desired X Position of the GameObject</param>
	/// <param name="_y">- The Desired Y Position of the GameObject</param>
	void setPosition(int _x, int _y) {
		setX(_x);
		setY(_y);
	}

	/// <summary>
	/// Sets the GameObjects X position.
	/// </summary>
	/// <param name="_x">- The Desired X Value</param>
	void setX(int _x) {
		position.x = _x;
	}

	/// <summary>
	/// Sets the GameObjects Y position.
	/// </summary>
	/// <param name="_y">- The Desired Y Value</param>
	void setY(int _y) {
		position.y = _y;
	}

	/// <summary>
	/// Sets the GameObjects Visability.
	/// </summary>
	/// <param name="_bool">- The Desired Visability of the GameObject</param>
	void setVisable(bool _bool) {
		visable = _bool;
	}

	/// <summary>
	/// Subtracts from the Objects Health.
	/// </summary>
	/// <param name="_value">- The Amount to change the Objects Health.</param>
	void damageObject(int _value) {
		this->health -= _value;
		this->adjustHealthRect();

		if (this->health <= 0) {
			this->visable = false;
		}
	}

	/// <summary>
	/// Adds to the Objects Health.
	/// </summary>
	/// <param name="_value">- The Amount to change the Objects Health.</param>
	void healObject(int _value) {
		this->health += _value;
		this->adjustHealthRect();
	}

	SDL_Rect& getBoxCollider() {
		return collider_Box;
	}

	Circle& getCircleCollider() {
		return collider_Circle;
	}

	void shiftColliders();

	bool checkCollision(Circle& _obj1, Circle& _obj2);
	bool checkCollision(Circle& _obj1, SDL_Rect& _obj2);

	void rotateTowardsPoint(int _x, int _y);

	void adjustHealthRect();

protected:

	SDL_Texture* getTexture(SDL_Renderer* _renderer, std::string _filename);
	
	void drawHealthBar(SDL_Renderer* _renderer);
	void positionHealthbar(int _x, int _y);

	double distanceSquared(int _object1_x, int _object1_y, int _object2_x, int _object2_y);
};
#pragma endregion

#pragma region Player Class

class Player : public GameObject{
private:
	int selectedWeapon = 1;

	SDL_Texture* gameObjectTexture2;
	SDL_Texture* gameObjectTexture3;

	Mouse* mouse;
	BulletManager* bulletManager;

public:
	Player(Mouse* mouse, BulletManager* _bulletManager);
	~Player();

	bool init(SDL_Renderer* _renderer) final override;
	void processInput(bool * keyDown, bool* buttonDown);

	void update();
	void draw(SDL_Renderer* _renderer) final override;

private:
	void fireSelectedWeapon();
};
#pragma endregion

#pragma region Zombie Class

class Zombie : public GameObject {
public:


private:

public:
	Zombie();
	~Zombie();

	bool init(SDL_Renderer* _renderer) final override;

	void update(BulletManager* _bulletManager);

	void resetObjectHealth() {
		this->health = this->maxHealth;
	}

private:

};
#pragma endregion
