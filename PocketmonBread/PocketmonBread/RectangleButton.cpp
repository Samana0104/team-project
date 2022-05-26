#include "RectangleButton.h"

RectangleButton::RectangleButton(const SDL_Rect& _buttonTexturePos, const SDL_Rect& _buttonTextureRenderingPos, SDL_Texture* _buttonTexture)
	: buttonTexture(_buttonTexture), buttonTexturePos(_buttonTexturePos), buttonTextureRenderingPos(_buttonTextureRenderingPos)
{
	this->buttonBigTextureRenderingPos.x = _buttonTextureRenderingPos.x - 35;
	this->buttonBigTextureRenderingPos.y = _buttonTextureRenderingPos.y - 40;
	this->buttonBigTextureRenderingPos.w = _buttonTextureRenderingPos.w + 70;
	this->buttonBigTextureRenderingPos.h = _buttonTextureRenderingPos.h + 40;
}

bool RectangleButton::isClickingButtonInRange(const int& xPos, const int& yPos)
{
	if (!this->isButtonSelection)
		return false;

	if (xPos >= this->buttonTextureRenderingPos.x && xPos <= this->buttonTextureRenderingPos.x + this->buttonTextureRenderingPos.w
		&& yPos >= this->buttonTextureRenderingPos.y && yPos <= this->buttonTextureRenderingPos.y + this->buttonTextureRenderingPos.h)
		return true;

	return false;
}

void RectangleButton::setButtonTexturePos(const SDL_Rect& _buttonTexturePos)
{
	this->buttonTexturePos = _buttonTexturePos;
}

void RectangleButton::setButtonTextureRenderingPos(const SDL_Rect& _buttonTextureRenderingPos)
{
	this->buttonTextureRenderingPos = _buttonTextureRenderingPos;
	this->buttonBigTextureRenderingPos.x = _buttonTextureRenderingPos.x - 35;
	this->buttonBigTextureRenderingPos.y = _buttonTextureRenderingPos.y - 40;
	this->buttonBigTextureRenderingPos.w = _buttonTextureRenderingPos.w + 70;
	this->buttonBigTextureRenderingPos.h = _buttonTextureRenderingPos.h + 40;
}

SDL_Rect RectangleButton::getButtonTexturePos() const
{
	return this->buttonTexturePos;
}

SDL_Rect RectangleButton::getButtonTextureRenderingPos() const
{
	return this->buttonTextureRenderingPos;
}

void RectangleButton::RenderButtonTexture(SDL_Renderer* renderer)
{
	if (this->isButtonSelection)
		SDL_SetTextureColorMod(this->buttonTexture, 255, 255, 255);
	else
		SDL_SetTextureColorMod(this->buttonTexture, 180, 180, 180);

	SDL_RenderCopy(renderer, this->buttonTexture, &(this->buttonTexturePos), &(this->buttonTextureRenderingPos));
}

void RectangleButton::RenderButtonTextureOnButton(SDL_Renderer* renderer)
{
	SDL_SetTextureColorMod(this->buttonTexture, 200, 200, 200);
	SDL_RenderCopy(renderer, this->buttonTexture, &(this->buttonTexturePos), &(this->buttonTextureRenderingPos));
	//SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	//SDL_RenderFillRect(renderer, &(this->buttonTextureRenderingPos));
}

// 이 기능은 편의점의 버튼 크기 확장을 위한 기능
void RectangleButton::RenderButtonTextureOnClicking(SDL_Renderer* renderer)
{
	SDL_SetTextureColorMod(this->buttonTexture, 150, 150, 150);
	SDL_RenderCopy(renderer, this->buttonTexture, &(this->buttonTexturePos), &(this->buttonBigTextureRenderingPos));
}

void RectangleButton::canSelectButton(const bool& selection)
{
	this->isButtonSelection = selection;
}

RectangleButton::~RectangleButton()
{
	SDL_DestroyTexture(this->buttonTexture);
}
