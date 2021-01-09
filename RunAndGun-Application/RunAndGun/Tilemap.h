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

	/// <summary>
	/// The TileMaps Init Function
	/// </summary>
	/// <param name="_renderer"> - the Games Renderer</param>
	/// <returns>Returns True if all assets are initialized correctly, false if an error occurs</returns>
	bool init(SDL_Renderer* _renderer);

	/// <summary>
	/// Draws the TileMap's Tiles.
	/// </summary>
	/// <param name="_renderer"> - The Games Renderer</param>
	void draw(SDL_Renderer* _renderer);

	/// <summary>
	/// Cleans the TileMap's required assets.
	/// </summary>
	void clean();

private:
	/// <summary>
	/// Loads the Selected Level from the given txt file.
	/// </summary>
	/// <returns>Returns true if the level loads correctly, false if an error occurs</returns>
	bool loadLevel();
};