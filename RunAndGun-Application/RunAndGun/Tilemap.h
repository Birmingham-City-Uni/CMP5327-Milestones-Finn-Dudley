#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <SDL.h>
#include <SDL_image.h>

#include "Tile.h"

#define TOTAL_TILES 943

#define MAP_SIZE_X 40
#define MAP_SIZE_Y 23

#define MAP_TILE_PIXELS 32

class Tilemap {
public:

	std::vector<Tile> collideableTiles;

private:
	int selectedLevel;
	std::vector<Tile> map_Tiles;

	SDL_Texture* tileset;
public:
	Tilemap(int _selectedLevel);
	~Tilemap();

	bool init(SDL_Renderer* _renderer);

	void draw(SDL_Renderer* _renderer);

	void clean();

private:
	bool loadLevel();
};