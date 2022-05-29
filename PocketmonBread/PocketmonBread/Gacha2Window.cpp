#include "Gacha2Window.h"
#include "ConstantDecl.h"

Gacha2Window::Gacha2Window(SDL_Renderer* gameRenderer) : pocketmonSeal(gameRenderer), WindowInterface()
{
	this->buttonEffectSound = Mix_LoadWAV("../../resources/sounds/main_button_sound.mp3");
	createWindowTexture(gameRenderer);
	createButton(gameRenderer);
	createText(gameRenderer);
	srand(static_cast<unsigned int>(time(NULL)));

	this->pocketmonSealTexturePos = { 0, 0, 270, 300 };
	this->pocketmonSealTextureRenderingPos = { 665, 230, 270, 300 };
}

void Gacha2Window::createWindowTexture(SDL_Renderer* gameRenderer)
{
	SDL_Surface* tmpSurface = IMG_Load("../../resources/images/gacha_background_result.png");
	this->windowTexture = SDL_CreateTextureFromSurface(gameRenderer, tmpSurface);
	this->windowTextureRenderingPos = { 0, 0, GAME_WINDOW::WIDTH, GAME_WINDOW::HEIGHT };
	SDL_FreeSurface(tmpSurface);
}

void Gacha2Window::createButton(SDL_Renderer* gameRenderer)
{
	SDL_Rect texturePos = { 0, 0, 90, 90 };
	SDL_Rect renderingPos = { 1400, 45, 90, 90 };

	SDL_Surface* tmpSurface = IMG_Load("../../resources/images/main_back_button.png");
	this->windowButtons[GACHA2_BUTTON::BACK] = new RectangleButton(texturePos, renderingPos, SDL_CreateTextureFromSurface(gameRenderer, tmpSurface));
	SDL_FreeSurface(tmpSurface);

	texturePos = { 0, 0, 437, 118 };
	renderingPos = { 581, 700, 437, 118 };
	tmpSurface = IMG_Load("../../resources/images/gacha_again_button.png");
	this->windowButtons[GACHA2_BUTTON::GACHA] = new RectangleButton(texturePos, renderingPos, SDL_CreateTextureFromSurface(gameRenderer, tmpSurface));
	SDL_FreeSurface(tmpSurface);
}

void Gacha2Window::createText(SDL_Renderer* gameRenderer)
{
	SDL_Color textColor = { 255, 255, 255, 255 };
	SDL_Rect renderingPos = { 560, 90, 0, 0 };

	this->windowTexts = new TTFTextManger(gameRenderer, "현재 보유 중인 포켓몬 빵 : 0개",
		TTF_OpenFont("../../resources/fonts/BMJUA_ttf.ttf", 40), renderingPos, textColor);
}

void Gacha2Window::renderWindow(SDL_Renderer* gameRenderer, const int& xPos, const int& yPos)
{
	SDL_RenderCopy(gameRenderer, this->windowTexture, &(this->windowTextureRenderingPos), &(this->windowTextureRenderingPos));
	renderButtons(gameRenderer, xPos, yPos);
	renderText(gameRenderer);
	SDL_RenderCopy(gameRenderer, this->pocketmonSeal.getPocketmonSealTextures(gachaResult), &(this->pocketmonSealTexturePos), &(this->pocketmonSealTextureRenderingPos));
}

void Gacha2Window::renderText(SDL_Renderer* gameRenderer)
{
	this->windowTexts->renderTextTexture(gameRenderer);
}

void Gacha2Window::renderButtons(SDL_Renderer* gameRenderer, const int& xPos, const int& yPos)
{
	bool isMouseInRange = false;
	for (int i = 0; i < GACHA2_BUTTON::COUNT; i++)
	{
		if (this->windowButtons[i]->isClickingButtonInRange(xPos, yPos))
		{
			SDL_SetCursor(getMouseHandCursor());
			this->windowButtons[i]->RenderButtonTextureOnButton(gameRenderer);
			isMouseInRange = true;
		}
		else
		{
			this->windowButtons[i]->RenderButtonTexture(gameRenderer);
		}
	}

	if (!isMouseInRange) // 이게 없으면 버튼이 범위안에 있어도 커서가 화살표로 바뀜
		SDL_SetCursor(getMouseArrowCursor());
}

