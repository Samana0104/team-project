#pragma once

#include "SDL.h"
#include "PhaseInterface.h"

class MainHandler
{
private:
	SDL_Window* gameWindow;
	SDL_Renderer* gameRenderer;
	PhaseInterface* gamePhase[GAME_PHASE::COUNT];
	GAME_PHASE::TYPE gamePresentPhase = GAME_PHASE::INTRO;
	bool isExecutingGame = false;


	void initSystem(const int& windowWidth, const int& windowHeight);
	void createPhase();

	void handleEvents();
	void handleSystemEvents(const SDL_Event& gameEvent);
	void updateDatas();
	void updateNextPhase();
	void renderFrames();
public:
	explicit MainHandler(const int& windowWidth, const int& windowHeight);

	void gameStart();
	~MainHandler();
};