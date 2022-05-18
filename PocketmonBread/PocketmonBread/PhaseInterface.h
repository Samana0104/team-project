#pragma once

#include "SDL.h"

enum PHASE
{
	NONE,
	INTRO,
	MAIN,
	COLLECTION,
	NOMARL_ENDING,
	TRUE_ENDING,
	COUNT = 6
};

class PhaseInterface
{
protected:
	PhaseInterface() { } // 생성 불가를 위해 프로텍트에 선언
public:
	virtual ~PhaseInterface() { }

	virtual void openPhase() = 0; // 페이즈 시작 할 때 실행되는 함수 
	virtual void handleEvents(const SDL_Event&) = 0; // 핸들 이벤트 처리 함수
	virtual void updateDatas() = 0; // 데이터 업데이트 함수
	virtual void renderFrames() = 0; // 렌더 그리는 함수
	virtual void closePhase() = 0; // 페이즈 끝날 때 실행되는 함수
	virtual PHASE getNextPhase() = 0; // 다음 페이즈는 뭔지 받아내는 함수
};