#pragma once

#include "PhaseInterface.h"
#include "RectangleButton.h"

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
		COUNT = 6
	};
}
class PhaseMain : public PhaseInterface
{
private:
	SDL_Texture* backgroundTexture;
	SDL_Rect backgroundTextureRenderPos;

	RectangleButton * mainButtons[MAIN_BUTTON::COUNT];
	Mix_Music* backgroundMusic;
	SDL_Rect presentMousePos;
	SDL_Cursor* mouseArrowCursor;
	SDL_Cursor* mouseHandCursor;

	void createBackgroundTexture(SDL_Renderer* gameRenderer);
	void createBackButton(SDL_Renderer* gameRenderer);
	void createMouseCursor();
	void renderButtons();
public:
	PhaseMain(SDL_Window* gameWindow, SDL_Renderer* gameRender);
	virtual ~PhaseMain();

	virtual void handleEvents(const SDL_Event&);
	virtual void updateDatas();
	virtual void renderFrames();
	virtual void openPhase();
	virtual void closePhase();
};