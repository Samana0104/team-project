#pragma once

#include "SDL.h"

namespace GAME_PHASE
{
	enum TYPE
	{
		NONE = -1,
		INTRO = 0,
		MAIN = 1,
		COLLECTION = 2,
		NOMARL_ENDING = 3,
		TRUE_ENDING = 4,
		EXIT = 5,
		COUNT = 6
	};
};

class PhaseInterface
{
private:
	SDL_Window* gameWindow;
	SDL_Renderer* gameRenderer;
	GAME_PHASE::TYPE nextGamePhase = GAME_PHASE::NONE;
protected:
	PhaseInterface(SDL_Window * _gameWindow, SDL_Renderer* _gameRenderer) : 
		gameWindow(_gameWindow), gameRenderer(_gameRenderer) { } // 상속한 자식 클래스 이외에 생성 불가를 위해 프로텍트에 선언
	void setNextGamePhase(const GAME_PHASE::TYPE& _nextgamePhase) { this->nextGamePhase = _nextgamePhase; }
public:
	virtual ~PhaseInterface() { }

	virtual void handleEvents(const SDL_Event&) = 0; // 핸들 이벤트 처리 함수
	virtual void updateDatas() = 0; // 데이터 업데이트 함수
	virtual void renderFrames() = 0; // 렌더 그리는 함수
	virtual void openPhase() = 0; // 페이즈 시작 할 때 실행되는 함수 
	virtual void closePhase() = 0; // 페이즈 끝날 때 실행되는 함수
	GAME_PHASE::TYPE getNextGamePhase() const { return this->nextGamePhase; } // 다음 페이즈는 뭔지 받아내는 함수
	SDL_Renderer* getGameRenderer() { return this->gameRenderer; } // 부모 클래스의 렌더러를 받아옴
	SDL_Window* getGameWindow() { return this->gameWindow; }
};