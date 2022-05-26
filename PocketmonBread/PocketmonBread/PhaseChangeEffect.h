#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "DelayTimer.h"

namespace CHANGE_EFFECT
{
	enum TRANSPARENCY
	{
		WHITE = 0,
		BLACK = 255
	};
};

class PhaseChangeEffect
{
private:
	SDL_Texture* effectTexture;
	SDL_Rect effectTextureRenderPos;
	int effectTransparency = 0;
	bool _isRendering = false;
public:
	explicit PhaseChangeEffect(SDL_Renderer* gameRenderer);
	~PhaseChangeEffect();

	bool isRendering();

	void renderPhaseOpeningEffectTexture(SDL_Renderer* gameRenderer);
};