#pragma once

#include <iostream>
#include <string>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class UIManager {
public:

private:

	SDL_Texture* healthbarTexture;

	SDL_Texture* rifleBulletTexture;
	SDL_Texture* pistolBulletTexture;
	SDL_Texture* shotgunShellTexture;
public:
	UIManager();
	~UIManager();

	bool init(SDL_Renderer* _renderer);
	void draw(SDL_Renderer* _renderer);
	void clean();

private:

};