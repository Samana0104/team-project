#include "PhaseCollection.h"
#include "SDL_image.h"
#include "ConstantDecl.h"

PhaseCollection::PhaseCollection(SDL_Window* gameWindow, SDL_Renderer* gameRenderer, Player* _gamePlayer) : 
	pocketmonSeals(gameRenderer), PhaseInterface(gameWindow, gameRenderer), gamePlayer(_gamePlayer)
{
	this->backgroundMusic = Mix_LoadMUS("../../resources/sounds/collection_bgm.mp3");
	this->buttonEffectSound = Mix_LoadWAV("../../resources/sounds/main_button_sound.mp3"); 
	createBackgroundTexture(gameRenderer);
	createBackButton(gameRenderer);
	createPhotoLeftButton(gameRenderer);
	createPhotoRightButton(gameRenderer);
	createCollectedCountText(gameRenderer);
	createCollectionPageText(gameRenderer);
	createTrueEndingButton(gameRenderer);
	createMouseCursor();
}

void PhaseCollection::createBackgroundTexture(SDL_Renderer* gameRenderer)
{
	SDL_Surface* tmpSurface = IMG_Load("../../resources/images/collection_background.png");
	this->backgroundTexture = SDL_CreateTextureFromSurface(gameRenderer, tmpSurface);
	this->backgroundTextureRenderPos = { 0, 0, GAME_WINDOW::WIDTH, GAME_WINDOW::HEIGHT };
	SDL_FreeSurface(tmpSurface);
}

void PhaseCollection::createBackButton(SDL_Renderer* gameRenderer)
{
	SDL_Rect texturePos = { 0, 0, 82, 219 };
	SDL_Rect renderingPos = { 1518, 108, 82, 219 };

	SDL_Surface* tmpSurface = IMG_Load("../../resources/images/collection_close_button.png");
	this->collectionButtons[COLLECTION_BUTTON::BACK] = new RectangleButton(texturePos, renderingPos, SDL_CreateTextureFromSurface(gameRenderer, tmpSurface));
	SDL_FreeSurface(tmpSurface);
}

void PhaseCollection::createPhotoLeftButton(SDL_Renderer* gameRenderer)
{
	SDL_Rect texturePos = { 0, 0, 61, 70 };
	SDL_Rect renderingPos = { 467, 803, 61, 70 };

	SDL_Surface* tmpSurface = IMG_Load("../../resources/images/collection_left_button.png");
	this->collectionButtons[COLLECTION_BUTTON::PHOTO_LEFT] = new RectangleButton(texturePos, renderingPos, SDL_CreateTextureFromSurface(gameRenderer, tmpSurface));
	SDL_FreeSurface(tmpSurface);
}


void PhaseCollection::createPhotoRightButton(SDL_Renderer* gameRenderer)
{
	SDL_Rect texturePos = { 0, 0, 61, 70 };
	SDL_Rect renderingPos = { 1344, 803, 61, 70 };

	SDL_Surface* tmpSurface = IMG_Load("../../resources/images/collection_right_button.png");
	this->collectionButtons[COLLECTION_BUTTON::PHOTO_RIGHT] = new RectangleButton(texturePos, renderingPos, SDL_CreateTextureFromSurface(gameRenderer, tmpSurface));
	SDL_FreeSurface(tmpSurface);
}

void PhaseCollection::createTrueEndingButton(SDL_Renderer* gameRenderer)
{
	SDL_Rect texturePos = { 0, 0, 270, 58 };
	SDL_Rect renderingPos = { 45, 350, 270, 58 };

	SDL_Surface* tmpSurface = IMG_Load("../../resources/images/true_ending_button.png");
	this->collectionButtons[COLLECTION_BUTTON::TRUE_ENDING] = new RectangleButton(texturePos, renderingPos, SDL_CreateTextureFromSurface(gameRenderer, tmpSurface));
	this->collectionButtons[COLLECTION_BUTTON::TRUE_ENDING]->canSelectButton(false);
	SDL_FreeSurface(tmpSurface);
}

void PhaseCollection::createCollectedCountText(SDL_Renderer* gameRenderer)
{
	SDL_Color textColor = { 255, 255, 255, 255 };
	SDL_Rect renderingPos = { 1313, 50, 0, 0 };
	std::string text("0 / ");
	text += std::to_string(COLLECTION_MAX_COUNT);

	this->collectedSealText = new TTFTextManger(gameRenderer, text,
		TTF_OpenFont("../../resources/fonts/NEXON Lv2 Gothic Bold.ttf", 34), renderingPos, textColor);
}

void PhaseCollection::createCollectionPageText(SDL_Renderer* gameRenderer)
{
	SDL_Color textColor = { 255, 255, 255, 255 };
	SDL_Rect renderingPos = { 880, 820, 0, 0 };
	std::string text("1 / 2");

	this->collectionPageText = new TTFTextManger(gameRenderer, text,
		TTF_OpenFont("../../resources/fonts/NEXON Lv2 Gothic Bold.ttf", 34), renderingPos, textColor);
}

