#pragma once

#include "PhaseInterface.h"
#include "SDL_image.h"
#include "DelayTimer.h"
#include "SDL_mixer.h"
#include "TTFTextManger.h"

class PhaseGachaScene : public PhaseInterface
{
private:
	SDL_Texture* backgroundTexture;
	SDL_Rect backgroundTextureRenderPos;
	Mix_Chunk* gachaSound;
	DelayTimer changeSceneTimer;
	DelayTimer textTimer;
	TTFTextManger* gachaText;
	std::string text;

	void createBackgroundTexture(SDL_Renderer* gameRenderer);
	void createGachaText(SDL_Renderer* gameRenderer);
public:
	PhaseGachaScene(SDL_Window* gameWindow, SDL_Renderer* gameRender);
	virtual ~PhaseGachaScene();

	virtual void handleEvents(const SDL_Event&);
	virtual void updateDatas();
	virtual void renderFrames();
	virtual void openPhase();
	virtual void closePhase();
};