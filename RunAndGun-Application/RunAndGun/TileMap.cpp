#include "Tilemap.h"

Tilemap::Tilemap(int _selectedLevel) : selectedLevel(_selectedLevel) {
	this->tileset = nullptr;
}

Tilemap::~Tilemap() {

}

bool Tilemap::init(SDL_Renderer* _renderer) {
	SDL_Surface* tmpSurface = IMG_Load("./assets/textures/tilemap.png");
	this->tileset = SDL_CreateTextureFromSurface(_renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	if (tileset == NULL) {
		return false;
	}

	if (!loadLevel()) {
		return false;
	}

	return true;
}

void Tilemap::draw(SDL_Renderer* _renderer) {
		
	for (auto tile : map_Tiles) SDL_RenderCopy(_renderer, tileset, &tile.getTexturePos(), &tile.getTilePos());
}

void Tilemap::clean() {
	SDL_DestroyTexture(tileset);

	collideableTiles.clear();
	map_Tiles.clear();
}

bool Tilemap::loadLevel() {
	std::string chosenLevel = "./assets/data/levels/level.txt";
	chosenLevel.insert(26, std::to_string(selectedLevel));

	std::ifstream levelFile(chosenLevel);

	if (levelFile.fail()) {
		std::cerr << "Unable to Load Level File" << std::endl;
		return false;
	}
	else {
		
		for (int _y = 0; _y < MAP_SIZE_Y; _y++) {
			for (int _x = 0; _x < MAP_SIZE_X; _x++) {
				int tileData;
				levelFile >> tileData;

				Tile instance = Tile(_x, _y, tileData, MAP_TILE_PIXELS);
				switch (tileData) {
				
					case 32:
					case 33:
					case 40:
					case 41:
					case 43:
					case 44:
						collideableTiles.push_back(instance);
				
					default:
						break;
				}

				map_Tiles.push_back(instance);
			}
		}
	}

	levelFile.close();

	std::cout << "File Read Complete" << std::endl;

	return true;
}