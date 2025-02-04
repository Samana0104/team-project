#include "PhaseMain.h"
#include "ConstantDecl.h"

PhaseMain::PhaseMain(SDL_Window* gameWindow, SDL_Renderer* gameRenderer, Player* _gamePlayer) : gamePlayer(_gamePlayer), PhaseInterface(gameWindow, gameRenderer)
{
	this->backgroundMusic = Mix_LoadMUS("../../resources/sounds/main_bgm.mp3");
	this->buttonEffectSound = Mix_LoadWAV("../../resources/sounds/main_button_sound.mp3");
	this->gachaMusic = Mix_LoadMUS("../../resources/sounds/gacha_bgm.mp3");

	createBackgroundTexture(gameRenderer);
	createCollectionButton(gameRenderer);
	createManualButton(gameRenderer);
	createBackButton(gameRenderer);
	createStage1Button(gameRenderer);
	createStage2Button(gameRenderer);
	createStage3Button(gameRenderer);
	createGameStartButton(gameRenderer);
	createGachaButton(gameRenderer);

	createSelectedStageText(gameRenderer);
	createBreadCountText(gameRenderer);

	createBackWaringWindow(gameRenderer);
	createManualWindow(gameRenderer);
	createStoryWindow(gameRenderer);
	createGacha1Window(gameRenderer);
	createGacha2Window(gameRenderer);

	createMouseCursor();
}


void PhaseMain::createBackgroundTexture(SDL_Renderer* gameRenderer)
{
	SDL_Surface* tmpSurface = IMG_Load("../../resources/images/main_background.png");
	this->backgroundTexture = SDL_CreateTextureFromSurface(gameRenderer, tmpSurface);
	this->backgroundTextureRenderPos = { 0, 0, GAME_WINDOW::WIDTH, GAME_WINDOW::HEIGHT };
	SDL_FreeSurface(tmpSurface);
}

void PhaseMain::createCollectionButton(SDL_Renderer* gameRenderer)
{
	SDL_Rect texturePos = { 0, 0, 100, 100 };
	SDL_Rect renderingPos = { 1105, 50, 100, 100 };

	SDL_Surface* tmpSurface = IMG_Load("../../resources/images/main_collection_button.png");
	this->mainButtons[MAIN_BUTTON::COLLECTION] = new RectangleButton(texturePos, renderingPos, SDL_CreateTextureFromSurface(gameRenderer, tmpSurface));
	SDL_FreeSurface(tmpSurface);
}

void PhaseMain::createManualButton(SDL_Renderer* gameRenderer)
{
	SDL_Rect texturePos = { 0, 0, 100, 100 };
	SDL_Rect renderingPos = { 1245, 50, 100, 100 };

	SDL_Surface* tmpSurface = IMG_Load("../../resources/images/main_manual_button.png");
	this->mainButtons[MAIN_BUTTON::MANUAL] = new RectangleButton(texturePos, renderingPos, SDL_CreateTextureFromSurface(gameRenderer, tmpSurface));
	SDL_FreeSurface(tmpSurface);
}

void PhaseMain::createBackButton(SDL_Renderer* gameRenderer)
{
	SDL_Rect texturePos = { 0, 0, 90, 90 };
	SDL_Rect renderingPos = { 1400, 45, 90, 90 };

	SDL_Surface* tmpSurface = IMG_Load("../../resources/images/main_back_button.png");
	this->mainButtons[MAIN_BUTTON::BACK] = new RectangleButton(texturePos, renderingPos, SDL_CreateTextureFromSurface(gameRenderer, tmpSurface));
	SDL_FreeSurface(tmpSurface);
}


void PhaseMain::createStage1Button(SDL_Renderer* gameRenderer)
{
	SDL_Rect texturePos = { 0, 0, 400, 300 };
	SDL_Rect renderingPos = { 80, 461, 400, 300 };

	SDL_Surface* tmpSurface = IMG_Load("../../resources/images/main_stage1_button.png");
	this->mainButtons[MAIN_BUTTON::STAGE_1] = new RectangleButton(texturePos, renderingPos, SDL_CreateTextureFromSurface(gameRenderer, tmpSurface));
	SDL_FreeSurface(tmpSurface);
}

