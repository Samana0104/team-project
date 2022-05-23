#include "PhaseMain.h"
#include "SDL_image.h"
#include "ConstantDecl.h"

PhaseMain::PhaseMain(SDL_Window* gameWindow, SDL_Renderer* gameRenderer) : PhaseInterface(gameWindow, gameRenderer)
{
	createBackgroundTexture(gameRenderer);
}


void PhaseMain::createBackgroundTexture(SDL_Renderer* gameRenderer)
{
	SDL_Surface* tmpSurface = IMG_Load("../../resources/images/main_background.png");
	this->backgroundTexture = SDL_CreateTextureFromSurface(gameRenderer, tmpSurface);
	this->backgroundTextureRenderPos = { 0, 0, GAME_WINDOW::WIDTH, GAME_WINDOW::HEIGHT };
	SDL_FreeSurface(tmpSurface);
}

void PhaseMain::openPhase()
{
	setNextGamePhase(GAME_PHASE::TYPE::NONE);
}

void PhaseMain::handleEvents(const SDL_Event& gameEvent)
{
}

void PhaseMain::updateDatas()
{
}

void PhaseMain::renderFrames()
{
	SDL_RenderCopy(getGameRenderer(), this->backgroundTexture, &(this->backgroundTextureRenderPos), &(this->backgroundTextureRenderPos));
	SDL_RenderPresent(getGameRenderer());
}

void PhaseMain::closePhase()
{
}

PhaseMain::~PhaseMain()
{
}