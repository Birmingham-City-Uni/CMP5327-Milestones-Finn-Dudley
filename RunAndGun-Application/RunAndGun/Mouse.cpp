#pragma once

#include <SDL.h>
#include <SDL_image.h>

class Mouse {
private:
	int mouseX;
	int mouseY;

	SDL_Rect position;

	SDL_Texture* crosshairTexture;
public:
	Mouse(SDL_Renderer* _renderer) {
		this->mouseX = -10;
		this->mouseY = -10;

		this->position = { mouseX, mouseY, 64,64 };
	}

	~Mouse(){

	}

	int getX() {
		return mouseX;
	}
	int getY() {
		return mouseY;
	}

	bool init(SDL_Renderer* _renderer) {
		SDL_Surface* tmpCrosshairSurface = IMG_Load("assets/crosshair.png");
		crosshairTexture = SDL_CreateTextureFromSurface(_renderer, tmpCrosshairSurface);
		SDL_FreeSurface(tmpCrosshairSurface);
		if (crosshairTexture == NULL) {
			return false;
		}

		SDL_ShowCursor(0);

		return true;
	}

	void processInput() {
		SDL_GetMouseState(&mouseX, &mouseY);
	}

	void update() {
		position.x = mouseX;
		position.y = mouseY;

		position.x -= position.w / 2;
		position.y -= position.h / 2;
	}

	void draw(SDL_Renderer* _renderer) {
		SDL_RenderCopy(_renderer, this->crosshairTexture, 0, &position);
	}

	void clean() {
		SDL_DestroyTexture(this->crosshairTexture);
	}
};