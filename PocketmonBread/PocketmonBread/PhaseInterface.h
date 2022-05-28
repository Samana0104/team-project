#pragma once

#include "SDL.h"
#include "Player.h"

namespace GAME_PHASE
{
	enum TYPE
	{
		NONE = -1,
		INTRO = 0,
		MAIN = 1,
		COLLECTION = 2,
		NORMARL_ENDING = 3,
		TRUE_ENDING = 4,
		STAGE1 = 5,
		STAGE2 = 6,
		STAGE3 = 7,
		EXIT = 8,
		COUNT = 9
	};
};

class PhaseInterface
{
private:
	SDL_Window* gameWindow; // 메인 핸들러에 있는 게임 윈도우 연결
	SDL_Renderer* gameRenderer; // 메인 핸들러에 있는 게임 렌더러 연결
	GAME_PHASE::TYPE nextGamePhase = GAME_PHASE::NONE; // 다음 게임 페이즈가 뭔지 저장하는 변수
protected:
	PhaseInterface(SDL_Window * _gameWindow, SDL_Renderer* _gameRenderer) : 
		gameWindow(_gameWindow), gameRenderer(_gameRenderer) { } // 상속한 자식 클래스 이외에 생성 불가를 위해 프로텍트에 생성자 선언
	void setNextGamePhase(const GAME_PHASE::TYPE& _nextgamePhase) { this->nextGamePhase = _nextgamePhase; } // 다음 게임 페이즈를 설정하기 위한 함수
public:
	virtual ~PhaseInterface() { }

	virtual void handleEvents(const SDL_Event&) = 0; // 핸들 이벤트 처리 함수 메인 핸들러에서 이벤트를 불러와 handleEvents쪽으로 넘겨줌
	virtual void updateDatas() = 0; // 데이터 업데이트 함수
	virtual void renderFrames() = 0; // 해당 렌더링 그리는 함수
	virtual void openPhase() = 0; // 페이즈 시작 할 때 실행되는 함수 
	virtual void closePhase() = 0; // 페이즈 끝날 때 실행되는 함수
	GAME_PHASE::TYPE getNextGamePhase() const { return this->nextGamePhase; } // 다음 게임 페이즈를 핸들러에 신호를 보내기 위한 함수
	SDL_Renderer* getGameRenderer() { return this->gameRenderer; } // 부모 클래스의 렌더러를 받아옴 원래는 protected에 gameRenderer랑 gameWindow를 둘까 하다가 아니다 싶어 get으로 둠
	SDL_Window* getGameWindow() { return this->gameWindow; } // 부모 클래스의 윈도우를 받아옴 위와 마찬가지로 get으로 둠
};