void PhaseMain::createStage2Button(SDL_Renderer* gameRenderer)
{
	SDL_Rect texturePos = { 0, 0, 400, 300 };
	SDL_Rect renderingPos = { 600, 461, 400, 300 };

	SDL_Surface* tmpSurface = IMG_Load("../../resources/images/main_stage2_button.png");
	this->mainButtons[MAIN_BUTTON::STAGE_2] = new RectangleButton(texturePos, renderingPos, SDL_CreateTextureFromSurface(gameRenderer, tmpSurface));
	//this->mainButtons[MAIN_BUTTON::STAGE_2]->canSelectButton(false);
	SDL_FreeSurface(tmpSurface);
}

void PhaseMain::createStage3Button(SDL_Renderer* gameRenderer)
{
	SDL_Rect texturePos = { 0, 0, 400, 300 };
	SDL_Rect renderingPos = { 1120, 461, 400, 300 };

	SDL_Surface* tmpSurface = IMG_Load("../../resources/images/main_stage3_button.png");
	this->mainButtons[MAIN_BUTTON::STAGE_3] = new RectangleButton(texturePos, renderingPos, SDL_CreateTextureFromSurface(gameRenderer, tmpSurface));
	//this->mainButtons[MAIN_BUTTON::STAGE_3]->canSelectButton(false);
	SDL_FreeSurface(tmpSurface);
}

void PhaseMain::createGameStartButton(SDL_Renderer* gameRenderer)
{
	SDL_Rect texturePos = { 0, 0, 265, 72 };
	SDL_Rect renderingPos = { 1250, 794, 265, 72 };

	SDL_Surface* tmpSurface = IMG_Load("../../resources/images/main_game_start_button.png");
	this->mainButtons[MAIN_BUTTON::GAME_START] = new RectangleButton(texturePos, renderingPos, SDL_CreateTextureFromSurface(gameRenderer, tmpSurface));
	SDL_FreeSurface(tmpSurface);
}

void PhaseMain::createGachaButton(SDL_Renderer* gameRenderer)
{
	SDL_Rect texturePos = { 0, 0, 265, 72 };
	SDL_Rect renderingPos = { 900, 794, 265, 72 };

	SDL_Surface* tmpSurface = IMG_Load("../../resources/images/main_gacha_button.png");
	this->mainButtons[MAIN_BUTTON::GACHA] = new RectangleButton(texturePos, renderingPos, SDL_CreateTextureFromSurface(gameRenderer, tmpSurface));
	SDL_FreeSurface(tmpSurface);
}

void PhaseMain::createSelectedStageText(SDL_Renderer* gameRenderer)
{
	SDL_Color textColor = { 0, 0, 0, 255 };
	SDL_Rect renderingPos = { 100, 790, 0, 0 };

	this->mainTexts[MAIN_TEXT::SELETED_STAGE] = new TTFTextManger(gameRenderer, "선택된 스테이지 : CU", 
		TTF_OpenFont("../../resources/fonts/CookieRun Bold.ttf", 55), renderingPos, textColor);
}

void PhaseMain::createBreadCountText(SDL_Renderer* gameRenderer)
{
	SDL_Color textColor = { 0, 0, 0, 255 };
	SDL_Rect renderingPos = { 750, 70, 0, 0 };

	this->mainTexts[MAIN_TEXT::BREAD_COUNT] = new TTFTextManger(gameRenderer, "소지한 빵 개수 : 0개",
		TTF_OpenFont("../../resources/fonts/BMJUA_ttf.ttf", 40), renderingPos, textColor);
}

void PhaseMain::createBackWaringWindow(SDL_Renderer* gameRenderer)
{
	this->mainWindows[MAIN_WINDOW::BACK] = new WaringWindow(gameRenderer);
	dynamic_cast<WaringWindow*>(this->mainWindows[MAIN_WINDOW::BACK])->addText(gameRenderer, "시작 화면으로 돌아가겠습니까?", 400);
}

void PhaseMain::createManualWindow(SDL_Renderer* gameRenderer)
{
	this->mainWindows[MAIN_WINDOW::MANUAL] = new ManualWindow(gameRenderer);
}

void PhaseMain::createStoryWindow(SDL_Renderer* gameRenderer)
{
	this->mainWindows[MAIN_WINDOW::STORY] = new StoryWindow(gameRenderer);
	this->mainWindows[MAIN_WINDOW::STORY]->setIsViewWindow(true);
	stopAllButtons();
}

