#pragma once

#include "SDL_ttf.h"
#include "SDL_image.h"
#include "RectangleButton.h"
#include "TTFTextManger.h"
#include "WindowInterface.h"
#include "Player.h"

namespace GACHA1_BUTTON
{
	enum TYPE
	{
		BACK = 0,
		GACHA = 1,
		COUNT = 2
	};
}

class Gacha1Window : public WindowInterface
{
private:
	SDL_Texture* windowTexture;
	SDL_Rect windowTextureRenderingPos;
	RectangleButton* windowButtons[GACHA1_BUTTON::COUNT];
	TTFTextManger * windowTexts;
	Mix_Chunk* buttonEffectSound;

	void createWindowTexture(SDL_Renderer* gameRenderer);
	void createButton(SDL_Renderer* gameRenderer);
	void createText(SDL_Renderer* gameRennderer);
	void renderText(SDL_Renderer* gameRenderer);
	void renderButtons(SDL_Renderer* gameRenderer, const int& xPos, const int& yPos);
public:
	explicit Gacha1Window(SDL_Renderer* gameRenderer);

	virtual ~Gacha1Window();
	virtual void renderWindow(SDL_Renderer* gameRenderer, const int& xPos, const int& yPos);
	virtual ButtonType getSeletedButtonTypeInWindow(const int& xPos, const int& yPos);

	void openGacha1Window(SDL_Renderer* gameRenderer, Player* gamePlayer);
};