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

void GameObject::shiftColliders() {
	collider_Box.x = position.x;
	collider_Box.y = position.y;

	collider_Circle.x = position.x + rotationPoint.x;
	collider_Circle.y = position.y + rotationPoint.y;
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

bool GameObject::checkTileCollision(std::vector<Tile> _collideableTiles) {

	SDL_Rect intersectResult;
	for (auto& tile : _collideableTiles) {
		if (SDL_IntersectRect(&collider_Box, &tile.getbox_Collider(), &intersectResult)) return true;
	}

	return false;
}

double GameObject::distanceSquared(int _obj1_x, int _obj1_y, int _obj2_x, int _obj2_y) {
	return 0;
}

#pragma endregion

#pragma region Player Definitions

Player::Player(Mouse* _mouse, BulletManager* _bulletManager) : mouse(_mouse), bulletManager(_bulletManager) {

	this->maxHealth = 100;
	this->health = this->maxHealth;
	this->selectedWeapon = 1;

	this->gameObjectTexture = nullptr;
	this->gameObjectTexture2 = nullptr;
	this->gameObjectTexture3 = nullptr;

	this->position = { 1280 / 2 - 40, 720 / 2, 50, 75 };
	this->oldPosX = nullptr; this->oldPosY = nullptr;
	this->rotationPoint = { (int)(position.w / 2), (int)(position.h * 0.75)};
	this->visable = true;

	this->movementSpeed = 1;
	this->velocityX = 0;
	this->velocityY = 0;
	this->rotationAngle = 0;

	collider_Circle.radius = position.w / 4;
	collider_Box.w = position.w;
	collider_Box.h = position.h / 2;
	this->shiftColliders();
}
Player::~Player() {
	RELEASEPOINTER(bulletManager);
	RELEASEPOINTER(oldPosX);
	RELEASEPOINTER(oldPosY);
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

	return true;
}

void Player::processInput(bool *keyDown, bool *buttonDown) {
	
	//Player Movement
	if (keyDown[SDL_SCANCODE_W] || keyDown[SDL_SCANCODE_UP]) {
		velocityY -= movementSpeed;
		if (velocityY < -MAX_MOVEMENT_SPEED) {
			velocityY = -MAX_MOVEMENT_SPEED;
		}
	}
	else if (velocityY < 0) {
		velocityY += movementSpeed;
	}

	if (keyDown[SDL_SCANCODE_S] || keyDown[SDL_SCANCODE_DOWN]) {
		velocityY += movementSpeed;
		if (velocityY > MAX_MOVEMENT_SPEED) {
			velocityY = MAX_MOVEMENT_SPEED;
		}
	}
	else if (velocityY > 0)
	{
		velocityY -= movementSpeed;
	}

	if (keyDown[SDL_SCANCODE_A] || keyDown[SDL_SCANCODE_LEFT]) {
		velocityX -= movementSpeed;
		if (velocityX < -MAX_MOVEMENT_SPEED) {
			velocityX = -MAX_MOVEMENT_SPEED;
		}
	}
	else if (velocityX < 0) {
		velocityX += movementSpeed;
	}

	if (keyDown[SDL_SCANCODE_D] || keyDown[SDL_SCANCODE_RIGHT]) {
		velocityX += movementSpeed;		
		if (velocityX > MAX_MOVEMENT_SPEED) {
			velocityX = MAX_MOVEMENT_SPEED;
		}
	}
	else if (velocityX > 0) {
		velocityX -= movementSpeed;
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

void Player::update(std::vector<Tile> _collideableTiles){

	oldPosX = &position.x;
	oldPosY = &position.y;

	position.x += velocityX;
	shiftColliders();

	if (getCentreX() - collider_Circle.radius < 0 || checkTileCollision(_collideableTiles) || getCentreX() + collider_Circle.radius > 1280) {
		position.x -= velocityX;
		shiftColliders();
	}

	position.y += velocityY;
	shiftColliders();

	if (getCentreY() - collider_Circle.radius < 0 || checkTileCollision(_collideableTiles) ||getCentreY() + collider_Circle.radius > 720) {
		position.y -= velocityY;
		shiftColliders();
	}

	rotateTowardsPoint(mouse->getX(), mouse->getY());

	positionHealthbar(position.x - HEALTHBAR_WIDTH / 4, position.y);
}

void Player::draw(SDL_Renderer* _renderer) {
	if (visable) {
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

	this->movementSpeed = 2;
	this->rotationAngle = 0;

	this->visable = true;
	this->position = { 1280 / 2, 720 / 2, 50, 50 };
	this->rotationPoint = { position.w/2, position.h/2 };
	this->collider_Box.w = 50;
	this->collider_Box.h = 50;

	this->gameObjectTexture = nullptr;

	this->shiftColliders();
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

void Zombie::update(BulletManager* _bulletManager, Player* _player, std::vector<Tile> _collideableTiles) {
	if (visable) {
		oldPosX = &position.x;
		oldPosY = &position.y;


		if (position.x < _player->getCentreX()) {
			position.x += movementSpeed;
			shiftColliders();

			if (checkTileCollision(_collideableTiles)) {
				position.x -= movementSpeed;
				shiftColliders();
			}
		}
		

		if (position.x > _player->getCentreX()) {
			position.x -= movementSpeed;
			shiftColliders();

			if (checkTileCollision(_collideableTiles)) {
				position.x += movementSpeed;
				shiftColliders();
			}
		}
		

		if (position.y < _player->getCentreY()) {
			position.y += movementSpeed;
			shiftColliders();

			if (checkTileCollision(_collideableTiles)) {
				position.y -= movementSpeed;
				shiftColliders();
			}
		}
		

		if (position.y > _player->getCentreY()) {
			position.y -= movementSpeed;

			if (checkTileCollision(_collideableTiles)) {
				position.y += movementSpeed;
			}
		}
		

		shiftColliders();
		positionHealthbar(position.x - HEALTHBAR_WIDTH / 4, (position.y + position.h) + 10);

		SDL_Rect intersectResult;
		for (auto& bullet : _bulletManager->bullets) {
			SDL_Rect tempBulletRect = { bullet.x, bullet.y, 10, 10 };

			if (SDL_IntersectRect(&collider_Box, &tempBulletRect, &intersectResult)) {
				damageObject(10);
				bullet.isVisable = false;
			}
		}

		if (SDL_IntersectRect(&collider_Box, &_player->collider_Box, &intersectResult)) {
			attackPlayer(_player);
		}
	}
}
#pragma endregion

