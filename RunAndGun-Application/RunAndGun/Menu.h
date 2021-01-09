#pragma once

#include <vector>
#include <SDL.h>
#include <SDL_image.h>

#include "UIManager.h"

class Menu {
public:
	int selectedMap;

	SDL_Color titleColor;
	SDL_Color helperColor;
	SDL_Color headingsColor;

	SDL_Rect titleRect;
	SDL_Rect helperRect1;
	SDL_Rect helperRect2;
	SDL_Rect level1Rect;
	SDL_Rect level2Rect;
	SDL_Rect level3Rect;

	SDL_Texture* titleTexture;
	SDL_Texture* helperTexture1;
	SDL_Texture* helperTexture2;
	SDL_Texture* heading1Texture;
	SDL_Texture* heading2Texture;
	SDL_Texture* heading3Texture;

private:

public:
	Menu() {

	}

	~Menu() {

	}

	/// <summary>
	/// Menu's Init Function
	/// </summary>
	/// <param name="_renderer"> - The Games Renderer</param>
	/// <param name="_uiManager"> - The Games UIManager</param>
	void init(SDL_Renderer* _renderer, UIManager* _uiManager) {
		//Colors
		titleColor = { 255, 0, 0, 255 };
		helperColor = { 200, 0, 0, 200 };
		headingsColor = { 0, 0, 200,200 };

		titleRect = { 1280 / 2 - 150 , 30 , 300, 100 };
		helperRect1 = { 1280 / 2 - 115, 150, 230, 30 };
		helperRect2 = { 1280 / 2 - 100, 180, 200, 75 };
		level1Rect = { 1280 / 2 - 100, 300, 200, 60 };
		level2Rect = { 1280 / 2 - 100, 380, 200, 60 };
		level3Rect = { 1280 / 2 - 100, 460, 200, 60 };

		// String Textures
		titleTexture = _uiManager->createTextTexture(_renderer, "RUN N' GUN", titleColor);
		helperTexture1 = _uiManager->createTextTexture(_renderer, "Press the Corrosponding Key.", helperColor);
		helperTexture2 = _uiManager->createTextTexture(_renderer, "Map Select:", helperColor);
		heading1Texture = _uiManager->createTextTexture(_renderer, "1 - Surrounded", headingsColor);
		heading2Texture = _uiManager->createTextTexture(_renderer, "2 - Dark Depths", headingsColor);
		heading3Texture = _uiManager->createTextTexture(_renderer, "3 - Winter Rampage", headingsColor);
	}

	/// <summary>
	/// Processes any necassary input needed for the main menu.
	/// </summary>
	/// <returns>Returns false if the gameloop is to be broke.</returns>
	bool processInput() {
		SDL_Event e;

		while (SDL_PollEvent(&e) != 0) {
			switch (e.type) {
				case SDL_QUIT:
					return false;
				case SDL_KEYDOWN:
					switch (e.key.keysym.scancode)
					{
					case SDL_SCANCODE_1:
						selectedMap = 1;
						return false;
						break;
					case SDL_SCANCODE_2:
						selectedMap = 2;
						return false;
						break;

					case SDL_SCANCODE_3:
						selectedMap = 3;
						return false;
						break;

					default:
						break;
					}
			}
		}

		return true;
	}

	/// <summary>
	/// Draws the Main Menu
	/// </summary>
	/// <param name="_renderer"> - The Games Renderer</param>
	void draw(SDL_Renderer* _renderer) {
		SDL_RenderClear(_renderer);
		SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);

		// Title Section
		//SDL_RenderFillRect(_renderer, &titleRect);
		SDL_RenderCopy(_renderer, titleTexture, NULL, &titleRect);

		// Helper Section
		SDL_RenderCopy(_renderer, helperTexture1, NULL, &helperRect1);
		SDL_RenderCopy(_renderer, helperTexture2, NULL, &helperRect2);

		// Level 1 Section
		//SDL_RenderFillRect(_renderer, &level1Rect);
		SDL_RenderCopy(_renderer, heading1Texture, NULL, &level1Rect);

		// Level 2 Section
		//SDL_RenderFillRect(_renderer, &level2Rect);
		SDL_RenderCopy(_renderer, heading2Texture, NULL, &level2Rect);

		// Level 3 Section
		//SDL_RenderFillRect(_renderer, &level3Rect);
		SDL_RenderCopy(_renderer, heading3Texture, NULL, &level3Rect);

		SDL_RenderPresent(_renderer);
	}

	/// <summary>
	/// Cleans and Assets from the Menu
	/// </summary>
	void clean() {
		SDL_DestroyTexture(titleTexture);
		SDL_DestroyTexture(helperTexture1);
		SDL_DestroyTexture(helperTexture2);
		SDL_DestroyTexture(heading1Texture);
		SDL_DestroyTexture(heading2Texture);
		SDL_DestroyTexture(heading3Texture);
	}

private:

};