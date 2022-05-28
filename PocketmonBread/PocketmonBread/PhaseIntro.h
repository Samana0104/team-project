#pragma once

#include "PhaseInterface.h"
#include "RectangleButton.h"
#include "WaringWindow.h"
#include "SDL_image.h"

namespace INTRO_BUTTON
{
	enum TYPE
	{
		START_BUTTON = 0,
		END_BUTTON,
		CHEAT_BUTTON,
		COUNT = 3
	};
}

namespace INTRO_WINDOW
{
	enum TYPE
	{
		CHEAT=0,
		EXIT=1,
		COUNT=2
	};
}

class PhaseIntro : public PhaseInterface
{
private:
	SDL_Texture* backgroundTexture;
	SDL_Rect backgroundTextureRenderPos;
	RectangleButton * introButtons[INTRO_BUTTON::TYPE::COUNT];
	Mix_Chunk* buttonEffectSound;
	Mix_Music* backgroundMusic;
	SDL_Rect presentMousePos;

	WindowInterface* introWindows[INTRO_WINDOW::COUNT];

	SDL_Cursor* mouseArrowCursor;
	SDL_Cursor* mouseHandCursor;

	Player* gamePlayer;

	void createBackgroundTexture(SDL_Renderer * gameRenderer);
	void createStartButton(SDL_Renderer* gameRenderer);
	void createEndButton(SDL_Renderer* gameRenderer);
	void createCheatButton(SDL_Renderer* gameRenderer);
	void createMouseCursor();
	void createExitWaringWindow(SDL_Renderer* gameRenderer);
	void createCheatWaringWindow(SDL_Renderer* gameRenderer);
	
	void renderButtons();
	void clickButtonsInRange();
	void selectButtonType(const INTRO_BUTTON::TYPE& buttonType);
	void selectWindowButtonType(const INTRO_WINDOW::TYPE& windowType);
	void selectExitWaringButtonType(const INTRO_WINDOW::TYPE& windowType);
	void selectCheatWaringButtonType(const INTRO_WINDOW::TYPE& windowType);
	void stopAllButtons();
	void startAllButtons();
public:
	PhaseIntro(SDL_Window * gameWindow, SDL_Renderer* gameRender, Player* _gamePlayer);
	virtual ~PhaseIntro();

	virtual void handleEvents(const SDL_Event&);
	virtual void updateDatas();
	virtual void renderFrames();
	virtual void openPhase();
	virtual void closePhase();
};