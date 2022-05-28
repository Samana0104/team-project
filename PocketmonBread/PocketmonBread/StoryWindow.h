#pragma once

#include "SDL.h"
#include "WindowInterface.h"

class StoryWindow : public WindowInterface
{
private:
	SDL_Texture* windowTexture;
	SDL_Rect windowTextureRenderingPos;

	void createWindowTexture(SDL_Renderer* gameRenderer);
public:
	explicit StoryWindow(SDL_Renderer* gameRenderer);

	virtual ~StoryWindow();
	virtual void renderWindow(SDL_Renderer* gameRenderer, const int& xPos, const int& yPos);
	virtual ButtonType getSeletedButtonTypeInWindow(const int& xPos, const int& yPos);
};