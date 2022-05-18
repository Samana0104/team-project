#pragma once

#include "SDL.h"
#include "PhaseInterface.h"

class MainHandler
{
private:
	SDL_Window* gameWindow;
	SDL_Renderer* gameRenderer;

	PhaseInterface* gamePhase[PHASE::COUNT];
	PHASE gamePresentPhase;

	bool isExecutingGame;


	void handleEvents();
	void handleSystemEvents(const SDL_Event& gameEvent);

	void initSystem(const int& windowWidth, const int& windowHeight);
	void createPhase();
public:
	explicit MainHandler(const int& windowWidth, const int& windowHeight);

	void gameStart();
	~MainHandler();
};