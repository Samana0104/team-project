#pragma once

#include "SDL_ttf.h"
#include "SDL_image.h"
#include "RectangleButton.h"
#include "TTFTextManger.h"
#include "WindowInterface.h"
#include "Player.h"
#include "PocketmonSeal.h"
#include <ctime>
#include <cstdlib>

namespace GACHA2_BUTTON
{
	enum TYPE
	{
		BACK = 0,
		GACHA = 1,
		COUNT = 2
	};
}

class Gacha2Window : public WindowInterface
{
private:
	SDL_Texture* windowTexture;
	SDL_Rect windowTextureRenderingPos;
	RectangleButton* windowButtons[GACHA2_BUTTON::COUNT];
	TTFTextManger* windowTexts;
	Mix_Chunk* buttonEffectSound;
	PocketmonSeal pocketmonSeal;
	SDL_Rect pocketmonSealTexturePos;
	SDL_Rect pocketmonSealTextureRenderingPos;

	POCKETMON::SEAL gachaResult = POCKETMON::TYPE_1;
	Player* gamePlayer;

	void createWindowTexture(SDL_Renderer* gameRenderer);
	void createButton(SDL_Renderer* gameRenderer);
	void createText(SDL_Renderer* gameRennderer);
	void renderText(SDL_Renderer* gameRenderer);
	void renderButtons(SDL_Renderer* gameRenderer, const int& xPos, const int& yPos);
public:
	explicit Gacha2Window(SDL_Renderer* gameRenderer);

	virtual ~Gacha2Window();
	virtual void renderWindow(SDL_Renderer* gameRenderer, const int& xPos, const int& yPos);
	virtual ButtonType getSeletedButtonTypeInWindow(const int& xPos, const int& yPos);

	void openGacha2Window(SDL_Renderer* gameRenderer, Player* gamePlayer);
	POCKETMON::SEAL pocketmonBreadGacha();
	POCKETMON::SEAL normalPocketmon();
	POCKETMON::SEAL rarePocketmon();
	POCKETMON::SEAL UniquePocketmon();
};