void PhaseCollection::createMouseCursor()
{
	this->mouseArrowCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
	this->mouseHandCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
}

void PhaseCollection::handleEvents(const SDL_Event& gameEvent)
{
	this->presentMousePos.x = gameEvent.button.x;
	this->presentMousePos.y = gameEvent.button.y;

	switch (gameEvent.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		if (gameEvent.button.button == SDL_BUTTON_LEFT)
			clickButtonsInRange();
		break;
	}
}

void PhaseCollection::clickButtonsInRange()
{
	for (int i = 0; i < COLLECTION_BUTTON::COUNT; i++)
	{
		if (this->collectionButtons[i]->isClickingButtonInRange(presentMousePos.x, presentMousePos.y))
			selectButtonType(static_cast<COLLECTION_BUTTON::TYPE>(i));
	}
}

void PhaseCollection::selectButtonType(const COLLECTION_BUTTON::TYPE& buttonType)
{

	switch (buttonType)
	{
	case COLLECTION_BUTTON::BACK:
		setNextGamePhase(GAME_PHASE::MAIN);
		break;
	case COLLECTION_BUTTON::PHOTO_LEFT:
		this->pocketmonSeals.ChangeFormerCollectionPage();
		this->collectionPageText->setText("1 / 2", getGameRenderer());
		break;
	case COLLECTION_BUTTON::PHOTO_RIGHT:
		this->pocketmonSeals.ChangeNextCollectionPage();
		this->collectionPageText->setText("2 / 2", getGameRenderer());
		break;
	case COLLECTION_BUTTON::TRUE_ENDING:
		setNextGamePhase(GAME_PHASE::TRUE_ENDING);
		break;
	}

	Mix_PlayChannel(1, this->buttonEffectSound, 0);
}

void PhaseCollection::updateDatas()
{
}

void PhaseCollection::renderFrames()
{
	SDL_RenderCopy(getGameRenderer(), this->backgroundTexture, &(this->backgroundTextureRenderPos), &(this->backgroundTextureRenderPos));
	this->collectedSealText->renderTextTexture(getGameRenderer());
	this->collectionPageText->renderTextTexture(getGameRenderer());
	this->pocketmonSeals.renderPocketmonSeal(getGameRenderer(), this->gamePlayer);
	renderButtons();
}

void PhaseCollection::renderButtons()
{
	bool isMouseInRange = false;
	for (int i = 0; i < COLLECTION_BUTTON::COUNT; i++)
	{
		if (i == COLLECTION_BUTTON::TRUE_ENDING)
		{
			if (!this->collectionButtons[COLLECTION_BUTTON::TRUE_ENDING]->getIsButtonSelection())
				continue;
		}

		if (this->collectionButtons[i]->isClickingButtonInRange(this->presentMousePos.x, this->presentMousePos.y))
		{
			SDL_SetCursor(this->mouseHandCursor);
			this->collectionButtons[i]->RenderButtonTextureOnButton(getGameRenderer());
			isMouseInRange = true;
		}
		else
		{
			this->collectionButtons[i]->RenderButtonTexture(getGameRenderer());
		}
	}

	if (!isMouseInRange) // 이게 없으면 버튼이 범위안에 있어도 커서가 화살표로 바뀜
		SDL_SetCursor(this->mouseArrowCursor);
}

void PhaseCollection::openPhase()
{
	if (this->gamePlayer->getPocketmonSealCount() == COLLECTION_MAX_COUNT)
		this->collectionButtons[COLLECTION_BUTTON::TRUE_ENDING]->canSelectButton(true);

	this->collectedSealText->setText(std::to_string(this->gamePlayer->getPocketmonSealCount()) + " / 12", getGameRenderer());
	this->pocketmonSeals.ChangeFormerCollectionPage();
	this->collectionPageText->setText("1 / 2", getGameRenderer());
	setNextGamePhase(GAME_PHASE::TYPE::NONE);
	Mix_FadeInMusic(this->backgroundMusic, -1, 2000);
}

void PhaseCollection::closePhase()
{
	SDL_SetCursor(this->mouseArrowCursor);
	Mix_HaltMusic();
}

PhaseCollection::~PhaseCollection()
{
	for (int i = 0; i < COLLECTION_BUTTON::COUNT; i++)
		delete this->collectionButtons[i];

	delete this->collectedSealText;
	delete this->collectionPageText;

	SDL_DestroyTexture(this->backgroundTexture);
	Mix_FreeMusic(this->backgroundMusic);
	Mix_FreeChunk(this->buttonEffectSound);
	SDL_FreeCursor(this->mouseArrowCursor);
	SDL_FreeCursor(this->mouseHandCursor);
}