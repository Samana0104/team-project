#include "MainHandler.h"
#include "PhaseIntro.h"
#include "PhaseMain.h"

MainHandler::MainHandler(const int& windowWidth, const int& windowHeight)
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
	this->gamePhase[GAME_PHASE::TYPE::INTRO] = new PhaseIntro(this->gameWindow, this->gameRenderer);
	this->gamePhase[GAME_PHASE::TYPE::MAIN] = new PhaseMain(this->gameWindow, this->gameRenderer);
}

void MainHandler::gameStart()
{
	this->isExecutingGame = true;

	while (this->isExecutingGame)
	{
		SDL_Delay(10);
		handleEvents();
		updateDatas();
		renderFrames();
	}
}

void MainHandler::handleEvents()
{
	SDL_Event gameEvent;

	if (!SDL_PollEvent(&gameEvent))
		return;

	handleSystemEvents(gameEvent);
	this->gamePhase[this->gamePresentPhase]->handleEvents(gameEvent);
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

void MainHandler::updateDatas()
{
	this->gamePhase[this->gamePresentPhase]->updateDatas();
	updateNextPhase();
}

void MainHandler::updateNextPhase()
{
	GAME_PHASE::TYPE gameType;

	gameType = this->gamePhase[this->gamePresentPhase]->getNextGamePhase();

	switch (gameType)
	{
	case GAME_PHASE::TYPE::NONE:
		return;
	case GAME_PHASE::TYPE::EXIT:
		this->isExecutingGame = false;
		return;
	}

	this->gamePhase[this->gamePresentPhase]->closePhase();
	this->gamePresentPhase = gameType;
	this->gamePhase[this->gamePresentPhase]->openPhase();
}

void MainHandler::renderFrames()
{
	this->gamePhase[this->gamePresentPhase]->renderFrames();
}

MainHandler::~MainHandler()
{
	delete this->gamePhase[GAME_PHASE::TYPE::INTRO];
	delete this->gamePhase[GAME_PHASE::TYPE::MAIN];
	SDL_DestroyRenderer(this->gameRenderer);
	SDL_Quit();
}
