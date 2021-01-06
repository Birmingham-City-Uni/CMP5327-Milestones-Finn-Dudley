#pragma once

#include <iostream>
#include <fstream>

#include <SDL.h>
#include <SDL_image.h>

#define MAP_SIZE_X 41
#define MAP_SIZE_Y 23

#define MAP_TILE_PIXELS 32

/// <summary>
/// Tile Data to know which type of tile to load.
/// Size will be adjusted when tilemap is finalized.
/// </summary>
const int MAP_DATA[MAP_SIZE_Y][MAP_SIZE_X] = {
	{5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5},
	{5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
	{5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
	{5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
	{5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
	{5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5}
};

class Tilemap {
public:

private:
	int MAP_TILE_PIXELS_;
	int MAP_SIZE_X_;
	int MAP_SIZE_Y_;

	SDL_Texture* tilesetTexture;
public:
	Tilemap();
	~Tilemap();

	bool init(SDL_Renderer* _renderer);

	void draw(SDL_Renderer* _renderer);

	void clean();

private:
	void loadLevel(int _selectedLevel);
};