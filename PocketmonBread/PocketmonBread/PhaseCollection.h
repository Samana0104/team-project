#pragma once

#include "PhaseInterface.h"
#include "RectangleButton.h"
#include "TTFTextManger.h"

namespace COLLECTION_BUTTON
{
	enum TYPE
	{
		BACK = 0,
		PHOTO_LEFT=1,
		PHOTO_RIGHT=2,
		COUNT=3
	};
}

const int COLLECTION_MAX_COUNT = 12;

class PhaseCollection : public PhaseInterface
{
private:
	SDL_Texture* backgroundTexture;
	SDL_Rect backgroundTextureRenderPos;

	RectangleButton* collectionButtons[COLLECTION_BUTTON::COUNT];
	Mix_Music* backgroundMusic;
	Mix_Chunk* buttonEffectSound;
	TTFTextManger* collectedSealText;

	SDL_Rect presentMousePos;
	SDL_Cursor* mouseArrowCursor;
	SDL_Cursor* mouseHandCursor;

	void createBackgroundTexture(SDL_Renderer* gameRenderer);
	void createBackButton(SDL_Renderer* gameRenderer);
	void createPhotoLeftButton(SDL_Renderer* gameRenderer);
	void createPhotoRightButton(SDL_Renderer* gameRenderer);
	void createCollectionCountText(SDL_Renderer* gameRenderer);
	void createMouseCursor();
	void clickButtonsInRange();
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