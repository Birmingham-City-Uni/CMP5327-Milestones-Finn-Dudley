#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <SDL.h>
#include <SDL_image.h>

#include "Mouse.cpp"
#include "Tile.h"
#include "BulletManager.h"


#define HEALTHBAR_WIDTH 75
#define HEALTHBAR_HEIGHT 5

#define MAX_MOVEMENT_SPEED 3

#define ZOMBIE_ATTACK_SPEED 2000

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

	/// <summary>
	/// Gets the GameObjects current rotation angle.
	/// </summary>
	/// <returns></returns>
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
	/// Gets the GameObjects Centre X rotation point.
	/// </summary>
	/// <returns>Returns the Centre X Position</returns>
	int getCentreX() {
		return position.x + rotationPoint.x;
	}

	/// <summary>
	/// Gets the GameObjects Centre Y rotation point.
	/// </summary>
	/// <returns>Returns the Centre Y Position</returns>
	int getCentreY() {
		return position.y + rotationPoint.y;
	}

	/// <summary>
	/// Gets the GameObjects Width.
	/// </summary>
	/// <returns>Returns the GameObjects Width.</returns>
	int getWidth() {
		return position.w;
	}

	/// <summary>
	/// Gets the GameObjects Height.
	/// </summary>
	/// <returns>Returns the GameObjects Height.</returns>
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
	/// <summary>
	/// Gets the GameObjects Box Collider
	/// </summary>
	/// <returns>Returns the GameObjects Box Collider.</returns>
	SDL_Rect& getBoxCollider() {
		return collider_Box;
	}

	/// <summary>
	/// Gets the GameObjects Circel Collider
	/// </summary>
	/// <returns>Returns the GameObjects Circle Collider.</returns>
	Circle& getCircleCollider() {
		return collider_Circle;
	}

	/// <summary>
	/// Moves the Colliders of the GameObject to match the X and Y position.
	/// </summary>
	void shiftColliders();

	/// <summary>
	/// Checks for Collisitions between two Circle Colliders.
	/// </summary>
	/// <param name="_obj1"> - The First Object Circle Collider.</param>
	/// <param name="_obj2"> - The Second Object Circle Collider.</param>
	/// <returns>Returns true if a collistion is occuring, false if no collision is occcuring.</returns>
	bool checkCollision(Circle& _obj1, Circle& _obj2);

	/// <summary>
	/// Checks for Collistions between a Circle and Box Collider.
	/// </summary>
	/// <param name="_obj1" - The Circle Collider></param>
	/// <param name="_obj2"> - The Box Collider</param>
	/// <returns>Returns True if a collision is occuring, false if no collision is occuring.</returns>
	bool checkCollision(Circle& _obj1, SDL_Rect& _obj2);

	/// <summary>
	/// Gives the rotation for the GameObject to look at the given x, y position.
	/// </summary>
	/// <param name="_x"> - The X position to rotate towards.</param>
	/// <param name="_y"> - The Y postion to rotatte towards.</param>
	void rotateTowardsPoint(int _x, int _y);

	/// <summary>
	/// Adjust the Rects of the GameObjects Healthbar depend on the current health.
	/// </summary>
	void adjustHealthRect();

protected:

	/// <summary>
	/// Gets the required texture.
	/// </summary>
	/// <param name="_renderer"> - The Games Renderer</param>
	/// <param name="_filename"> - The textures Directory.</param>
	/// <returns>Returns a useable texture.</returns>
	SDL_Texture* getTexture(SDL_Renderer* _renderer, std::string _filename);
	
	/// <summary>
	/// Draws the GameObjects Healthbar.
	/// </summary>
	/// <param name="_renderer">- The Games Renderer</param>
	void drawHealthBar(SDL_Renderer* _renderer);

	/// <summary>
	/// Positions the GameObjects healthbar accoring to the given x, y position
	/// </summary>
	/// <param name="_x"> - the desired x position.</param>
	/// <param name="_y"> - the desired y position.</param>
	void positionHealthbar(int _x, int _y);

	/// <summary>
	/// Checks the GameObjects Collision with the Games Tiles.
	/// </summary>
	/// <param name="_collideableTiles"> - The Vector of the collideable Tiles.</param>
	/// <returns></returns>
	bool checkTileCollision(std::vector<Tile> _collideableTiles);

	/// <summary>
	/// The Distance Squared between two x,y positions.
	/// </summary>
	/// <param name="_object1_x"> - The First x Position</param>
	/// <param name="_object1_y"> - The First Y Position</param>
	/// <param name="_object2_x"> - The Second X Position</param>
	/// <param name="_object2_y"> - The Second Y Position</param>
	/// <returns></returns>
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

	/// <summary>
	/// The Players Init Function
	/// </summary>
	/// <param name="_renderer">- The Games Renderer</param>
	/// <returns>Returns True if all initializes correctly, false if an error occurs.</returns>
	bool init(SDL_Renderer* _renderer) final override;

	/// <summary>
	/// Processes the Players Input.
	/// </summary>
	/// <param name="keyDown"> - the Games array tracking which key is pressed.</param>
	/// <param name="buttonDown"> - The Games Array Tracking which mousebutton is pressed.</param>
	void processInput(bool * keyDown, bool* buttonDown);

	/// <summary>
	/// The Players Update Function
	/// </summary>
	/// <param name="_collideableTiles"> - The Vector of the tilemaps collideable tiles.</param>
	void update(std::vector<Tile> _collideableTiles);

	/// <summary>
	/// The Players Draw Function
	/// </summary>
	/// <param name="_renderer"> - The Games Renderer</param>
	void draw(SDL_Renderer* _renderer) final override;

	/// <summary>
	/// Gets the value of the currently selected weapon.
	/// </summary>
	/// <returns>Returns the selected weapon int value.</returns>
	int getSelectedWeapon() {
		return selectedWeapon;
	}

private:
	/// <summary>
	/// Fires the Currently Selected Weapon.
	/// </summary>
	void fireSelectedWeapon();
};
#pragma endregion

#pragma region Zombie Class

class Zombie : public GameObject {
public:


private:
	bool attackCooldown;
	unsigned int lastAttack;

public:
	Zombie();
	~Zombie();

	/// <summary>
	/// The Zombies Init Function
	/// </summary>
	/// <param name="_renderer"> - The Games Renderer</param>
	/// <returns>Returns True if all inisitalized properly, false if an error occurs.</returns>
	bool init(SDL_Renderer* _renderer) final override;

	/// <summary>
	/// Updates the Zombie
	/// </summary>
	/// <param name="_bulletManager"> - The BulletsManagers Class</param>
	/// <param name="_player"> - The Players Class</param>
	/// <param name="_collideablTiles"> - A Vector of collideable tiles.</param>
	void update(BulletManager* _bulletManager, Player* _player, std::vector<Tile> _collideablTiles);

	/// <summary>
	/// Resets the Objects Health, to its max health.
	/// </summary>
	void resetObjectHealth() {
		this->health = this->maxHealth;
	}

	/// <summary>
	/// Attacks the Player if in Range.
	/// </summary>
	/// <param name="_player"> - The Players Class</param>
	void attackPlayer(Player* _player) {
		if (attackCooldown) {
			attackCooldown = false;
			_player->damageObject(10);
			lastAttack = SDL_GetTicks() + ZOMBIE_ATTACK_SPEED;
		}
		else if (lastAttack < SDL_GetTicks()) {
			attackCooldown = true;
		}
	}

private:

};
#pragma endregion
