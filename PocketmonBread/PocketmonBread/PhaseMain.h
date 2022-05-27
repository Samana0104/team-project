#pragma once

#include "PhaseInterface.h"
#include "RectangleButton.h"
#include "TTFTextManger.h"
#include "WaringWindow.h"
#include "ManualWindow.h"

namespace MAIN_BUTTON
{
	enum TYPE
	{
		STAGE_1 = 0,
		STAGE_2 = 1,
		STAGE_3 = 2,
		COLLECTION = 3,
		GAME_START = 4,
		BACK = 5,
		MANUAL = 6,
		GACHA = 7,
		COUNT = 8
	};
}

namespace MAIN_TEXT
{
	enum TYPE
	{
		SELETED_STAGE=0,
		SCORE = 1,
		BREAD_COUNT = 2,
		COUNT=3,
	};
}

namespace MAIN_WINDOW
{
	enum TYPE
	{
		BACK=0,
		MANUAL = 1,
		COUNT=2
	};
}

class PhaseMain : public PhaseInterface
{
private:
	SDL_Texture* backgroundTexture;
	SDL_Rect backgroundTextureRenderPos;

	RectangleButton * mainButtons[MAIN_BUTTON::COUNT];
	MAIN_BUTTON::TYPE selectedStage = MAIN_BUTTON::STAGE_1;

	Mix_Music* backgroundMusic;
	Mix_Chunk* buttonEffectSound;
	SDL_Rect presentMousePos;
	TTFTextManger* mainTexts[MAIN_TEXT::COUNT];

	WindowInterface* mainWindows[MAIN_WINDOW::COUNT];

	SDL_Cursor* mouseArrowCursor;
	SDL_Cursor* mouseHandCursor;
	

	void createBackgroundTexture(SDL_Renderer* gameRenderer);
	void createBackButton(SDL_Renderer* gameRenderer);
	void createCollectionButton(SDL_Renderer* gameRenderer);
	void createManualButton(SDL_Renderer* gameRenderer);
	void createStage1Button(SDL_Renderer* gameRenderer);
	void createStage2Button(SDL_Renderer* gameRenderer);
	void createStage3Button(SDL_Renderer* gameRenderer);
	void createGameStartButton(SDL_Renderer* gameRenderer);
	void createGachaButton(SDL_Renderer* gameRenderer);
	void createSelectedStageText(SDL_Renderer* gameRenderer);
	void createScoreText(SDL_Renderer* gameRenderer);
	void createBreadCountText(SDL_Renderer* gameRenderer);
	void createBackWaringWindow(SDL_Renderer* gameRenderer);
	void createManualWindow(SDL_Renderer* gameRenderer);
	void createMouseCursor();

	void clickButtonsInRange();
	void selectButtonType(const MAIN_BUTTON::TYPE& buttonType);

	void selectWindowButtonType(const MAIN_WINDOW::TYPE& windowType);
	void selectBackWaringButtonType(const MAIN_WINDOW::TYPE& windowType);
	void selectManualButtonType(const MAIN_WINDOW::TYPE& windowType);
	void renderButtons();
	void stopAllButtons();
	void startAllButtons();
public:
	PhaseMain(SDL_Window* gameWindow, SDL_Renderer* gameRender);
	virtual ~PhaseMain();

	virtual void handleEvents(const SDL_Event&);
	virtual void updateDatas();
	virtual void renderFrames();
	virtual void openPhase();
	virtual void closePhase();
};