#pragma once

#include <iostream>
#include <string>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class UIManager {

private:
	int lastScore;
	int selectedWeaponUI;

	TTF_Font* textFont;

	SDL_Texture* scoreFontTexture;
	SDL_Color scoreColor;
	SDL_Rect scorePosition;

	SDL_Texture* rifleBulletTexture;
	SDL_Texture* pistolBulletTexture;
	SDL_Texture* shotgunShellTexture;
	SDL_Rect weaponTypePosition;

public:
	UIManager();
	~UIManager();

	bool init(SDL_Renderer* _renderer);
	void draw(SDL_Renderer* _renderer, int _selectedWeapon);
	void clean();

	void updateScoreText(SDL_Renderer* _renderer, int _score);

	SDL_Texture* createTextTexture(SDL_Renderer* _renderer, std::string _textForTexture, SDL_Color _textColor);
};