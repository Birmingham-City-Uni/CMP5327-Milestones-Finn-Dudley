#include "Player.h"

#define RELEASEPOINTER(x) { if(x){ delete x; x = NULL;} }

#pragma region Player

Player::Player(SDL_Renderer * renderer) {
	this->renderer = renderer;
	this->texture = nullptr;

	this->rect = { 1280 / 2, 720 / 2, 50, 75 };
	this->rotationPoint = { rect.w /2, rect.h / 2};
	this->visable = true;

	this->movementSpeed = 3;
	this->rotationSpeed = 2;
	this->rotationAngle = 0;
}
Player::~Player() {

}

bool Player::init() {

	SDL_Surface* tmpSurface = IMG_Load("assets/player/player-rifle.png");
	this->texture = SDL_CreateTextureFromSurface(this->renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	if (texture == NULL) {
		return false;
	}

	return true;
}

void Player::processInput(bool *keyDown) {

	if (keyDown[SDL_SCANCODE_W] || keyDown[SDL_SCANCODE_UP]) {
		// if forward is pressed this will run
		rect.y -= movementSpeed;
	}

	if (keyDown[SDL_SCANCODE_S] || keyDown[SDL_SCANCODE_DOWN]) {
		// if down is pressed this will run
		rect.y += movementSpeed;
	}

	if (keyDown[SDL_SCANCODE_A] || keyDown[SDL_SCANCODE_LEFT]) {
		// if left is pressed this will run
		rect.x -= movementSpeed;
	}

	if (keyDown[SDL_SCANCODE_D] || keyDown[SDL_SCANCODE_RIGHT]) {
		// if right is pressed this will run
		rect.x += movementSpeed;
	}

	if (keyDown[SDL_SCANCODE_Q]) {
		rotationAngle -= rotationSpeed;
	}
	if (keyDown[SDL_SCANCODE_E]) {
		rotationAngle += rotationSpeed;
	}
}

void Player::update() {

}

void Player::draw() {
	if (visable) SDL_RenderCopyEx(this->renderer, this->texture, 0, &rect, this->rotationAngle, &rotationPoint, SDL_FLIP_NONE);
}

void Player::clean() {
	SDL_DestroyTexture(this->texture);
}

#pragma endregion

