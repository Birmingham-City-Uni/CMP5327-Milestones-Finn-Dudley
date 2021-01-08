#include "UIManager.h"

UIManager::UIManager() {
	this->pistolBulletTexture = nullptr;
	this->rifleBulletTexture = nullptr;
	this->shotgunShellTexture = nullptr;

	this->lastScore = -1;
}

UIManager::~UIManager() {

}

bool UIManager::init(SDL_Renderer* _renderer) {
	
	SDL_Surface* pistolUISurface = IMG_Load("./assets/textures/pistolBulletUI.png");
	SDL_Surface* rifleUISurface = IMG_Load("./assets/textures/rifleBulletUI.png");
	SDL_Surface* shotgunUISurface = IMG_Load("./assets/textures/shotgunBulletUI.png");

	this->pistolBulletTexture = SDL_CreateTextureFromSurface(_renderer, pistolUISurface);
	this->rifleBulletTexture = SDL_CreateTextureFromSurface(_renderer, rifleUISurface);
	this->shotgunShellTexture = SDL_CreateTextureFromSurface(_renderer, shotgunUISurface);

	SDL_FreeSurface(pistolUISurface);
	SDL_FreeSurface(rifleUISurface);
	SDL_FreeSurface(shotgunUISurface);

	if (pistolBulletTexture == NULL || rifleBulletTexture == NULL || shotgunShellTexture == NULL) {
		return false;
	}
	
	textFont = TTF_OpenFont("./assets/fonts/SpecialElite.ttf", 28);

	scorePosition = { 1280/2 - 32, 10, 75, 28 };
	scoreColor = { 255, 0, 0, 255 };
	updateScoreText(_renderer, 0);

	weaponTypePosition = { 1240, 600, 30, 100 };

	return true;
}

void UIManager::draw(SDL_Renderer* _renderer, int _selectedWeapon) {
	SDL_SetRenderDrawColor(_renderer, 1, 1, 1, 0);
	SDL_RenderFillRect(_renderer, &scorePosition);

	SDL_RenderCopy(_renderer, scoreFontTexture, NULL, &scorePosition);
	if (selectedWeaponUI != _selectedWeapon) selectedWeaponUI = _selectedWeapon;
	switch (selectedWeaponUI) {
	case 1: default:
		SDL_RenderCopy(_renderer, this->pistolBulletTexture, NULL, &weaponTypePosition);
		break;
	case 2:
		SDL_RenderCopy(_renderer, this->rifleBulletTexture, NULL, &weaponTypePosition);
		break;
	case 3:
		SDL_RenderCopy(_renderer, this->shotgunShellTexture, NULL, &weaponTypePosition);
		break;
	}
}

void UIManager::clean() {
	SDL_DestroyTexture(pistolBulletTexture);
	SDL_DestroyTexture(rifleBulletTexture);
	SDL_DestroyTexture(shotgunShellTexture);

}

void UIManager::updateScoreText(SDL_Renderer* _renderer, int _score) {
	if (lastScore < _score) {
		lastScore = _score;
		scoreFontTexture = createTextTexture(_renderer, "Score: " + std::to_string(_score), scoreColor);
	}
}

SDL_Texture* UIManager::createTextTexture(SDL_Renderer* _renderer, std::string _textForTexture, SDL_Color _textColor) {

	SDL_Surface* tempTextSurface = TTF_RenderText_Solid(textFont, _textForTexture.c_str(), _textColor);
	if (tempTextSurface == NULL) {
		std::cerr << "Text Surface was Unable to Render: " << SDL_GetError() << std::endl;
		return NULL;
	}
	else {
		SDL_Texture* fontTexture_ = SDL_CreateTextureFromSurface(_renderer, tempTextSurface);
		SDL_FreeSurface(tempTextSurface);
		return fontTexture_;
	}
}