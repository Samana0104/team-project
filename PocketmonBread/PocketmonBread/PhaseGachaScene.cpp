#include "PhaseGachaScene.h"
#include "ConstantDecl.h"

PhaseGachaScene::PhaseGachaScene(SDL_Window* gameWindow, SDL_Renderer* gameRenderer) : textTimer(50), changeSceneTimer(150.0), 
text("Æ÷ÄÏ¸ó »§ ¶â´ÂÁß."), PhaseInterface(gameWindow, gameRenderer)
{
	this->gachaSound = Mix_LoadWAV("../../resources/sounds/sfx_CRY_1.wav");

	createBackgroundTexture(gameRenderer);
	createGachaText(gameRenderer);
}

void PhaseGachaScene::createBackgroundTexture(SDL_Renderer* gameRenderer)
{
	SDL_Surface* tmpSurface = IMG_Load("../../resources/images/gacha_progress.png");
	this->backgroundTexture = SDL_CreateTextureFromSurface(gameRenderer, tmpSurface);
	this->backgroundTextureRenderPos = { 0, 0, GAME_WINDOW::WIDTH, GAME_WINDOW::HEIGHT };
	SDL_FreeSurface(tmpSurface);
}

void PhaseGachaScene::createGachaText(SDL_Renderer* gameRenderer)
{
	SDL_Color textColor = { 255, 255, 255, 255 };
	SDL_Rect renderingPos = { 550, 800, 0, 0 };

	this->gachaText = new TTFTextManger(gameRenderer, text,
		TTF_OpenFont("../../resources/fonts/DungGeunMo.ttf", 40), renderingPos, textColor);
}


void PhaseGachaScene::handleEvents(const SDL_Event& gameEvent)
{
}

void PhaseGachaScene::updateDatas()
{
	if (this->textTimer.isDelaying())
	{
		this->textTimer.decreaseTime(1.0);
	}
	else
	{
		text += ".";
		this->gachaText->setText(this->text, getGameRenderer());
	}

	if(this->changeSceneTimer.isDelaying())
	{
		this->changeSceneTimer.decreaseTime(1.0);
		return;
	}

	setNextGamePhase(GAME_PHASE::MAIN);
}

void PhaseGachaScene::renderFrames()
{
	SDL_RenderCopy(getGameRenderer(), this->backgroundTexture, &(this->backgroundTextureRenderPos), &(this->backgroundTextureRenderPos));
	this->gachaText->renderTextTexture(getGameRenderer());
}


void PhaseGachaScene::openPhase()
{
	text = "Æ÷ÄÏ¸ó »§ ¶â´ÂÁß.";
	this->gachaText->setText(this->text, getGameRenderer());
	setNextGamePhase(GAME_PHASE::NONE);
	this->textTimer.reInitTimer();
	this->changeSceneTimer.reInitTimer();
	Mix_PlayChannel(1, this->gachaSound, 0);
}

void PhaseGachaScene::closePhase()
{
}

PhaseGachaScene::~PhaseGachaScene()
{
	delete this->gachaText;
	SDL_DestroyTexture(this->backgroundTexture);
	Mix_FreeChunk(this->gachaSound);
}