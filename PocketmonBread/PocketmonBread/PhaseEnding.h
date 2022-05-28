#pragma once

#include "PhaseInterface.h"
#include "TTFTextManger.h"
#include "SDL_mixer.h"

namespace ENDING
{
	enum SCENE
	{
		SCENE_1 = 0,
		SCENE_2 = 1,
		SCENE_3 = 2
	};
}

class PhaseEnding : public PhaseInterface
{
private:
	SDL_Texture* endingScene1Texture;
	SDL_Texture* endingScene2Texture;
	SDL_Rect backgroundTextureRenderPos;

	Mix_Music* backgroundMusic;
	TTFTextManger* endingText;

	void createEndingSceneTextures(SDL_Renderer* gameRenderer);
	void createEndingText(SDL_Renderer* gameRenderer);
	ENDING::SCENE presentScene = ENDING::SCENE_1;

	void changeNextScene();
public:
	PhaseEnding(SDL_Window* gameWindow, SDL_Renderer* gameRenderer);
	virtual ~PhaseEnding();

	virtual void handleEvents(const SDL_Event&);
	virtual void updateDatas();
	virtual void renderFrames();
	virtual void openPhase();
	virtual void closePhase();
};