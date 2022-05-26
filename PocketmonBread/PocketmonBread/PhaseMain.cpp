#include "PhaseMain.h"
#include "SDL_image.h"
#include "ConstantDecl.h"

PhaseMain::PhaseMain(SDL_Window* gameWindow, SDL_Renderer* gameRenderer) : PhaseInterface(gameWindow, gameRenderer)
{
	this->backgroundMusic = Mix_LoadMUS("../../resources/sounds/main_bgm.mp3");
	this->buttonEffectSound = Mix_LoadWAV("../../resources/sounds/main_button_sound.mp3");
	createBackgroundTexture(gameRenderer);
	createCollectionButton(gameRenderer);
	createManualButton(gameRenderer);
	createBackButton(gameRenderer);
	createStage1Button(gameRenderer);
	createStage2Button(gameRenderer);
	createStage3Button(gameRenderer);
	createGameStartButton(gameRenderer);
	createGachaButton(gameRenderer);
	createSelectedStageText(gameRenderer);
	createMouseCursor();
}


void PhaseMain::createBackgroundTexture(SDL_Renderer* gameRenderer)
{
	SDL_Surface* tmpSurface = IMG_Load("../../resources/images/main_background.png");
	this->backgroundTexture = SDL_CreateTextureFromSurface(gameRenderer, tmpSurface);
	this->backgroundTextureRenderPos = { 0, 0, GAME_WINDOW::WIDTH, GAME_WINDOW::HEIGHT };
	SDL_FreeSurface(tmpSurface);
}

void PhaseMain::createCollectionButton(SDL_Renderer* gameRenderer)
{
	SDL_Rect texturePos = { 0, 0, 100, 100 };
	SDL_Rect renderingPos = { 1100, 50, 100, 100 };

	SDL_Surface* tmpSurface = IMG_Load("../../resources/images/main_collection_button.png");
	this->mainButtons[MAIN_BUTTON::COLLECTION] = new RectangleButton(texturePos, renderingPos, SDL_CreateTextureFromSurface(gameRenderer, tmpSurface));
	SDL_FreeSurface(tmpSurface);
}

void PhaseMain::createManualButton(SDL_Renderer* gameRenderer)
{
	SDL_Rect texturePos = { 0, 0, 100, 100 };
	SDL_Rect renderingPos = { 1250, 50, 100, 100 };

	SDL_Surface* tmpSurface = IMG_Load("../../resources/images/main_manual_button.png");
	this->mainButtons[MAIN_BUTTON::MANUAL] = new RectangleButton(texturePos, renderingPos, SDL_CreateTextureFromSurface(gameRenderer, tmpSurface));
	SDL_FreeSurface(tmpSurface);
}

void PhaseMain::createBackButton(SDL_Renderer* gameRenderer)
{
	SDL_Rect texturePos = { 0, 0, 100, 100 };
	SDL_Rect renderingPos = { 1400, 50, 100, 100 };

	SDL_Surface* tmpSurface = IMG_Load("../../resources/images/main_back_button.png");
	this->mainButtons[MAIN_BUTTON::BACK] = new RectangleButton(texturePos, renderingPos, SDL_CreateTextureFromSurface(gameRenderer, tmpSurface));
	SDL_FreeSurface(tmpSurface);
}


void PhaseMain::createStage1Button(SDL_Renderer* gameRenderer)
{
	SDL_Rect texturePos = { 0, 0, 400, 300 };
	SDL_Rect renderingPos = { 80, 430, 400, 300 };

	SDL_Surface* tmpSurface = IMG_Load("../../resources/images/main_stage1_button.png");
	this->mainButtons[MAIN_BUTTON::STAGE_1] = new RectangleButton(texturePos, renderingPos, SDL_CreateTextureFromSurface(gameRenderer, tmpSurface));
	SDL_FreeSurface(tmpSurface);
}

void PhaseMain::createStage2Button(SDL_Renderer* gameRenderer)
{
	SDL_Rect texturePos = { 0, 0, 400, 300 };
	SDL_Rect renderingPos = { 600, 430, 400, 300 };

	SDL_Surface* tmpSurface = IMG_Load("../../resources/images/main_stage2_button.png");
	this->mainButtons[MAIN_BUTTON::STAGE_2] = new RectangleButton(texturePos, renderingPos, SDL_CreateTextureFromSurface(gameRenderer, tmpSurface));
	//this->mainButtons[MAIN_BUTTON::STAGE_2]->canSelectButton(false);
	SDL_FreeSurface(tmpSurface);
}

void PhaseMain::createStage3Button(SDL_Renderer* gameRenderer)
{
	SDL_Rect texturePos = { 0, 0, 400, 300 };
	SDL_Rect renderingPos = { 1120, 430, 400, 300 };

	SDL_Surface* tmpSurface = IMG_Load("../../resources/images/main_stage3_button.png");
	this->mainButtons[MAIN_BUTTON::STAGE_3] = new RectangleButton(texturePos, renderingPos, SDL_CreateTextureFromSurface(gameRenderer, tmpSurface));
	//this->mainButtons[MAIN_BUTTON::STAGE_3]->canSelectButton(false);
	SDL_FreeSurface(tmpSurface);
}

