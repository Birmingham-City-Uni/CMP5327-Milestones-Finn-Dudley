#pragma once

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

#include "Mouse.cpp"
#include "BulletManager.h"

#pragma region GameObject Class

class GameObject abstract {
public:
	bool visable;

protected:
	int health;

	int movementSpeed;
	int rotationAngle;

	SDL_Rect position;
	SDL_Point rotationPoint;

	SDL_Texture* texture;

public:
	/// <summary>
	/// Initializes the Class' assets for use.
	/// </summary>
	/// <returns> true if Initialized, false if not.</returns>
	virtual bool init(SDL_Renderer* _renderer) { return true; };

	virtual void update() {};

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

protected:
	/// <summary>
	/// Sets the GameObjects current render Texture.
	/// </summary>
	/// <param name="_filename">- The File directory of the Texture</param>
	/// <returns></returns>
	bool setTexture(SDL_Renderer* _renderer, std::string _filename);
};
#pragma endregion

#pragma region Player Class

class Player : public GameObject{
private:
	int rotationSpeed;
	
	Mouse* mouse;
	BulletManager* bulletManager;
public:
	Player(Mouse* mouse);
	~Player();

	bool init(SDL_Renderer* _renderer) final override;
	void processInput(bool * keyDown);

	void update() final override;
	void draw(SDL_Renderer* _renderer) final override;
};
#pragma endregion

#pragma region Zombie Class


#pragma endregion
