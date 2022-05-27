#pragma once

#include "SDL.h"
#include "WindowInterface.h"
#include "RectangleButton.h"

namespace MANUAL_BUTTON
{
	enum TYPE
	{
		CONSENTING = 0,
		COUNT=1
	};
}

class ManualWindow : public WindowInterface
{
private:
	SDL_Texture* windowTexture;
	SDL_Rect windowTextureRenderingPos;
	RectangleButton* windowButtons;
	Mix_Chunk* buttonEffectSound;

	void createWindowTexture(SDL_Renderer* gameRenderer);
	void createButton(SDL_Renderer* gameRenderer);
	void renderButtons(SDL_Renderer* gameRenderer, const int& xPos, const int& yPos);
public:
	explicit ManualWindow(SDL_Renderer* gameRenderer);

	virtual ~ManualWindow();
	virtual void renderWindow(SDL_Renderer* gameRenderer, const int& xPos, const int& yPos);
	virtual ButtonType getSeletedButtonTypeInWindow(const int& xPos, const int& yPos);
};