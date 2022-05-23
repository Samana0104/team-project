#pragma once

#include "PhaseInterface.h"
#include "RectangleButton.h"

namespace INTRO_BUTTON
{
	enum TYPE
	{
		START_BUTTON,
		END_BUTTON,
		CHEAT_BUTTON,
		COUNT = 3
	};
}

class PhaseIntro : public PhaseInterface
{
private:
	SDL_Texture* backgroundTexture;
	SDL_Rect backgroundTextureRenderPos;
	RectangleButton * introButtons[INTRO_BUTTON::TYPE::COUNT];
	SDL_Rect presentMousePos;

	SDL_Cursor* mouseArrowCursor;
	SDL_Cursor* mouseHandCursor;

	void createBackgroundTexture(SDL_Renderer * gameRenderer);
	void createStartButton(SDL_Renderer* gameRenderer);
	void createEndButton(SDL_Renderer* gameRenderer);
	void createCheatButton(SDL_Renderer* gameRenderer);
	void createMouseCursor();
	void renderButtons();
	void clickButtonsInRange(const int& mouseXPos, const int& mouseYPos);
	void selectButtonType(const INTRO_BUTTON::TYPE& buttonType);
public:
	PhaseIntro(SDL_Window * gameWindow, SDL_Renderer* gameRender);
	virtual ~PhaseIntro();

	virtual void openPhase();
	virtual void handleEvents(const SDL_Event&);
	virtual void updateDatas();
	virtual void renderFrames();
	virtual void closePhase();
};