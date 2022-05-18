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
	PhaseInterface() { } // ���� �Ұ��� ���� ������Ʈ�� ����
public:
	virtual ~PhaseInterface() { }

	virtual void openPhase() = 0; // ������ ���� �� �� ����Ǵ� �Լ� 
	virtual void handleEvents(const SDL_Event&) = 0; // �ڵ� �̺�Ʈ ó�� �Լ�
	virtual void updateDatas() = 0; // ������ ������Ʈ �Լ�
	virtual void renderFrames() = 0; // ���� �׸��� �Լ�
	virtual void closePhase() = 0; // ������ ���� �� ����Ǵ� �Լ�
	virtual PHASE getNextPhase() = 0; // ���� ������� ���� �޾Ƴ��� �Լ�
};