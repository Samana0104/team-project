#pragma once

#include "PhaseInterface.h"
#include "TTFTextManger.h"
#include "SDL_mixer.h"

namespace TRUE_ENDING
{
	enum SCENE
	{
		SCENE_1 = 0,
		SCENE_2 = 1,
		SCENE_3 = 2
	};
}

class PhaseTrueEnding : public PhaseInterface
{
private:
	SDL_Texture* TrueEndingScene1Texture;
	SDL_Texture* TrueEndingScene2Texture;
	SDL_Rect backgroundTextureRenderPos;

	Mix_Music* backgroundMusic;
	TTFTextManger* thanksForplayingText;

	void createTrueEndingSceneTextures(SDL_Renderer* gameRenderer);
	void createThanksForPlayingText(SDL_Renderer* gameRenderer);
	TRUE_ENDING::SCENE presentScene = TRUE_ENDING::SCENE_1;

	void changeNextScene();
public:
	PhaseTrueEnding(SDL_Window* gameWindow, SDL_Renderer* gameRenderer);
	virtual ~PhaseTrueEnding();

	virtual void handleEvents(const SDL_Event&);
	virtual void updateDatas();
	virtual void renderFrames();
	virtual void openPhase();
	virtual void closePhase();
};