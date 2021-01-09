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

	/// <summary>
	/// The UIManagers Init Function.
	/// </summary>
	/// <param name="_renderer"> - The Games Renderer</param>
	/// <returns>Returns true if everything initializes correctly, false if an error occurs.</returns>
	bool init(SDL_Renderer* _renderer);

	/// <summary>
	/// Draws the UI in the Manager
	/// </summary>
	/// <param name="_renderer"> - The Games Renderer</param>
	/// <param name="_selectedWeapon"> - The Players Selected Weapon</param>
	void draw(SDL_Renderer* _renderer, int _selectedWeapon);

	/// <summary>
	/// Cleans all Necassry Assets in the UIManager.
	/// </summary>
	void clean();

	/// <summary>
	/// Updates the Score Text Texture.
	/// </summary>
	/// <param name="_renderer"> - The Games Renderer</param>
	/// <param name="_score"> - The Current Score in-game.</param>
	void updateScoreText(SDL_Renderer* _renderer, int _score);

	/// <summary>
	/// Creates a Text Texture from the given string.
	/// </summary>
	/// <param name="_renderer"> - the Games Renderer</param>
	/// <param name="_textForTexture"> - The Text to Be Turned into a Texture</param>
	/// <param name="_textColor"> - The Color of the Texts Texture.</param>
	/// <returns></returns>
	SDL_Texture* createTextTexture(SDL_Renderer* _renderer, std::string _textForTexture, SDL_Color _textColor);
};