void PhaseMain::createGacha1Window(SDL_Renderer* gameRenderer)
{
	this->mainWindows[MAIN_WINDOW::GACHA1] = new Gacha1Window(gameRenderer);
}

void PhaseMain::createGacha2Window(SDL_Renderer* gameRenderer)
{
	this->mainWindows[MAIN_WINDOW::GACHA2] = new Gacha2Window(gameRenderer);
}

void PhaseMain::createMouseCursor()
{
	this->mouseArrowCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
	this->mouseHandCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
}

void PhaseMain::handleEvents(const SDL_Event& gameEvent)
{
	this->presentMousePos.x = gameEvent.button.x;
	this->presentMousePos.y = gameEvent.button.y;

	switch (gameEvent.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		if (gameEvent.button.button == SDL_BUTTON_LEFT)
			clickButtonsInRange();
		break;
	}
}

void PhaseMain::clickButtonsInRange()
{
	for (int i = 0; i < MAIN_WINDOW::COUNT; i++)
	{
		if (this->mainWindows[i]->isViewingWindow())
		{
			selectWindowButtonType(static_cast<MAIN_WINDOW::TYPE>(i));
			return;
		}
	}

	for (int i = 0; i < MAIN_BUTTON::COUNT; i++)
	{
		if (this->mainButtons[i]->isClickingButtonInRange(presentMousePos.x, presentMousePos.y))
			selectButtonType(static_cast<MAIN_BUTTON::TYPE>(i));
	}
}

void PhaseMain::selectWindowButtonType(const MAIN_WINDOW::TYPE& windowType)
{
	switch (windowType)
	{
	case MAIN_WINDOW::BACK:
		selectBackWaringButtonType(windowType);
		break;
	case MAIN_WINDOW::MANUAL:
		selectManualButtonType(windowType);
		break;
	case MAIN_WINDOW::STORY:
		this->mainWindows[MAIN_WINDOW::STORY]->setIsViewWindow(false);
		this->mainWindows[MAIN_WINDOW::MANUAL]->setIsViewWindow(true);
		break;
	case MAIN_WINDOW::GACHA1:
		selectGacha1ButtonType(windowType);
		break;
	case MAIN_WINDOW::GACHA2:
		selectGacha2ButtonType(windowType);
		break;
	}
}

void PhaseMain::selectBackWaringButtonType(const MAIN_WINDOW::TYPE& windowType)
{
	switch (this->mainWindows[windowType]->getSeletedButtonTypeInWindow(presentMousePos.x, presentMousePos.y))
	{
	case WARING_BUTTON::CONSENTING:
		setNextGamePhase(GAME_PHASE::INTRO);
		break;
	case NO_RETURN_TYPE:
		return;
		break;
	}

	startAllButtons();
	this->mainWindows[windowType]->setIsViewWindow(false);
}

void PhaseMain::selectManualButtonType(const MAIN_WINDOW::TYPE& windowType)
{
	switch (this->mainWindows[windowType]->getSeletedButtonTypeInWindow(presentMousePos.x, presentMousePos.y))
	{
	case MANUAL_BUTTON::CONSENTING:
		break;
	case NO_RETURN_TYPE:
		return;
		break;
	}

	startAllButtons();
	this->mainWindows[windowType]->setIsViewWindow(false);
}

void PhaseMain::selectGacha1ButtonType(const MAIN_WINDOW::TYPE& windowType)
{
	switch (this->mainWindows[windowType]->getSeletedButtonTypeInWindow(presentMousePos.x, presentMousePos.y))
	{
	case GACHA1_BUTTON::GACHA:
		setNextGamePhase(GAME_PHASE::GACHA_SCENE);
		return;
		break;
	case NO_RETURN_TYPE:
		return;
		break;
	}

	startAllButtons();
	Mix_HaltMusic();
	Mix_FadeInMusic(this->backgroundMusic, -1, 2000);
	this->mainWindows[windowType]->setIsViewWindow(false);
}

