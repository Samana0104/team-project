#pragma once

#include "PhaseInterface.h"
#include "RectangleButton.h"

namespace COLLECTION_BUTTON
{
	enum TYPE
	{
	};
}
class PhaseCollection : public PhaseInterface
{
private:
	SDL_Texture* backgroundTexture;
	SDL_Rect backgroundTextureRenderPos;

	//RectangleButton* mainButtons[MAIN_BUTTON::COUNT];
	Mix_Music* backgroundMusic;
	SDL_Rect presentMousePos;
	SDL_Cursor* mouseArrowCursor;
	SDL_Cursor* mouseHandCursor;

	void createBackgroundTexture(SDL_Renderer* gameRenderer);
	void createMouseCursor();
	void clickButtonsInRange(const int& mouseXPos, const int& mouseYPos);
	void selectButtonType(const COLLECTION_BUTTON::TYPE& buttonType);
	void renderButtons();
public:
	PhaseCollection(SDL_Window* gameWindow, SDL_Renderer* gameRender);
	virtual ~PhaseCollection();

	virtual void handleEvents(const SDL_Event&);
	virtual void updateDatas();
	virtual void renderFrames();
	virtual void openPhase();
	virtual void closePhase();
};