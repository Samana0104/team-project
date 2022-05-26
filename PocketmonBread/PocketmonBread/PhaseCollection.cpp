#include "PhaseCollection.h"
#include "SDL_image.h"
#include "ConstantDecl.h"

PhaseCollection::PhaseCollection(SDL_Window* gameWindow, SDL_Renderer* gameRenderer) : PhaseInterface(gameWindow, gameRenderer)
{
	this->backgroundMusic = Mix_LoadMUS("../../resources/sounds/collection_bgm.mp3");
	createBackgroundTexture(gameRenderer);
	createMouseCursor();
}


void PhaseCollection::createBackgroundTexture(SDL_Renderer* gameRenderer)
{
	SDL_Surface* tmpSurface = IMG_Load("../../resources/images/collection_background.png");
	this->backgroundTexture = SDL_CreateTextureFromSurface(gameRenderer, tmpSurface);
	this->backgroundTextureRenderPos = { 0, 0, GAME_WINDOW::WIDTH, GAME_WINDOW::HEIGHT };
	SDL_FreeSurface(tmpSurface);
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

	//switch (gameEvent.type)
	//{
	//case SDL_MOUSEBUTTONDOWN:
	//	//if (gameEvent.button.button == SDL_BUTTON_LEFT)
	//		//clickButtonsInRange(gameEvent.button.x, gameEvent.button.y);
	//	break;
	//}
}

//void PhaseCollection::clickButtonsInRange(const int& mouseXPos, const int& mouseYPos)
//{
//	for (int i = 0; i < MAIN_BUTTON::COUNT; i++)
//	{
//		if (this->mainButtons[i]->isClickingButtonInRange(mouseXPos, mouseYPos))
//			selectButtonType(static_cast<MAIN_BUTTON::TYPE>(i));
//	}
//}
//
//void PhaseCollection::selectButtonType(const MAIN_BUTTON::TYPE& buttonType)
//{
//
//	switch (buttonType)
//	{
//	case MAIN_BUTTON::BACK:
//		setNextGamePhase(GAME_PHASE::INTRO);
//		break;
//	case MAIN_BUTTON::COLLECTION:
//		break;
//	}
//
//	//Mix_PlayChannel(1, this->buttonEffectSound, 0);
//}

void PhaseCollection::updateDatas()
{
}

void PhaseCollection::renderFrames()
{
	SDL_RenderCopy(getGameRenderer(), this->backgroundTexture, &(this->backgroundTextureRenderPos), &(this->backgroundTextureRenderPos));
	//renderButtons();
}

//void PhaseCollection::renderButtons()
//{
//	bool isMouseInRange = false;
//	for (int i = 0; i < MAIN_BUTTON::COUNT; i++)
//	{
//		if (this->mainButtons[i]->isClickingButtonInRange(this->presentMousePos.x, this->presentMousePos.y))
//		{
//			SDL_SetCursor(this->mouseHandCursor);
//			this->mainButtons[i]->RenderButtonTextureOnButton(getGameRenderer());
//			isMouseInRange = true;
//		}
//		else
//		{
//			this->mainButtons[i]->RenderButtonTexture(getGameRenderer());
//		}
//	}
//
//	if (!isMouseInRange) // 이게 없으면 버튼이 범위안에 있어도 커서가 화살표로 바뀜
//		SDL_SetCursor(this->mouseArrowCursor);
//}

void PhaseCollection::openPhase()
{
	setNextGamePhase(GAME_PHASE::TYPE::NONE);
	Mix_FadeInMusic(this->backgroundMusic, -1, 3000);
}

void PhaseCollection::closePhase()
{
	SDL_SetCursor(this->mouseArrowCursor);
	Mix_HaltMusic();
}

PhaseCollection::~PhaseCollection()
{
	//for (int i = 0; i < MAIN_BUTTON::COUNT; i++)
	//	delete this->mainButtons[i];

	Mix_FreeMusic(this->backgroundMusic);
	SDL_FreeCursor(this->mouseArrowCursor);
	SDL_FreeCursor(this->mouseHandCursor);
}