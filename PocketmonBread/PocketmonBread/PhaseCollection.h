#pragma once

#include "PhaseInterface.h"
#include "RectangleButton.h"
#include "TTFTextManger.h"
#include "PocketmonSeal.h"

namespace COLLECTION_BUTTON
{
	enum TYPE
	{
		BACK = 0,
		PHOTO_LEFT=1,
		PHOTO_RIGHT=2,
		TRUE_ENDING=3,
		COUNT=4
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
	TTFTextManger* collectionPageText;

	SDL_Rect presentMousePos;
	SDL_Cursor* mouseArrowCursor;
	SDL_Cursor* mouseHandCursor;

	PocketmonSeal pocketmonSeals;
	Player * gamePlayer;

	void createBackgroundTexture(SDL_Renderer* gameRenderer);
	void createBackButton(SDL_Renderer* gameRenderer);
	void createPhotoLeftButton(SDL_Renderer* gameRenderer);
	void createPhotoRightButton(SDL_Renderer* gameRenderer);
	void createTrueEndingButton(SDL_Renderer* gameRenderer);

	void createCollectedCountText(SDL_Renderer* gameRenderer);
	void createCollectionPageText(SDL_Renderer* gameRenderer);

	void createMouseCursor();
	void clickButtonsInRange();
	void selectButtonType(const COLLECTION_BUTTON::TYPE& buttonType);
	void renderButtons();
public:
	PhaseCollection(SDL_Window* gameWindow, SDL_Renderer* gameRender, Player* _gamePlayer);
	virtual ~PhaseCollection();

	virtual void handleEvents(const SDL_Event&);
	virtual void updateDatas();
	virtual void renderFrames();
	virtual void openPhase();
	virtual void closePhase();
};