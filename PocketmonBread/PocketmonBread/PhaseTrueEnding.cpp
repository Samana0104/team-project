#include "PhaseTrueEnding.h"
#include "ConstantDecl.h"

PhaseTrueEnding::PhaseTrueEnding(SDL_Window* gameWindow, SDL_Renderer* gameRenderer) : PhaseInterface(gameWindow, gameRenderer)
{
	backgroundMusic = Mix_LoadMUS("../../resources/sounds/ending_bgm.mp3");
	createTrueEndingSceneTextures(gameRenderer);
	createThanksForPlayingText(gameRenderer);
}

void PhaseTrueEnding::createTrueEndingSceneTextures(SDL_Renderer* gameRenderer)
{
	SDL_Surface* tmpSurface = IMG_Load("../../resources/images/ending_scene1.png");
	this->TrueEndingScene1Texture = SDL_CreateTextureFromSurface(gameRenderer, tmpSurface);
	this->backgroundTextureRenderPos = { 0, 0, GAME_WINDOW::WIDTH, GAME_WINDOW::HEIGHT };
	SDL_FreeSurface(tmpSurface);

	tmpSurface = IMG_Load("../../resources/images/true_ending_scene2.png");
	this->TrueEndingScene2Texture = SDL_CreateTextureFromSurface(gameRenderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
}

void PhaseTrueEnding::createThanksForPlayingText(SDL_Renderer* gameRenderer)
{
	SDL_Color textColor = { 0, 0, 0, 255 };
	SDL_Rect renderingPos = { 900, 820, 0, 0 };

	this->thanksForplayingText = new TTFTextManger(gameRenderer, "게임을 플레이해 주셔서 감사합니다.",
		TTF_OpenFont("../../resources/fonts/thePudingW.ttf", 50), renderingPos, textColor);
}

void PhaseTrueEnding::handleEvents(const SDL_Event& gameEvent)
{
	switch (gameEvent.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		if (gameEvent.button.button == SDL_BUTTON_LEFT)
			changeNextScene();
		break;
	}
}

void PhaseTrueEnding::changeNextScene()
{
	switch (this->presentScene)
	{
	case TRUE_ENDING::SCENE_1:
		this->presentScene = TRUE_ENDING::SCENE_2;
		break;
	case TRUE_ENDING::SCENE_2:
		this->presentScene = TRUE_ENDING::SCENE_3;
		break;
	case TRUE_ENDING::SCENE_3:
		setNextGamePhase(GAME_PHASE::INTRO);
		break;
	}
}

void PhaseTrueEnding::updateDatas()
{
}

void PhaseTrueEnding::renderFrames()
{
	switch (this->presentScene)
	{
	case TRUE_ENDING::SCENE_1:
		SDL_RenderCopy(getGameRenderer(), this->TrueEndingScene1Texture, &(this->backgroundTextureRenderPos), &(this->backgroundTextureRenderPos));
		break;
	case TRUE_ENDING::SCENE_2:
		SDL_RenderCopy(getGameRenderer(), this->TrueEndingScene2Texture, &(this->backgroundTextureRenderPos), &(this->backgroundTextureRenderPos));
		break;
	case TRUE_ENDING::SCENE_3:
		SDL_RenderCopy(getGameRenderer(), this->TrueEndingScene2Texture, &(this->backgroundTextureRenderPos), &(this->backgroundTextureRenderPos));
		this->thanksForplayingText->renderTextTexture(getGameRenderer());
		break;
	}
}

void PhaseTrueEnding::openPhase()
{
	this->presentScene = TRUE_ENDING::SCENE_1;
	setNextGamePhase(GAME_PHASE::TYPE::NONE);
	Mix_FadeInMusic(this->backgroundMusic, -1, 2000);
}

void PhaseTrueEnding::closePhase()
{
	Mix_HaltMusic();
}

PhaseTrueEnding::~PhaseTrueEnding()
{
	delete this->thanksForplayingText;
	Mix_FreeMusic(this->backgroundMusic);
	SDL_DestroyTexture(this->TrueEndingScene1Texture);
	SDL_DestroyTexture(this->TrueEndingScene2Texture);
}