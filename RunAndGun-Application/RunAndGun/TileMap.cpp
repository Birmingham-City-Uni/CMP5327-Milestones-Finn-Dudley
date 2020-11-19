#include "Tilemap.h"

Tilemap::Tilemap(SDL_Renderer* renderer) {
	this->renderer = renderer;
}

Tilemap::~Tilemap() {
	if (renderer) {
		delete renderer;
		renderer = nullptr;
	}
}

bool Tilemap::init() {

	SDL_Surface* tmpTilemapSurface = IMG_Load("./assets/tilemap.png");
	this->tilesetTexture = SDL_CreateTextureFromSurface(this->renderer, tmpTilemapSurface);
	SDL_FreeSurface(tmpTilemapSurface);
	if (tilesetTexture == NULL) {
		return false;
	}

	return true;
}

void Tilemap::draw() {
	for (int _y = 0; _y < MAP_SIZE_Y; _y++){
		for (int _x = 0; _x < MAP_SIZE_X; _x++) {

			SDL_Rect srcRect = { (MAP_DATA[_y][_x] % 8) * 32, ((MAP_DATA[_y][_x]) / 8) * 32, 32, 32 };
			SDL_Rect destRect = { _x * MAP_TILE_PIXELS, _y * MAP_TILE_PIXELS, MAP_TILE_PIXELS, MAP_TILE_PIXELS };
			SDL_RenderCopy(renderer, tilesetTexture, &srcRect, &destRect);
		}
	}
}

void Tilemap::clean() {
	SDL_DestroyTexture(tilesetTexture);
}