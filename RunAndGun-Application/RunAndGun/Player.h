#pragma once

#include <SDL.h>
#include <SDL_image.h>

class Player {
public:

private:

	int movementSpeed;
	int rotationSpeed;
	float rotationAngle;

	SDL_Rect rect;
	SDL_Point rotationPoint;
	
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	bool visable;
public:
	Player(SDL_Renderer* renderer);
	~Player();

	bool init();
	void processInput(bool * keyDown);

	void update();

	void draw();

	void clean();

};
