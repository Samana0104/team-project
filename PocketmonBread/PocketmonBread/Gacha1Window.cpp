#include "Gacha1Window.h"
#include "ConstantDecl.h"

Gacha1Window::Gacha1Window(SDL_Renderer* gameRenderer) : WindowInterface()
{
	this->buttonEffectSound = Mix_LoadWAV("../../resources/sounds/main_button_sound.mp3");
	createWindowTexture(gameRenderer);
	createButton(gameRenderer);
	createText(gameRenderer);
}

void Gacha1Window::createWindowTexture(SDL_Renderer* gameRenderer)
{
	SDL_Surface* tmpSurface = IMG_Load("../../resources/images/gacha_background.png");
	this->windowTexture = SDL_CreateTextureFromSurface(gameRenderer, tmpSurface);
	this->windowTextureRenderingPos = { 0, 0, GAME_WINDOW::WIDTH, GAME_WINDOW::HEIGHT };
	SDL_FreeSurface(tmpSurface);
}

void Gacha1Window::createButton(SDL_Renderer* gameRenderer)
{
	SDL_Rect texturePos = { 0, 0, 90, 90 };
	SDL_Rect renderingPos = { 1400, 45, 90, 90 };

	SDL_Surface* tmpSurface = IMG_Load("../../resources/images/main_back_button.png");
	this->windowButtons[GACHA1_BUTTON::BACK] = new RectangleButton(texturePos, renderingPos, SDL_CreateTextureFromSurface(gameRenderer, tmpSurface));
	SDL_FreeSurface(tmpSurface);

	texturePos = { 0, 0, 437, 118 };
	renderingPos = { 581, 700, 437, 118 };
	tmpSurface = IMG_Load("../../resources/images/gacha_button.png");
	this->windowButtons[GACHA1_BUTTON::GACHA] = new RectangleButton(texturePos, renderingPos, SDL_CreateTextureFromSurface(gameRenderer, tmpSurface));
	SDL_FreeSurface(tmpSurface);
}

void Gacha1Window::createText(SDL_Renderer* gameRenderer)
{
	SDL_Color textColor = { 255, 255, 255, 255 };
	SDL_Rect renderingPos = { 550, 90, 0, 0 };

	this->windowTexts = new TTFTextManger(gameRenderer, "현재 보유 중인 포켓몬 빵 : 0개",
		TTF_OpenFont("../../resources/fonts/BMJUA_ttf.ttf", 40), renderingPos, textColor);
}

void Gacha1Window::renderWindow(SDL_Renderer* gameRenderer, const int& xPos, const int& yPos)
{
	SDL_RenderCopy(gameRenderer, this->windowTexture, &(this->windowTextureRenderingPos), &(this->windowTextureRenderingPos));
	renderButtons(gameRenderer, xPos, yPos);
	renderText(gameRenderer);
}

void Gacha1Window::renderText(SDL_Renderer* gameRenderer)
{
	this->windowTexts->renderTextTexture(gameRenderer);
}

void Gacha1Window::renderButtons(SDL_Renderer* gameRenderer, const int& xPos, const int& yPos)
{
	bool isMouseInRange = false;
	for (int i = 0; i < GACHA1_BUTTON::COUNT; i++)
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

ButtonType Gacha1Window::getSeletedButtonTypeInWindow(const int& xPos, const int& yPos)
{
	for (int i = 0; i < GACHA1_BUTTON::COUNT; i++)
	{
		if (this->windowButtons[i]->isClickingButtonInRange(xPos, yPos))
		{
			Mix_PlayChannel(1, this->buttonEffectSound, 0);
			return i;
		}
	}

	return NO_RETURN_TYPE;
}

void Gacha1Window::openGacha1Window(SDL_Renderer* gameRenderer, Player* gamePlayer)
{
	this->windowTexts->setText("현재 보유 중인 포켓몬 빵 : " + std::to_string(gamePlayer->getObtainedBread()) + "개", gameRenderer);
}

Gacha1Window::~Gacha1Window()
{
	delete this->windowTexts;
	delete this->windowButtons[GACHA1_BUTTON::BACK];
	delete this->windowButtons[GACHA1_BUTTON::GACHA];

	SDL_DestroyTexture(this->windowTexture);
	Mix_FreeChunk(this->buttonEffectSound);
}
