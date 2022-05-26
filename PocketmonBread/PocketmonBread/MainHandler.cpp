#include "MainHandler.h"
#include "PhaseIntro.h"
#include "PhaseMain.h"
#include "PhaseCollection.h"

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
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);
	TTF_Init();
}

void MainHandler::createPhase()
{
	this->gamePhase[GAME_PHASE::TYPE::INTRO] = new PhaseIntro(this->gameWindow, this->gameRenderer);
	this->gamePhase[GAME_PHASE::TYPE::MAIN] = new PhaseMain(this->gameWindow, this->gameRenderer);
	this->gamePhase[GAME_PHASE::TYPE::COLLECTION] = new PhaseCollection(this->gameWindow, this->gameRenderer);
	this->gamePhaseChangeEffect = new PhaseChangeEffect(this->gameRenderer);
}

void MainHandler::gameStart()
{
	this->isExecutingGame = true;
	this->gamePhase[this->gamePresentPhase]->openPhase();

	while (this->isExecutingGame)
	{
		SDL_Delay(5);
		handleEvents();
		updateDatas();
		renderFrames();
		updateNextPhase();
	}

	this->gamePhase[this->gamePresentPhase]->closePhase();
}

void MainHandler::handleEvents()
{
	SDL_Event gameEvent;

	if (!SDL_PollEvent(&gameEvent))
		return;

	if (this->gamePhaseChangeEffect->isRendering())
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
}

void MainHandler::renderFrames()
{
	this->gamePhase[this->gamePresentPhase]->renderFrames();

	if (this->gamePhase[this->gamePresentPhase]->getNextGamePhase() != GAME_PHASE::NONE)
		this->gamePhaseChangeEffect->renderPhaseOpeningEffectTexture(this->gameRenderer);

	SDL_RenderPresent(this->gameRenderer);
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


	if (this->gamePhaseChangeEffect->isRendering())
		return;

	this->gamePhase[this->gamePresentPhase]->closePhase();
	this->gamePresentPhase = gameType;
	this->gamePhase[this->gamePresentPhase]->openPhase();


}

MainHandler::~MainHandler()
{
	delete this->gamePhase[GAME_PHASE::INTRO];
	delete this->gamePhase[GAME_PHASE::MAIN];
	delete this->gamePhase[GAME_PHASE::COLLECTION];
	//delete this->gamePhaseChangeEffect;

	//Mix_CloseAudio();
	//TTF_Quit();
	SDL_DestroyRenderer(this->gameRenderer);
	SDL_Quit();
}
