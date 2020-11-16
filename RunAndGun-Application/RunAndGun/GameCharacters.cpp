#include "GameCharacters.h"

#define RELEASEPOINTER(x) { if(x){ delete x; x = NULL;} }

SDL_Texture* loadTexture(const char* filename, SDL_Renderer* renderer) {
	
	std::cout << "Loading File: " << filename << std::endl;
	SDL_Surface* surface = IMG_Load(filename);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	std::cout << "Finished Loading: " << filename << std::endl;

	return texture;
}

#pragma region Player

Player::Player(SDL_Renderer * renderer) {
	this->health = 100;

	this->position.y = 0;
	this->position.x = 0;
	this->rotationAngle = 0;

	this->texture = NULL;
	this->renderer = renderer;
}
Player::~Player() {
	RELEASEPOINTER(renderer);

	SDL_DestroyTexture(this->texture);
}

void Player::init() {

	std::cout << "Loading File: Player Texture" << std::endl;
	SDL_Surface* surface = IMG_Load("./Assets/player/PlayerRifle.png");
	this->position.w = surface->w;
	this->position.h = surface->h;
	SDL_Texture* texture = SDL_CreateTextureFromSurface(this->renderer, surface);
	SDL_FreeSurface(surface);
	
}

void Player::processInput(bool *keyDown) {
	 
	if (keyDown[SDL_SCANCODE_W] || keyDown[SDL_SCANCODE_UP]) {
		// if forward is pressed this will run
	}

	if (keyDown[SDL_SCANCODE_S] || keyDown[SDL_SCANCODE_DOWN]) {
		// if down is pressed this will run
	}

	if (keyDown[SDL_SCANCODE_A] || keyDown[SDL_SCANCODE_LEFT]) {
		// if left is pressed this will run
	}

	if (keyDown[SDL_SCANCODE_D] || keyDown[SDL_SCANCODE_RIGHT]) {
		// if right is pressed this will run
	}
}

void Player::update() {

}

void Player::draw() {

	SDL_RenderCopy(this->renderer, this->texture, NULL, &position);
}

#pragma endregion

