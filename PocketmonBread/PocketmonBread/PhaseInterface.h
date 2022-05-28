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
	SDL_Window* gameWindow; // ���� �ڵ鷯�� �ִ� ���� ������ ����
	SDL_Renderer* gameRenderer; // ���� �ڵ鷯�� �ִ� ���� ������ ����
	GAME_PHASE::TYPE nextGamePhase = GAME_PHASE::NONE; // ���� ���� ����� ���� �����ϴ� ����
protected:
	PhaseInterface(SDL_Window * _gameWindow, SDL_Renderer* _gameRenderer) : 
		gameWindow(_gameWindow), gameRenderer(_gameRenderer) { } // ����� �ڽ� Ŭ���� �̿ܿ� ���� �Ұ��� ���� ������Ʈ�� ������ ����
	void setNextGamePhase(const GAME_PHASE::TYPE& _nextgamePhase) { this->nextGamePhase = _nextgamePhase; } // ���� ���� ����� �����ϱ� ���� �Լ�
public:
	virtual ~PhaseInterface() { }

	virtual void handleEvents(const SDL_Event&) = 0; // �ڵ� �̺�Ʈ ó�� �Լ� ���� �ڵ鷯���� �̺�Ʈ�� �ҷ��� handleEvents������ �Ѱ���
	virtual void updateDatas() = 0; // ������ ������Ʈ �Լ�
	virtual void renderFrames() = 0; // �ش� ������ �׸��� �Լ�
	virtual void openPhase() = 0; // ������ ���� �� �� ����Ǵ� �Լ� 
	virtual void closePhase() = 0; // ������ ���� �� ����Ǵ� �Լ�
	GAME_PHASE::TYPE getNextGamePhase() const { return this->nextGamePhase; } // ���� ���� ����� �ڵ鷯�� ��ȣ�� ������ ���� �Լ�
	SDL_Renderer* getGameRenderer() { return this->gameRenderer; } // �θ� Ŭ������ �������� �޾ƿ� ������ protected�� gameRenderer�� gameWindow�� �ѱ� �ϴٰ� �ƴϴ� �;� get���� ��
	SDL_Window* getGameWindow() { return this->gameWindow; } // �θ� Ŭ������ �����츦 �޾ƿ� ���� ���������� get���� ��
};