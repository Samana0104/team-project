#include "ManualWindow.h"
#include "ConstantDecl.h"

ManualWindow::ManualWindow(SDL_Renderer* gameRenderer) : WindowInterface()
{
	this->buttonEffectSound = Mix_LoadWAV("../../resources/sounds/window_button_sound.mp3");
	createWindowTexture(gameRenderer);
	createButton(gameRenderer);
}

void ManualWindow::createWindowTexture(SDL_Renderer* gameRenderer)
{
	SDL_Surface* tmpSurface = IMG_Load("../../resources/images/manual_window.png");
	this->windowTexture = SDL_CreateTextureFromSurface(gameRenderer, tmpSurface);
	this->windowTextureRenderingPos = { 0, 0, GAME_WINDOW::WIDTH, GAME_WINDOW::HEIGHT };
	SDL_FreeSurface(tmpSurface);
}

void ManualWindow::createButton(SDL_Renderer* gameRenderer)
{
	SDL_Rect texturePos = { 0, 0, 658, 77 };
	SDL_Rect renderingPos = { 471, 670, 658, 77 };

	SDL_Surface* tmpSurface = IMG_Load("../../resources/images/manual_ok_button.png");
	this->windowButtons = new RectangleButton(texturePos, renderingPos, SDL_CreateTextureFromSurface(gameRenderer, tmpSurface));
	SDL_FreeSurface(tmpSurface);
}

void ManualWindow::renderWindow(SDL_Renderer* gameRenderer, const int& xPos, const int& yPos)
{
	SDL_RenderCopy(gameRenderer, this->windowTexture, &(this->windowTextureRenderingPos), &(this->windowTextureRenderingPos));
	renderButtons(gameRenderer, xPos, yPos);
}

void ManualWindow::renderButtons(SDL_Renderer* gameRenderer, const int& xPos, const int& yPos)
{
	if (this->windowButtons->isClickingButtonInRange(xPos, yPos))
	{
		SDL_SetCursor(getMouseHandCursor());
		this->windowButtons->RenderButtonTextureOnButton(gameRenderer);
	}
	else
	{
		this->windowButtons->RenderButtonTexture(gameRenderer);
	}
}


ButtonType ManualWindow::getSeletedButtonTypeInWindow(const int& xPos, const int& yPos)
{
	if (this->windowButtons->isClickingButtonInRange(xPos, yPos))
	{
		Mix_PlayChannel(1, this->buttonEffectSound, 0);
		return MANUAL_BUTTON::CONSENTING;
	}

	return NO_RETURN_TYPE;
}

ManualWindow::~ManualWindow()
{
	delete this->windowButtons;

	SDL_DestroyTexture(this->windowTexture);
	Mix_FreeChunk(this->buttonEffectSound);
}
