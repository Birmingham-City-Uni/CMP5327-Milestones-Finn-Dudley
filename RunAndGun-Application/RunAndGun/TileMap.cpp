#include "Tilemap.h"

Tilemap::Tilemap() {

}

Tilemap::~Tilemap() {

}

bool Tilemap::init(SDL_Renderer* _renderer) {
	SDL_Surface* tmpSurface = IMG_Load("./assets/textures/tilemap.png");
	this->tilesetTexture = SDL_CreateTextureFromSurface(_renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	if (tilesetTexture == NULL) {
		return false;
	}

	return true;
}

void Tilemap::draw(SDL_Renderer* _renderer) {
	for (int _y = 0; _y < MAP_SIZE_Y; _y++){
		for (int _x = 0; _x < MAP_SIZE_X; _x++) {

			SDL_Rect srcRect = { (MAP_DATA[_y][_x] % 8) * 32, ((MAP_DATA[_y][_x]) / 8) * 32, 32, 32 };
			SDL_Rect destRect = { _x * MAP_TILE_PIXELS, _y * MAP_TILE_PIXELS, MAP_TILE_PIXELS, MAP_TILE_PIXELS };
			SDL_RenderCopy(_renderer, tilesetTexture, &srcRect, &destRect);
		}
	}
}

void Tilemap::clean() {
	SDL_DestroyTexture(tilesetTexture);
}

void Tilemap::loadLevel(int _selectedLevel) {

	std::fstream levelFile("assets/data/level1.json", std::fstream::binary);

	levelFile.close();
}