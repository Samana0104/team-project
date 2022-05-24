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
		gameWindow(_gameWindow), gameRenderer(_gameRenderer) { } // ����� �ڽ� Ŭ���� �̿ܿ� ���� �Ұ��� ���� ������Ʈ�� ����
	void setNextGamePhase(const GAME_PHASE::TYPE& _nextgamePhase) { this->nextGamePhase = _nextgamePhase; }
public:
	virtual ~PhaseInterface() { }

	virtual void handleEvents(const SDL_Event&) = 0; // �ڵ� �̺�Ʈ ó�� �Լ�
	virtual void updateDatas() = 0; // ������ ������Ʈ �Լ�
	virtual void renderFrames() = 0; // ���� �׸��� �Լ�
	virtual void openPhase() = 0; // ������ ���� �� �� ����Ǵ� �Լ� 
	virtual void closePhase() = 0; // ������ ���� �� ����Ǵ� �Լ�
	GAME_PHASE::TYPE getNextGamePhase() const { return this->nextGamePhase; } // ���� ������� ���� �޾Ƴ��� �Լ�
	SDL_Renderer* getGameRenderer() { return this->gameRenderer; } // �θ� Ŭ������ �������� �޾ƿ�
	SDL_Window* getGameWindow() { return this->gameWindow; }
};