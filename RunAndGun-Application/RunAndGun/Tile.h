#pragma once

#include <SDL.h>
#include <SDL_image.h>

class Tile {

private:
	SDL_Rect box_Collider;
	SDL_Rect tilePosition;
	SDL_Rect texturePosition;

public:
	Tile(int _x, int _y, int _tileType, int _tilemap_pixels) {
		
		texturePosition = { (_tileType % 8) * 32, (_tileType / 8) * 32, _tilemap_pixels, _tilemap_pixels };
		tilePosition = { _x * _tilemap_pixels, _y * _tilemap_pixels, _tilemap_pixels, _tilemap_pixels };

		box_Collider = { _x * _tilemap_pixels, (_y * _tilemap_pixels) - _tilemap_pixels, _tilemap_pixels, _tilemap_pixels };
	}

	~Tile() {

	}

	/// <summary>
	/// Gets the Tiles Box Collider.
	/// </summary>
	/// <returns>Returns the Tiles Box Collider</returns>
	SDL_Rect getbox_Collider() {
		return box_Collider;
	}

	/// <summary>
	/// Gets the Tiles Texture Position
	/// </summary>
	/// <returns>Returns the Tiles Texture Position</returns>
	SDL_Rect getTexturePos() {
		return texturePosition;
	}

	/// <summary>
	/// Gets the Tiles Position
	/// </summary>
	/// <returns>Returns the Textures Position</returns>
	SDL_Rect getTilePos() {
		return tilePosition;
	}
};