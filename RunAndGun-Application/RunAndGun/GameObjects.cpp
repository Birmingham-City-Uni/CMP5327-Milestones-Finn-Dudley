#include "GameObjects.h"

#define RELEASEPOINTER(x) { if(x){ delete x; x = NULL;} }
#define PI 3.14159

#pragma region GameObject Definitions

void GameObject::draw(SDL_Renderer* _renderer) {
	if (visable) SDL_RenderCopyEx(_renderer, this->texture, 0, &position, this->rotationAngle, &rotationPoint, SDL_FLIP_NONE);
}

void GameObject::clean() {
	SDL_DestroyTexture(this->texture);
}

bool GameObject::setTexture(SDL_Renderer* _renderer, std::string _filename) {
	SDL_Surface* tmpSurface = IMG_Load(_filename.c_str());
	this->texture = SDL_CreateTextureFromSurface(_renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	if (this->texture == NULL) {
		return false;
	}

	return true;
}
#pragma endregion

#pragma region Player Definitions

Player::Player(Mouse* _mouse) : mouse(_mouse){
	this->texture = nullptr;
	this->bulletManager = nullptr;

	this->position = { 1280 / 2, 720 / 2, 50, 75 };
	this->rotationPoint = { (int)(position.w / 2), (int)(position.h * 0.70)};
	this->visable = true;

	this->movementSpeed = 3;
	this->rotationSpeed = 2;
	this->rotationAngle = 0;
}
Player::~Player() {
	bulletManager->clean();

	if (bulletManager) {
		delete bulletManager;
		bulletManager = nullptr;
	}
}

bool Player::init(SDL_Renderer* _renderer) {

	if (!setTexture(_renderer, "assets/player/player-rifle.png")) {
		return false;
	}

	bulletManager = new BulletManager();
	if (!bulletManager->init(_renderer)) {
		std::cerr << "Failed to Initialize Bullet Manager: " << SDL_GetError() << std::endl;
		return false;
	}

	return true;
}

void Player::processInput(bool *keyDown) {

	if (keyDown[SDL_SCANCODE_W] || keyDown[SDL_SCANCODE_UP]) {
		position.y -= movementSpeed;
	}

	if (keyDown[SDL_SCANCODE_S] || keyDown[SDL_SCANCODE_DOWN]) {
		position.y += movementSpeed;
	}

	if (keyDown[SDL_SCANCODE_A] || keyDown[SDL_SCANCODE_LEFT]) {
		position.x -= movementSpeed;
	}

	if (keyDown[SDL_SCANCODE_D] || keyDown[SDL_SCANCODE_RIGHT]) {
		position.x += movementSpeed;
	}

	if (keyDown[SDL_SCANCODE_SPACE]) {
		bulletManager->fireBullet( (position.x + rotationPoint.x), (position.y + rotationPoint.y), rotationAngle);
	}

}

void Player::update(){
	rotationAngle = -90 + atan2((position.y + rotationPoint.y) - mouse->getY(), (position.x + rotationPoint.x) - mouse->getX()) * (180 / PI);

	bulletManager->update();
}

void Player::draw(SDL_Renderer* _renderer) {
	if (visable) {
		bulletManager->draw(_renderer);
		SDL_RenderCopyEx(_renderer, this->texture, 0, &position, this->rotationAngle, &rotationPoint, SDL_FLIP_NONE);
	}
}
#pragma endregion

#pragma region Zombie Definitions


#pragma endregion

