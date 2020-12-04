#include "GameObjects.h"

#define RELEASEPOINTER(x) { if(x){ delete x; x = NULL;} }

#pragma region GameObject Definitions

void GameObject::draw(SDL_Renderer* _renderer) {
	if (visable) SDL_RenderCopyEx(_renderer, this->gameObjectTexture, 0, &position, this->rotationAngle, &rotationPoint, SDL_FLIP_NONE);
}

void GameObject::clean() {
	SDL_DestroyTexture(this->gameObjectTexture);
}

SDL_Texture* GameObject::getTexture(SDL_Renderer* _renderer, std::string _filename) {
	SDL_Surface* tmpSurface = IMG_Load(_filename.c_str());
	SDL_Texture* texture_ = SDL_CreateTextureFromSurface(_renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);

	return texture_;
}
#pragma endregion

#pragma region Player Definitions

Player::Player(Mouse* _mouse) : mouse(_mouse){
	this->gameObjectTexture = nullptr;
	this->gameObjectTexture2 = nullptr;
	this->gameObjectTexture3 = nullptr;
	this->bulletManager = nullptr;

	this->position = { 1280 / 2, 720 / 2, 50, 75 };
	this->rotationPoint = { (int)(position.w / 2), (int)(position.h * 0.75)};
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

	this->gameObjectTexture = getTexture(_renderer, "./assets/textures/player/player-pistol.png");
	this->gameObjectTexture2 = getTexture(_renderer, "./assets/textures/player/player-rifle.png");
	this->gameObjectTexture3 = getTexture(_renderer, "./assets/textures/player/player-shotgun.png");
	if(this->gameObjectTexture == NULL || this->gameObjectTexture2 == NULL || this->gameObjectTexture3 == NULL){
		return false;
	}

	bulletManager = new BulletManager();
	if (!bulletManager->init(_renderer, getTexture(_renderer, "./assets/textures/pellet.png"))) {
		std::cerr << "Failed to Initialize Bullet Manager: " << SDL_GetError() << std::endl;
		return false;
	}

	return true;
}

void Player::processInput(bool *keyDown, bool *buttonDown) {

	//Player Movement
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

	// Player Shooting
	if (keyDown[SDL_SCANCODE_SPACE] || buttonDown[SDL_BUTTON_LEFT]) {
		bulletManager->fireBullet( (position.x + rotationPoint.x), (position.y + rotationPoint.y), rotationAngle);
	}

	// Player Gun Selection
	if (keyDown[SDL_SCANCODE_1]) {
		selectedWeapon = 1;
	}
	if (keyDown[SDL_SCANCODE_2]) {
		selectedWeapon = 2;
	}
	if (keyDown[SDL_SCANCODE_3]) {
		selectedWeapon = 3;
	}
}

void Player::update(){
	rotationAngle = -90 + atan2((position.y + rotationPoint.y) - mouse->getY(), (position.x + rotationPoint.x) - mouse->getX()) * (180 / PI);
	bulletManager->update();
}

void Player::draw(SDL_Renderer* _renderer) {
	if (visable) {
		bulletManager->draw(_renderer);
		switch (selectedWeapon) {
		case 1: default:
			SDL_RenderCopyEx(_renderer, this->gameObjectTexture, 0, &position, this->rotationAngle, &rotationPoint, SDL_FLIP_NONE);
			break;
		case 2:
			SDL_RenderCopyEx(_renderer, this->gameObjectTexture2, 0, &position, this->rotationAngle, &rotationPoint, SDL_FLIP_NONE);
			break;
		case 3:
			SDL_RenderCopyEx(_renderer, this->gameObjectTexture3, 0, &position, this->rotationAngle, &rotationPoint, SDL_FLIP_NONE);
			break;
		}
	}
}
#pragma endregion

#pragma region Zombie Definitions


#pragma endregion

