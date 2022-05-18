#pragma once

#include "SDL.h"

class RectangleButton
{
private:
	SDL_Rect buttonTexturePos;
	SDL_Rect buttonTextureRenderingPos;
	SDL_Texture* buttonTexture;
public:
	explicit RectangleButton(const SDL_Rect & _buttonTexturePos, const SDL_Rect& _buttonTextureRenderingPos, SDL_Texture* _buttonTexture);
	bool isClickingButtonInRange(const int& xPos, const int& yPos);

	void setButtonTexturePos(const SDL_Rect& _buttonTexturePos);
	void setButtonTextureRenderingPos(const SDL_Rect& _buttonTextureRenderingPos);
	SDL_Rect getButtonTexturePos() const;
	SDL_Rect getButtonTextureRenderingPos() const;

	void RenderButtonTexture(SDL_Renderer * renderer);
	void RenderButtonTextureOnClicking(SDL_Renderer * renderer);
};