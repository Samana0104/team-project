#include "PhaseChangeEffect.h"
#include "ConstantDecl.h"


PhaseChangeEffect::PhaseChangeEffect(SDL_Renderer * gameRenderer) 
{
	SDL_Surface* tmpSurface = IMG_Load("../../resources/images/phase_change_effect.png");
	this->effectTexture = SDL_CreateTextureFromSurface(gameRenderer, tmpSurface);
	this->effectTextureRenderPos = { 0, 0, GAME_WINDOW::WIDTH, GAME_WINDOW::HEIGHT };
	SDL_FreeSurface(tmpSurface);
}

bool PhaseChangeEffect::isRendering()
{
	return this->_isRendering;
}

void PhaseChangeEffect::renderPhaseOpeningEffectTexture(SDL_Renderer* gameRenderer)
{
	if (!this->_isRendering)
	{
		this->_isRendering = true;
		this->effectTransparency = CHANGE_EFFECT::WHITE;
	}

	if (this->effectTransparency <= CHANGE_EFFECT::BLACK)
	{
		SDL_SetTextureAlphaMod(this->effectTexture, effectTransparency);
		effectTransparency += 3;
	} 
	else
	{
		this->_isRendering = false;
	}

	SDL_RenderCopy(gameRenderer, this->effectTexture, &(this->effectTextureRenderPos), &(this->effectTextureRenderPos));
}

PhaseChangeEffect::~PhaseChangeEffect()
{
	SDL_DestroyTexture(this->effectTexture);
}