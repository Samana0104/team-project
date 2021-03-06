#pragma once

#include "SDL.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "PhaseInterface.h"
#include "PhaseChangeEffect.h"
#include "Player.h"

class MainHandler
{
private:
	SDL_Window* gameWindow;
	SDL_Renderer* gameRenderer;
	PhaseInterface* gamePhase[GAME_PHASE::COUNT];
	PhaseChangeEffect* gamePhaseChangeEffect;
	Player* gamePlayer;
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