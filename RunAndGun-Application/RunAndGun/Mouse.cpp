#pragma once

#include <SDL.h>
#include <SDL_image.h>

class Mouse {
private:
	int mouseX;
	int mouseY;

	SDL_Rect rect;

	SDL_Renderer* renderer;
	SDL_Texture* crosshairTexture;
public:
	Mouse(SDL_Renderer* renderer) {
		this->mouseX = -10;
		this->mouseY = -10;

		this->rect = { mouseX, mouseY, 64,64 };
		this->renderer = renderer;
	}

	~Mouse(){
		if (renderer) {
			delete renderer;
			renderer = nullptr;
		}
	}

	bool init() {
		SDL_Surface* tmpCrosshairSurface = IMG_Load("assets/crosshair.png");
		crosshairTexture = SDL_CreateTextureFromSurface(this->renderer, tmpCrosshairSurface);
		SDL_FreeSurface(tmpCrosshairSurface);
		if (crosshairTexture == NULL) {
			return false;
		}

		return true;
	}

	void processInput() {
		SDL_GetMouseState(&mouseX, &mouseY);
	}

	void update() {
		rect.x = mouseX;
		rect.y = mouseY;

		rect.x -= rect.w / 2;
		rect.y -= rect.h / 2;
	}

	void draw() {
		SDL_RenderCopy(this->renderer, this->crosshairTexture, 0, &rect);
	}

	void clean() {
		SDL_DestroyTexture(this->crosshairTexture);
	}
};