void PhaseMain::createGameStartButton(SDL_Renderer* gameRenderer)
{
	SDL_Rect texturePos = { 0, 0, 300, 100 };
	SDL_Rect renderingPos = { 1200, 780, 300, 100 };

	SDL_Surface* tmpSurface = IMG_Load("../../resources/images/main_game_start_button.png");
	this->mainButtons[MAIN_BUTTON::GAME_START] = new RectangleButton(texturePos, renderingPos, SDL_CreateTextureFromSurface(gameRenderer, tmpSurface));
	SDL_FreeSurface(tmpSurface);
}

void PhaseMain::createGachaButton(SDL_Renderer* gameRenderer)
{
	SDL_Rect texturePos = { 0, 0, 300, 100 };
	SDL_Rect renderingPos = { 800, 780, 300, 100 };

	SDL_Surface* tmpSurface = IMG_Load("../../resources/images/main_gacha_button.png");
	this->mainButtons[MAIN_BUTTON::GACHA] = new RectangleButton(texturePos, renderingPos, SDL_CreateTextureFromSurface(gameRenderer, tmpSurface));
	SDL_FreeSurface(tmpSurface);
}

void PhaseMain::createSelectedStageText(SDL_Renderer* gameRenderer)
{
	SDL_Color textColor = { 255, 255, 255, 255 };
	SDL_Rect renderingPos = { 100, 800, 0, 0 };

	this->selectedStageText = new TTFTextManger(gameRenderer, "선택된 스테이지 : 테스트", TTF_OpenFont("../../resources/fonts/main_seleted_stage.ttf", 50), renderingPos, textColor);
}

void PhaseMain::createMouseCursor()
{
	this->mouseArrowCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
	this->mouseHandCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
}

void PhaseMain::handleEvents(const SDL_Event& gameEvent)
{
	this->presentMousePos.x = gameEvent.button.x;
	this->presentMousePos.y = gameEvent.button.y;

	switch (gameEvent.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		if (gameEvent.button.button == SDL_BUTTON_LEFT)
			clickButtonsInRange(gameEvent.button.x, gameEvent.button.y);
		break;
	}
}

void PhaseMain::clickButtonsInRange(const int& mouseXPos, const int& mouseYPos)
{
	for (int i = 0; i < MAIN_BUTTON::COUNT; i++)
	{
		if (this->mainButtons[i]->isClickingButtonInRange(mouseXPos, mouseYPos))
			selectButtonType(static_cast<MAIN_BUTTON::TYPE>(i));
	}
}

void PhaseMain::selectButtonType(const MAIN_BUTTON::TYPE& buttonType)
{

	switch (buttonType)
	{
	case MAIN_BUTTON::COLLECTION:
		setNextGamePhase(GAME_PHASE::COLLECTION);
		break;
	case MAIN_BUTTON::BACK:
		setNextGamePhase(GAME_PHASE::INTRO);
		break;
	case MAIN_BUTTON::STAGE_1:
	case MAIN_BUTTON::STAGE_2:
	case MAIN_BUTTON::STAGE_3:
		this->selectedStage = buttonType;
		break;
	}

	Mix_PlayChannel(1, this->buttonEffectSound, 0);
}

void PhaseMain::updateDatas()
{

}

void PhaseMain::renderFrames()
{
	SDL_RenderCopy(getGameRenderer(), this->backgroundTexture, &(this->backgroundTextureRenderPos), &(this->backgroundTextureRenderPos));
	renderButtons();
	this->selectedStageText->renderTextTexture(getGameRenderer());
}

void PhaseMain::renderButtons()
{
	bool isMouseInRange = false;
	for (int i = 0; i < MAIN_BUTTON::COUNT; i++)
	{
		if (this->mainButtons[i]->isClickingButtonInRange(this->presentMousePos.x, this->presentMousePos.y))
		{
			SDL_SetCursor(this->mouseHandCursor);
			this->mainButtons[i]->RenderButtonTextureOnButton(getGameRenderer());
			isMouseInRange = true;
		}
		else
		{
			this->mainButtons[i]->RenderButtonTexture(getGameRenderer());
		}
	}

	this->mainButtons[this->selectedStage]->RenderButtonTextureOnClicking(getGameRenderer());

	if (!isMouseInRange) // 이게 없으면 버튼이 범위안에 있어도 커서가 화살표로 바뀜
		SDL_SetCursor(this->mouseArrowCursor);
}

void PhaseMain::openPhase()
{
	setNextGamePhase(GAME_PHASE::TYPE::NONE);
	this->selectedStage = MAIN_BUTTON::STAGE_1;
	Mix_FadeInMusic(this->backgroundMusic, -1, 3000);
}

void PhaseMain::closePhase()
{
	this->presentMousePos.x = 0;
	this->presentMousePos.y = 0;
	SDL_SetCursor(this->mouseArrowCursor);
	Mix_HaltMusic();
}

PhaseMain::~PhaseMain()
{
	for (int i = 0; i < MAIN_BUTTON::COUNT; i++)
		delete this->mainButtons[i];

	delete selectedStageText;
	Mix_FreeMusic(this->backgroundMusic);
	SDL_FreeCursor(this->mouseArrowCursor);
	SDL_FreeCursor(this->mouseHandCursor);
}