void PhaseMain::selectGacha2ButtonType(const MAIN_WINDOW::TYPE& windowType)
{
	switch (this->mainWindows[windowType]->getSeletedButtonTypeInWindow(presentMousePos.x, presentMousePos.y))
	{
	case GACHA2_BUTTON::GACHA:
		setNextGamePhase(GAME_PHASE::GACHA_SCENE);
		//dynamic_cast<Gacha2Window*>(this->mainWindows[MAIN_WINDOW::GACHA2])->openGacha2Window(getGameRenderer(), gamePlayer);
		return;
		break;
	case NO_RETURN_TYPE:
		return;
		break;
	}

	startAllButtons();
	Mix_HaltMusic();
	Mix_FadeInMusic(this->backgroundMusic, -1, 2000);
	this->mainWindows[windowType]->setIsViewWindow(false);
}

void PhaseMain::startAllButtons()
{
	for (int i = 0; i < MAIN_BUTTON::COUNT; i++)
		this->mainButtons[i]->canSelectButton(true);

	if (!this->gamePlayer->isStage1Cleared())
		this->mainButtons[MAIN_BUTTON::STAGE_2]->canSelectButton(false);

	if (!this->gamePlayer->isStage2Cleared())
		this->mainButtons[MAIN_BUTTON::STAGE_3]->canSelectButton(false);

	if(this->gamePlayer->getObtainedBread() <= 0)
		this->mainButtons[MAIN_BUTTON::GACHA]->canSelectButton(false);
	/*
		이 부분은 나중에 플레이어 정보 받아서 수정해야 할 부분
	*/
}

void PhaseMain::selectButtonType(const MAIN_BUTTON::TYPE& buttonType)
{
	if (buttonType == this->selectedStage)
		return;

	switch (buttonType)
	{
	case MAIN_BUTTON::COLLECTION:
		setNextGamePhase(GAME_PHASE::COLLECTION);
		break;
	case MAIN_BUTTON::BACK:
		this->mainWindows[MAIN_WINDOW::BACK]->setIsViewWindow(true);
		stopAllButtons();
		break;
	case MAIN_BUTTON::MANUAL:
		this->mainWindows[MAIN_WINDOW::MANUAL]->setIsViewWindow(true);
		stopAllButtons();
		break;
	case MAIN_BUTTON::GACHA:
		this->mainWindows[MAIN_WINDOW::GACHA1]->setIsViewWindow(true);
		dynamic_cast<Gacha1Window*>(this->mainWindows[MAIN_WINDOW::GACHA1])->openGacha1Window(getGameRenderer(), gamePlayer);
		stopAllButtons();
		Mix_HaltMusic();
		Mix_FadeInMusic(this->gachaMusic, -1, 2000);
		break;
	case MAIN_BUTTON::GAME_START:
		startGameOnSelectedStage();
		break;
	case MAIN_BUTTON::STAGE_1:
		this->mainTexts[MAIN_TEXT::SELETED_STAGE]->setText("선택된 스테이지 : CU", getGameRenderer());
		this->selectedStage = buttonType;
		break;
	case MAIN_BUTTON::STAGE_2:
		//setNextGamePhase(GAME_PHASE::STAGE2);
		this->mainTexts[MAIN_TEXT::SELETED_STAGE]->setText("선택된 스테이지 : GS25", getGameRenderer());
		this->selectedStage = buttonType;
		break;
	case MAIN_BUTTON::STAGE_3:
		//setNextGamePhase(GAME_PHASE::STAGE3);
		this->mainTexts[MAIN_TEXT::SELETED_STAGE]->setText("선택된 스테이지 : 7ELEVEN", getGameRenderer());
		this->selectedStage = buttonType;
		break;
	}

	Mix_PlayChannel(1, this->buttonEffectSound, 0);
}

void PhaseMain::stopAllButtons()
{
	for (int i = 0; i < MAIN_BUTTON::COUNT; i++)
		this->mainButtons[i]->canSelectButton(false);
}

void PhaseMain::startGameOnSelectedStage()
{
	switch (this->selectedStage)
	{
	case MAIN_BUTTON::STAGE_1:
		setNextGamePhase(GAME_PHASE::STAGE1);
		break;
	case MAIN_BUTTON::STAGE_2:
		setNextGamePhase(GAME_PHASE::STAGE2);
		break;
	case MAIN_BUTTON::STAGE_3:
		setNextGamePhase(GAME_PHASE::STAGE3);
		break;
	}
}

void PhaseMain::updateDatas()
{

}

