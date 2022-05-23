#pragma once

#include "PhaseInterface.h"
#include "RectangleButton.h"

class PhaseMain : public PhaseInterface
{
private:
	SDL_Texture* backgroundTexture;
	SDL_Rect backgroundTextureRenderPos;
	SDL_Rect presentMousePos;

	SDL_Cursor* mouseArrowCursor;
	SDL_Cursor* mouseHandCursor;

	void createBackgroundTexture(SDL_Renderer* gameRenderer);
public:
	PhaseMain(SDL_Window* gameWindow, SDL_Renderer* gameRender);
	virtual ~PhaseMain();

	virtual void openPhase();
	virtual void handleEvents(const SDL_Event&);
	virtual void updateDatas();
	virtual void renderFrames();
	virtual void closePhase();
};