#pragma once

#include "PhaseInterface.h"

class PhaseIntro : public PhaseInterface
{
private:
public:
	virtual ~PhaseIntro();

	virtual void openPhase();
	virtual void handleEvents(const SDL_Event&);
	virtual void updateDatas();
	virtual void renderFrames();
	virtual void closePhase();
	virtual PHASE getNextPhase();
};