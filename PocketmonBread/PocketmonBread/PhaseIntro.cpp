#include "PhaseIntro.h"
#include "ConstantDecl.h"

PhaseIntro::PhaseIntro(SDL_Window * gameWindow, SDL_Renderer* gameRenderer, Player* _gamePlayer) : gamePlayer(_gamePlayer), PhaseInterface(gameWindow, gameRenderer)
{
	this->backgroundMusic = Mix_LoadMUS("../../resources/sounds/intro_bgm.mp3");
	this->buttonEffectSound = Mix_LoadWAV("../../resources/sounds/intro_button_sound.mp3");

	createBackgroundTexture(gameRenderer);
	createStartButton(gameRenderer);
	createEndButton(gameRenderer);
	createCheatButton(gameRenderer);
	createExitWaringWindow(gameRenderer);
	createCheatWaringWindow(gameRenderer);
	createMouseCursor();
}

void PhaseIntro::createBackgroundTexture(SDL_Renderer* gameRenderer)
{
	SDL_Surface* tmpSurface = IMG_Load("../../resources/images/intro_background.png");
	this->backgroundTexture = SDL_CreateTextureFromSurface(gameRenderer, tmpSurface);
	this->backgroundTextureRenderPos = { 0, 0, GAME_WINDOW::WIDTH, GAME_WINDOW::HEIGHT };
	SDL_FreeSurface(tmpSurface);
}

void PhaseIntro::createStartButton(SDL_Renderer* gameRenderer)
{
	SDL_Rect texturePos = { 0, 0, 387, 84 };
	SDL_Rect renderingPos = { 607, 600, 387, 84 };

	SDL_Surface* tmpSurface = IMG_Load("../../resources/images/intro_start_button.png");
	this->introButtons[INTRO_BUTTON::START_BUTTON] = new RectangleButton(texturePos, renderingPos, SDL_CreateTextureFromSurface(gameRenderer, tmpSurface));
	SDL_FreeSurface(tmpSurface);
}

void PhaseIntro::createEndButton(SDL_Renderer* gameRenderer)
{
	SDL_Rect texturePos = { 0, 0, 387, 84 };
	SDL_Rect renderingPos = { 607, 700, 387, 84 };

	SDL_Surface* tmpSurface = IMG_Load("../../resources/images/intro_end_button.png");
	this->introButtons[INTRO_BUTTON::END_BUTTON] = new RectangleButton(texturePos, renderingPos, SDL_CreateTextureFromSurface(gameRenderer, tmpSurface));
	SDL_FreeSurface(tmpSurface);
}

void PhaseIntro::createCheatButton(SDL_Renderer* gameRenderer)
{
	SDL_Rect texturePos = { 120, 0, 150, 84 };
	SDL_Rect renderingPos = { 1470, 820, 100, 50 };

	SDL_Surface* tmpSurface = IMG_Load("../../resources/images/intro_cheat_button.png");
	this->introButtons[INTRO_BUTTON::CHEAT_BUTTON] = new RectangleButton(texturePos, renderingPos, SDL_CreateTextureFromSurface(gameRenderer, tmpSurface));
	SDL_FreeSurface(tmpSurface);
}

void PhaseIntro::createExitWaringWindow(SDL_Renderer* gameRenderer)
{
	this->introWindows[INTRO_WINDOW::EXIT] = new WaringWindow(gameRenderer);
	dynamic_cast<WaringWindow*>(this->introWindows[INTRO_WINDOW::EXIT])->addText(gameRenderer, "게임을 종료하겠습니까?", 400);
}

void PhaseIntro::createCheatWaringWindow(SDL_Renderer* gameRenderer)
{
	this->introWindows[INTRO_WINDOW::CHEAT] = new WaringWindow(gameRenderer);
	dynamic_cast<WaringWindow*>(this->introWindows[INTRO_WINDOW::CHEAT])->addText(gameRenderer, "치트 모드로 진입하겠습니까?", 330);
	dynamic_cast<WaringWindow*>(this->introWindows[INTRO_WINDOW::CHEAT])->addText(gameRenderer, "<주의>", 420);
	dynamic_cast<WaringWindow*>(this->introWindows[INTRO_WINDOW::CHEAT])->addText(gameRenderer, "치트 모드로 진행 시", 480);
	dynamic_cast<WaringWindow*>(this->introWindows[INTRO_WINDOW::CHEAT])->addText(gameRenderer, "모든 진행 상황이 사라집니다.", 540);
}

void PhaseIntro::createMouseCursor()
{
	this->mouseArrowCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
	this->mouseHandCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
}

void PhaseIntro::handleEvents(const SDL_Event& gameEvent)
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

void PhaseIntro::clickButtonsInRange()
{
	for (int i = 0; i < INTRO_WINDOW::COUNT; i++)
	{
		if (this->introWindows[i]->isViewingWindow())
		{
			selectWindowButtonType(static_cast<INTRO_WINDOW::TYPE>(i));
			return;
		}
	}

	for (int i=0; i < INTRO_BUTTON::COUNT; i++)
	{
		if (this->introButtons[i]->isClickingButtonInRange(presentMousePos.x, presentMousePos.y))
			selectButtonType(static_cast<INTRO_BUTTON::TYPE>(i));
	}
}

