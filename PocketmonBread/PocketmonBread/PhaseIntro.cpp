#include "SDL_image.h"
#include "PhaseIntro.h"
#include "ConstantDecl.h"

PhaseIntro::PhaseIntro(SDL_Window * gameWindow, SDL_Renderer* gameRenderer) : PhaseInterface(gameWindow, gameRenderer)
{
	createBackgroundTexture(gameRenderer);
	createStartButton(gameRenderer);
	createEndButton(gameRenderer);
	createCheatButton(gameRenderer);
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
	SDL_Rect renderingPos = { 600, 500, 387, 84 };

	SDL_Surface* tmpSurface = IMG_Load("../../resources/images/intro_start_button.png");
	this->introButtons[INTRO_BUTTON::TYPE::START_BUTTON] = new RectangleButton(texturePos, renderingPos, SDL_CreateTextureFromSurface(gameRenderer, tmpSurface));
	SDL_FreeSurface(tmpSurface);
}

void PhaseIntro::createEndButton(SDL_Renderer* gameRenderer)
{
	SDL_Rect texturePos = { 0, 0, 387, 84 };
	SDL_Rect renderingPos = { 600, 600, 387, 84 };

	SDL_Surface* tmpSurface = IMG_Load("../../resources/images/intro_end_button.png");
	this->introButtons[INTRO_BUTTON::TYPE::END_BUTTON] = new RectangleButton(texturePos, renderingPos, SDL_CreateTextureFromSurface(gameRenderer, tmpSurface));
	SDL_FreeSurface(tmpSurface);
}

void PhaseIntro::createCheatButton(SDL_Renderer* gameRenderer)
{
	SDL_Rect texturePos = { 0, 0, 387, 84 };
	SDL_Rect renderingPos = { 1350, 800, 200, 50 };

	SDL_Surface* tmpSurface = IMG_Load("../../resources/images/intro_cheat_button.png");
	this->introButtons[INTRO_BUTTON::TYPE::CHEAT_BUTTON] = new RectangleButton(texturePos, renderingPos, SDL_CreateTextureFromSurface(gameRenderer, tmpSurface));
	SDL_FreeSurface(tmpSurface);
}

void PhaseIntro::createMouseCursor()
{
	this->mouseArrowCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
	this->mouseHandCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
}

void PhaseIntro::openPhase()
{
	setNextGamePhase(GAME_PHASE::TYPE::NONE);
}

void PhaseIntro::handleEvents(const SDL_Event& gameEvent)
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

void PhaseIntro::clickButtonsInRange(const int& mouseXPos, const int& mouseYPos)
{
	for (int i = 0; i < INTRO_BUTTON::TYPE::COUNT; i++)
	{
		if (this->introButtons[i]->isClickingButtonInRange(mouseXPos, mouseYPos))
			selectButtonType(static_cast<INTRO_BUTTON::TYPE>(i));
	}
}

void PhaseIntro::selectButtonType(const INTRO_BUTTON::TYPE& buttonType)
{
	switch (buttonType)
	{
	case INTRO_BUTTON::TYPE::START_BUTTON:
		setNextGamePhase(GAME_PHASE::TYPE::MAIN);
		break;
	case INTRO_BUTTON::TYPE::END_BUTTON:
		setNextGamePhase(GAME_PHASE::TYPE::EXIT);
		break;
	case INTRO_BUTTON::TYPE::CHEAT_BUTTON:
		break;
	}

	SDL_SetCursor(this->mouseArrowCursor);
}

void PhaseIntro::updateDatas()
{
}

void PhaseIntro::renderFrames()
{
	SDL_RenderCopy(getGameRenderer(), this->backgroundTexture, &(this->backgroundTextureRenderPos), &(this->backgroundTextureRenderPos));
	renderButtons();
	SDL_RenderPresent(getGameRenderer());
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

void PhaseIntro::closePhase()
{
}

PhaseIntro::~PhaseIntro()
{
	SDL_DestroyTexture(this->backgroundTexture);
	SDL_FreeCursor(this->mouseArrowCursor);
	SDL_FreeCursor(this->mouseHandCursor);
}