ButtonType Gacha2Window::getSeletedButtonTypeInWindow(const int& xPos, const int& yPos)
{
	for (int i = 0; i < GACHA2_BUTTON::COUNT; i++)
	{
		if (this->windowButtons[i]->isClickingButtonInRange(xPos, yPos))
		{
			Mix_PlayChannel(1, this->buttonEffectSound, 0);
			return i;
		}
	}

	return NO_RETURN_TYPE;
}

void Gacha2Window::openGacha2Window(SDL_Renderer* gameRenderer, Player* gamePlayer)
{
	gamePlayer->usePocketmonBread();
	this->windowTexts->setText("현재 보유 중인 포켓몬 빵 : " + std::to_string(gamePlayer->getObtainedBread()) + "개", gameRenderer);
	gachaResult = pocketmonBreadGacha();
	gamePlayer->obtainPocketmonSeal(gachaResult);

	if (gamePlayer->getObtainedBread() <= 0)
		this->windowButtons[GACHA2_BUTTON::GACHA]->canSelectButton(false);
	else
		this->windowButtons[GACHA2_BUTTON::GACHA]->canSelectButton(true);
}

POCKETMON::SEAL Gacha2Window::pocketmonBreadGacha()
{
	int random = static_cast<unsigned int>((rand() % 10)) + 1;

	if (random <= 1)
		return UniquePocketmon();
	else if (random >= 2 && random <= 4)
		return rarePocketmon();
	else
		return normalPocketmon();
}

POCKETMON::SEAL Gacha2Window::normalPocketmon()
{
	int random = static_cast<unsigned int>((rand() % 6));

	switch(random)
	{
	case 0:
		return static_cast<POCKETMON::SEAL>(POCKETMON::TYPE_2);
	case 1:
		return static_cast<POCKETMON::SEAL>(POCKETMON::TYPE_3);
	case 2:
		return static_cast<POCKETMON::SEAL>(POCKETMON::TYPE_5);
	case 3:
		return static_cast<POCKETMON::SEAL>(POCKETMON::TYPE_6);
	case 4:
		return static_cast<POCKETMON::SEAL>(POCKETMON::TYPE_8);
	case 5:
		return static_cast<POCKETMON::SEAL>(POCKETMON::TYPE_9);
	}

	return static_cast<POCKETMON::SEAL>(random); // 버그 방지용
}

POCKETMON::SEAL Gacha2Window::rarePocketmon()
{
	int random = static_cast<unsigned int>((rand() % 4));

	switch (random)
	{
	case 0:
		return static_cast<POCKETMON::SEAL>(POCKETMON::TYPE_1);
	case 1:
		return static_cast<POCKETMON::SEAL>(POCKETMON::TYPE_4);
	case 2:
		return static_cast<POCKETMON::SEAL>(POCKETMON::TYPE_7);
	case 3:
		return static_cast<POCKETMON::SEAL>(POCKETMON::TYPE_10);
	}

	return static_cast<POCKETMON::SEAL>(random);  // 버그 방지용
}

POCKETMON::SEAL Gacha2Window::UniquePocketmon()
{
	int random = static_cast<int>((rand() % 2));

	switch (random)
	{
	case 0:
		return static_cast<POCKETMON::SEAL>(POCKETMON::TYPE_11);
	case 1:
		return static_cast<POCKETMON::SEAL>(POCKETMON::TYPE_12);
	}

	return static_cast<POCKETMON::SEAL>(random);
}

Gacha2Window::~Gacha2Window()
{
	delete this->windowTexts;
	delete this->windowButtons[GACHA2_BUTTON::BACK];
	delete this->windowButtons[GACHA2_BUTTON::GACHA];

	SDL_DestroyTexture(this->windowTexture);
	Mix_FreeChunk(this->buttonEffectSound);
}