void PhaseIntro::selectWindowButtonType(const INTRO_WINDOW::TYPE& windowType)
{
	switch (windowType)
	{
	case INTRO_WINDOW::CHEAT:
		selectCheatWaringButtonType(windowType);
		break;
	case INTRO_WINDOW::EXIT:
		selectExitWaringButtonType(windowType);
		break;
	}
}

void PhaseIntro::selectCheatWaringButtonType(const INTRO_WINDOW::TYPE& windowType)
{
	switch (this->introWindows[windowType]->getSeletedButtonTypeInWindow(presentMousePos.x, presentMousePos.y))
	{
	case WARING_BUTTON::CONSENTING:
		this->gamePlayer->applyPlayerCheatMode();
		setNextGamePhase(GAME_PHASE::MAIN);
		break;
	case NO_RETURN_TYPE:
		return;
		break;
	}

	startAllButtons();
	this->introWindows[windowType]->setIsViewWindow(false);
}

void PhaseIntro::selectExitWaringButtonType(const INTRO_WINDOW::TYPE& windowType)
{
	switch (this->introWindows[windowType]->getSeletedButtonTypeInWindow(presentMousePos.x, presentMousePos.y))
	{
	case WARING_BUTTON::CONSENTING:
		setNextGamePhase(GAME_PHASE::EXIT);
		break;
	case NO_RETURN_TYPE:
		return;
		break;
	}

	startAllButtons();
	this->introWindows[windowType]->setIsViewWindow(false);
}

void PhaseIntro::selectButtonType(const INTRO_BUTTON::TYPE& buttonType)
{	
	
	switch (buttonType)
	{
	case INTRO_BUTTON::START_BUTTON:
		setNextGamePhase(GAME_PHASE::MAIN);
		break;
	case INTRO_BUTTON::END_BUTTON:
		this->introWindows[INTRO_WINDOW::EXIT]->setIsViewWindow(true);
		stopAllButtons();
		break;
	case INTRO_BUTTON::CHEAT_BUTTON:
		this->introWindows[INTRO_WINDOW::CHEAT]->setIsViewWindow(true);
		stopAllButtons();
		break;
	}

	Mix_PlayChannel(1, this->buttonEffectSound, 0);
}

void PhaseIntro::stopAllButtons()
{
	for (int i = 0; i < INTRO_BUTTON::COUNT; i++)
		this->introButtons[i]->canSelectButton(false);
}

void PhaseIntro::startAllButtons()
{
	for (int i = 0; i < INTRO_BUTTON::COUNT; i++)
		this->introButtons[i]->canSelectButton(true);
}

void PhaseIntro::updateDatas()
{
}

void PhaseIntro::renderFrames()
{
	SDL_RenderCopy(getGameRenderer(), this->backgroundTexture, &(this->backgroundTextureRenderPos), &(this->backgroundTextureRenderPos));
	renderButtons();

	for (int i = 0; i < INTRO_WINDOW::COUNT; i++)
	{
		if (this->introWindows[i]->isViewingWindow())
			introWindows[i]->renderWindow(getGameRenderer(), this->presentMousePos.x, this->presentMousePos.y);
	}
}

void PhaseIntro::renderButtons()
{
	bool isMouseInRange = false;
	for (int i = 0; i < INTRO_BUTTON::COUNT; i++)
	{
		if (this->introButtons[i]->isClickingButtonInRange(this->presentMousePos.x, this->presentMousePos.y))
		{
			SDL_SetCursor(this->mouseHandCursor);
			this->introButtons[i]->RenderButtonTextureOnButton(getGameRenderer());
			isMouseInRange = true;
		}
		else
		{
			this->introButtons[i]->RenderButtonTexture(getGameRenderer());
		}
	}

	if(!isMouseInRange) // 이게 없으면 버튼이 범위안에 있어도 커서가 화살표로 바뀜
		SDL_SetCursor(this->mouseArrowCursor);
}

void PhaseIntro::openPhase()
{
	this->presentMousePos.x = 0;
	this->presentMousePos.y = 0;
	setNextGamePhase(GAME_PHASE::NONE);
	Mix_FadeInMusic(this->backgroundMusic, -1, 2000);
}

void PhaseIntro::closePhase()
{
	SDL_SetCursor(this->mouseArrowCursor);
	Mix_HaltMusic();
}

PhaseIntro::~PhaseIntro()
{
	delete this->introButtons[INTRO_BUTTON::START_BUTTON];
	delete this->introButtons[INTRO_BUTTON::END_BUTTON];
	delete this->introButtons[INTRO_BUTTON::CHEAT_BUTTON];
	delete this->introWindows[INTRO_WINDOW::CHEAT];
	delete this->introWindows[INTRO_WINDOW::EXIT];

	SDL_DestroyTexture(this->backgroundTexture);
	Mix_FreeMusic(this->backgroundMusic);
	Mix_FreeChunk(this->buttonEffectSound);
	SDL_FreeCursor(this->mouseArrowCursor);
	SDL_FreeCursor(this->mouseHandCursor);
}