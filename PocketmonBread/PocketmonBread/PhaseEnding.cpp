#include "PhaseEnding.h"
#include "ConstantDecl.h"

PhaseEnding::PhaseEnding(SDL_Window* gameWindow, SDL_Renderer* gameRenderer) : PhaseInterface(gameWindow, gameRenderer)
{
	backgroundMusic = Mix_LoadMUS("../../resources/sounds/ending_bgm.mp3");
	createEndingSceneTextures(gameRenderer);
	createEndingText(gameRenderer);
}

void PhaseEnding::createEndingSceneTextures(SDL_Renderer* gameRenderer)
{
	SDL_Surface* tmpSurface = IMG_Load("../../resources/images/ending_scene1.png");
	this->endingScene1Texture = SDL_CreateTextureFromSurface(gameRenderer, tmpSurface);
	this->backgroundTextureRenderPos = { 0, 0, GAME_WINDOW::WIDTH, GAME_WINDOW::HEIGHT };
	SDL_FreeSurface(tmpSurface);

	tmpSurface = IMG_Load("../../resources/images/ending_scene2.png");
	this->endingScene2Texture = SDL_CreateTextureFromSurface(gameRenderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
}

void PhaseEnding::createEndingText(SDL_Renderer* gameRenderer)
{
	SDL_Color textColor = { 0, 0, 0, 255 };
	SDL_Rect renderingPos = { 910, 820, 0, 0 };

	this->endingText = new TTFTextManger(gameRenderer, "씰을 다 모으면 무슨일이 일어날지도?",
		TTF_OpenFont("../../resources/fonts/thePudingW.ttf", 50), renderingPos, textColor);
}

void PhaseEnding::handleEvents(const SDL_Event& gameEvent)
{
	switch (gameEvent.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		if (gameEvent.button.button == SDL_BUTTON_LEFT)
			changeNextScene();
		break;
	}
}

void PhaseEnding::changeNextScene()
{
	switch (this->presentScene)
	{
	case ENDING::SCENE_1:
		this->presentScene = ENDING::SCENE_2;
		break;
	case ENDING::SCENE_2:
		this->presentScene = ENDING::SCENE_3;
		break;
	case ENDING::SCENE_3:
		setNextGamePhase(GAME_PHASE::MAIN);
		break;
	}
}

void PhaseEnding::updateDatas()
{
}

void PhaseEnding::renderFrames()
{
	switch (this->presentScene)
	{
	case ENDING::SCENE_1:
		SDL_RenderCopy(getGameRenderer(), this->endingScene1Texture, &(this->backgroundTextureRenderPos), &(this->backgroundTextureRenderPos));
		break;
	case ENDING::SCENE_2:
		SDL_RenderCopy(getGameRenderer(), this->endingScene2Texture, &(this->backgroundTextureRenderPos), &(this->backgroundTextureRenderPos));
		break;
	case ENDING::SCENE_3:
		SDL_RenderCopy(getGameRenderer(), this->endingScene2Texture, &(this->backgroundTextureRenderPos), &(this->backgroundTextureRenderPos));
		this->endingText->renderTextTexture(getGameRenderer());
		break;
	}
}

void PhaseEnding::openPhase()
{
	this->presentScene = ENDING::SCENE_1;
	setNextGamePhase(GAME_PHASE::TYPE::NONE);
	Mix_FadeInMusic(this->backgroundMusic, -1, 2000);
}

void PhaseEnding::closePhase()
{
	Mix_HaltMusic();
}

PhaseEnding::~PhaseEnding()
{
	delete this->endingText;
	Mix_FreeMusic(this->backgroundMusic);
	SDL_DestroyTexture(this->endingScene1Texture);
	SDL_DestroyTexture(this->endingScene2Texture);
}