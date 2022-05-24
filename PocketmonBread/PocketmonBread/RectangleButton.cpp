#include "RectangleButton.h"
#include <iostream>
RectangleButton::RectangleButton(const SDL_Rect& _buttonTexturePos, const SDL_Rect& _buttonTextureRenderingPos, SDL_Texture* _buttonTexture) 
	: buttonTexture(_buttonTexture)
{
	setButtonTexturePos(_buttonTexturePos);
	setButtonTextureRenderingPos(_buttonTextureRenderingPos);
}

bool RectangleButton::isClickingButtonInRange(const int& xPos, const int& yPos)
{
	if (!this->setButtonSelection)
		return false;

	if (xPos >= this->buttonTextureRenderingPos.x && xPos <= this->buttonTextureRenderingPos.x + this->buttonTextureRenderingPos.w
		&& yPos >= this->buttonTextureRenderingPos.y && yPos <= this->buttonTextureRenderingPos.y + this->buttonTextureRenderingPos.h)
		return true;

	return false;
}

void RectangleButton::setButtonTexturePos(const SDL_Rect& _buttonTexturePos)
{
	this->buttonTexturePos.x = _buttonTexturePos.x;
	this->buttonTexturePos.y = _buttonTexturePos.y;
	this->buttonTexturePos.w = _buttonTexturePos.w;
	this->buttonTexturePos.h = _buttonTexturePos.h;
}

void RectangleButton::setButtonTextureRenderingPos(const SDL_Rect& _buttonTextureRenderingPos)
{
	this->buttonTextureRenderingPos.x = _buttonTextureRenderingPos.x;
	this->buttonTextureRenderingPos.y = _buttonTextureRenderingPos.y;
	this->buttonTextureRenderingPos.w = _buttonTextureRenderingPos.w;
	this->buttonTextureRenderingPos.h = _buttonTextureRenderingPos.h;
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
	if (this->setButtonSelection)
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

void RectangleButton::RenderButtonTextureOnClicking(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, this->buttonTexture, &(this->buttonTexturePos), &(this->buttonTextureRenderingPos));
}

void RectangleButton::canSelectButton(const bool& selection)
{
	this->setButtonSelection = selection;
}

RectangleButton::~RectangleButton()
{
	SDL_DestroyTexture(this->buttonTexture);
}
