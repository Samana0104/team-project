#include "MainHandler.h"
#include "PhaseIntro.h"

MainHandler::MainHandler(const int& windowWidth, const int& windowHeight) : isExecutingGame(false), gamePresentPhase(PHASE::INTRO)
{
	initSystem(windowWidth, windowHeight);
	createPhase();
}

void MainHandler::initSystem(const int& windowWidth, const int& windowHeight)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	this->gameWindow = SDL_CreateWindow("PocketmonBread", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, 0);
	this->gameRenderer = SDL_CreateRenderer(this->gameWindow, -1, 0);
}

void MainHandler::createPhase()
{
	this->gamePhase[PHASE::INTRO] = new PhaseIntro();
}

void MainHandler::gameStart()
{
	this->isExecutingGame = true;

	while (this->isExecutingGame)
	{
		SDL_Delay(100);
		handleEvents();
		//updateDatas();
		//renderFrames();
		SDL_RenderPresent(this->gameRenderer);
	}
}

void MainHandler::handleEvents()
{
	SDL_Event gameEvent;

	if (!SDL_PollEvent(&gameEvent))
		return;

	handleSystemEvents(gameEvent);
}

void MainHandler::handleSystemEvents(const SDL_Event& gameEvent)
{
	switch (gameEvent.type)
	{
	case SDL_QUIT:
		this->isExecutingGame = false;
		break;
	}
}

MainHandler::~MainHandler()
{
	SDL_Quit();
}