void PhaseMain::renderFrames()
{
	SDL_RenderCopy(getGameRenderer(), this->backgroundTexture, &(this->backgroundTextureRenderPos), &(this->backgroundTextureRenderPos));
	renderButtons();
	this->mainTexts[MAIN_TEXT::SELETED_STAGE]->renderTextTexture(getGameRenderer());
	this->mainTexts[MAIN_TEXT::BREAD_COUNT]->renderTextTexture(getGameRenderer());

	for (int i = 0; i < MAIN_WINDOW::COUNT; i++)
	{
		if (this->mainWindows[i]->isViewingWindow())
			mainWindows[i]->renderWindow(getGameRenderer(), this->presentMousePos.x, this->presentMousePos.y);
	}
}

void PhaseMain::renderButtons()
{
	bool isMouseInRange = false;
	for (int i = 0; i < MAIN_BUTTON::COUNT; i++)
	{
		if (this->mainButtons[i]->isClickingButtonInRange(this->presentMousePos.x, this->presentMousePos.y))
		{
			if (i == this->selectedStage)
				continue;

			SDL_SetCursor(this->mouseHandCursor);
			this->mainButtons[i]->RenderButtonTextureOnButton(getGameRenderer());
			isMouseInRange = true;
		}
		else
		{
			this->mainButtons[i]->RenderButtonTexture(getGameRenderer());
		}
	}

	this->mainButtons[this->selectedStage]->RenderButtonTextureOnClicking(getGameRenderer());

	if (!isMouseInRange) // 이게 없으면 버튼이 범위안에 있어도 커서가 화살표로 바뀜
		SDL_SetCursor(this->mouseArrowCursor);
}

void PhaseMain::openPhase()
{
	if(!this->mainWindows[MAIN_WINDOW::STORY]->isViewingWindow())
		startAllButtons();

	this->mainTexts[MAIN_TEXT::SELETED_STAGE]->setText("선택된 스테이지 : CU", getGameRenderer());
	this->selectedStage = MAIN_BUTTON::STAGE_1;
	this->mainTexts[MAIN_TEXT::BREAD_COUNT]->setText("소지한 빵 개수 : " + std::to_string(this->gamePlayer->getObtainedBread()) + "개", getGameRenderer());
	setNextGamePhase(GAME_PHASE::TYPE::NONE);

	if(this->mainWindows[MAIN_WINDOW::GACHA2]->isViewingWindow())
		Mix_FadeInMusic(this->gachaMusic, -1, 2000);
	else
		Mix_FadeInMusic(this->backgroundMusic, -1, 2000);
}

void PhaseMain::closePhase()
{
	if (getNextGamePhase() == GAME_PHASE::GACHA_SCENE)
	{
		this->mainWindows[MAIN_WINDOW::GACHA1]->setIsViewWindow(false);
		this->mainWindows[MAIN_WINDOW::GACHA2]->setIsViewWindow(true);
		dynamic_cast<Gacha2Window*>(this->mainWindows[MAIN_WINDOW::GACHA2])->openGacha2Window(getGameRenderer(), gamePlayer);
	}

	this->presentMousePos.x = 0;
	this->presentMousePos.y = 0;
	SDL_SetCursor(this->mouseArrowCursor);
	Mix_HaltMusic();
}

PhaseMain::~PhaseMain()
{
	for (int i = 0; i < MAIN_BUTTON::COUNT; i++)
		delete this->mainButtons[i];

	delete this->mainTexts[MAIN_TEXT::SELETED_STAGE];
	delete this->mainTexts[MAIN_TEXT::BREAD_COUNT];
	delete this->mainWindows[MAIN_WINDOW::BACK];
	delete this->mainWindows[MAIN_WINDOW::MANUAL];
	delete this->mainWindows[MAIN_WINDOW::STORY];
	delete this->mainWindows[MAIN_WINDOW::GACHA1];
	delete this->mainWindows[MAIN_WINDOW::GACHA2];

	Mix_FreeMusic(this->backgroundMusic);
	Mix_FreeMusic(this->gachaMusic);
	Mix_FreeChunk(this->buttonEffectSound);
	SDL_DestroyTexture(this->backgroundTexture);

	SDL_FreeCursor(this->mouseArrowCursor);
	SDL_FreeCursor(this->mouseHandCursor);
}