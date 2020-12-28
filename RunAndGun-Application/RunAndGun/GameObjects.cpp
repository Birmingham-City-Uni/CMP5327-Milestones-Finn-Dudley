#include "GameObjects.h"

#define RELEASEPOINTER(x) { if(x){ delete x; x = NULL;} }

#pragma region GameObject Definitions

void GameObject::draw(SDL_Renderer* _renderer) {
	if (visable) {
		SDL_RenderCopyEx(_renderer, this->gameObjectTexture, 0, &position, this->rotationAngle, &rotationPoint, SDL_FLIP_NONE);
		drawHealthBar(_renderer);
	}
}

void GameObject::clean() {
	SDL_DestroyTexture(this->gameObjectTexture);
}

void GameObject::rotateTowardsPoint(int _x, int _y) {
	this->rotationAngle = -90 + atan2((position.y + rotationPoint.y) - _y, (position.x + rotationPoint.x) - _x) * (180 / PI);
}

SDL_Texture* GameObject::getTexture(SDL_Renderer* _renderer, std::string _filename) {
	SDL_Surface* tmpSurface = IMG_Load(_filename.c_str());
	SDL_Texture* texture_ = SDL_CreateTextureFromSurface(_renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);

	return texture_;
}

void GameObject::drawHealthBar(SDL_Renderer* _renderer) {
	// Health Bar Background Render
	SDL_SetRenderDrawColor(_renderer, 1, 1, 1, 0);
	SDL_RenderFillRect(_renderer, &healthbarBackground);

	// Health Bar Render
	SDL_SetRenderDrawColor(_renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(_renderer, &healthBar);
}

void GameObject::adjustHealthRect() {
	float barSegment = (float)HEALTHBAR_WIDTH / (float)maxHealth;
	healthBar.w = health * barSegment;
}

void GameObject::positionHealthbar(int _x,int  _y) {
	healthBar.x = _x;
	healthBar.y = _y;
	healthbarBackground.x = healthBar.x;
	healthbarBackground.y = healthBar.y;
}

#pragma endregion

#pragma region Player Definitions

Player::Player(Mouse* _mouse) : mouse(_mouse){

	this->maxHealth = 100;
	this->health = this->maxHealth;

	this->gameObjectTexture = nullptr;
	this->gameObjectTexture2 = nullptr;
	this->gameObjectTexture3 = nullptr;
	this->bulletManager = nullptr;

	this->position = { 1280 / 2, 720 / 2, 50, 75 };
	this->rotationPoint = { (int)(position.w / 2), (int)(position.h * 0.75)};
	this->visable = true;

	this->movementSpeed = 3;
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

	std::cout << "Player Max Health: " << this->maxHealth << std::endl;
	std::cout << "Current Player Health: " << this->health << std::endl;

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
		fireSelectedWeapon();
	}

	// Player Gun Selection
	if (keyDown[SDL_SCANCODE_1]) {
		selectedWeapon = 1; // Pistol Selected
		bulletManager->changeWeaponTime();
	}
	if (keyDown[SDL_SCANCODE_2]) {
		selectedWeapon = 2; // Rifle Selected
		bulletManager->changeWeaponTime();
	}
	if (keyDown[SDL_SCANCODE_3]) {
		selectedWeapon = 3; // Shotgun Selected
		bulletManager->changeWeaponTime();
	}
}

void Player::update(){
	rotateTowardsPoint(mouse->getX(), mouse->getY());
	bulletManager->update();

	positionHealthbar(position.x - HEALTHBAR_WIDTH / 4, position.y);
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

		drawHealthBar(_renderer);
	}
}

void Player::fireSelectedWeapon() {
		switch (selectedWeapon)
		{
		default: case 1:
			bulletManager->shootPistol(getCentreX(), getCentreY(), rotationAngle);
			break;

		case 2:
			bulletManager->shootRifle(getCentreX(), getCentreY(), rotationAngle);
			break;

		case 3:
			bulletManager->shootShotgun(getCentreX(), getCentreY(), rotationAngle);
			break;
		}


}
#pragma endregion

#pragma region Zombie Definitions

Zombie::Zombie() {
	this->maxHealth = 100;
	this->health = this->maxHealth;

	this->movementSpeed = 1.5;
	this->rotationAngle = 0;

	this->visable = true;
	this->position = { 1280 / 2, 720 / 2, 50, 50 };
	this->rotationPoint = { position.w/2, position.h/2 };

	this->gameObjectTexture = nullptr;
}

Zombie::~Zombie() {

}

bool Zombie::init(SDL_Renderer* _renderer) {

	this->gameObjectTexture = getTexture(_renderer, "./assets/textures/zombie/zombie-normal.png");
	if (gameObjectTexture == NULL) {
		return false;
	}

	return true;
}

void Zombie::update() {
	if (visable) {
		positionHealthbar(position.x - HEALTHBAR_WIDTH / 4, (position.y + position.h) + 10);
	}
}
#pragma endregion

