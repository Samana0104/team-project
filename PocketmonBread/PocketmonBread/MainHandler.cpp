#include "MainHandler.h"
#include "PhaseIntro.h"
#include "PhaseMain.h"
#include "GameStage1.h"
#include "GameStage2.h"
#include "GameStage3.h"
#include "PhaseCollection.h"
#include "PhaseEnding.h"
#include "PhaseTrueEnding.h"

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
	this->gamePhase[GAME_PHASE::INTRO] = new PhaseIntro(this->gameWindow, this->gameRenderer);
	this->gamePhase[GAME_PHASE::MAIN] = new PhaseMain(this->gameWindow, this->gameRenderer);
	this->gamePhase[GAME_PHASE::COLLECTION] = new PhaseCollection(this->gameWindow, this->gameRenderer);
	this->gamePhase[GAME_PHASE::STAGE1] = new Stage1(this->gameWindow, this->gameRenderer);
	//this->gamePhase[GAME_PHASE::COLLECTION] = new Stage2(this->gameWindow, this->gameRenderer);
	//this->gamePhase[GAME_PHASE::COLLECTION] = new Stage3(this->gameWindow, this->gameRenderer);
	this->gamePhase[GAME_PHASE::TRUE_ENDING] = new PhaseTrueEnding(this->gameWindow, this->gameRenderer);
	this->gamePhase[GAME_PHASE::NORMARL_ENDING] = new PhaseEnding(this->gameWindow, this->gameRenderer);
	this->gamePhaseChangeEffect = new PhaseChangeEffect(this->gameRenderer);
}

void MainHandler::gameStart()
{
	this->isExecutingGame = true;
	this->gamePhase[this->gamePresentPhase]->openPhase();

	while (this->isExecutingGame)
	{
		SDL_Delay(10);
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
	delete this->gamePhase[GAME_PHASE::STAGE1];
	delete this->gamePhase[GAME_PHASE::NORMARL_ENDING];
	delete this->gamePhase[GAME_PHASE::TRUE_ENDING];
	//delete this->gamePhaseChangeEffect;

	//Mix_CloseAudio();
	//TTF_Quit();
	SDL_DestroyRenderer(this->gameRenderer);
	SDL_Quit();
}
