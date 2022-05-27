#include "WaringWindow.h"
#include "ConstantDecl.h"

WaringWindow::WaringWindow(SDL_Renderer* gameRenderer) : WindowInterface()
{
	this->buttonEffectSound = Mix_LoadWAV("../../resources/sounds/window_button_sound.mp3");
	createWindowTexture(gameRenderer);
	createButton(gameRenderer);
}

void WaringWindow::createWindowTexture(SDL_Renderer* gameRenderer)
{
	SDL_Surface* tmpSurface = IMG_Load("../../resources/images/warning_window.png");
	this->windowTexture = SDL_CreateTextureFromSurface(gameRenderer, tmpSurface);
	this->windowTextureRenderingPos = { 0, 0, GAME_WINDOW::WIDTH, GAME_WINDOW::HEIGHT };
	SDL_FreeSurface(tmpSurface);
}

void WaringWindow::createButton(SDL_Renderer* gameRenderer)
{
	SDL_Rect texturePos = { 0, 0, 658, 77 };
	SDL_Rect renderingPos = { 471, 600, 658, 77 };

	SDL_Surface* tmpSurface = IMG_Load("../../resources/images/warning_ok_button.png");
	this->windowButtons[WARING_BUTTON::CONSENTING] = new RectangleButton(texturePos, renderingPos, SDL_CreateTextureFromSurface(gameRenderer, tmpSurface));
	SDL_FreeSurface(tmpSurface);

	texturePos = { 0, 0, 658, 77 };
	renderingPos = { 471, 700, 658, 77 };
	tmpSurface = IMG_Load("../../resources/images/warning_cancel_button.png");
	this->windowButtons[WARING_BUTTON::REFUSING] = new RectangleButton(texturePos, renderingPos, SDL_CreateTextureFromSurface(gameRenderer, tmpSurface));
	SDL_FreeSurface(tmpSurface);
}

void WaringWindow::renderWindow(SDL_Renderer* gameRenderer, const int& xPos, const int& yPos)
{
	SDL_RenderCopy(gameRenderer, this->windowTexture, &(this->windowTextureRenderingPos), &(this->windowTextureRenderingPos));
	renderButtons(gameRenderer, xPos, yPos);
	renderText(gameRenderer);
}

void WaringWindow::renderText(SDL_Renderer* gameRenderer)
{
	for (int i=0; i<this->windowTexts.size(); i++)
	{
		this->windowTexts[i]->renderTextTexture(gameRenderer);
	}
}

void WaringWindow::renderButtons(SDL_Renderer* gameRenderer, const int& xPos, const int& yPos)
{
	bool isMouseInRange = false;
	for (int i = 0; i < WARING_BUTTON::COUNT; i++)
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

ButtonType WaringWindow::getSeletedButtonTypeInWindow(const int& xPos, const int& yPos)
{
	for (int i = 0; i < WARING_BUTTON::COUNT; i++)
	{
		if (this->windowButtons[i]->isClickingButtonInRange(xPos, yPos))
		{
			Mix_PlayChannel(1, this->buttonEffectSound, 0);
			return i;
		}
	}

	return NO_RETURN_TYPE;
}

void WaringWindow::addText(SDL_Renderer* gameRenderer, const std::string& text, int textXPos, int textYPos)
{
	SDL_Color textColor = { 0, 0, 0, 255 };
	SDL_Rect renderingPos = { textXPos, textYPos, 0, 0 };

	this->windowTexts.push_back(new TTFTextManger(gameRenderer, text, TTF_OpenFont("../../resources/fonts/NEXON Lv2 Gothic Bold.ttf", 45), renderingPos, textColor));
}

WaringWindow::~WaringWindow()
{
	delete this->windowButtons[WARING_BUTTON::CONSENTING];
	delete this->windowButtons[WARING_BUTTON::REFUSING];

	SDL_DestroyTexture(this->windowTexture);
	Mix_FreeChunk(this->buttonEffectSound);
}
