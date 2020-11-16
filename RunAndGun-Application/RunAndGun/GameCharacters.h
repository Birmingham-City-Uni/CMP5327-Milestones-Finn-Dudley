#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

class Player {
public:

private:
	float health;

	SDL_Rect position;
	
	float rotationAngle;

	SDL_Renderer* renderer;
	SDL_Texture* texture;

public:
	Player(SDL_Renderer*);
	~Player();

	void init();

	void processInput( bool * keyDown);
	void update();
	void draw();
	

	float getHealth() { return health; }
	float getAngle() { return rotationAngle; }

private:
	
};