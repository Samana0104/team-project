#include "RectangleButton.h"

RectangleButton::RectangleButton(const SDL_Rect& _buttonTexturePos, const SDL_Rect& _buttonTextureRenderingPos, SDL_Texture* _buttonTexture) 
	: buttonTexture(_buttonTexture)
{
	setButtonTexturePos(_buttonTexturePos);
	setButtonTextureRenderingPos(_buttonTextureRenderingPos);
}

bool RectangleButton::isClickingButtonInRange(const int& xPos, const int& yPos)
{
	if (xPos >= this->buttonTextureRenderingPos.x && yPos <= this->buttonTextureRenderingPos.x + this->buttonTextureRenderingPos.w
		&& yPos >= this->buttonTextureRenderingPos.y && yPos <= this->buttonTextureRenderingPos.y + this->buttonTextureRenderingPos.h)
		return true;

	return false;
}

void RectangleButton::setButtonTexturePos(const SDL_Rect& _srcPos)
{
	this->buttonTexturePos.x = _srcPos.x;
	this->buttonTexturePos.y = _srcPos.y;
	this->buttonTexturePos.w = _srcPos.w;
	this->buttonTexturePos.h = _srcPos.h;
}

void RectangleButton::setButtonTextureRenderingPos(const SDL_Rect& _renderPos)
{
	this->buttonTextureRenderingPos.x = _renderPos.x;
	this->buttonTextureRenderingPos.y = _renderPos.y;
	this->buttonTextureRenderingPos.w = _renderPos.w;
	this->buttonTextureRenderingPos.h = _renderPos.h;
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
}

void RectangleButton::RenderButtonTextureOnClicking(SDL_Renderer* renderer)
{
}
